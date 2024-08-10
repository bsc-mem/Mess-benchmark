#!/usr/bin/env python3
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

def main():
    argv = sys.argv
    if len(argv) < 2:
        print('usage ' + argv[0] + ' working_dir')
        exit()

    working_dir = os.path.abspath(argv[1])
    output_dir = os.path.join(working_dir, 'output/')

    with open(os.path.join(working_dir, 'config.sh')) as f:
        config = dict(x.rstrip().split("=", 1) for x in f)
    # print(config)

    

    # process BW
    bw_parser = parse.Parser('bandwidth', os.path.join(working_dir, 'bw-lat'), config)    
    df_bw_raw = bw_parser.process()
    # ask valeria what is this doing...
    visualization.metric_per_pause(df_bw_raw, 'bandwidth')
    df_bw_mean = calculator.MeanCalculator.calculate(df_bw_raw, 'bandwidth')


    # process LAT
    lat_parser = parse.Parser('latency', os.path.join(working_dir, 'bw-lat'), config)
    df_lat_raw = lat_parser.process()
    visualization.metric_per_pause(df_lat_raw, 'latency')
    df_lat_mean = calculator.MeanCalculator.calculate(df_lat_raw, 'latency')


    

    # merge BW and LAT dataframes
    df = df_bw_mean.merge(df_lat_mean)

 

    # The dataframe is split by read-write ratio to facilitate furher processing steps
    # The map translates rd_percentage to the corresponding dataframe (part of the original dataframe)
    dfs_rw = utils.split_dataframe_by_rd_percentage(df)

    # quick fix of something i dont understand yet
    # df = dfs_rw
    # Remove outliers
    # TODO (an important TODO...)

    # Smoothen the curves
    # dfs_rw = corrections.smooth_curves(config, dfs_rw)
    
    # Save curves into files
    # utils.save_curves_to_file(config, os.path.join(output_dir, 'curves'), dfs_rw)

    # Merge into the final dataframe
    # df = utils.merge_dataframes(list(dfs_rw.values()))

    # save the final dataframe
    # df.to_csv(os.path.join(output_dir, 'bandwidth-latency.csv'), index=False)


    visualization.final_curves(config, os.path.join(output_dir, 'bandwidth-latency.pdf'), dfs_rw, lat_column='latency_mean', bw_column='bandwidth_mean', lat_unit='ns')



if __name__ == '__main__':
    main()

