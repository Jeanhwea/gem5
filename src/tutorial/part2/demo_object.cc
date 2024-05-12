#include "tutorial/part2/demo_object.hh"

#include <iostream>

#include "base/trace.hh"
#include "debug/Demo.hh"

namespace gem5
{

DemoObject::DemoObject(const DemoObjectParams &params) :
    SimObject(params),
    event([this]{processEvent();}, name()),
    latency(100),
    timesLeft(10)
{
    DPRINTF(Demo, "DemoObject Created\n");
}

void
DemoObject::processEvent()
{
    timesLeft--;
    DPRINTF(Demo, "Hello world! Processing the event! %d left\n", timesLeft);

    if (timesLeft <= 0) {
        DPRINTF(Demo, "Done firing!\n");
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
