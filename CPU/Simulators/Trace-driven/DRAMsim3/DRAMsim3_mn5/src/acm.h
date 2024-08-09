#ifndef ACM_H_
#define ACM_H_

// information for initializing ACM@rowBuffer
struct ACMInfo {
    uint32_t sortedReadLatency;
    uint32_t sortedWriteLatency;
    uint32_t numberOfACMs;
    uint32_t recordSize;
    uint64_t ACMAllocatedSpace;

};


#endif  // ACM_H_
