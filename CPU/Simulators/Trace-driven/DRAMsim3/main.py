import os 
import pandas as pd
import sys
import json

try: 
    from tqdm import tqdm
    has_tqdm = True 
except: 
    has_tqdm = False

def parse_results_file(filename, measurment_dir_name):
    try: 
        with open(filename, "r") as f: 
            data = json.load(f)
    except: 
        return pd.DataFrame(columns=["rw_ratio", "pause", "bandwidth", "latency", "row_buffer_hit_rate"])
    

    read_latencies = []
    read_counts = []
    bandwidths = []

    num_read_row_hits = []
    num_write_row_hits = []
    write_counts = []


    rw_ratio = measurment_dir_name.split("_")[1]
    pause = measurment_dir_name.split("_")[2]

    for channel_id, channel_results in data.items(): 
        read_latencies.append(channel_results["average_read_latency"])
        read_counts.append(channel_results["num_reads_done"])
        bandwidths.append(channel_results["average_bandwidth"])
        
        write_counts.append(channel_results["num_writes_done"])
        num_read_row_hits.append(channel_results["num_read_row_hits"])
        num_write_row_hits.append(channel_results["num_write_row_hits"])


    ## weighted avg of read latencies
    running_sum = 0
    for rl, wl in zip(read_latencies, read_counts): 
        running_sum += rl * wl

    latency = running_sum / sum(read_counts)
    bandwidth = sum(bandwidths) / len(bandwidths)

    row_buffer_hit_rate = (sum(num_read_row_hits) + sum(num_write_row_hits)) / (sum(read_counts) + sum(write_counts))

    return pd.DataFrame({"rw_ratio": rw_ratio, "pause": pause, "bandwidth": bandwidth, "latency": latency, "row_buffer_hit_rate": row_buffer_hit_rate, "row_buffer_miss_rate": 1-row_buffer_hit_rate, "row_buffer_empty_rate": 0}, index=[0])


iterator = tqdm if has_tqdm else lambda x: x

def main(args): 

    if len(args) != 2: 
        print("Usage: python main.py <results_directory>")
        sys.exit(1)

    base_directory = args[1]

    final_df = pd.DataFrame(columns=["rw_ratio", "pause", "bandwidth", "latency", "row_buffer_hit_rate", "row_buffer_miss_rate", "row_buffer_empty_rate"])
    dirs = [d for d in os.listdir(base_directory) if "measurment" in d and os.path.isdir(f"{base_directory}/{d}")]
    results_files = [f"{base_directory}/{d}/dramsim3.json" for d in dirs]

    for file, dirname in iterator(zip(results_files, dirs)): 
        tmp_df = parse_results_file(file, dirname)
        if tmp_df.shape[0] > 0:
            final_df = pd.concat([final_df, tmp_df])

    final_df.to_csv("results.csv", index=False)

if __name__ == "__main__":
    main(sys.argv)
