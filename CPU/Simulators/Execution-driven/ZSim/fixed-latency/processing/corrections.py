from scipy.signal import savgol_filter

def remove_outliers():
    pass

def smooth_curves():
    pass

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

def smooth_curves(config, dfs_rw):
    """ Performs smoothing of (x,y) data points where x is bandwidth and y is latency

        Parameters:
        config (dictionary): configuration
        dfs_rw (dictionary): dictionary mapping read-write ratio to corresponding dataframe

        Returns:
        dictionary: Copy of input dictionary with added columns 'smooth_bandwidth' and 'smooth_latency'
    """
    for rw, df in dfs_rw.items():
        x = df['bandwidth_mean'].tolist()
        y = df['latency_mean'].tolist()

        smooth_x, smooth_y = savgol_filter((x, y),
                                            int(config['SMOOTH_SAVGOL_WINDOW_LENGTH']),
                                            int(config['SMOOTH_SAVGOL_POLYORDER']))

        df.loc[:, 'bandwidth_smooth'] = smooth_x.copy()
        df.loc[:, 'latency_smooth'] = smooth_y.copy()

    return dfs_rw

