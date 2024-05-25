#ifndef __LEARNING_GEM5_FAREWELL_OBJECT_HH__
#define __LEARNING_GEM5_FAREWELL_OBJECT_HH__

#include <string>

#include "params/FarewellObject.hh"
#include "sim/sim_object.hh"

namespace gem5
{

class FarewellObject : public SimObject
{
  private:
    void processEvent();

    EventFunctionWrapper event;

    void fillBuffer();

    float bandwidth;

    int bufferSize;

    char *buffer;

    std::string message;

    int bufferUsed;

  public:
    FarewellObject(const FarewellObjectParams &p);
    ~FarewellObject();

    void sayGoodbye(std::string name);
};

} // namespace gem5

#endif // __LEARNING_GEM5_FAREWELL_OBJECT_HH__
