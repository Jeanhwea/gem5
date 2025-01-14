#ifndef __LEARNING_GEM5_DEMO_OBJECT_HH__
#define __LEARNING_GEM5_DEMO_OBJECT_HH__

#include "params/DemoObject.hh"
#include "sim/sim_object.hh"
#include "tutorial/part2/farewell_object.hh"

namespace gem5
{

class DemoObject : public SimObject
{
private:
    void processEvent();
    EventFunctionWrapper event;
    FarewellObject* farewell;

    const std::string myName;
    const Tick latency;
    int timesLeft;

public:
    DemoObject(const DemoObjectParams &p);

    void startup() override;
};

} // namespace gem5

#endif // __LEARNING_GEM5_DEMO_OBJECT_HH__
