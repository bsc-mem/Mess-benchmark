# StressMe
StressMe is a tool for obtaining bandwidth-latency curves.

## Quick Start

- Ensure that you have access to uncore counters (e.g. on epeec, run `sudo /opt/admin/event_paranoid_zero.sh`).
- Install or locate the performance monitoring tools (e.g. Likwid).
- Setup the configuration parameters in the runner script.
- Run the runner script. This takes hours, depending on your configuration parameters. Advice is to run it as `nohup ./runner.sh &` which allows you to disconnect from the server and keep the job running.
The current implementation allows only direct runs on nodes. Support for job scheduling systems will come soon.
You can use `htop` to verify that cores follow desired work distribution.
