# Copyright (c) 2024, Barcelona Supercomputing Center
# Contact: pouya.esmaili    [at] bsc [dot] es
#          petar.radojkovic [at] bsc [dot] es
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
#     * Redistributions of source code must retain the above copyright notice,
#       this list of conditions and the following disclaimer.
#
#     * Redistributions in binary form must reproduce the above copyright
#       notice, this list of conditions and the following disclaimer in the
#       documentation and/or other materials provided with the distribution.
#
#     * Neither the name of the copyright holder nor the names
#       of its contributors may be used to endorse or promote products
#       derived from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

from abc import ABC, abstractmethod
from random import seed
from random import random


def Factory(type, format, config):
    """ Create LineParser object depending on the counter type and file format.

        TODO right now, we only support bandwidth measurements made with likwid
        and latency measurements made with perf

        Input:
        type - indicates whether bandwidth or latency counters are processed
        format - indicates the format of input files (depends on the tool used to record counters)
    """
    line_parsers = {
            'bandwidth' : {'likwid' : BandwidthLikwidLineParser},
            'latency': {'perf' : LatencyPerfLineParser}
    }
 

    return line_parsers[type][format](config)

class LineParser(ABC):
    @abstractmethod
    def __init__(self):
        pass

    @abstractmethod
    def parse_line(self, line):
        """ Parse a raw line (line) and return a tuple (stats, values, done).

        Input:
        - line : Raw line

        Return:
        - stats  : Array of counters/stats names
        - values : Array of values matching above stats
        - done   : Boolean indicating whether processing is completed
        """

        pass


class BandwidthLikwidLineParser(LineParser):

    def __init__(self, config):
        self.core_count = int(config['STREAM_CORE_COUNT_SOCKET'])
        self.socket_count = int(int(config['STREAM_CORE_COUNT']) / int(config['STREAM_CORE_COUNT_SOCKET']))
        self.used_sockets = [0] # This expect array, even if only one value
        self.max_channels = int(config['MEM_MAX_CHANNELS'])

        self.cycle_counter = 0
        self.rd_counter = 0
        self.wr_counter = 0
        self.should_measure_bw=0
        
        
        #print(f'core_count = {self.core_count}')
        #print(f'socket_count = {self.socket_count}')
        # print(f'max_channels= {self.max_channels}')

    # What if not all memory channels are populated, like in the case of 2:6 DRAMs/Optanes?
    def parse_line(self, line):
        line = line.replace('#' , ':').replace(' ', '')
        tokens = line.split(':')
        # print(tokens)
        if 'STAT' in tokens[0]:
            return None, None, False
        elif tokens[0] == 'Runtime (RDTSC) [s]':
            return ['runtime'], [float(tokens[2])], False
        elif 'l3-0b' in tokens[0]:
            self.should_measure_bw=1
            return None, None, False
        elif 'mGETS' == tokens[0]:
            if self.should_measure_bw==0:
                return None, None, False
            self.rd_counter = self.rd_counter + 1
            if self.rd_counter == 24:
                self.rd_counter = 0;
            # channel = tokens[1][4] # e.g. MBOX0C0. Assuming single digit channel ID
            return ['_'.join(['rd', 'socket' , 'MC', str(self.rd_counter)]) for sock in self.used_sockets],\
                [float(tokens[1])],\
                False
        elif 'mGETXIM' == tokens[0]:
            if self.should_measure_bw==0:
                return None, None, False
            should_measure_bw=0
            self.wr_counter = self.wr_counter + 1
            if self.wr_counter == 24:
                self.wr_counter = 0;
            return ['_'.join(['wr', 'socket' , 'MC', str(self.wr_counter)]) for sock in self.used_sockets],\
                [float(tokens[1])],\
                False
        elif 'cycles' == tokens[0]:
            # print(tokens)
            self.cycle_counter = self.cycle_counter + 1
            if self.cycle_counter == 24:
                self.cycle_counter = 0
            return ['_'.join([tokens[0], str(self.cycle_counter) ]) for sock in self.used_sockets],\
                [float(tokens[1])],\
                False
        elif 'heartbeats' == tokens[0]:
            return tokens[0], tokens[0], True
        else:
            return None, None, False

class BandwidthPerfLineParser(LineParser):
    def __init__(self, config):
        self.core_count = int(config['STREAM_CORE_COUNT_SOCKET']) # EPEEC: 16, APASS: 24
        self.socket_count = int(int(config['STREAM_CORE_COUNT']) / int(config['STREAM_CORE_COUNT_SOCKET']))
        self.used_sockets = [0] # This expect array, even if only one value
        self.max_channels = int(config['MEM_MAX_CHANNELS'])

    
    def parse_line(self, line):
        tokens = line.split(' ')
        tokens[:] = [x for x in tokens if x] # eliminate empty '' tokens
        # print(tokens)
        if 'STAT' in tokens[0]:
            return None, None, False
        elif len(tokens) < 2:
            return None, None, False
        elif 'PM_MBA' in tokens[1]:
            # sccl= int(int(tokens[1][9])/2)
            # ddrc= int(tokens[1][15])
            # channel = 4*sccl+ddrc # e.g. MBOX0C0. Assuming single digit channel ID
            # if channel < 8:
            return ['_'.join(['socket' + str(sock), str(tokens[1])]) for sock in self.used_sockets],\
                [float(tokens[0].replace(',', ''))/2],\
                False
            # else:
            #     return None, None, False
        elif tokens[1] == 'seconds':    
            return ['runtime'], [float(tokens[0])], True
        else:
            return None, None, False


class LatencyPerfLineParser(LineParser):
    def __init__(self, config):
        # number of memory controllers should be considered for overflowing of these counters...
        # for Skylake we have 2 MC
        self.rd_counter=0
        self.rd_latency_counter=0
        self.should_measure_lat=0


    def parse_line(self, line):
        line = line.replace('#' , ':').replace(' ', '')
        tokens = line.split(':')
        if len(tokens) < 2:
            return None, None, False
        elif 'l3-0b' in tokens[0]:
            self.should_measure_lat=1
            return None, None, False
        elif 'mGETS' == tokens[0]:
            # print(tokens)
            if self.should_measure_lat==0:
                return None, None, False
            self.rd_counter = self.rd_counter + 1
            if self.rd_counter == 24:
                self.rd_counter = 0
            return ['_'.join([ 'MC_' + tokens[0], str(self.rd_counter)])], [float(tokens[1])], False
        elif 'mGETXIM' == tokens[0]:
            # print(tokens)
            if self.should_measure_lat==0:
                return None, None, False
            return ['_'.join([ 'MC_' + tokens[0], str(self.rd_counter)])], [float(tokens[1])], False
        elif 'latGETnl' == tokens[0]:
            if self.should_measure_lat==0:
                return None, None, False
            self.should_measure_lat=0
            # print(tokens)
            self.rd_latency_counter = self.rd_latency_counter + 1
            if self.rd_latency_counter == 24:
                self.rd_latency_counter = 0
            return ['_'.join([ 'MC', tokens[0], str(self.rd_latency_counter)])], [float(tokens[1])], True if self.rd_latency_counter==0 else False

        else:
            return None, None, False

