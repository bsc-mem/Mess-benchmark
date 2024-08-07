import os
import pandas as pd
from collections import defaultdict

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
