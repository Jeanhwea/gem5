from m5.params import *
from m5.SimObject import SimObject


class DemoObject(SimObject):
    type = "DemoObject"
    cxx_header = "tutorial/part2/demo_object.hh"
    cxx_class = "gem5::DemoObject"

    time_to_wait = Param.Latency("Time before firing the event")
    number_of_fires = Param.Int(
        1, "Number of times to fire the event before goodbye"
    )
    farewell_object = Param.FarewellObject("A farewell object")


class FarewellObject(SimObject):
    type = "FarewellObject"
    cxx_header = "tutorial/part2/farewell_object.hh"
    cxx_class = "gem5::FarewellObject"

    buffer_size = Param.MemorySize(
        "1kB", "Size of buffer to fill with goodbye"
    )
    write_bandwidth = Param.MemoryBandwidth(
        "100MB/s", "Bandwidth to fill the buffer"
    )
