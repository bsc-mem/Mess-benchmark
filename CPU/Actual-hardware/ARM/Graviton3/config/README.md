# Configuration file
This document explains the purpose and the format of the configuration file and the contained parameters.

## Purpose
The purpose of the configuration file is to control various aspects of the tool execution, starting from measurement, data processing and visualization.

## Format
Configuration file follows [TOML](https://toml.io) format.
TOML is based on [INI](https://en.wikipedia.org/wiki/INI_file) format and allows writing simple human-readable files that are easy to parse.
Here we show the short summary of features used in the config file. There are also official [full specification](https://toml.io/en/latest).


## Config parameters
The configuration file is organized into sections.

Platform section describes the platform where the tool is executed. This information is used for post-processing and visualization.

Experiments section defines the variables used in measuring phase.

Counters section controlls the performance counter monitoring tools.