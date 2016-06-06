#!/bin/bash
g++ -pthread -O0 cpuBenchmarkEXPIOPS.cpp -o cpuBenchmarkEXPIOPS.out
echo "CPU Experiment program compiled"
./cpuBenchmarkEXPIOPS.out
exit 0