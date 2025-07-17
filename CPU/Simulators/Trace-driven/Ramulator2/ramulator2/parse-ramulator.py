import os
import yaml
import re
import sys

regex_read_latency = r"(.*)avg_read_latency_(\d+): (\d+\.\d+)"
regex_n_read_reqs  = r"(.*)num_read_reqs_(\d+): (\d+)"
regex_n_write_reqs  = r"(.*)num_write_reqs_(\d+): (\d+)"
regex_mem_sys_cycles = r"(.*)memory_system_cycles: (\d+)"


data = [dict() for _ in range(8)]
total_cycles = 0

def parse_stats_file(filename): 
    with open(filename, 'r') as f:
        lines = f.readlines()

    for line in lines: 
        ## Does this line match anyting?
        for id, regex in [["avg_read_latency", regex_read_latency], ["num_read_reqs", regex_n_read_reqs], ["num_write_reqs", regex_n_write_reqs]]:
            match = re.match(regex, line)
            try: 
                if match:
                    key = match.group(2)
                    value = match.group(3)
                    data[int(key)][id] = value
            except: 
                print("Error parsing line: ", line)

        match = re.match(regex_mem_sys_cycles, line)
        if match: 
            total_cycles = int(match.group(2))



    ## weighted average of read latency 
    total_read_reqs = 0
    total_write_reqs = 0
    total_latency = 0
    for d in data: 
        total_read_reqs += int(d["num_read_reqs"])
        total_write_reqs += int(d["num_write_reqs"])
        total_latency += int(d["num_read_reqs"]) * float(d["avg_read_latency"])
    
    average_latency = total_latency / total_read_reqs
    print("Average read latency: ", average_latency, "cycles")

    ## Bandwidth
    bandwidth = (total_read_reqs + total_write_reqs) * 64 / total_cycles
    print("Bandwidth: ", bandwidth, "B/cycle")

    return bandwidth, average_latency


    



def main(args):
    if len(args) != 2:
        print("Usage: python parse-ramulator.py <input_file>")
        sys.exit(1)

    input_file = args[1]
    parse_stats_file(input_file)

if __name__ == "__main__": 
    main(sys.argv)

