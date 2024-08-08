import os
import pandas as pd
import calculator
import line_parser

class Parser:
    def __init__(self, type, input_dir, config):
        self.input_dir = input_dir
        # print("input_dir:" + input_dir)
        # print(type, "  ", input_dir)
        # self.files = [f for f in os.listdir(input_dir) if os.path.isfile(os.path.join(input_dir, f))]
        self.files = [f for f in os.listdir(input_dir)]
        self.config = config
        if type == 'bandwidth':
            # Returns BandwidthLikwidLineParser()
            if config['BW_TOOL'].replace('"','') == 'likwid':
                self.line_parser = line_parser.Factory(type, 'likwid', config)
            else:
                self.line_parser = line_parser.Factory(type, 'perf', config)
            self.calculator = calculator.Factory(type, config['BW_TOOL'].replace('"',''))
        else:
            # Returns LatencyPerfLineParser()
            self.line_parser = line_parser.Factory(type, 'perf', config)
            self.calculator = calculator.Factory(type, 'perf')

        
        self.df = None
        pass

    def process(self):
        self.parse()
        self.calculateMetrics()
        return self.df

    def parse(self):
        df_data = {}
        for fname in self.files:
            filename='/zsim.out'
            # print(fname)
            # fname = fname + '/zsim.out'
            fname_tokens = fname.rstrip('.txt').split('_')
            # if int(fname_tokens[1])!= 56 and int(fname_tokens[1])!= 100:
            #     continue
            
            if int(fname_tokens[1])< 50:
                continue

            # print(os.path.join(self.input_dir, fname+filename))
            with open(os.path.join(self.input_dir, fname+filename), 'r') as f: #errors='ignore'

                # if int(fname_tokens[1])!= 100:
                #     continue
                # if int(fname_tokens[2])> 2:
                #     continue

                # print(fname)
                lines = f.readlines()
                
                new_result = {'type' : '-'.join([self.config['MEM_TYPE'].replace("\"", ""), self.config['MEM_FREQ']]), 'rd_percentage' : int(fname_tokens[1]), 'pause' : int(fname_tokens[2]), 'repeat' : 0, 'measure' : 1}
                # new_result = {'type' : '-'.join([self.config['MEM_TYPE'].replace("\"", ""), self.config['MEM_FREQ']]), 'arraySize4Latency' : int(fname_tokens[2]), 'repeat' : 0, 'measure' : 1}
                result = new_result
                measure = 1
                for line in lines:
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

                # exit(0)
        # for k,v in df_data.items():
        #    print(f'{k} {len(v)}')

        df = pd.DataFrame(df_data)



        # print(df.info(verbose=True))
        # print(df.to_string())

        df.sort_values(by=['type', 'rd_percentage', 'pause', 'measure'], inplace=True)
       
        self.df = df
        return df

    def calculateMetrics(self):
        self.calculator.calculate(self.df, self.config)


