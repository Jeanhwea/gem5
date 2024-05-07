#ifndef __LEARNING_GEM5_DEMO_OBJECT_HH__
#define __LEARNING_GEM5_DEMO_OBJECT_HH__

#include "params/DemoObject.hh"
#include "sim/sim_object.hh"

namespace gem5
{

    class DemoObject : public SimObject
    {
    public:
        DemoObject(const DemoObjectParams &p);
    };

} // namespace gem5

#endif // __LEARNING_GEM5_DEMO_OBJECT_HH__
