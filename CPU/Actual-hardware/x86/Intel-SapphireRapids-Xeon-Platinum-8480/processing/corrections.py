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


from scipy.signal import savgol_filter
import pandas as pd
pd.options.mode.chained_assignment = None  # default='warn'

def remove_outliers():
    pass

def smooth_curves():
    pass

def is_outlier(s):
    lower_limit = s.mean() - (s.std() * 1)
    upper_limit = s.mean() + (s.std() * 1)
    return ~s.between(lower_limit, upper_limit)

def filter_identify_outliers(df):
    df['outlier'] = df.groupby(['type', 'rd_percentage', 'pause'])['bandwidth'].apply(is_outlier)
    df['bandwidth_outliers'] = df['bandwidth'] * df['outlier']
    return df

def annotate_discarded_pauses(df, df_pause_cutoff):
    pauses = df['pause'].values
    rws = df['rd_percentage'].values
    #cutoff = [p < pause_cutoff[rw] for p,rw in zip(pauses, rws)]
    if not df_pause_cutoff is None:
        cutoff = [p < df_pause_cutoff.loc[rw, 'pause'] for p,rw in zip(pauses, rws)]
    else:
        cutoff = [False for p,rw in zip(pauses, rws)]
    print(cutoff)
    #comment the following line to enable filtering based on pause
    #cutoff = [False for p,rw in zip(pauses, rws)]
    df['discarded'] = cutoff
    return df

def annotate_discarded_data_points(df, df_discarded):
    pass

def smooth_curves(config, dfs_rw):
    """ Performs smoothing of (x,y) data points where x is bandwidth and y is latency

        Parameters:
        config (dictionary): configuration
        dfs_rw (dictionary): dictionary mapping read-write ratio to corresponding dataframe

        Returns:
        dictionary: Copy of input dictionary with added columns 'smooth_bandwidth' and 'smooth_latency'
    """
    for rw, df in dfs_rw.items():
        x = df['bandwidth_mean'].tolist()
        y = df['latency_mean'].tolist()

        smooth_x, smooth_y = savgol_filter((x, y),
                                            int(config['SMOOTH_SAVGOL_WINDOW_LENGTH']),
                                            int(config['SMOOTH_SAVGOL_POLYORDER']))

        smooth_x, smooth_y = savgol_filter((x, y),
                                            int(config['SMOOTH_SAVGOL_WINDOW_LENGTH']),
                                            int(config['SMOOTH_SAVGOL_POLYORDER']))

        df.loc[:, 'bandwidth_smooth'] = smooth_x.copy()
        df.loc[:, 'latency_smooth'] = smooth_y.copy()

    return dfs_rw

# On memory mode, each CAS write requires a CAS read. This happens due to the
# cache structure present in the mode. When writing into the memory, the memory
# controller first needs to read the TAG stored in the cacheline to check if
# that is the correct address, otherwise it could be writing in a wrong address.
# For instance, on a kernel with 0% reads/100% writes, we see a similar number
# of CAS writes and CAS reads, since for every write the system first needs to
# read the TAG to check it, and then perform the write. Therefore, on a 50%
# kernel we end up not having a 50%/50% traffic, but instead we have something
# around 66% reads/33% writes. The 50%/50% traffic is observed on a 0% reads kernel.
# This happens because, differently from the oncore caches, the DRAM cache is a
# simple DRAM being operated by the memory controller as a cache, and it does
# not have the hardware mechanisms to check TAG, write through (if necessary),
# and fetch the data in case of miss.
# Here we map the CAS read/CAS write performed on the kernels to the correct
# read/write ratios to have the correct traffic plotted.
def adjust_rw_ratios_bandwidth_df(df):
    read_columns = [c for c in df.columns if 'RD' in c]
    write_columns = [c for c in df.columns if 'WR' in c]
    df['cas_read'] = df[read_columns].sum(axis=1)
    df['cas_write'] = df[write_columns].sum(axis=1)
    
    rws = pd.unique(df['rd_percentage'])
    df['rd_mapped'] = df['rd_percentage']
    rws_mappings = []
    for rd_percentage in rws:
        row = df[(df['rd_percentage'] == rd_percentage) & (df['pause'] == 0)].iloc[0]
        new_ratio = (float(row['cas_read']) * 100) / (float(row['cas_read']) + float(row['cas_write']))
        rws_mappings.append(round(new_ratio))
        df['rd_mapped'] = df['rd_mapped'].replace([rd_percentage], new_ratio)

    df.rd_mapped = df.rd_mapped.round().astype(int)
    df.drop(columns=['cas_read'] + ['cas_write'], inplace=True)
    return df, rws_mappings

def adjust_rw_ratios_latency_df(df, rws_mappings):
    rws = pd.unique(df['rd_percentage'])
    df['rd_mapped'] = df['rd_percentage']
    df['rd_mapped'] = df['rd_mapped'].replace(rws, rws_mappings)

    return df

# This is a sanity check for PROFET.
def remove_double_lat_points(df_rw):
    max_bw = 0
    max_bw_idx = None
    for rw, df in df_rw.items():
        for idx, bw in list(df['bandwidth_smooth'].items()):
            if bw > max_bw:
                max_bw = bw
                max_bw_idx = idx
            else:
                break

        df.drop(df.index[0:max_bw_idx], axis=0, inplace=True)
        max_bw = 0
        max_bw_idx = None

    #for rw, df in df_rw.items():
        #df.drop(df.index[0:df['bandwidth_mean'].idxmax()], axis=0, inplace=True)

    return df_rw
