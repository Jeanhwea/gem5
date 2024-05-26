from m5.params import *
from m5.SimObject import SimObject


class DemoMemory(SimObject):
    type = "DemoMemory"
    cxx_header = "tutorial/part2/demo_memory.hh"
    cxx_class = "gem5::DemoMemory"

    inst_port = ResponsePort("CPU side port, receives requests")
    data_port = ResponsePort("CPU side port, receives requests")
    mem_side = RequestPort("Memory side port, sends requests")
