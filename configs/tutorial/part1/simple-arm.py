import m5
from m5.objects import *

# 创建系统
system = System()

# 设置 时钟 电压域
system.clk_domain = SrcClockDomain()
system.clk_domain.clock = "1GHz"
system.clk_domain.voltage_domain = VoltageDomain()

system.mem_mode = "timing"  # Use timing accesses
system.mem_ranges = [AddrRange("512MB")]  # Create an address range

# arm
system.cpu = ArmTimingSimpleCPU()

# membus
system.membus = SystemXBar()

system.cpu.icache_port = system.membus.cpu_side_ports
system.cpu.dcache_port = system.membus.cpu_side_ports

# 中断控制器
system.cpu.createInterruptController()

# system.cpu.interrupts[0].pio = system.membus.mem_side_ports
# system.cpu.interrupts[0].int_requestor = system.membus.cpu_side_ports
# system.cpu.interrupts[0].int_responder = system.membus.mem_side_ports

# DDR3 内存控制器
system.mem_ctrl = MemCtrl()
system.mem_ctrl.dram = DDR3_1600_8x8()
system.mem_ctrl.dram.range = system.mem_ranges[0]
system.mem_ctrl.port = system.membus.mem_side_ports

system.system_port = system.membus.cpu_side_ports

# SE
# 二进制可执行文件
binary = "/opt/src/gem5/cpu_tests/benchmarks/bin/arm/Bubblesort"
system.workload = SEWorkload.init_compatible(binary)

# 创建进程
process = Process()
process.cmd = [binary]
system.cpu.workload = process
system.cpu.createThreads()

# 模拟对象
root = Root(full_system=False, system=system)  # SE 模式
m5.instantiate()

# 启动模拟
print(f"Beginning simulation!")
exit_event = m5.simulate()
print(f"Exiting @ tick {m5.curTick()} because {exit_event.getCause()}")
