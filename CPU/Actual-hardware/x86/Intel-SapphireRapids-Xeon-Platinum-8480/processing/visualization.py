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


import os
import pandas as pd
import matplotlib
import matplotlib.pyplot as plt
from matplotlib.backends.backend_pdf import PdfPages
# import seaborn as sns
import numpy as np
from numpy import ones,vstack
from numpy.linalg import lstsq

fontSizeMess=34
# def metric_per_pause(df, metric):
#     if not metric in df.columns:
#         print(f'Metric {metric} not found in columns of the provided data frame.')
#     stats_dir = '.'
#     try:
#         df_pause_cutoff = pd.read_csv(os.path.join(stats_dir, 'pause_cutoff.csv'), index_col='rd_percentage')
#     except:
#         df_pause_cutoff = None

#     rws = pd.unique(df['rd_percentage'])
#     with PdfPages(os.path.join(stats_dir, f'{metric}_per_pause.pdf')) as pdf:
#         for rw in rws:
#             fig, ax = plt.subplots(1,1)
#             dff = df[df['rd_percentage'] == rw]
#             plot = sns.boxplot(data=dff, x='pause', y=metric)
#             plot.set_xlabel('pause')
#             plot.set_ylabel(f'{metric}')
#             plot.set_title(f'{metric} per pause for rd_percentage = {rw}')
#             fig.set_size_inches([16,9])
#             fig.tight_layout()
#             pdf.savefig(fig)
#             plt.close()


# Returns a color based on provided configuration and read-write ratio
# The configuration needs to contain the memory frequency as this is used for color palette selection
def calculate_color(config, rw, rw_list=None):
#    cmap = matplotlib.cm.get_cmap('rainbow')
    if 'MemMode' in str(config):
        cmap = matplotlib.cm.get_cmap('Greens')
    elif 'DDR' in str(config):
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

def plot_limit_line(ax, max_bw_dram, mem_cfg):
    if max_bw_dram != 0:
        ax.axvline(x=max_bw_dram, color=calculate_color(mem_cfg, 75), linewidth=2, linestyle=':')
        ax.text(x=max_bw_dram, y=650, s=f'Max. theoretical BW = {int(max_bw_dram)} GB/s', horizontalalignment='right')

def make_custom_legend(ax, mem_type, mem_freq, rw_list):
    yoffset = 0
    # ' - '.join([mem_type, mem_freq])
    #for mem_cfg in ['DDR4 AppDirect - 2666']:
    for mem_cfg in [' - '.join([mem_type, mem_freq])]:
        legend_elements = [matplotlib.lines.Line2D([0], [0],
            color=calculate_color(mem_cfg, rw), lw=4, label='Line') for
            rw in [50, 100]] # TODO when profiling also for 0:48, change here
        # leg = ax.legend(title=mem_cfg, handles=legend_elements, labels=['Rd:Wr 50:50', 'Rd:Wr 100:0'], ncol=3, bbox_to_anchor=[0.2, 1+yoffset], loc='upper center')
        leg = ax.legend(handles=legend_elements, labels=['Rd:Wr 50:50', 'Rd:Wr 100:0'], ncol=3, bbox_to_anchor=[0.25, 1+yoffset], loc='upper center', fontsize=22)
        ax.add_artist(leg)
        yoffset -= 0.1


def print_application_data_points(ax, data_points_baseline, curves, config, color):
    x_points_baseline = []
    y_points_baseline = []
    for row in data_points_baseline:
        # row[1] represents the rd_percentage of each sample of the application
        # and it is used to find the proper curve in the memory profiling
        rd_percentage = int(round(row[0]/2))*2
        if rd_percentage < 50:
            rd_percentage = 50
        curve = np.asarray(curves[rd_percentage]['bandwidth_smooth'])
        i = len(curves[rd_percentage]['bandwidth_smooth'])-1

        while i >= 0 and curves[rd_percentage]['bandwidth_smooth'].iloc[i] < row[1]:
            i -= 1

        x1 = curves[rd_percentage]['bandwidth_smooth'].iloc[i]
        y1 = curves[rd_percentage]['latency_smooth'].iloc[i]
        x2 = curves[rd_percentage]['bandwidth_smooth'].iloc[i+1]
        y2 = curves[rd_percentage]['latency_smooth'].iloc[i+1]
        points = [(x1,y1),(x2,y2)]
        x_coords, y_coords = zip(*points)
        A = vstack([x_coords,ones(len(x_coords))]).T
        m, c = lstsq(A, y_coords, rcond=None)[0]
        # print("Line Solution is y = {m}x + {c}".format(m=m,c=c))

        latency = (m*row[1])+c


        x_point = row[1]
        y_point = latency

        x_points_baseline.append(x_point)
        y_points_baseline.append(y_point)

        print('max bandwidth for this specific rd_wr ratio:', curves[rd_percentage]['bandwidth_smooth'].max(), 'diff is: ', curves[rd_percentage]['bandwidth_smooth'].max()-row[1])

    # points_baseline = ax.plot(x_points_baseline, y_points_baseline, "o", color=color, alpha=0.05)

    # ax.plot(x_points_baseline, y_points_baseline, "x", color='black', markersize=fontSizeMess-3)
    ax.text(x=x_points_baseline[1]-30, y=y_points_baseline[1]+60, s='Copy \nScale', horizontalalignment='left', fontsize=fontSizeMess-5)

    ax.text(x=x_points_baseline[2]-27, y=y_points_baseline[2]+200, s='Add \nTriad', horizontalalignment='left', fontsize=fontSizeMess-5)

    # Add dashed vertical lines
    for x, y in zip(x_points_baseline, y_points_baseline):
        if x<200:
            ax.axvline(x=x, ymin=0, ymax=(140+y)/700, color='black', linestyle='--')
        else:
            ax.axvline(x=x, ymin=0, ymax=(290+y)/700, color='black', linestyle='--')

    # return points_baseline


def final_curves(config, filepath, dfs_rw, bw_column='bandwidth_smooth', lat_column='latency_smooth', lat_unit='ns'):
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
    max_bw_dram = int(config['DRAM_MAX_CHANNELS'])*8*int(config['DRAM_FREQ']) / 1000 #in GB/s
    # Set plot sizes
    plt.gca().set_xlim([0, 1.05*max_bw_dram])
    plt.yticks(fontsize=fontSizeMess)
    plt.gca().set_ylim([0, 700])
    plt.xticks(fontsize=fontSizeMess)
    plt.rcParams['font.size'] = fontSizeMess
    ax.set_xlabel('Used Memory bandwidth [GB/s]', fontsize=fontSizeMess+3)
    ax.set_ylabel('Memory access latency [ns]', fontsize=fontSizeMess+3)
    # Get experiment parameters
    mem_type = config['MEM_TYPE'].replace("\"", "")
    mem_freq = config['DRAM_FREQ']
    machine = config['NAME']
    cpu = config['CPU'].replace("\"", "")
    # Add plot details
    plot_limit_line(ax, max_bw_dram, config)
    # make_custom_legend(ax, mem_type, mem_freq, list(dfs_rw.keys()))

    print(list(dfs_rw.keys()))
    for rw, df in dfs_rw.items():
        #if rw in range(15, 17):
        df[bw_column] = df[bw_column].div(1000)
        if lat_unit == 'cycles':
            #df.loc[:, lat_column] = df[lat_column].apply(lambda lat : lat / float(config['CPU_FREQ']))
            df[lat_column] = df[lat_column].div(df.measured_frequency)
            #print(f'{df[lat_column]} and {df[bw_column]}')
        plot = ax.plot(np.array(df[bw_column]), np.array(df[lat_column]), color=calculate_color(mem_type, rw, list(dfs_rw.keys())), linewidth=1)

    stream_data = []
    stream_data.append((50,196)) # copy
    stream_data.append((50,192)) # scale
    stream_data.append((66,202)) # add
    stream_data.append((66,204)) # triad
    # print_stream_values(ax, stream_data, original_data_points, config)
    print_application_data_points(ax, stream_data, dfs_rw, config, color='black')

    #ax.set_title(f'Bandwidth-Latency curves for {mem_type}-{mem_freq} on {machine} ({cpu})')
    fig.set_size_inches([16,9])
    fig.tight_layout()
    fig.savefig(filepath, bbox_inches='tight',pad_inches=0.0)

    plt.close()

