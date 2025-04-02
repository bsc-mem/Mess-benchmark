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


import sys
import os
import matplotlib.pyplot as plt
from matplotlib.backends.backend_pdf import PdfPages
import pandas as pd
import seaborn as sns
from scipy.signal import savgol_filter
from scipy.optimize import curve_fit
from numpy import arange

def plot_pause_lat(df):
    plot = sns.lineplot(data=df, x='pause', y='latency_mean', hue='rd_percentage')
    fig = plot.get_figure()
    plot.set_xlim([0, 1000])
    plot.set_xlabel('pause')
    plot.set_ylabel('latency [ns]')
    fig.savefig('pause_lat.pdf')
    plt.close()

def plot_pause_bw(df):
    plot = sns.lineplot(data=df, x='pause', y='bandwidth_mean', hue='rd_percentage')
    fig = plot.get_figure()
    plot.set_xlim([0, 1000])
    plot.set_xlabel('pause')
    plot.set_ylabel('bandwidth [GB/s]')
    fig.savefig('pause_bw.pdf')
    plt.close()

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

def smooth_data(df):
    #x = sorted(df['bandwidth_median'].tolist())
    #y = sorted(df['latency_median'].tolist())
    x = df['bandwidth_median'].tolist()
    y = df['latency_median'].tolist()
    smooth_x, smooth_y = savgol_filter((x, y), 7, 3)
    df['smooth_latency'] = smooth_y
    df['smooth_bandwidth'] = smooth_x
    return df

def save_bwlat_curve_to_file(bw, lat, rw, filename):
    # add value for bw=0 and add a very big value for very big BW
    # we assume that latency for 0GB/s is the same as the latency for the minimal BW we have measured
    bw = [0] + list(reversed(bw)) + [500]
    lat = [lat[0]] + list(reversed(lat)) + [10000]
    bw = [1000 * b for b in bw] # convert from GB/s to MB/s
    lat = [2.8 * l for l in lat] # convert from ns to cycles
    df = pd.DataFrame({'bandwidth' : reversed(bw), 'latency' : reversed(lat)})
    os.makedirs(os.path.dirname(filename), exist_ok=True)
    df.to_csv(filename, sep='\t', index=False, header=False)


def discard_marked_data(df):
    return df[df['discarded'] == False]


def calculate_averages(df):
    df = df.groupby(['type', 'rd_percentage', 'pause'], as_index=False).agg({'bandwidth': ['mean', 'median', 'std', 'min', 'max'], 'latency': ['mean', 'median', 'std', 'min', 'max']})
    df.columns = ['_'.join(col).rstrip('_') for col in df.columns.values]
    return df

def plot_bw_limit(df, ax):
    types = pd.unique(df['type'])
    for type in types:
       tech, freq = type.split('-')
       num_channels = 4
       #bw_lim = float(freq) * 8 * num_channels / 1000 # 8B per transfer
       bw_lim = 1600.0 * 8 * 6 / 1000 # 8B per transfer, 6 active channels
       ax.axvline(x=bw_lim, color='black')
       ax.text(x=bw_lim, y=900, s=f'Max. theoretical bandwidth = {bw_lim} GB/s', horizontalalignment='right')


def plot_bw_lat_analysis(stats_dir):
    #load dataset
    #df_all = pd.read_csv(os.path.join(stats_dir, 'merged-lat-bw_all_measurements.csv'))
    df_all = pd.read_csv(os.path.join(stats_dir, 'bandwidth-latency.csv'))
    df_all.sort_values(by=['type', 'rd_percentage', 'pause', 'measure'], inplace=True)
    try:
        df_pause_cutoff = pd.read_csv(os.path.join(stats_dir, 'pause_cutoff.csv'), index_col='rd_percentage')
    except:
        df_pause_cutoff = None

    # fix BW and LAT
    df_all['latency'] = df_all['latency'] / 2.8
    df_all['bandwidth'] = df_all['bandwidth'] / 2

    df_all = filter_identify_outliers(df_all)
    df_filt = df_all[~df_all['outlier']]
    df_filt = calculate_averages(df_filt)
    df_all_mean = calculate_averages(df_all)

    df_filt = annotate_discarded_pauses(df_filt, df_pause_cutoff)
    df_all_mean = annotate_discarded_pauses(df_all_mean, df_pause_cutoff)
    df_filt = discard_marked_data(df_filt)
    df_all_mean = discard_marked_data(df_all_mean)
    print(df_all_mean)

    rws = pd.unique(df_all['rd_percentage'])
    with PdfPages(os.path.join(stats_dir, 'lat_bw_details.pdf')) as pdf:
        for rw in rws:
            fig, ax = plt.subplots(1,1)
            dff_all = df_all[df_all['rd_percentage'] == rw]
            dff_all_mean = df_all_mean[df_all_mean['rd_percentage'] == rw]
            dff_filt = df_filt[df_filt['rd_percentage'] == rw]
            plot = sns.scatterplot(data=dff_all_mean, x='bandwidth_median', y='latency_median')
            #plot = sns.scatterplot(data=dff_filt, x='bandwidth_mean', y='latency_mean')
            plot = sns.scatterplot(data=dff_all, x='bandwidth', y='latency', style='outlier', color='0.2')
            xerrs = [dff_all_mean['bandwidth_mean'] - dff_all_mean['bandwidth_min'], dff_all_mean['bandwidth_max'] - dff_all_mean['bandwidth_mean']]
            yerrs = [dff_all_mean['latency_mean'] - dff_all_mean['latency_min'], dff_all_mean['latency_max'] - dff_all_mean['latency_mean']]
            plot.errorbar(x=dff_all_mean['bandwidth_mean'], y=dff_all_mean['latency_mean'], xerr=xerrs, yerr=yerrs, fmt='none')
            for i, txt in enumerate(dff_all_mean['pause']):
                plot.annotate(txt, (dff_all_mean['bandwidth_mean'].iat[i], dff_all_mean['latency_mean'].iat[i]),
                        color=('#888888' if dff_all_mean['discarded'].iat[i] else '#000000'))
            plot_bw_limit(dff_all, plot)
            dff_all_mean = smooth_data(dff_all_mean)
            save_bwlat_curve_to_file(dff_all_mean['smooth_bandwidth'].tolist(), dff_all_mean['smooth_latency'].tolist(), rw,
                    os.path.join(stats_dir, 'bwlats', 'bwlat_' + str(rw) + '.txt'))
            ax.plot(dff_all_mean['smooth_bandwidth'], dff_all_mean['smooth_latency'])
            fig = plot.get_figure()
            plot.set_xlim([0, 128])
            plot.set_ylim([0, 1000])
            plot.set_xlabel('bandwidth [GB/s]')
            plot.set_ylabel('latency [ns]')
            mem_types = ','.join(pd.unique(dff_all['type']))
            mem_types = 'DDR4-2666'
            plot.set_title(f'Bandwidth-Latency for {mem_types} with rd_percentage = {rw}; showing all measurements and mean; error bars show min-max range')
            fig.set_size_inches([16,9])
            fig.tight_layout()
            pdf.savefig(fig)
            plt.close()

def objective(x, a, b, c, d):
	return a*b^x + c * x + d


def plot_bw_lat_analysis_filtered(stats_dir):
    #load dataset
    #df_all = pd.read_csv(os.path.join(stats_dir, 'merged-lat-bw_ddr4-2666_all_measurements.csv'))
    df_all = pd.read_csv(os.path.join(stats_dir, 'bandwidth-latency.csv'))
    df_all.sort_values(by=['type', 'rd_percentage', 'pause', 'measure'], inplace=True)

    # fix BW and LAT
    df_all['latency'] = df_all['latency'] / 2.8
    df_all['bandwidth'] = df_all['bandwidth'] / 2

    df_all = filter_identify_outliers(df_all)
    df_filt = df_all[~df_all['outlier']]
    df_filt = calculate_averages(df_filt)
    df_all_mean = calculate_averages(df_all)

    df_filt = annotate_discarded_pauses(df_filt)
    df_all_mean = annotate_discarded_pauses(df_all_mean)
    print(df_all_mean)

    rws = pd.unique(df_all['rd_percentage'])
    with PdfPages(os.path.join(stats_dir, 'lat_bw_filtered.pdf')) as pdf:
        for rw in rws:
            dff_all = df_all[df_all['rd_percentage'] == rw]
            dff_all_mean = df_all_mean[df_all_mean['rd_percentage'] == rw]
            dff_filt = df_filt[df_filt['rd_percentage'] == rw]
            plot = sns.scatterplot(data=dff_filt, x='bandwidth_mean', y='latency_mean')
            #plot = sns.scatterplot(data=dff_filt, x='bandwidth_mean', y='latency_mean')
            #plot = sns.scatterplot(data=dff_all, x='bandwidth', y='latency', style='outlier', color='0.2')
            #xerrs = [dff_filt['bandwidth_mean'] - dff_filt['bandwidth_min'], dff_filt['bandwidth_max'] - dff_filt['bandwidth_mean']]
            #yerrs = [dff_filt['latency_mean'] - dff_filt['latency_min'], dff_filt['latency_max'] - dff_filt['latency_mean']]
            #plot.errorbar(x=dff_filt['bandwidth_mean'], y=dff_filt['latency_mean'], xerr=xerrs, yerr=yerrs, fmt='none')
            for i, txt in enumerate(dff_filt['pause']):
                plot.annotate(txt, (dff_filt['bandwidth_mean'].iat[i], dff_filt['latency_mean'].iat[i]),
                        color=('#888888' if dff_filt['discarded'].iat[i] else '#000000'))
            #draw smooth lines
            dff_filt = dff_filt[~dff_filt['discarded']]
            dff_filt.sort_values(by='bandwidth_mean', inplace=True)
            x = dff_filt['bandwidth_mean']
            y = dff_filt['latency_mean']
            plot = sns.lineplot(x=x, y=y)
            print(x)
            ys = savgol_filter(y, 15, 4)
            plot = sns.lineplot(x=x, y=ys)
            #popt, _ = curve_fit(objective, x, y)
            #a, b, c, d = popt
            #x_line = arange(min(x), max(x), 1)
            #y_line = objective(x_line, a, b, c, d)
            #sns.lineplot(x=x_line, y=y_line)
            fig = plot.get_figure()
            plot.set_xlim([0, 40])
            plot.set_ylim([0, 1000])
            plot.set_xlabel('bandwidth [GB/s]')
            plot.set_ylabel('latency [ns]')
            plot.set_title(f'Bandwidth-Latency for rd_percentage = {rw}; showing all measurements and mean; error bars show min-max range')
            fig.set_size_inches([16,9])
            fig.tight_layout()
            pdf.savefig(fig)
            plt.close()


def main():
    if len(sys.argv) != 2:
        print('Usage: ' + sys.argv[0] + ' dir_name')
        exit()

    plot_bw_lat_analysis(sys.argv[1])
    #plot_bw_lat_analysis_filtered(sys.argv[1])


if __name__ == '__main__':
    main()
