#ifndef __LEARNING_GEM5_DEMO_MEMORY_HH__
#define __LEARNING_GEM5_DEMO_MEMORY_HH__

#include "mem/port.hh"
#include "params/DemoMemory.hh"
#include "sim/sim_object.hh"

namespace gem5
{

class DemoMemory : public SimObject
{
  private:

    class CPUSidePort : public ResponsePort
    {
      private:
        DemoMemory *owner;
        bool needRetry;
        PacketPtr blockedPacket;

      public:
        CPUSidePort(const std::string& name, DemoMemory *owner) :
            ResponsePort(name), owner(owner), needRetry(false),
            blockedPacket(nullptr)
        { }

        void sendPacket(PacketPtr pkt);
        AddrRangeList getAddrRanges() const override;
        void trySendRetry();

      protected:
        Tick recvAtomic(PacketPtr pkt) override
        { panic("recvAtomic unimpl."); }

        void recvFunctional(PacketPtr pkt) override;
        bool recvTimingReq(PacketPtr pkt) override;
        void recvRespRetry() override;
    };

    class MemSidePort : public RequestPort
    {
      private:
        DemoMemory *owner;
        PacketPtr blockedPacket;

      public:
        MemSidePort(const std::string& name, DemoMemory *owner) :
            RequestPort(name), owner(owner), blockedPacket(nullptr)
        { }

        void sendPacket(PacketPtr pkt);

      protected:
        bool recvTimingResp(PacketPtr pkt) override;
        void recvReqRetry() override;
        void recvRangeChange() override;
    };

    bool handleRequest(PacketPtr pkt);
    bool handleResponse(PacketPtr pkt);
    void handleFunctional(PacketPtr pkt);
    AddrRangeList getAddrRanges() const;
    void sendRangeChange();

    CPUSidePort instPort;
    CPUSidePort dataPort;
    MemSidePort memPort;
    bool blocked;

  public:
    DemoMemory(const DemoMemoryParams &params);

    Port &getPort(const std::string &if_name,
                  PortID idx=InvalidPortID) override;
};

} // namespace gem5

#endif // __LEARNING_GEM5_DEMO_MEMORY_HH__
