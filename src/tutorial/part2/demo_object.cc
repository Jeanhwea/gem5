#include "tutorial/part2/demo_object.hh"

#include <iostream>

#include "base/trace.hh"
#include "debug/Demo.hh"

namespace gem5
{

DemoObject::DemoObject(const DemoObjectParams &params) :
    SimObject(params),
    event([this]{processEvent();}, name()),
    farewell(params.farewell_object),
    myName(params.name),
    latency(params.time_to_wait),
    timesLeft(params.number_of_fires)
{
    DPRINTF(Demo, "DemoObject Created, with name %s\n", myName);
    panic_if(!farewell, "DemoObject must have a non-null FarewellObject");
}

void
DemoObject::processEvent()
{
    timesLeft--;
    DPRINTF(Demo, "Hello world! Processing the event! %d left\n", timesLeft);

    if (timesLeft <= 0) {
        DPRINTF(Demo, "Done firing!\n");
        farewell->sayGoodbye(myName);
    } else {
        schedule(event, curTick() + latency);
    }
}

void
DemoObject::startup()
{
    schedule(event, latency);
}

} // namespace gem5
