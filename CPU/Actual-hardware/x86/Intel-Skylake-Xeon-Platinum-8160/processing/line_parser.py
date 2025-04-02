# Copyright (c) 2024, Barcelona Supercomputing Center
# Contact: mess             [at] bsc [dot] es
#          pouya.esmaili    [at] bsc [dot] es
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

def Factory(type, format, config):
    """ Create LineParser object depending on the counter type and file format.

        TODO right now, we only support bandwidth measurements made with likwid
        and latency measurements made with perf

        Input:
        type - indicates whether bandwidth or latency counters are processed
        format - indicates the format of input files (depends on the tool used to record counters)
    """
    # line_parsers = {
    #         'bandwidth' : {'likwid' : BandwidthLikwidLineParser},
    #         'latency': {'perf' : LatencyPerfLineParser}
    # }

    line_parsers = {
            'bandwidth' : {'likwid' : BandwidthLikwidLineParser},
            'bandwidth' : {'vtune' : BandwidthVtuneLineParser},
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

class BandwidthVtuneLineParser(LineParser):
    def __init__(self, config):
        self.core_count = int(config['STREAM_CORE_COUNT_SOCKET']) # EPEEC: 16, APASS: 24
        self.socket_count = int(int(config['STREAM_CORE_COUNT']) / int(config['STREAM_CORE_COUNT_SOCKET']))
        self.used_sockets = [0] # This expect array, even if only one value
        self.max_channels = int(config['MEM_MAX_CHANNELS'])
        #print(f'core_count = {self.core_count}')
        #print(f'socket_count = {self.socket_count}')
        #print(f'max_channels= {self.max_channels}')

    def parse_line(self, line):
        tokens = line.split(' ')
        tokens[:] = [x for x in tokens if x] # eliminate empty '' tokens
        # print(tokens)
        if 'STAT' in tokens[0]:
            return None, None, False
        elif tokens[0] == 'Elapsed':
            if tokens[1] == 'Time:':
                return ['runtime'], [float(tokens[2].replace('\n',''))], False
        elif 'vtune' in tokens[0]:
            return None, None, False
        elif 'CAS_COUNT' in tokens[0]:
            # devide bandwidth value by two because it is counting both sockets
            channel = tokens[0][-2] # e.g. MBOX0C0. Assuming single digit channel ID
            return ['_'.join([tokens[0], 'socket' + str(sock), 'ch' + channel]) for sock in self.used_sockets],\
                [float(tokens[1])/2],\
                True if channel == str(self.max_channels - 1) else False
        elif 'PQ_INSERTS' in tokens[0]:
            channel = tokens[1][4] # e.g. MBOX0C0. Assuming single digit channel ID
            return ['_'.join([tokens[0], 'socket' + str(sock), 'ch' + channel]) for sock in self.used_sockets],\
                [float(tokens[2])],\
                True if channel == str(self.max_channels - 1) and 'WPQ' in tokens[0] else False
        else:
            return None, None, False

class BandwidthLikwidLineParser(LineParser):
    def __init__(self, config):
        self.core_count = int(config['STREAM_CORE_COUNT_SOCKET']) # EPEEC: 16, APASS: 24
        self.socket_count = int(int(config['STREAM_CORE_COUNT']) / int(config['STREAM_CORE_COUNT_SOCKET']))
        self.used_sockets = [0] # This expect array, even if only one value
        self.max_channels = int(config['MEM_MAX_CHANNELS'])
        #print(f'core_count = {self.core_count}')
        #print(f'socket_count = {self.socket_count}')
        #print(f'max_channels= {self.max_channels}')

    # What if not all memory channels are populated, like in the case of 2:6 DRAMs/Optanes?
    def parse_line(self, line):
        tokens = line.split(',')
        if 'STAT' in tokens[0]:
            return None, None, False
        elif tokens[0] == 'Runtime (RDTSC) [s]':
            return ['runtime'], [float(tokens[2])], False
        elif 'CAS_COUNT' in tokens[0]:
            channel = tokens[1][4] # e.g. MBOX0C0. Assuming single digit channel ID
            return ['_'.join([tokens[0], 'socket' + str(sock), 'ch' + channel]) for sock in self.used_sockets],\
                [float(tokens[2])],\
                True if channel == str(self.max_channels - 1) and 'WR' in tokens[0] else False
        elif 'PQ_INSERTS' in tokens[0]:
            channel = tokens[1][4] # e.g. MBOX0C0. Assuming single digit channel ID
            return ['_'.join([tokens[0], 'socket' + str(sock), 'ch' + channel]) for sock in self.used_sockets],\
                [float(tokens[2])],\
                True if channel == str(self.max_channels - 1) and 'WPQ' in tokens[0] else False
        else:
            return None, None, False

class LatencyPerfLineParser(LineParser):
    def __init__(self, config):
        pass

    def parse_line(self, line):
        tokens = line.split()
        if len(tokens) < 2:
            return None, None, False
        if ':u' in tokens[1]:
            return [tokens[1].replace(':u', '')], [float(tokens[0].replace('.', '').replace(',', ''))], False
        elif tokens[1] == 'seconds' and tokens[2] == 'time':
            return ['seconds_user'], [float(tokens[0].replace(',', ''))], True
        else:
            return None, None, False

