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


from scipy.signal import savgol_filter

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

        df.loc[:, 'bandwidth_smooth'] = smooth_x.copy()
        df.loc[:, 'latency_smooth'] = smooth_y.copy()

    return dfs_rw

