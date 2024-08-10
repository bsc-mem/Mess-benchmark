/*
 * Copyright (c) 2024, Barcelona Supercomputing Center
 * Contact: pouya.esmaili    [at] bsc [dot] es
 *          petar.radojkovic [at] bsc [dot] es
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright notice,
 *       this list of conditions and the following disclaimer.
 *
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *
 *     * Neither the name of the copyright holder nor the names
 *       of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef PERF_HELPER_H_
#define PERF_HELPER_H_

#include <linux/perf_event.h>
#include <stdint.h>// for uint64 !
#include <sys/ioctl.h>
#include <asm/unistd.h>
#include <unistd.h> // for kernel call
#include <stdlib.h>
#include <cstring> // for memset
#include <ctime>

#include <iostream>
using namespace std;

static long perf_event_open(struct perf_event_attr *hw_event, pid_t pid,int cpu, int group_fd, unsigned long flags) {
    int ret;
    ret = syscall(__NR_perf_event_open, hw_event, pid, cpu, group_fd, flags);
    return ret;
}

struct perf_event_attr pe;

int fileDescriptor,fileDescriptor2;
uint64_t id1,id2;
char buf[4096];

clock_t beginTime,endTime;

struct read_format {
  uint64_t nr;
  struct {
    uint64_t value;
    uint64_t id;
  } values[];
};

struct read_format* rf;

struct PerfCounterEventInformation {
    string name;
    uint32_t type;
    uint64_t config;
};

struct PerfCounterEventInformation perfCounterEventInformation[3][2];


void setPerfCounters() {
    // counters for cpu cycles and instructions
    perfCounterEventInformation[0][0].name = "cycles:u";
    perfCounterEventInformation[0][0].type = PERF_TYPE_HARDWARE;
    perfCounterEventInformation[0][0].config =PERF_COUNT_HW_CPU_CYCLES;
    perfCounterEventInformation[0][1].name = "instructions:u";
    perfCounterEventInformation[0][1].type = PERF_TYPE_HARDWARE;
    perfCounterEventInformation[0][1].config =PERF_COUNT_HW_INSTRUCTIONS;
    
    // <umask><eventselector>
    // counters for tlb1 miss and tlb2 hit
    perfCounterEventInformation[1][0].name = "tlb1missTLBhit";
    perfCounterEventInformation[1][0].type = PERF_TYPE_RAW;
    perfCounterEventInformation[1][0].config =0x0F45;
    perfCounterEventInformation[1][1].name = "tlb1missTLBmiss";
    perfCounterEventInformation[1][1].type = PERF_TYPE_RAW;
    perfCounterEventInformation[1][1].config =0xF045;

    // counters for tlb2 miss and pagewalk
    perfCounterEventInformation[2][0].name = "pagewalkside0";
    perfCounterEventInformation[2][0].type = PERF_TYPE_RAW;
    perfCounterEventInformation[2][0].config =0x0146;
    perfCounterEventInformation[2][1].name = "pagewalkside1";
    perfCounterEventInformation[2][1].type = PERF_TYPE_RAW;
    perfCounterEventInformation[2][1].config =0x0246;
}




void initializeProfiling(uint32_t select) {
    rf = (struct read_format*) buf;

    memset(&pe, 0, sizeof(struct perf_event_attr));
    pe.size = sizeof(struct perf_event_attr);
    pe.type = perfCounterEventInformation[select][0].type;
    pe.config = perfCounterEventInformation[select][0].config;
    pe.disabled = 1;
    pe.exclude_kernel = 1;
    pe.exclude_hv = 1;
    pe.read_format = PERF_FORMAT_GROUP | PERF_FORMAT_ID;
    // pid = 0  and cpu = -1 means current process any cpu
    fileDescriptor = perf_event_open(&pe, 0, -1, -1, 0);
    ioctl(fileDescriptor, PERF_EVENT_IOC_ID, &id1);

    memset(&pe, 0, sizeof(struct perf_event_attr));
    pe.size = sizeof(struct perf_event_attr);
    pe.type = perfCounterEventInformation[select][1].type;
    pe.config = perfCounterEventInformation[select][1].config;
    pe.disabled = 1;
    pe.exclude_kernel = 1;
    pe.exclude_hv = 1;
    pe.read_format = PERF_FORMAT_GROUP | PERF_FORMAT_ID;
    // pid = 0  and cpu = -1 means current process any cpu
    fileDescriptor2 = perf_event_open(&pe, 0, -1, fileDescriptor, 0);
    ioctl(fileDescriptor2, PERF_EVENT_IOC_ID, &id2);

    if (fileDescriptor == -1 || fileDescriptor2 == -1) {
        cout << " fileDescriptor has some problem " << fileDescriptor  << fileDescriptor2 << endl;
        return;
    }
}


void startProfiling() {
    ioctl(fileDescriptor, PERF_EVENT_IOC_RESET, PERF_IOC_FLAG_GROUP);
    beginTime = clock();
    ioctl(fileDescriptor, PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP);
}

void endProfiling() {
    ioctl(fileDescriptor, PERF_EVENT_IOC_DISABLE, PERF_IOC_FLAG_GROUP);
    endTime = clock();
}



void readProfiling(uint32_t select) {
    uint64_t cpuInstructions,cpuCycles;
    read(fileDescriptor, buf, sizeof(buf));
    for(uint32_t i=0;i<rf->nr;i++)
    {
      if (rf->values[i].id == id1)
      {
        cpuCycles = rf->values[i].value;

        cout << cpuCycles << " " << perfCounterEventInformation[select][0].name << " " << endl;

        // cout << "cycles of cpu : " << cpuCycles << endl;
      }
      else if (rf->values[i].id == id2)
      {
        cpuInstructions = rf->values[i].value;
        cout << cpuInstructions << " " << perfCounterEventInformation[select][1].name << " " << endl;
        
      }
      else{
        cout << "wrong place" << endl;
      }
    }

    if (select==0)
    {
        cout << "mem latency is (with time): " << 1000000000*((double)((endTime - beginTime)/CLOCKS_PER_SEC)/(cpuInstructions)) << "ns" << endl;
        // cout << "mem latency is: " << ((double)cpuCycles/(cpuInstructions))/2.25 << "ns" << endl;
        cout << "calculated clocks per seconds is: " << (cpuCycles/((double)(endTime - beginTime)/ CLOCKS_PER_SEC)) << endl; 
    }
}

void readExecutionTime() {
    cout << ((double)(endTime - beginTime)/ CLOCKS_PER_SEC) << " seconds time elapsed" << endl;
}


#endif
