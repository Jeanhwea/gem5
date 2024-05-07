#include "tutorial/part2/demo_object.hh"

#include <iostream>

namespace gem5
{

    DemoObject::DemoObject(const DemoObjectParams &params) :
        SimObject(params)
    {
        std::cout << "Demo World! From a SimObject!" << std::endl;
    }

} // namespace gem5
