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

import os
import pandas as pd
import calculator
import line_parser

class Parser:
    def __init__(self, type, input_dir, config):
        self.input_dir = input_dir
        self.files = [f for f in os.listdir(input_dir) if os.path.isfile(os.path.join(input_dir, f))]
        self.config = config
        if type == 'bandwidth':
            # Returns BandwidthLikwidLineParser()
            if config['BW_TOOL'].replace('"','') == 'likwid':
                self.line_parser = line_parser.Factory(type, 'likwid', config)
            elif config['BW_TOOL'].replace('"','') == 'vtune':
                self.line_parser = line_parser.Factory(type, 'vtune', config)
        else:
            # Returns LatencyPerfLineParser()
            self.line_parser = line_parser.Factory(type, 'perf', config)
        self.calculator = calculator.Factory(type)
        self.df = None
        pass

    def process(self):
        self.parse()
        self.calculateMetrics()
        return self.df

    def parse(self):
    #def extract_statistics(input_dir, files, process_line_function):
        df_data = {}
        for fname in self.files:
            with open(os.path.join(self.input_dir, fname), 'r') as f: #errors='ignore'
                lines = f.readlines()
                fname_tokens = fname.rstrip('.txt').split('_')
                # print(fname_tokens)
                if int(fname_tokens[2])<50:
                    continue
                # new_result = {'type' : 'DDR4-2666', 'rd_percentage' : int(fname_tokens[2]), 'pause' : int(fname_tokens[3]), 'repeat' : 0, 'measure' : 1}
                new_result = {'type' : '-'.join([self.config['MEM_TYPE'].replace("\"", ""), self.config['MEM_FREQ']]), 'rd_percentage' : int(fname_tokens[2]), 'pause' : int(fname_tokens[3]), 'repeat' : 0, 'measure' : 1}
                result = new_result
                measure = 1
                for line in lines:
                    # print(line)
                    stats, vals, done = self.line_parser.parse_line(line)
                    # print(stats, vals, done)
                    if stats is not None and vals is not None:
                        for s, v in zip(stats, vals):
                            result[s] = v
                        if done:
                            for s, v in result.items():
                                if s not in df_data:
                                    df_data[s] = [v]
                                else:
                                    df_data[s].append(v)
                            result = new_result
                            result['measure'] = measure
                            measure += 1
        # for k,v in df_data.items():
        #    print(f'{k} {len(v)}')
        df = pd.DataFrame(df_data)
        print(df.info(verbose=True))
        df.sort_values(by=['type', 'rd_percentage', 'pause', 'measure'], inplace=True)
        self.df = df
        return df

    def calculateMetrics(self):
        self.calculator.calculate(self.df, self.config)


