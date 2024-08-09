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


import sys
import os
import os.path
import pandas as pd
import matplotlib
import matplotlib.pyplot as plt
from matplotlib.backends.backend_pdf import PdfPages
import seaborn as sns
import numpy as np
import utils

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
def calculate_color(config, rw, rw_list=None):
    if 'AppDirect' in str(config):
        cmap = matplotlib.cm.get_cmap('Greens')
    elif 'blacks' in str(config):
        cmap = matplotlib.cm.get_cmap('Greys')
    elif 'optane' in str(config):
        cmap = matplotlib.cm.get_cmap('Blues')
    else:
        cmap = matplotlib.cm.get_cmap('Reds')

    if rw_list is None:
        c = 0.8
    else:
        min_val = 0.2
        max_val = 1
        n_curves = len(rw_list)
        dist = (max_val - min_val) / n_curves # finds the color distance between each curve considering the number of curves we want to plot
        rw_pos = np.where(np.array(rw_list) == rw)[0][0] # position of the curve in the set of distances
        c = (n_curves - rw_pos) * dist + min_val

    return cmap(c)

def plot_limit_line(ax, max_bw_dram, max_bw_optane, mem_cfg):
    if max_bw_dram != 0:
        ax.axvline(x=max_bw_dram, color=calculate_color('optane', 75), linewidth=2, linestyle=':')
        ax.text(x=max_bw_dram, y=2000, s=f'Max. theoretical BW - DRAM = {int(max_bw_dram)} mb/s', horizontalalignment='right', fontsize=11)

    #if max_bw_optane != 0:
    #    ax.axvline(x=int(max_bw_optane), color=calculate_color('DDR4', 75), linewidth=2, linestyle=':')
    #    ax.text(x=int(max_bw_optane), y=950, s=f'Max. theoretical BW - Optane = {int(max_bw_optane)} MB/s', horizontalalignment='right')

def make_custom_legend(ax, mem_type, mem_freq):
    yoffset = 0
    # ' - '.join([mem_type, mem_freq])
    #for mem_cfg in ['DDR4 AppDirect - 2666']:
    for mem_cfg in [' - '.join([mem_type, mem_freq])]:
        legend_elements = [matplotlib.lines.Line2D([0], [0],
            color=calculate_color(curve, 75), lw=4, label='Line') for curve in
            ['AppDirect', 'blacks', 'optane', 'dram']] # TODO when profiling also for 0:48, change here
        leg = ax.legend(title='Memory Mode (MM) and AppDirect (AP) (bandwidth stress level) (Rd:Wr 50-100)', fontsize=11, handles=legend_elements,
                labels=['Optane-AD (Optane)', 'Optane-MM (Optane)', 'Optane-MM (DRAM)', 'DRAM-MM (DRAM)'], ncol=4,
                bbox_to_anchor=[0.5, 1+yoffset], loc='upper center')
        plt.setp(leg.get_title(), fontsize=11)
        ax.add_artist(leg)
        yoffset -= 0.1

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

    fig, ax = plt.subplots(1,1)

    # Find bandwidth and latency max values to automatically set the limits
    # TODO rn the max latency is set manually because of the image size in inches
    max_bw_dram = int(config['DRAM_MAX_CHANNELS'])*8*int(config['DRAM_FREQ']) #in MB/s
    #max_bw_optane = int(config['OPTANE_MAX_CHANNELS'])*8*int(config['OPTANE_FREQ']) #in MB/s
    max_bw_optane = 1*8*int(config['DRAM_FREQ']) #in MB/s
    max_bw = max(max_bw_dram, max_bw_optane)
    max_lat = 0
    max_pol = []
    #for key, df in dfs_rw.items():
    #    max_pol.append(max(df[lat_column]))
    #max_lat = np.max(max_pol)

    plt.gca().set_xlim([0, 1.05*max_bw_dram])
    #plt.gca().set_xscale('log')
    #plt.gca().set_ylim([0, 1.1*max_lat])
    plt.gca().set_ylim([0, 2500])

    ax.tick_params(axis='both', labelsize=12)
    ax.set_xlabel('Bandwidth [MB/s]', fontsize=12)
    ax.set_ylabel('Latency [ns]', fontsize=12)
    mem_type = config['MEM_TYPE'].replace("\"", "")
    mem_freq = config['DRAM_FREQ'] if 'DDR4' in str(mem_type) else config['OPTANE_FREQ']
    machine = config['NAME']
    cpu = config['CPU'].replace("\"", "")

    plot_limit_line(ax, max_bw_dram, max_bw_optane, config)
    make_custom_legend(ax, mem_type, mem_freq)

    for df_dict in dfs_rw:
        for rw, df in df_dict.items():
            # Convert latency to nanoseconds if necessary
            if lat_unit == 'cycles':
                #df.loc[:, lat_column] = df[lat_column].apply(lambda lat : lat / float(config['CPU_FREQ']))
                df[lat_column] = df[lat_column].div(df.frequency)
                #if df[lat_column].max() > 1000:
                #    print(rw)
            plot = ax.plot(np.array(df[bw_column]), np.array(df[lat_column]),
                    color=calculate_color(df['type'][0], rw, list(df_dict.keys())), linewidth=1)

    #ax.set_title(f'Bandwidth-Latency curves for {mem_type}-{mem_freq} on {machine} ({cpu})')
    ax.set_title(f'Bandwidth-Latency curves comparing DRAM and Optane in {machine} ({cpu})', fontsize=12)
    fig.set_size_inches([16,9])
    fig.tight_layout()
    fig.savefig(filepath)
    plt.close()

def main():
    dfs = []

    for dir in sys.argv[1:]:
        working_dir = os.path.abspath(dir)
        output_dir = os.path.join(working_dir, 'output/')

        with open(os.path.join(working_dir, 'config.sh')) as f:
            config = dict(x.rstrip().split("=", 1) for x in f)
        #dfs[str(sys.argv.index(dir)-1)] = []
        #dfs[str(sys.argv.index(dir)-1)].append(config)

        df = pd.read_csv(os.path.join(output_dir, 'bandwidth-latency.csv'))
        dfs.append(df)
        print(pd.unique(df['rd_percentage']))

    # The dataframe is split by read-write ratio to facilitate furher processing steps
    # The map translates rd_percentage to the corresponding dataframe (part of the original dataframe)
    dfs_rw = []
    for df in dfs:
        dfs_rw.append(utils.split_dataframe_by_rd_percentage(df))

    #rw_percentage = [50, 52, 54, 56, 58, 60, 62, 64, 66, 68, 70, 72, 74, 76, 78, 80]
    #for df in dfs_rw:
    #    for rw in rw_percentage:
    #        df.pop(rw)
    rw_percentage = [50, 60]
    for rw in rw_percentage:
        dfs_rw[1].pop(rw)


    #                          *                 *
    # 67 68 68 70 70 71 73 75 75 78 80 80 82 84 84 87 88 90 90 93 93 98 100
    #rw_percentage1 = [50, 67, 68, 69, 70, 71, 72, 73, 74, 75, 77, 78, 79, 80, 81, 83, 84, 85, 87, 88, 90, 92, 93, 95, 97, 100]
    rw_percentage1 = [68, 70, 72, 74, 77, 79, 81, 84, 87, 90, 93, 97]
    for rw in rw_percentage1:
        dfs_rw[3].pop(rw)
    #for rw, df in dfs_rw[0].items():
    #    df['type'] = 'new'

    #rw_percentage2 = [50, 60]
    #for rw in rw_percentage2:
    #    dfs_rw[3].pop(rw)

    final_curves(config, os.path.join('./', 'bandwidth-latency.pdf'), dfs_rw)


if __name__ == '__main__':
    main()
