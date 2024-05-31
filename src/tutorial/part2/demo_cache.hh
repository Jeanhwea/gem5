#ifndef __LEARNING_GEM5_DEMO_CACHE_DEMO_CACHE_HH__
#define __LEARNING_GEM5_DEMO_CACHE_DEMO_CACHE_HH__

#include <unordered_map>

#include "base/statistics.hh"
#include "mem/port.hh"
#include "params/DemoCache.hh"
#include "sim/clocked_object.hh"

namespace gem5
{

/**
 * A very demo cache object. Has a fully-associative data store with random
 * replacement.
 * This cache is fully blocking (not non-blocking). Only a single request can
 * be outstanding at a time.
 * This cache is a writeback cache.
 */
class DemoCache : public ClockedObject
{
  private:

    class CPUSidePort : public ResponsePort
    {
      private:
        /// Since this is a vector port, need to know what number this one is
        int id;

        /// The object that owns this object (DemoCache)
        DemoCache *owner;

        /// True if the port needs to send a retry req.
        bool needRetry;

        /// If we tried to send a packet and it was blocked, store it here
        PacketPtr blockedPacket;

      public:
        CPUSidePort(const std::string& name, int id, DemoCache *owner) :
            ResponsePort(name), id(id), owner(owner), needRetry(false),
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
        /// The object that owns this object (DemoCache)
        DemoCache *owner;

        /// If we tried to send a packet and it was blocked, store it here
        PacketPtr blockedPacket;

      public:
        MemSidePort(const std::string& name, DemoCache *owner) :
            RequestPort(name), owner(owner), blockedPacket(nullptr)
        { }

        void sendPacket(PacketPtr pkt);

      protected:
        bool recvTimingResp(PacketPtr pkt) override;
        void recvReqRetry() override;
        void recvRangeChange() override;
    };

    bool handleRequest(PacketPtr pkt, int port_id);
    bool handleResponse(PacketPtr pkt);
    void sendResponse(PacketPtr pkt);
    void handleFunctional(PacketPtr pkt);
    void accessTiming(PacketPtr pkt);
    bool accessFunctional(PacketPtr pkt);
    void insert(PacketPtr pkt);
    AddrRangeList getAddrRanges() const;
    void sendRangeChange() const;

    /// Latency to check the cache. Number of cycles for both hit and miss
    const Cycles latency;

    /// The block size for the cache
    const Addr blockSize;

    /// Number of blocks in the cache (size of cache / block size)
    const unsigned capacity;

    /// Instantiation of the CPU-side port
    std::vector<CPUSidePort> cpuPorts;

    /// Instantiation of the memory-side port
    MemSidePort memPort;

    /// True if this cache is currently blocked waiting for a response.
    bool blocked;

    /// Packet that we are currently handling. Used for upgrading to larger
    /// cache line sizes
    PacketPtr originalPacket;

    /// The port to send the response when we recieve it back
    int waitingPortId;

    /// For tracking the miss latency
    Tick missTime;

    /// An incredibly demo cache storage. Maps block addresses to data
    std::unordered_map<Addr, uint8_t*> cacheStore;

    /// Cache statistics
  protected:
    struct DemoCacheStats : public statistics::Group
    {
        DemoCacheStats(statistics::Group *parent);
        statistics::Scalar hits;
        statistics::Scalar misses;
        statistics::Histogram missLatency;
        statistics::Formula hitRatio;
    } stats;

  public:

    DemoCache(const DemoCacheParams &params);

    Port &getPort(const std::string &if_name,
                  PortID idx=InvalidPortID) override;

};

} // namespace gem5

#endif // __LEARNING_GEM5_DEMO_CACHE_DEMO_CACHE_HH__
