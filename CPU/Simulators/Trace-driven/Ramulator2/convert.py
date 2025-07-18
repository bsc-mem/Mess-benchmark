
import os
import pandas as pd
import matplotlib
import matplotlib.pyplot as plt
from matplotlib.backends.backend_pdf import PdfPages
import seaborn as sns
import numpy as np
import corrections
from numpy import ones,vstack
from numpy.linalg import lstsq

import csv


def find(s, el):
    for i in s.index:
        if s[i] == el: 
            return i
    return None

# Returns a color based on provided configuration and read-write ratio
# The configuration needs to contain the memory frequency as this is used for color palette selection
def calculate_color(rw,mode=0):
    cmap = matplotlib.cm.get_cmap('Blues')

    if mode:
        cmap = matplotlib.cm.get_cmap('Reds')

    min = 0.2
    max = 1
    factor = (100.0 - 0.0)/(max-min) #convert 50-100 interval to min-max
    rw_reverse = 75.0 + 75.0 - rw
    c = (rw_reverse - 50.0)/factor + min
    #c = (rw - 50.0)/factor + min
    return cmap(c)
    #return (c, c, c, 0.9)


def plot_limit_line(ax):
    # I set the xlimit as the max_bw * 0.05 on the final_curves
    max_bw = ax.get_xlim()[1]*(1/1.05)
    ax.axvline(x=max_bw, color=calculate_color(75), linewidth=4, linestyle=':')
    ax.text(x=max_bw, y=450, s=f'Max. theoretical BW = {round(max_bw)} GB/s', horizontalalignment='right')

def make_custom_legend(ax, mem_type, mem_freq, rw_list):
    yoffset = 0
    # ' - '.join([mem_type, mem_freq])
    for mem_cfg in [' - '.join([mem_type, mem_freq])]:
        legend_elements = [matplotlib.lines.Line2D([0], [0],
            color=calculate_color(rw), lw=4, label='Line') for
            rw in [0, 100]] # TODO when profiling also for 0:48, change here
        leg = ax.legend(handles=legend_elements, labels=['CXL: Rd:Wr 0:100', 'Rd:Wr 100:0'], ncol=3, bbox_to_anchor=[0.2, 1+yoffset], loc='upper center')
        ax.add_artist(leg)
    # for mem_cfg in [' - '.join([mem_type, mem_freq])]:
    #     legend_elements = [matplotlib.lines.Line2D([0], [0],
    #         color=calculate_color(rw,1), lw=4, label='Line') for
    #         rw in [50, 100]] # TODO when profiling also for 0:48, change here
    #     leg = ax.legend(handles=legend_elements, labels=['Sim: Rd:Wr 50:50', 'Rd:Wr 100:0'], ncol=3, bbox_to_anchor=[0.2, 0.94+yoffset], loc='upper center')
    #     ax.add_artist(leg)
    
def print_application_data_points(ax, data_points_baseline, curves, color):
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

    ax.plot(x_points_baseline, y_points_baseline, "x", color='black', markersize=20)
    ax.text(x=x_points_baseline[1]+.5, y=y_points_baseline[1]-49 , s='Copy \nScale', horizontalalignment='left', fontsize=15)

    ax.text(x=x_points_baseline[2]-1.5, y=y_points_baseline[2]+25, s='Add \nTriad', horizontalalignment='left', fontsize=15)

    # return points_baseline



df = pd.read_csv('results.csv')


print(df)



rws = pd.unique(df['rw_ratio'])

# print(rws)



df.sort_values(by=['pause'], inplace=True)


# print(df['bandwidth'].max())




# devide based on rw ratio
df_rws = {}
for rd_percentage in rws:
        df_rws[rd_percentage] = df[df['rw_ratio'] == rd_percentage].reset_index(drop=True)
        # print(df_rws[rd_percentage])

dfs_rw = corrections.smooth_curves(df_rws)
df_rws = corrections.smooth_curves(df_rws)

# print(df_rws[100])

tmpMin = []
tmpMax = []
for df_rw in dfs_rw:
    if df_rw>40:
        tmpMin.append(dfs_rw[df_rw]['latency_smooth'].min()) 
        tmpMax.append(dfs_rw[df_rw]['bandwidth_smooth'].max())

# lead off hard coded
# leadOffLatency = 19
leadOffLatency= min(tmpMin)
maximumBandwidth= max(tmpMax)
print ("max bw: ", maximumBandwidth, 8*maximumBandwidth/307)
print("lead off latency: ", leadOffLatency)

# print("tmpMin: ", tmpMin)

latencyThreshhold = leadOffLatency*2
bandwidthMin = []
for df_rw in dfs_rw:
    if df_rw>40:
        mylist = (dfs_rw[df_rw]['latency_smooth'],dfs_rw[df_rw]['bandwidth_smooth'])
        tmplist = [x for x in mylist[0] if x>latencyThreshhold]
        myIndex = find(mylist[0], tmplist[-1]) 
        bandwidthMin.append(mylist[1][myIndex])

max_bw = 307 #in GB/s
print('min saturate bw', min(bandwidthMin), ' ' , min(bandwidthMin)/max_bw)
tmpMax = []
for df_rw in dfs_rw:
    if df_rw>40:
        tmpMax.append(dfs_rw[df_rw]['latency_smooth'].max()) 
    # print("minimum lat of diff r/w ratio", dfs_rw[df_rw]['latency_smooth'].min())

print('max max latency is ', max(tmpMax))
print('max min latency is ', min(tmpMax))

print("\n\n***************** visualization...\n\n")

fig, ax = plt.subplots(1,1)

# max_bw = 307
max_lat = 0
max_pol = []

plt.gca().set_xlim([0, 1.05*max_bw])
plt.yticks(fontsize=38)
plt.gca().set_ylim([0, 500])
plt.xticks(fontsize=38)
plt.rcParams['font.size'] = 38


# ax.set_xlabel('Used CXL interface bandwidth [GB/s]', fontsize=38)
# ax.set_ylabel('CXL device memory \n access latency [ns]', fontsize=38)
ax.set_xlabel('Used Memory bandwidth [GB/s]', fontsize=38)
ax.set_ylabel('Memory access latency [ns]', fontsize=38)
mem_type = 'CXL'
mem_freq = 'xxx'
machine = 'CXL Host'
cpu = 'NaN'

bw_column = 'bandwidth'
lat_column = 'latency'

plot_limit_line(ax)

# creat legend
# make_custom_legend(ax, mem_type, mem_freq, list(df_rws.keys()))

filepath='./output.pdf'

bw_column2 = 'bandwidth_smooth'
lat_column2 = 'latency_smooth'

for rw, df in df_rws.items():

    # if os.path.exists("./simOut/"+ "sim_bwlat_" + str(rw) + ".txt"):
    #     # df_rws_sim = pd.read_csv("./simOut/"+ "sim_bwlat_" + str(rw) + ".txt")
    #     f2 = open("./simOut/"+ "sim_bwlat_" + str(rw) + ".txt", 'r')
    #     lines = f2.readlines()
    #     print(lines)
    #     x = []
    #     y = []
    #     for line in lines:
    #         p = line.split()
    #         x.append(float(p[0]))
    #         y.append(float(p[1]))

    #     print(x)
    #     print(y)
    #     plot = ax.plot(x, y, color=calculate_color(rw,1), linewidth=1)


    # LLC latency is 27 ns
    if rw > 4:
    #     if rw%4==0:
            
        # plot = ax.plot(df[bw_column], df[lat_column], color=calculate_color(rw), linewidth=1)
        plot = ax.plot(df[bw_column2]*8, df[lat_column2]*(1/2.4), color=calculate_color(rw), linewidth=1)

        # plot = ax.plot(df[bw_column], df[lat_column], color=calculate_color(rw), linewidth=1)
        # plot = ax.plot(df[bw_column], df[lat_column]+27, color=calculate_color(rw), linewidth=1)
    
    # pd.DataFrame({'a':df[bw_column]*1000, 'b':(df[lat_column]+27)*2.3}).to_csv(f'bwlat_{rw}.txt', index=False, header=False, sep='\t')
    # pd.DataFrame({'a':df[bw_column]*1000, 'b':(df[lat_column]+27)*2.1}).to_csv(f'bwlat_{rw}.txt', index=False, header=False, sep='\t')

stream_data = []
stream_data.append((50,245.9193951/8)) # copy
stream_data.append((50,236.6837924/8)) # scale
stream_data.append((66,245.94/8)) # add
stream_data.append((66,246.93/8)) # triad

# print_application_data_points(ax, stream_data, dfs_rw, color='black')

# ax.set_title(f'Bandwidth-Latency curves for CXL Host to Memory Over CXL')
# ax.set_title(f'Bandwidth-Latency curves for Core to Memory Over CXL')
fig.set_size_inches([16,9])
fig.tight_layout()
fig.savefig(filepath)
plt.close()
