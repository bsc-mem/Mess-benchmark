################################################################################
# Copyright (c) 2023, Valéria S. Girelli
#                     Pouya Esmaili Dokht
#                     Mariana Carmin
#                     Petar Radojkovic
#                     Paul Carpenter
#                     Eduard Ayguade
#                     Contact: valeria.soldera [at] bsc [dot] es
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
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
################################################################################
from abc import ABC, abstractmethod

def Factory(type, format):
    calculators = {
            'bandwidth' : {'likwid' : BandwidthLikwidCalculator},
            'bandwidth' : {'perf' : BandwidthPerfCalculator},
            'latency' : {'perf' : LatencyPerfCalculator} 
    }
    return calculators[type][format]

class Calculator(ABC):
    def __init__(self):
        pass

    @abstractmethod
    def calculate(self, data, config):
        """ Receive dataframe with raw counters and return dataframe with calculated derived metric
        
        Remove columns that become obsolete after the calculation (i.e. source columns for calculations)

        """
        pass

# this is currently is written for Kunpeng processor. it should be generalize for other platform
class BandwidthPerfCalculator(Calculator):
    def calculate(df, config=None):
        """ Calculate bandwidth taking number of DRAM CAS/OPTANE INSERT commands as input.

        The function tries to automatically select CAS or INSERT columns from dataframe. If none or both columns exist,
        an exception is raised. It is currently assumed that exactly one of these counter types is present.
        TODO: Handle an existance of both counter types.

        """
        

        cas_columns = [c for c in df.columns if 'socket0_' in c ]
        insert_columns = [c for c in df.columns if 'INSERTS' in c]


        wr_columns = [c for c in df.columns if 'Read' in c]
        rd_columns = [c for c in df.columns if 'Write' in c]

        writeCounter = df[wr_columns].sum(axis=1)
        readCounter = df[rd_columns].sum(axis=1)

        # print(writeCounter, readCounter)
        df['rd_percentage_actual'] = (readCounter) / (writeCounter+readCounter)


        if len(cas_columns) == 0 and len(insert_columns) == 0:
            raise UserWarning
        if len(cas_columns) > 0 and len(insert_columns) > 0:
            raise UserWarning

        if len(cas_columns) > 0:
            bandwidth_columns = cas_columns
        elif len(insert_columns) > 0:
            bandwidth_columns = insert_columns
        else:
            raise Exception

        # bandwidth = total_CAS/INSERT_command_count * cache_line_size (64B) / runtime (in B/s)
        # divide by 1e9 to get bandwidth in GB/s or by 1e6 to get bw in MB/s
        df['bandwidth'] = df[bandwidth_columns].sum(axis=1) / 1000
        # df['bandwidth'] = df[bandwidth_columns].sum(axis=1) * 32 / df['runtime'] / 1000 / 1000 / 
        df.drop(columns=bandwidth_columns, inplace=True)
        print('maximum bw: ', df['bandwidth'].max())


class BandwidthLikwidCalculator(Calculator):
    def calculate(df, config=None):
        """ Calculate bandwidth taking number of DRAM CAS/OPTANE INSERT commands as input.

        The function tries to automatically select CAS or INSERT columns from dataframe. If none or both columns exist,
        an exception is raised. It is currently assumed that exactly one of these counter types is present.
        TODO: Handle an existance of both counter types.

        """
        cas_columns = [c for c in df.columns if 'CAS' in c]
        insert_columns = [c for c in df.columns if 'INSERTS' in c]

        if len(cas_columns) == 0 and len(insert_columns) == 0:
            raise UserWarning
        if len(cas_columns) > 0 and len(insert_columns) > 0:
            raise UserWarning

        if len(cas_columns) > 0:
            bandwidth_columns = cas_columns
        elif len(insert_columns) > 0:
            bandwidth_columns = insert_columns
        else:
            raise Exception

        # bandwidth = total_CAS/INSERT_command_count * cache_line_size (64B) / runtime (in B/s)
        # divide by 1e9 to get bandwidth in GB/s or by 1e6 to get bw in MB/s
        #df['bandwidth'] = df[bandwidth_columns].sum(axis=1) * 64 / df['runtime'] / 1000 / 1000 / 1000
        df['bandwidth'] = df[bandwidth_columns].sum(axis=1) * 64 / df['runtime'] / 1000 / 1000
        df.drop(columns=bandwidth_columns + ['runtime'], inplace=True)
        return df

class LatencyPerfCalculator(Calculator):
    def calculate(df, config):
        # Calculates an average latency of a memory access removing the cost of virtual-to-physical address translation.
        # We use the following information:
        # - r1008: cycles spent in pagewalking
        # - r2008: STLB hits
        # - STLB_HIT_LATENCY: latency of STLB hit (in cycles) in the given architecture, provided in the configuration file
        # From the total number of cycles, we remove:
        # - the number of cycles spent on pagewalking
        # - the number of cycles required to access the STLB (STLB_HIT_LATENCY * #hits on the STLB)
        # The remaining cycles are divided by the amount of memory accesses performed by ptr_chase,
        # which is also provided on the configuration file.
        # df['latency'] = (df['cycles'] - df['r1008'] - float(config['STLB_HIT_LATENCY']) * df['r2008']) / int(config['PTRCHASE_NUM_INSTRUCTIONS']) # cycles per access
        df['latency'] = (1000000000*df['seconds_user'] -  (df['r2012']/float(config['CPU_FREQ'])) - float(config['STLB_HIT_LATENCY']) * df['r1012']) / int(config['PTRCHASE_NUM_INSTRUCTIONS']) # cycles per access
        df.drop(columns=['cycles', 'instructions', 'r2012', 'r1012', 'seconds_user'], inplace=True)
        print('minimum latency: ', df['latency'].min())
        print('maximum latency: ', df['latency'].max())
        return df

class MeanCalculator(Calculator):
    def calculate(df, metric):
        if metric=='bandwidth':
            df = df.groupby(['type', 'rd_percentage', 'pause'], as_index=False).agg({metric: ['mean', 'std', 'min', 'max'], 'rd_percentage_actual': ['mean']})
        else:
            df = df.groupby(['type', 'rd_percentage', 'pause'], as_index=False).agg({metric: ['mean', 'std', 'min', 'max']})
        # df = df.groupby(['type', 'rd_percentage', 'pause'], as_index=False).agg({metric: ['mean', 'std', 'min', 'max']})
        df.columns = ['_'.join(col).rstrip('_') for col in df.columns.values]
        print(df)
        return df

