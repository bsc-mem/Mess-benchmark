#!/usr/bin/env python3
import sys
import toml
import os

def create_runner_config(base_cfg, runner_config_path):
    param_map = {
        'Platform.name'      : 'NAME',
        'Platform.cpu'       : 'CPU',
        'Platform.cpu-freq'  : 'CPU_FREQ',
        'Platform.mem'       : 'MEM',
        'Platform.mem-type'  : 'MEM_TYPE',
        'Platform.mem-freq'  : 'MEM_FREQ',
        'Platform.mem-max-channels' : 'MEM_MAX_CHANNELS',
        'Platform.stlb-hit-latency' : 'STLB_HIT_LATENCY',
        'Experiments.stream-core-list'               : 'STREAM_CORE_LIST',
        'Experiments.stream-core-count'              : 'STREAM_CORE_COUNT',
        'Experiments.stream-core-count-socket'       : 'STREAM_CORE_COUNT_SOCKET',
        'Experiments.stream-numactl-additional-args' : 'STREAM_NUMACTL_ADDITIONAL_ARGS',
        'Experiments.ptrchase-core' : 'PTRCHASE_CORE',
        'Experiments.ptrchase-numactl-additional-args' : 'PTRCHASE_NUMACTL_ADDITIONAL_ARGS',
        'Experiments.rwratio-min'   : 'RWRATIO_MIN',
        'Experiments.rwratio-max'   : 'RWRATIO_MAX',
        'Experiments.rwratio-step'  : 'RWRATIO_STEP',
        'Experiments.stream-pauses' : 'PAUSES',
        'Experiments.point-reps'    : 'POINT_REPS',
        'Experiments.bw-meas-reps'  : 'BW_MEAS_REPS',
        'Experiments.lat-meas-reps' : 'LAT_MEAS_REPS',
        'Experiments.time-stream-stabilize' : 'TIME_STREAM_STABILIZE',
        'Experiments.time-after-bw'         : 'TIME_AFTER_BW_MEAS',
        'Experiments.time-after-stream-termination'    : 'TIME_AFTER_STREAM_TERMINATION',
        'Counters.bw-tool'          : 'BW_TOOL',
        'Counters.bw-tool-path'     : 'BW_TOOL_PATH',
        'Counters.bw-tool-cores'    : 'BW_TOOL_CORES',
        'Counters.bw-tool-sample-time': 'BW_TOOL_SAMPLE_TIME',
        'Counters.bw-tool-counters' : 'BW_TOOL_COUNTERS',
        'Counters.bw-tool-custom-cmd' : 'BW_TOOL_CUSTOM_CMD',
        'Counters.lat-tool'         : 'LAT_TOOL',
        'Counters.lat-tool-path'    : 'LAT_TOOL_PATH',
        'Counters.lat-tool-counters': 'LAT_TOOL_COUNTERS',
        'Counters.lat-tool-custom-cmd': 'LAT_TOOL_CUSTOM_CMD',
        'Processing.smooth-savgol-window-length' : 'SMOOTH_SAVGOL_WINDOW_LENGTH',
        'Processing.smooth-savgol-polyorder'     : 'SMOOTH_SAVGOL_POLYORDER',
        'Benchmarks.ptrchase-num-instructions'  : 'PTRCHASE_NUM_INSTRUCTIONS',
        'Benchmarks.ptrchase-num-iterations'     : 'PTRCHASE_NUM_ITERATIONS',
        'Benchmarks.ptrchase-array-size'         : 'PTRCHASE_ARRAY_SIZE',

    }

    with open(runner_config_path, 'w') as f:
        for src_param, dst_param in param_map.items():
            # We assume that param_map keys are in format Section.param
            # Therefore, the split should return exactly two values
            section, param = src_param.split('.')
            assert(section in base_cfg)
            try:
                value = base_cfg[section][param]
                if param == "name":
                    formatted_val = os.uname()[1]
                elif isinstance(value, int):
                    formatted_val = value
                elif isinstance(value, str):
                    formatted_val = f'"{value}"'
                elif isinstance(value, list):
                    formatted_val = ' '.join([str(v) for v in value])
                    formatted_val = f'"{formatted_val}"'
                elif isinstance(value, float):
                    formatted_val = value
                else:
                    raise ValueError
            except KeyError:
                print(f'WARNING: Parameter {param} in section {section} does not exist in the config file. Using empty string as default value.')
                formatted_val=""

            f.write(f'{dst_param}={formatted_val}\n')

def main():
    if len(sys.argv) != 2:
        print('This script translates the provided configuration file in TOML format\n'
        'to the configuration file required by the runner.sh script.\n'
        'Usage:\n'
        f'\t{sys.argv[0]} input_config_file\n')
    else:
        config = toml.load(sys.argv[1])
        # print(config)
        create_runner_config(config, './config.sh')


if __name__ == '__main__':
    main()
