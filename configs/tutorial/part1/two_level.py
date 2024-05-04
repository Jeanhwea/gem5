import m5
from m5.objects import *

m5.util.addToPath("../../")

from caches import *
from common import SimpleOpts

default_binary = "/opt/src/gem5/tests/test-progs/hello/bin/x86/linux/hello"
SimpleOpts.add_option("binary", nargs="?", default=default_binary)

args = SimpleOpts.parse_args()

# 创建系统
system = System()

# 设置 时钟 电压域
system.clk_domain = SrcClockDomain()
system.clk_domain.clock = "1GHz"
system.clk_domain.voltage_domain = VoltageDomain()

system.mem_mode = "timing"  # Use timing accesses
system.mem_ranges = [AddrRange("512MB")]  # Create an address range

# x86
system.cpu = X86TimingSimpleCPU()

# system.cpu.icache_port = system.membus.cpu_side_ports
# system.cpu.dcache_port = system.membus.cpu_side_ports
system.cpu.icache = L1ICache(args)
system.cpu.dcache = L1DCache(args)
system.cpu.icache.connectCPU(system.cpu)
system.cpu.dcache.connectCPU(system.cpu)

# L2 Bus
system.l2bus = L2XBar()
system.cpu.icache.connectBus(system.l2bus)
system.cpu.dcache.connectBus(system.l2bus)

# L2 cache
system.l2cache = L2Cache(args)
system.l2cache.connectCPUSideBus(system.l2bus)

# membus
system.membus = SystemXBar()
# Connect the L2 cache to the membus
system.l2cache.connectMemSideBus(system.membus)


# 中断控制器
system.cpu.createInterruptController()

system.cpu.interrupts[0].pio = system.membus.mem_side_ports
system.cpu.interrupts[0].int_requestor = system.membus.cpu_side_ports
system.cpu.interrupts[0].int_responder = system.membus.mem_side_ports

# DDR3 内存控制器
system.mem_ctrl = MemCtrl()
system.mem_ctrl.dram = DDR3_1600_8x8()
system.mem_ctrl.dram.range = system.mem_ranges[0]
system.mem_ctrl.port = system.membus.mem_side_ports

system.system_port = system.membus.cpu_side_ports

# SE
# 二进制可执行文件
system.workload = SEWorkload.init_compatible(args.binary)

# 创建进程
process = Process()
process.cmd = [args.binary]
system.cpu.workload = process
system.cpu.createThreads()

# 模拟对象
root = Root(full_system=False, system=system)  # SE 模式
m5.instantiate()

# 启动模拟
print(f"Beginning simulation!")
exit_event = m5.simulate()
print(f"Exiting @ tick {m5.curTick()} because {exit_event.getCause()}")
