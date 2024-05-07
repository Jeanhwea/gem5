from m5.params import *
from m5.SimObject import SimObject


class DemoObject(SimObject):
    type = "DemoObject"
    cxx_header = "tutorial/part2/demo_object.hh"
    cxx_class = "gem5::DemoObject"
