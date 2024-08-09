#ifndef __MEMORY_SYSTEM__H
#define __MEMORY_SYSTEM__H

#include <functional>
#include <string>

#include "configuration.h"
#include "dram_system.h"
#include "hmc.h"
#include "acm.h"

// for delay queue
#include <vector>
#include <iostream> 
using namespace std; // for debugging purposes

namespace dramsim3 {

// delay queue structure of missing link by Rommel Sanchez -- 
// 7 cycle for open page policy (13 for close page)
struct delayedInfo{
    uint64_t        addr;
    bool            isWrite;
    uint64_t    delayedTicks;
};

// This should be the interface class that deals with CPU
class MemorySystem {
   public:
		MemorySystem(const std::string &config_file, const std::string &output_dir,
		           std::function<void(uint64_t)> read_callback,
		           std::function<void(uint64_t)> write_callback);
		~MemorySystem();
		void ClockTick();
		void RegisterCallbacks(std::function<void(uint64_t)> read_callback,
		                     std::function<void(uint64_t)> write_callback);
		double GetTCK() const;
		int GetBusBits() const;
		int GetBurstLength() const;
		int GetQueueSize() const;
		void PrintStats() const;
		void ResetStats();

		uint64_t wait_for_PIM_cycles();
		void setDelayQueue(uint32_t delayQueue);
		void EnableACMatRowBuffer(void* acmInfo); // Enable ACM@RowBuffer
		void setWriteAddressACM(uint64_t startAddress);
		void setSortedReadAddressACM(uint64_t startAddress);
		void setSizeOfACM(uint64_t numnerOfElement, uint64_t elementSize);

		uint64_t GetACMDelayforZSimBoundPhase();

		uint64_t GetChannelMask();
		uint64_t GetRankMask();
		uint64_t GetBankMask();
		uint64_t GetRowMask();

		bool WillAcceptTransaction(uint64_t hex_addr, bool is_write) const;
		bool AddTransaction(uint64_t hex_addr, bool is_write);

	private:
		// delay queue object from Rommel Sanchez in No Man's Land paper.
		vector<delayedInfo> queuedTransactions; 
		// These have to be pointers because Gem5 will try to push this object
		// into container which will invoke a copy constructor, using pointers
		// here is safe
		Config *config_;
		BaseDRAMSystem *dram_system_;

		// added for acm@RowBuffer
		bool ACMEnable; // ACM@rowBuffer Enable bit
		uint64_t* ACMNextFreeSlot; 
		uint64_t CurrentCycle; // not directly related to ACM needed here for timing management
		uint32_t DelayQueueWaitCycle;
		uint64_t ConventionalPerspectiveStartAddress;
		uint64_t SortedPerspectiveStartAddress;
		uint64_t ACMArbiter;

		ACMInfo acmInfo;

};

//MemorySystem* GetMemorySystem(const std::string &config_file, const std::string &output_dir,
//                 std::function<void(uint64_t)> read_callback,
//                 std::function<void(uint64_t)> write_callback);

}  // namespace dramsim3

#endif
