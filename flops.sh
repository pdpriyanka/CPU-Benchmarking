#!/bin/bash
g++ -pthread -O0 cpuBenchmarkEXPFLOPS.cpp -o cpuBenchmarkEXPFLOPS.out
echo "CPU Experiment program compiled"
./cpuBenchmarkEXPFLOPS.out
exit 0