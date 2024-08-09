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


    # try: 
    #     with open(filename, "r") as f: 
    #         data = json.load(f)
    # except: 
    #     return pd.DataFrame(columns=["rw_ratio", "pause", "bandwidth", "latency"])

    rw_ratio = measurment_dir_name.split("_")[1]
    pause = measurment_dir_name.split("_")[2]

    frequency = 2.4

    mem_cycles = 0
    read_latency = 0
    read_counts = 0
    write_counts = 0
    # row_hits_channel_0_core = 0
    # row_misses_channel_0_core = 0
    # row_conflicts_channel_0_core = 0


    with open(filename, 'r') as f:
        lines = f.readlines()
        
        for line in lines:
            tokens = line.split(' ')
            tokens[:] = [x for x in tokens if x] # eliminate empty '' tokens
            
            if len(tokens) < 2:
                continue

            if tokens[0] == "memory_system_cycles:":
                mem_cycles = float(tokens[1])
            elif tokens[0] == "avg_read_latency_0:":
                read_latency = float(tokens[1])
            elif tokens[0] == "total_num_read_requests:":
                read_counts = float(tokens[1])
            elif tokens[0] == "total_num_write_requests:":
                write_counts = float(tokens[1])
            # elif tokens[0] == "ramulator.row_hits_channel_0_core":
            #     row_hits_channel_0_core = float(tokens[1])
            # elif tokens[0] == "ramulator.row_misses_channel_0_core":
            #     row_misses_channel_0_core = float(tokens[1])
            # elif tokens[0] == "ramulator.row_conflicts_channel_0_core":
            #     row_conflicts_channel_0_core = float(tokens[1])


    
    bandwidth = frequency*64*(read_counts + write_counts) / mem_cycles
    
    # hit_rate = row_hits_channel_0_core / (row_hits_channel_0_core + row_misses_channel_0_core + row_conflicts_channel_0_core)
    # miss_rate = row_misses_channel_0_core / (row_hits_channel_0_core + row_misses_channel_0_core + row_conflicts_channel_0_core)
    # empty_rate = row_conflicts_channel_0_core / (row_hits_channel_0_core + row_misses_channel_0_core + row_conflicts_channel_0_core)
    



    # return pd.DataFrame({"rw_ratio": rw_ratio, "pause": pause, "bandwidth": bandwidth, "latency": read_latency, "row_buffer_hit_rate": hit_rate, "row_buffer_miss_rate": miss_rate, "row_buffer_empty_rate": empty_rate}, index=[0])
    return pd.DataFrame({"rw_ratio": rw_ratio, "pause": pause, "bandwidth": bandwidth, "latency": read_latency}, index=[0])


iterator = tqdm if has_tqdm else lambda x: x



def main(args): 

    if len(args) != 2: 
        print("Usage: python main.py <results_directory>")
        sys.exit(1)

    base_directory = args[1]

    # final_df = pd.DataFrame(columns=["rw_ratio", "pause", "bandwidth", "latency", "row_buffer_hit_rate", "row_buffer_miss_rate", "row_buffer_empty_rate"])
    final_df = pd.DataFrame(columns=["rw_ratio", "pause", "bandwidth", "latency"])


    dirs = [d for d in os.listdir(base_directory) if "measurment" in d and os.path.isdir(f"{base_directory}/{d}")]
    results_files = [f"{base_directory}/{d}/output.out" for d in dirs]

    for file, dirname in iterator(zip(results_files, dirs)): 
        tmp_df = parse_results_file(file, dirname)
        if tmp_df.shape[0] > 0:
            final_df = pd.concat([final_df, tmp_df])

    final_df.to_csv("results.csv", index=False)

if __name__ == "__main__":
    main(sys.argv)
