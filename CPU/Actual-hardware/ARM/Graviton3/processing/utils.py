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
from collections import defaultdict
import numpy as np
from scipy import stats


def split_dataframe_by_rd_percentage(df):
    """ Returns a map of read-write ratio -> corresponding sub-dataframe

        The function preserves the columns from input dataframe

        Parameters:
        df (pandas DataFrame) - input dataframe

        Returns:
        dictionary - mapping read-write ratio to corresponding sub-DataFrame

    """
    rws = pd.unique(df['rd_percentage'])
    df_rws = {}
    for rd_percentage in rws:
        df_rws[rd_percentage] = df[df['rd_percentage'] == rd_percentage].reset_index(drop=True)
    return df_rws

def split_dataframe_by_rd_pause_percentage(df):
    """ Returns a map of read-write ratio -> corresponding sub-dataframe

        The function preserves the columns from input dataframe

        Parameters:
        df (pandas DataFrame) - input dataframe

        Returns:
        dictionary - mapping read-write ratio to corresponding sub-DataFrame

    """
    rws = pd.unique(df['rd_percentage'])
    pauses = pd.unique(df['pause'])

    # df_rws = {}
    df_rws = defaultdict(dict)
    for rd_percentage in rws:
        for pause in pauses:
            df_temp = df[(df['rd_percentage'] == rd_percentage)]
            df_rws[str(rd_percentage)+str(pause)] = df_temp[(df['pause'] == pause)]



    return df_rws

def remove_outliers(df,col,n_std): 
    mean = df[col].mean()
    sd = df[col].std()
    # if(sd>100):
    #     print(sd)
    #     print(mean)
    #     print(df)
    #     print(df[col])
    df = df[(df[col] <= mean+(n_std*sd))]
    df = df[(df[col] >= mean-(n_std*sd))]
    
    # if(sd>100):
    #     print(df)
  
    return df


def discard_outliers(dfs,typeOfData):
    """ discard outliers 

        Parameters:
        mapped pause, read-write ratio to corresponding sub-DataFrame


        Returns:
        mapped pause, read-write ratio to corresponding sub-DataFrame without outliers
    """



    print('discarging outliers for ' + typeOfData)

    for df in dfs:
        # maybe not a bad idea to go to this filter more than once. 
        # specifically for higher repeats
        dfs[df] = remove_outliers(dfs[df], typeOfData,1)

    return dfs

def remove_anomality(dfs, window, maxIndex):
    # maxIndex = len(dfs.index)

    # print(window)

    for index, row in dfs.iterrows():
        # print (index,row["bandwidth_mean"], row["latency_mean"])
        if index<5:
            continue
        
        if maxIndex==index+2:
            # print('break')
            break

        # print (dfs.loc[index,"bandwidth_mean"])
        postIndex=0
        preIndex=-1
        window_tmp=window

        while window_tmp!=0:
            postIndex = postIndex + 1
            # jump over empty slots
            while index+postIndex not in dfs.index:
                postIndex = postIndex + 1
                if index+postIndex>=maxIndex:
                    break

            window_tmp = window_tmp - 1
            
        # if index==39:
        #     print('after post index' ,index+preIndex, index, index+postIndex)

        while index+preIndex not in dfs.index:
            preIndex = preIndex - 1
            if index+preIndex<0:
                break
  
        # if index==39:
        #     print('after pre index' ,index+preIndex, index, index+postIndex)

        if index+preIndex<0 or index+postIndex>=maxIndex:
            continue

        # if index==39:
        #     print('after all' ,index+preIndex, index, index+postIndex)


        if dfs.loc[index+preIndex,"bandwidth_mean"]<dfs.loc[index,"bandwidth_mean"] and dfs.loc[index+postIndex,"bandwidth_mean"] < dfs.loc[index+preIndex,"bandwidth_mean"]:
            dfs = dfs.drop([index, index+preIndex])
            # print (index,row["bandwidth_mean"], row["latency_mean"], 'dropped')
           


    return dfs

def discard_bw_outliers(dfs):
    """ discard outliers 

        Parameters:
        Merged DataFrame


        Returns:
        Merged DataFrame without outliers
    """
    # write below line in a less embarassing way
    for df in dfs:
        maxIndex= len(dfs[df].index)

    for df in dfs:

        # print(dfs[df].to_string())


        for i in range(1,15):
            for j in range(1,8):
                dfs[df] = remove_anomality(dfs[df], j, maxIndex)
    


        # print(dfs[df].to_string())



    return dfs


def merge_dataframes(dfs):
    """ Concatenates a list of dataframes, assuming that all dataframes have the same columns

        Parameters:
        dfs (list) - List of input dataframes

        Returns:
        pandas DataFrame - resulting DataFrame
    """
    return pd.concat(dfs)

def save_curves_to_file(config, outdir, dfs_rw, bw_column = 'bandwidth_smooth', lat_column = 'latency_smooth', lat_unit='ns'):
    """ Saves bandwidth-latency curves in a provided folder in a format expected by Profet tool

        Bandwidth is saved in MB/s and latency in cycles. The function expects bandwidth and latency in the input to be
        in GB/s and nanoseconds, respectively.

        Parameters:
        config (dictionary) - configuration
        outdir (string) - output folder where the files are written (the folder is created if it does not exist)
        dfs_rw (dictionary) - maps read-write ratio to correpsonding dataframe
        bw_column (string) - column used for bandwidth in provided dataframe (default: bandwidth_smooth)
        lat_column (string) - column used for latency in provided dataframe (default: latency_smooth)
        lat_unit (string) - unit for provided latency. Possible options 'ns', 'cycles' (default: 'ns')

        Returns:
        nothing

    """
    assert(lat_unit in ['ns', 'cycles'])
    os.makedirs(outdir, exist_ok=True)
    for rw, df in dfs_rw.items():
        df_copy = df[[bw_column, lat_column]].copy()

        # Convert bandwidth from GB/s to MB/s
        df_copy.loc[:, bw_column] = df_copy[bw_column].apply(lambda bw : bw * 1000)
        
        # Convert latency to cycles if necessary
        if lat_unit == 'ns':
            df_copy.loc[:, lat_column] = df_copy[lat_column].apply(lambda lat : lat * float(config['CPU_FREQ']))

        df_copy.to_csv(os.path.join(outdir, f'bwlat_{rw}.txt'), sep='\t', index=False, header=False)
