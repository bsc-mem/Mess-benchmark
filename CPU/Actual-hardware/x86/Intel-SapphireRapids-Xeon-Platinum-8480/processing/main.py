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
import os.path
import pandas as pd
import numpy as np
import toml
import calculator
import corrections
import parse
import utils
import visualization
from corrections import adjust_rw_ratios_bandwidth_df, adjust_rw_ratios_latency_df

def main():
    argv = sys.argv
    if len(argv) < 2:
        print('usage ' + argv[0] + ' working_dir')
        exit()

    working_dir = os.path.abspath(argv[1])
    output_dir = os.path.join(working_dir, 'output/')

    with open(os.path.join(working_dir, 'config.sh')) as f:
        config = dict(x.rstrip().split("=", 1) for x in f)

    # process BW
    bw_parser = parse.Parser('bandwidth', os.path.join(working_dir, 'bw'), config)
    df_bw_raw = bw_parser.parse()
    df_bw_raw, rws_mappings = adjust_rw_ratios_bandwidth_df(df_bw_raw)
    df_bw_raw = calculator.BandwidthCalculator.calculate(df_bw_raw, config)
    # visualization.metric_per_pause(df_bw_raw, 'bandwidth')
    dfs_bw_raw = utils.split_dataframe_by_rd_pause_percentage(df_bw_raw)
    dfs_bw_raw = utils.discard_outliers(dfs_bw_raw, 'bandwidth')
    df_bw_raw = utils.merge_dataframes(dfs_bw_raw)
    
    df_bw_mean = calculator.MeanCalculator.calculate(df_bw_raw, 'bandwidth')

    # process LAT
    lat_parser = parse.Parser('latency', os.path.join(working_dir, 'lat'), config)
    df_lat_raw = lat_parser.parse()
    df_lat_raw = adjust_rw_ratios_latency_df(df_lat_raw, rws_mappings)
    df_lat_raw = calculator.LatencyCalculator.calculate(df_lat_raw, config)
    # visualization.metric_per_pause(df_lat_raw, 'latency')
    dfs_lat_raw = utils.split_dataframe_by_rd_pause_percentage(df_lat_raw)
    dfs_lat_raw = utils.discard_outliers(dfs_lat_raw, 'latency')
    df_lat_raw = utils.merge_dataframes(dfs_lat_raw)

    df_lat_mean = calculator.MeanCalculator.calculate(df_lat_raw, 'latency')

    # merge BW and LAT dataframes
    df = df_bw_mean.merge(df_lat_mean)
    df = df[(df['rd_percentage'] != 8) & (df['rd_percentage'] != 16) & (df['rd_percentage'] != 18)]

    # The dataframe is split by read-write ratio to facilitate furher processing steps
    # The map translates rd_percentage to the corresponding dataframe (part of the original dataframe)
    dfs_rw = utils.split_dataframe_by_rd_percentage(df)

    # Smoothen the curves
    dfs_rw = corrections.smooth_curves(config, dfs_rw)

    #  processing data for saturate bw range and max latency range 

    # measure lead-off latency
    tmpMin = []
    tmpBWmaxMess = []
    
    for df_rw in dfs_rw:
        tmpMin.append(dfs_rw[df_rw]['latency_smooth'].min()) 
        tmpBWmaxMess.append(dfs_rw[df_rw]['bandwidth_smooth'].max()/1000) # bandwidth is in MB per seconds !!!
    
    

    leadOffLatency= min(tmpMin)
    print('lead off latency is ', leadOffLatency)
    latencyThreshhold = leadOffLatency*2

    # max theoritical bandwidth
    max_bw = int(config['DRAM_MAX_CHANNELS'])*8*int(config['DRAM_FREQ']) / 1000 #in GB/s

    print('max Mess bw is ', max(tmpBWmaxMess), max(tmpBWmaxMess)/max_bw)

    # calculate min saturated bandwidth
    bandwidthMin = []
    for df_rw in dfs_rw:
        mylist = (dfs_rw[df_rw]['latency_smooth'],dfs_rw[df_rw]['bandwidth_smooth'])
        tmplist = [x for x in mylist[0] if x>latencyThreshhold]
        myIndex = find(mylist[0], tmplist[-1]) 
        bandwidthMin.append(mylist[1][myIndex]/1000) # bandwidth is in MB per seconds !!! 
    print('min saturate bw', min(bandwidthMin), ' ' , min(bandwidthMin)/max_bw)
    tmpMax = []
    for df_rw in dfs_rw:
        tmpMax.append(dfs_rw[df_rw]['latency_smooth'].max()) 

    print('max max latency is ', max(tmpMax))
    print('max min latency is ', min(tmpMax))


    # Remove duplicated data points
    #dfs_rw = corrections.remove_double_lat_points(dfs_rw)

    # Save curves into files
    # uti
    # ls.save_curves_to_file(config, os.path.join(output_dir, 'curves'), dfs_rw)

    # Merge into the final dataframe
    df = utils.merge_dataframes(list(dfs_rw.values()))

    # save the final dataframe
    df.to_csv(os.path.join(output_dir, 'bandwidth-latency.csv'), index=False)

    visualization.final_curves(config, os.path.join(output_dir, 'bandwidth-latency.pdf'), dfs_rw)

def find(s, el):
    for i in s.index:
        if s[i] == el: 
            return i
    return None

if __name__ == '__main__':
    main()

