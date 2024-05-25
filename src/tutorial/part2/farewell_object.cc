#include "tutorial/part2/farewell_object.hh"

#include "base/trace.hh"
#include "debug/Demo.hh"
#include "sim/sim_exit.hh"

namespace gem5
{

FarewellObject::FarewellObject(const FarewellObjectParams &params) :
    SimObject(params),
    event([this]{ processEvent(); }, name() + ".event"),
    bandwidth(params.write_bandwidth),
    bufferSize(params.buffer_size),
    buffer(nullptr),
    bufferUsed(0)
{
    buffer = new char[bufferSize];
    DPRINTF(Demo, "Created the farewell object\n");
}

FarewellObject::~FarewellObject()
{
    delete[] buffer;
}

void
FarewellObject::processEvent()
{
    DPRINTF(Demo, "Processing the event!\n");
    fillBuffer();
}

void
FarewellObject::sayGoodbye(std::string other_name)
{
    DPRINTF(Demo, "Saying goodbye to %s\n", other_name);

    message = "Farewell " + other_name + "!! ";

    fillBuffer();
}

void
FarewellObject::fillBuffer()
{
    // There better be a message
    assert(message.length() > 0);

    // Copy from the message to the buffer per byte.
    int bytes_copied = 0;
    for (auto it = message.begin();
         it < message.end() && bufferUsed < bufferSize - 1;
         it++, bufferUsed++, bytes_copied++) {
        // Copy the character into the buffer
        buffer[bufferUsed] = *it;
    }

    if (bufferUsed < bufferSize - 1) {
        // Wait for the next copy for as long as it would have taken
        DPRINTF(Demo, "Scheduling another fillBuffer in %d ticks\n",
                bandwidth * bytes_copied);
        schedule(event, curTick() + bandwidth * bytes_copied);
    } else {
        DPRINTF(Demo, "Farewell done copying!\n");
        // Be sure to take into account the time for the last bytes
        exitSimLoop(buffer, 0, curTick() + bandwidth * bytes_copied);
    }
}

} // namespace gem5
