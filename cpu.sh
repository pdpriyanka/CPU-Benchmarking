#!/bin/bash
g++ -pthread -O0 cpuBenchmark.cpp -o cpuBenchmark.out
echo "Cpu program compiled"
./cpuBenchmark.out
exit 0