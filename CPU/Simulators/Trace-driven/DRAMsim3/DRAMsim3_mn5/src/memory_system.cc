#include "memory_system.h"

namespace dramsim3 {
MemorySystem::MemorySystem(const std::string &config_file,
                           const std::string &output_dir,
                           std::function<void(uint64_t)> read_callback,
                           std::function<void(uint64_t)> write_callback)
    : config_(new Config(config_file, output_dir)) {
    // TODO: ideal memory type?
    if (config_->IsHMC()) {
        dram_system_ = new HMCMemorySystem(*config_, output_dir, read_callback,
                                           write_callback);
    } else {
        dram_system_ = new JedecDRAMSystem(*config_, output_dir, read_callback,
                                           write_callback);
    }

    // ACM@rowBuffer configuration is initialized here. 
    CurrentCycle=0; // cycles
    ACMEnable=0; // ACM is disabled by default
    ACMArbiter=0; // start from allocating ACM number zero
}

MemorySystem::~MemorySystem() {

    // cout << "cycles left in PIM engine: " << ACMNextFreeSlot[0]-CurrentCycle << endl;
    delete (dram_system_);
    delete (config_);
}


void MemorySystem::setDelayQueue(uint32_t delayQueue){
    // cout << "debug (dramsim3): " << "delayQueue is: " << delayQueue << endl;
    DelayQueueWaitCycle = delayQueue;
}

uint64_t MemorySystem::wait_for_PIM_cycles() {
    // The correct approach is to find the maximum
    // for ACM implementation this is enough
    // cout << "dramsim3: " << ACMNextFreeSlot[0] << " " <<  CurrentCycle << endl;
    return ACMNextFreeSlot[0]-CurrentCycle;
}

// Enable ACM@RowBuffer
void MemorySystem::EnableACMatRowBuffer(void* acmInfo){
    // printf("ACM Write becomes enable\n");
    ACMEnable = 1;
    this->acmInfo = *(static_cast<ACMInfo*>(acmInfo));

    ACMNextFreeSlot = new uint64_t [this->acmInfo.numberOfACMs];

    for (uint64_t i = 0; i < this->acmInfo.numberOfACMs; ++i)
    {
        ACMNextFreeSlot[i]=0;
    }

    // cout << "debug (dramsim3): " << "ACM is enable." << endl;
    // cout << "debug (dramsim3): " << "sortedReadLatency: " << this->acmInfo.sortedReadLatency << endl;
    // cout << "debug (dramsim3): " << "sortedWriteLatency: " << this->acmInfo.sortedWriteLatency << endl;
    // cout << "debug (dramsim3): " << "numberOfACMs: " << this->acmInfo.numberOfACMs << endl;
    // cout << "debug (dramsim3): " << "recordSize: " << this->acmInfo.recordSize << endl;
    // cout << "debug (dramsim3): " << "ACMAllocatedSpace: " << this->acmInfo.ACMAllocatedSpace << endl;
    // cout << endl << endl; 
}

void MemorySystem::setWriteAddressACM(uint64_t startAddress) {
    // cout<< "ACM setWriteAddressACM dramsim3 " << startAddress << endl;
    ConventionalPerspectiveStartAddress=startAddress;
}

void MemorySystem::setSortedReadAddressACM(uint64_t startAddress) {
    // cout<< "ACM setSortedReadAddressACM dramsim3 " << startAddress << endl;
    SortedPerspectiveStartAddress=startAddress;
}

void MemorySystem::setSizeOfACM(uint64_t numnerOfElement, uint64_t elementSize) {
    // cout<< "ACM number of element is " << numnerOfElement <<" and size of element is: " << elementSize << endl;
    acmInfo.recordSize=elementSize;
    acmInfo.ACMAllocatedSpace=numnerOfElement*elementSize;
}

uint64_t MemorySystem::GetACMDelayforZSimBoundPhase() { // happened in Bound phase
    // printf("%llu %llu %lld, \n",ACMNextFreeSlot, CurrentCycle, ACMNextFreeSlot-CurrentCycle);
    if (ACMNextFreeSlot[0]>CurrentCycle) {
        return ACMNextFreeSlot[0]-CurrentCycle;
    }
    else { 
        return 0;
    }
}

void MemorySystem::ClockTick() { 

    vector<delayedInfo>::iterator it = queuedTransactions.begin();

    /////////////////       start of delay queue code       ///////////////////////
    // Rommel Sanchez (missing link paper. a.k.a. No Man's Land)
    // decrease delay until it is zero. then initiate the transaction. happened in Weave phase
    while(it != queuedTransactions.end()) {

        if ((*it).delayedTicks>0) {
            (*it).delayedTicks--;
            it++;
        }
        else {
	        struct delayedInfo t = *it;
            if (dram_system_->WillAcceptTransaction(t.addr, t.isWrite)) {
                if (dram_system_->AddTransaction(t.addr, t.isWrite)== false) {
                    struct delayedInfo newTransaction = {t.addr, t.isWrite, 0};
                    queuedTransactions.push_back(newTransaction);
                }
                it = queuedTransactions.erase(it);
            }
	        else {
                it++;
            }
        }
    }
    // /////////////////       end of delay queue code       ///////////////////////

    CurrentCycle++; // added for timing management of ACM@RowBuffer
    dram_system_->ClockTick(); 
}

double MemorySystem::GetTCK() const { return config_->tCK; }

int MemorySystem::GetBusBits() const { return config_->bus_width; }

int MemorySystem::GetBurstLength() const { return config_->BL; }

int MemorySystem::GetQueueSize() const { return config_->trans_queue_size; }

void MemorySystem::RegisterCallbacks(
    std::function<void(uint64_t)> read_callback,
    std::function<void(uint64_t)> write_callback) {
    dram_system_->RegisterCallbacks(read_callback, write_callback);
}

uint64_t MemorySystem::GetChannelMask() { return config_->ch_mask;}

uint64_t MemorySystem::GetRankMask() { return config_->ra_mask;}

uint64_t MemorySystem::GetBankMask() { return config_->ba_mask;}

uint64_t MemorySystem::GetRowMask() { return config_->ro_mask;}

bool MemorySystem::WillAcceptTransaction(uint64_t hex_addr,
                                         bool is_write) const {
    return dram_system_->WillAcceptTransaction(hex_addr, is_write);
}

bool MemorySystem::AddTransaction(uint64_t hex_addr, bool is_write) {
    // Delay Queue used in Missing Link paper of Rommel Sanchez. We adopt it for ACM use as well 
    uint64_t final_Delay_in_Q;
    double tCK = config_->tCK;

    /////////               Start of acm@RowBuffer Section              /////////
    // ACM write  
    uint64_t ACMOccupancy;
    if (!ACMEnable) { // normal execution without ACM@RowBuffer
        // printf("ACM Write is not enable\n");
        final_Delay_in_Q = DelayQueueWaitCycle;
    }
    else if( (is_write) && (ConventionalPerspectiveStartAddress<=hex_addr && hex_addr<ConventionalPerspectiveStartAddress+acmInfo.ACMAllocatedSpace) ) {
        // cout << "CurrentCycle: " << CurrentCycle << endl;
        // cout << "before cycles left in PIM engine: " << ((int64_t)ACMNextFreeSlot[ACMArbiter])-(int64_t)CurrentCycle << endl;
        // printf("ACM write access is called in dramsim3\n");
        ACMOccupancy = (acmInfo.sortedWriteLatency/tCK); // 13.33 for ddr4 in MN4 -> 13 (-1 is necessary for correct timings) 
        if(ACMNextFreeSlot[ACMArbiter]==0 || ACMNextFreeSlot[ACMArbiter]<CurrentCycle) {
            final_Delay_in_Q = 0; //DELAY_QUEUE_WAIT_CYCLE;
            ACMNextFreeSlot[ACMArbiter] = CurrentCycle + ACMOccupancy ; 
        }
        else {
            final_Delay_in_Q = (ACMNextFreeSlot[ACMArbiter]-CurrentCycle); // + DELAY_QUEUE_WAIT_CYCLE;
            ACMNextFreeSlot[ACMArbiter]+= ACMOccupancy; 
        }
        // cout << "after cycles left in PIM engine: " << ((int64_t)ACMNextFreeSlot[ACMArbiter])-(int64_t)CurrentCycle << endl;
        ACMArbiter = (ACMArbiter+1) % this->acmInfo.numberOfACMs;

        // cout << "cycles left in PIM engine: " << ACMNextFreeSlot[0]-CurrentCycle << endl;
    }// else if it is ACM SortedRead
    else if( (!is_write) && (SortedPerspectiveStartAddress<=hex_addr && hex_addr<SortedPerspectiveStartAddress+acmInfo.ACMAllocatedSpace) ) {
        // printf("ACM read access is called\n");
        ACMOccupancy = (acmInfo.sortedReadLatency/tCK); // 9.33 for ddr4 in MN4 -> 9 (is error important?)
        // this should never happened since first we write, then we read!!! 
        if(ACMNextFreeSlot[ACMArbiter]==0 || ACMNextFreeSlot[ACMArbiter]<CurrentCycle) {
            final_Delay_in_Q =  ACMOccupancy; 
            ACMNextFreeSlot[ACMArbiter] = CurrentCycle + ACMOccupancy;
        }
        else {
            final_Delay_in_Q = (ACMNextFreeSlot[ACMArbiter]-CurrentCycle) + ACMOccupancy;  
            ACMNextFreeSlot[ACMArbiter] += ACMOccupancy;
        }
        ACMArbiter = (ACMArbiter+1) % this->acmInfo.numberOfACMs;
    }// else normal access
    else {
        // printf("normal access to ddr4\n");
        final_Delay_in_Q = DelayQueueWaitCycle;
    }

    // generate delay queue. we add transactions later, after delay cycles reach zero.    
    struct delayedInfo newTransaction = {hex_addr, is_write, final_Delay_in_Q};
    queuedTransactions.push_back(newTransaction);
    return true;
   // return dram_system_->AddTransaction(hex_addr, is_write); // original code
}

void MemorySystem::PrintStats() const { dram_system_->PrintStats(); }

void MemorySystem::ResetStats() { dram_system_->ResetStats(); }

MemorySystem* GetMemorySystem(const std::string &config_file, const std::string &output_dir,
                 std::function<void(uint64_t)> read_callback,
                 std::function<void(uint64_t)> write_callback) {
    return new MemorySystem(config_file, output_dir, read_callback, write_callback);
}
}  // namespace dramsim3

// This function can be used by autoconf AC_CHECK_LIB since
// apparently it can't detect C++ functions.
// Basically just an entry in the symbol table
extern "C" {
void libdramsim3_is_present(void) { ; }
}
