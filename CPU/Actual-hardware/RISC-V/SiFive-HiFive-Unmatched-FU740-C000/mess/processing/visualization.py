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

import os
import pandas as pd
import matplotlib
import matplotlib.pyplot as plt
from matplotlib.backends.backend_pdf import PdfPages
import seaborn as sns
import numpy as np

def metric_per_pause(df, metric):
    if not metric in df.columns:
        print(f'Metric {metric} not found in columns of the provided data frame.')
    stats_dir = '.'
    try:
        df_pause_cutoff = pd.read_csv(os.path.join(stats_dir, 'pause_cutoff.csv'), index_col='rd_percentage')
    except:
        df_pause_cutoff = None

    rws = pd.unique(df['rd_percentage'])
    with PdfPages(os.path.join(stats_dir, f'{metric}_per_pause.pdf')) as pdf:
        for rw in rws:
            fig, ax = plt.subplots(1,1)
            dff = df[df['rd_percentage'] == rw]
            plot = sns.boxplot(data=dff, x='pause', y=metric)
            plot.set_xlabel('pause')
            plot.set_ylabel(f'{metric}')
            plot.set_title(f'{metric} per pause for rd_percentage = {rw}')
            fig.set_size_inches([16,9])
            fig.tight_layout()
            pdf.savefig(fig)
            plt.close()


# Returns a color based on provided configuration and read-write ratio
# The configuration needs to contain the memory frequency as this is used for color palette selection
def calculate_color(config, rw):
#    cmap = matplotlib.cm.get_cmap('rainbow')
    if '2133' in str(config):
        cmap = matplotlib.cm.get_cmap('Reds')
    elif '2666' in str(config):
        cmap = matplotlib.cm.get_cmap('Blues')
    else:
        cmap = matplotlib.cm.get_cmap('rainbow')
    min = 0.2
    max = 1
    factor = (100.0 - 0.0)/(max-min) #convert 50-100 interval to min-max
    rw_reverse = 75.0 + 75.0 - rw
    c = (rw_reverse - 50.0)/factor + min
    #c = (rw - 50.0)/factor + min
    return cmap(c)
    #return (c, c, c, 0.9)

def plot_limit_line(ax, mem_cfg):
    # I set the xlimit as the max_bw * 0.05 on the final_curves
    max_bw = ax.get_xlim()[1]/1.05
    ax.axvline(x=max_bw, color=calculate_color(mem_cfg, 75), linewidth=2, linestyle=':')
    ax.text(x=max_bw, y=750, s=f'Max. theoretical BW = {float(max_bw)} GB/s', horizontalalignment='right')

def make_custom_legend():
    yoffset = 0
    for mem_cfg in ['DDR4-2133', 'DDR4-2666']:
        legend_elements = [matplotlib.lines.Line2D([0], [0], color=calculate_color(mem_cfg, rw), lw=4, label='Line')
                for rw in [50, 100]] # TODO when profiling also for 0:48, change here
        leg = ax.legend(title=mem_cfg, handles=legend_elements, labels=['Rd:Wr 50:50', 'Rd:Wr 100:0'], ncol=3, bbox_to_anchor=[0.1, 1+yoffset], loc='upper center')
        ax.add_artist(leg)
        yoffset -= 0.1

def plot_stream_line(ax, mem_cfg):
    # I set the xlimit as the max_bw * 0.05 on the final_curves
    offset=30
    max_bw=244.88/2
    ax.axvline(x=max_bw, color='k', linewidth=1, linestyle=':')
    ax.text(x=max_bw, y=750, s=f'stream original bw (copy) = {float(max_bw)} GB/s', horizontalalignment='right')

    max_bw=249.48/2
    ax.axvline(x=max_bw, color='k', linewidth=1, linestyle=':')
    ax.text(x=max_bw, y=750-offset, s=f'stream counter bw (copy) = {float(max_bw)} GB/s', horizontalalignment='right')

    max_bw=248.08/2
    ax.axvline(x=max_bw, color='k', linewidth=1, linestyle=':')
    ax.text(x=max_bw, y=750-offset-offset, s=f'stream original bw (triad) = {float(max_bw)} GB/s', horizontalalignment='right')

    max_bw=248.73/2
    ax.axvline(x=max_bw, color='k', linewidth=1, linestyle=':')
    ax.text(x=max_bw, y=750-offset-offset-offset, s=f'stream counter bw (triad) = {float(max_bw)} GB/s', horizontalalignment='right')


def final_curves(config, filepath, dfs_rw, bw_column='bandwidth_smooth', lat_column='latency_smooth', lat_unit='cycles'):
    """ Plots curves and saves the plot in a file with the provided name

        Parameters:
        config (dictionary) - configuration
        filepath (string) - absolute path to the file where plot is saved
        dfs_rw (dictionary) - maps rd_percentage to corresponding DataFrame
        bw_column (string) - column used for bandwidth in provided dataframe (default: bandwidth_smooth)
        lat_column (string) - column used for latency in provided dataframe (default: latency_smooth)
        lat_unit (string) - unit of latency (supported: 'ns', 'cycles'; default: 'ns'). Perf output is on cycles.

        Returns:
        nothing

    """
    print("\n\n***************** in visualization function\n\n")
    # print(dfs_rw)



    fig, ax = plt.subplots(1,1)

    # Find bandwidth and latency max values to automatically set the limits
    # TODO rn the max latency is set manually because of the image size in inches
    # TODO: change it to get automatically the number of installed DIMMs (might change)
    max_bw = int(config['MEM_MAX_CHANNELS'])*8*int(config['MEM_FREQ']) / 1000 #in GB/s
    max_lat = 0
    max_pol = []
    # for key, df in dfs_rw.items():
        # print(df, key)
        # print(df[lat_column])
        # max_pol.append(max(df[lat_column]))
    

    # max_lat = np.max(max_pol)



    plt.gca().set_xlim([0, 1.05*max_bw])
    #plt.gca().set_ylim([0, 1.1*max_lat])
    plt.gca().set_ylim([0, 800])

    ax.set_xlabel('bandwidth [GB/s]')
    ax.set_ylabel('latency [ns]')
    mem_type = config['MEM_TYPE']
    mem_freq = config['MEM_FREQ']
    machine = config['NAME']
    cpu = config['CPU']

    plot_limit_line(ax, config)
    # plot_stream_line(ax, config)

    for rw, df in dfs_rw.items():
        # Convert latency to nanoseconds if necessary
        if lat_unit == 'cycles':
            df.loc[:, lat_column] = df[lat_column].apply(lambda lat : lat / float(config['CPU_FREQ']))
        plot = ax.plot(df[bw_column], df[lat_column], color=calculate_color(mem_freq, rw), linewidth=1)

    ax.set_title(f'Bandwidth-Latency curves for {mem_type}-{mem_freq} on HiFive Unmatched ({cpu})')
    fig.set_size_inches([16,9])
    fig.tight_layout()
    fig.savefig(filepath)
    plt.close()

    # make_custom_legend()


