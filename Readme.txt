Instructions to execute program for CPU benchmark.
1.Open the terminal.  If you want to use amazon EC2 instances then connect to it from terminal.
2.For compiling and running C++ programs , you must have g++ installed .
3.Run  the following command to install g++
 sudo yum install gcc-c++
4. From terminal go to the folder where source code of cpu is saved.
5.To run the bash screept
 Give executable permission to it
 chmod 500 cpu.sh

Then execute following command to run the bash script
./cpu.sh  

Or
 Without bash script you can type following commands
g++ -pthread -O0 cpuBenchmark.cpp -o cpuBenchmark.out
./cpuBenchmark.out
 After executing  the above  commands or bash script program will start running and you can see the printed output on screen. 

To execute the CPU performance experiment.There are two seperate programs for flops and iops. you either run bash file or commands on terminals
First give read and execute permission to bash file
For FLOPS EXpermiment

Chmod 500 flops.sh

To execute bash file
./flops.sh

Or
Without bash script you can type following commands
g++ -pthread -O0 cpuBenchmarkEXPFLOPS.cpp -o cpuBenchmarkEXPFLOPS.out

./cpuBenchmarkEXPFLOPS.out



For this program output is print on screen as well txt file is created .




For IOPS Eepermiment

Chmod 500 iops.sh

To execute bash file
./iops.sh

Or
Without bash script you can type following commands
g++ -pthread -O0 cpuBenchmarkEXPIOPS.cpp -o cpuBenchmarkEXPIOPS.out

./cpuBenchmarkEXPIOPS.out

For this program output is print on screen as well txt file is created .



Extra Credit : 
To install the Linkpack

1. Download the linkpack for linux and save it on local drive.

2. Extract that download folder on local drive.

3. Open the terminal on linux machine.

4. Go to "benchmarks" folder and then go to "linpack" folder by using cd command.
	for ex : if path for linpack folder is cpu/linkpackl_10.3/benchmark/linkpack
	execute command : $cd cpu/linkpackl_10.3/benchmark/linkpack

5. if system is 64 bit ,execute command :$./xlinpack_xeon64 
   otherwise if 32 bit then execute command :$./xlinpack_xeon64  
