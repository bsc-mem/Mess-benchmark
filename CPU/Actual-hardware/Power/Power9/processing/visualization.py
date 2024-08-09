import os
import pandas as pd
import matplotlib
import matplotlib.pyplot as plt
from matplotlib.backends.backend_pdf import PdfPages
import seaborn as sns
import numpy as np
from numpy import ones,vstack
from numpy.linalg import lstsq

fontSizeMess=34

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
    cmap = matplotlib.cm.get_cmap('Blues')
    # if '2133' in str(config):
    #     cmap = matplotlib.cm.get_cmap('Reds')
    # elif '2666' in str(config):
    #     cmap = matplotlib.cm.get_cmap('Blues')
    # else:
    #     cmap = matplotlib.cm.get_cmap('rainbow')
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
    max_bw = ax.get_xlim()[1]*(1/1.05)
    ax.axvline(x=max_bw, color=calculate_color(mem_cfg, 75), linewidth=2, linestyle=':')
    ax.text(x=max_bw, y=650, s=f'Max. theoretical BW = {int(max_bw)} GB/s', horizontalalignment='right')

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

def print_stream_values(ax, data_points, original_data_points_curve, config):

    x_points = []
    y_points = []
    rd_percentage_points = []
    name_list = ['stream', 'scale', 'add', 'triad']

    # print(data_points)

    # print(original_data_points_curve)

    rd_percentage_select=0

    i=0
    #  data points are (rd_percentege, bandwidth)
    for data_point in data_points:
        i= i + 1
        
        # if i==10000:
        #     break
        # print(i)
        # print(data_point)
        # print('rd_select', 'min_rd_', 'data[0]')
        # rd_percentage are in inceassing order
        for original_data_point_curve in original_data_points_curve:

            # max_rd_percentage = original_data_points_curve[original_data_point_curve]['rd_percentage_actual_mean'].max()
            min_rd_percentage = original_data_points_curve[original_data_point_curve]['rd_percentage_actual_mean'].mean()
            
            print(rd_percentage_select, min_rd_percentage, data_point[0])

            if rd_percentage_select==0:
                rd_percentage_select = original_data_point_curve
            
            if 100*min_rd_percentage < data_point[0]:
                rd_percentage_select = original_data_point_curve


        finalBW=0
        finalLat=0
        rd_percentage_points.append(rd_percentage_select)
        # print('rd_percentage_select is : ', rd_percentage_select)
        # bw are in decreasing order
        for bw,lat in zip(original_data_points_curve[rd_percentage_select]['bandwidth_mean'], original_data_points_curve[rd_percentage_select]['latency_mean']):
            
            # print(data_point[1], bw, lat, finalBW, finalLat)

            if finalBW==0:
                finalBW = bw
                finalLat = lat#/float(config['CPU_FREQ'])
            
            if bw > data_point[1]:
                finalBW = bw
                finalLat = lat#/float(config['CPU_FREQ'])


        
        x_points.append(data_point[1])
        y_points.append(finalLat)
        ax.plot(data_point[1], finalLat, "x", color='black', markersize=20, label=name_list[i-1])
    
    print(x_points)
    print(y_points)
    print(rd_percentage_points)
    # print(x_points, y_points)
    # ax.plot(x_points, y_points, "x", color='black', markersize=20)

    # ax.text(x=x_points[0]+3, y=y_points[0]-30, s=f'Stream results: \nCopy kernel = {float(x_points[0])} \nTriad kernel = {float(x_points[1])} GB/s', horizontalalignment='left')
    ax.text(x=x_points[1]-1, y=y_points[1]+30 , s='Copy \nScale', horizontalalignment='left', fontsize=15)

    ax.text(x=x_points[2]+3, y=y_points[2]-20, s='Add \nTriad', horizontalalignment='left', fontsize=15)

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

    # points_baseline = ax.plot(x_points_baseline, y_points_baseline, "o", color=color, alpha=0.05)

    # ax.plot(x_points_baseline, y_points_baseline, "x", color='black', markersize=fontSizeMess-3)
    ax.text(x=x_points_baseline[1]-17, y=y_points_baseline[1]+100 , s='Copy \nScale', horizontalalignment='left', fontsize=fontSizeMess-5)

    ax.text(x=x_points_baseline[2]+2, y=y_points_baseline[2]+100, s='Add \nTriad', horizontalalignment='left', fontsize=fontSizeMess-5)

    # Add dashed vertical lines
    for x, y in zip(x_points_baseline, y_points_baseline):
        ax.axvline(x=x, ymin=0, ymax=(180+y)/700, color='black', linestyle='--')

def final_curves(config, filepath, dfs_rw, bw_column='bandwidth_smooth', lat_column='latency_smooth', lat_unit='cycles', original_data_points=None):
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
    max_bw = int(config['MEM_MAX_CHANNELS'])*8*int(config['MEM_FREQ']) / 1000 #in MB/s
    max_lat = 0
    max_pol = []
    # for key, df in dfs_rw.items():
        # print(df, key)
        # print(df[lat_column])
        # max_pol.append(max(df[lat_column]))


    # max_lat = np.max(max_pol)



    plt.gca().set_xlim([0, 1.05*max_bw])
    plt.yticks(fontsize=fontSizeMess)
    plt.gca().set_ylim([0, 700])
    plt.xticks(fontsize=fontSizeMess)
    plt.rcParams['font.size'] = fontSizeMess


    ax.set_xlabel('Used Memory bandwidth [GB/s]', fontsize=fontSizeMess+3)
    ax.set_ylabel('Memory access latency [ns]', fontsize=fontSizeMess+3)

    mem_type = config['MEM_TYPE']
    mem_freq = config['MEM_FREQ']
    machine = config['NAME']
    cpu = config['CPU']

    plot_limit_line(ax, config)
    # make_custom_legend(ax, mem_type, mem_freq, list(dfs_rw.keys()))

    for rw, df in dfs_rw.items():
        # Convert latency to nanoseconds if necessary
        if lat_unit == 'cycles':
            df.loc[:, lat_column] = df[lat_column].apply(lambda lat : lat / float(config['CPU_FREQ']))
        plot = ax.plot(df[bw_column], df[lat_column], color=calculate_color(mem_freq, rw), linewidth=1)

    stream_data = []
    stream_data.append((66,58.8)) # copy
    stream_data.append((66,54.5)) # scale
    stream_data.append((75,61.3)) # add
    stream_data.append((75,61.3)) # triad
    # print_stream_values(ax, stream_data, original_data_points, config)
    print_application_data_points(ax, stream_data, dfs_rw, config, color='black')

    # ax.set_title(f'Bandwidth-Latency curves for {mem_type}-{mem_freq} on Power9 (8335-GTH)')
    fig.set_size_inches([16,9])
    fig.tight_layout()
    fig.savefig(filepath, bbox_inches='tight',pad_inches=0.0)
    plt.close()

    # make_custom_legend()


