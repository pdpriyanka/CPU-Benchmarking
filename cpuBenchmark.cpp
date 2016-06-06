#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>
#include <sys/time.h>

using namespace std;
/**
CPU benchmark. This program calculates the floating point operations per seconds and integer operations per second.
*/
void calFLOPS();
void *calculateFLOPS(void *p);
void calIOPS();
void *calculateIOPS(void *p);
/* Constants for loop interations.
	Conversion factor for FLOPS to Giga Flops
*/

const int LOOPVARIABLE = 1500000;
const long double FLOOPVARIABLE = 1500000;
const long double CONVERTIONFACTOR = 1000000000;


int main(){

	cout<< "Floating point operations per second calculation";
	calFLOPS();

	cout<< "\n\nIntegers operations per second calculation";
	calIOPS();

	return 0;
}

/*
This function is called by threads and 
it calculates the floating point operations per second
*/
void *calculateFLOPS(void *p1){
	double a= 124.23525, b = 21.2412, c = 2342.23432, d = 23.324, e= 2.3412, f = 123.21, g = 1231.12, h =567.4, j = 34.4, k =24, l =342.24,
	 m= 324.23525, n = 51.2412, o = 242.23432, p = 254.324, q= 112.3412, r = 853.21, s = 31.12, t =67.4, u = 34.4, v =4, w =3.24, x =89.131, y =123.23, z =123.123,
	 v1 =12.3, v2 = 3, v3 = 56.5, v4 = 88.56, v5 = 787.43, v6 = 0, v7 = 0, v8 =0, v9 = 0, v10 = 1, v11 = 54, v12 = 12, v13= 45, v14 = 5.66, v15 = 123.12, v16 =1 ,
	 v17 =1, v18 = 12, v19 =12, v20 = 12.1, v21 = 1.1, v22 = 12;
	
	struct timeval beforeTime, afterTime; 

	// get initial time
	gettimeofday (&beforeTime, NULL);
	for(double i = 0; i < FLOOPVARIABLE; i++)
	{
		a = a + b;
		c = d + e;
		f = g * h;
		m = m + n;
		j = k * l;


		q = o + p;
		s = r + s;
		v = t * u;
		m = k + n;
		j = w * l;

		x = x * y;
		v6 = v1 + v2;
		v7 = v3 * v4;
		v8 = v5 * v5;
		v9 = g * k;	
	}	
	// get end time
	gettimeofday (&afterTime, NULL);

	// calculate the difference between initial time and end time in seconds
	long double totalTime = ((afterTime.tv_sec - beforeTime.tv_sec)*1000L) + ((double)(afterTime.tv_usec - beforeTime.tv_usec)/1000L);
	totalTime = totalTime/1000;

	// pass the time in second into main thread as a return value
	long double *value = (long double *)malloc(sizeof(long double));
	*value = totalTime;
	pthread_exit(value);
}

/*
* This functions creates 1, 2, 4 threads and do calculations of iops/giga iops
*/
void calFLOPS(){
	pthread_t memThreads[4];
	void* f1, * f2 , * f3, *f4;
	int noOfThreads = 1;
	long double  flops = 0, time1 = 0, time2 =0 , time3 = 0, time4= 0; 

	/*one loop has total 33 instructions : 
		inside loop - 15 arithmatic + 15 assignment instuctions
		in for - 1 loop condition and 2 ( addition and assignment of i) post loop instructions  
		2 more - loop condition at last time + intialization of i

	There are FLOOPVARIABLE intereation hence total instructions = (33 * FLOOPVARIABLE) + 2
	*/
	long double noOfOp =  33 * FLOOPVARIABLE, totalOps = 0;
	noOfOp = noOfOp + 2;

	//Create 1 thread  
	pthread_create(&memThreads[0], NULL, calculateFLOPS, NULL);

	// complete the created thread
	pthread_join(memThreads[0], &f1);

	time1 = *((long double *)f1);
	flops = noOfOp / time1;

	printf("\n\n For number of Threads =  %d, floating point operations per second = %Lf FLOPS\n ", noOfThreads,flops);
	flops = flops / CONVERTIONFACTOR;

	printf("\n For number of Threads = %d, giga floating point operations per second = %Lf Giga FLOPS\n ", noOfThreads,flops);
	free(f1);


	//For 2 threads
	noOfThreads = 2;
	flops = 0;
	time1 =0;
	//Create 2 threads
	pthread_create(&memThreads[0], NULL, calculateFLOPS, NULL);
	pthread_create(&memThreads[1], NULL,calculateFLOPS, NULL);


	//complete the created threds
	pthread_join(memThreads[0], &f1);

	pthread_join(memThreads[1], &f2);

	time1 = *((long double *)f1);
	time2 = *((long double *)f2);

	// flops = (no of threads * total floating point operations for each thread)/ (average of time taken by threads in second)
	time1 = (time1 + time2) / noOfThreads;
	totalOps = noOfThreads * noOfOp;
	flops =  totalOps / time1;

	printf("\n\n For number of Threads = %d, floating point operations per second = %Lf FLOPS\n ", noOfThreads,flops);

	//convert flops to giga flops 
	flops = flops / CONVERTIONFACTOR;
	printf("\n For number of Threads = %d, giga floating point operations per second = %Lf Giga FLOPS\n ", noOfThreads,flops);

	free(f1);
	free(f2);


	//For 4 thread 
	noOfThreads = 4;
	flops = 0;
	time1 = 0;
	time2 = 0;

	// create 4 threads
	pthread_create(&memThreads[0], NULL, calculateFLOPS, NULL);
	pthread_create(&memThreads[1], NULL, calculateFLOPS, NULL);
	pthread_create(&memThreads[2], NULL, calculateFLOPS, NULL);
	pthread_create(&memThreads[3], NULL, calculateFLOPS, NULL);

	//complete the created threads
	pthread_join(memThreads[0], &f1);

	pthread_join(memThreads[1], &f2);

	pthread_join(memThreads[2], &f3);

	pthread_join(memThreads[3], &f4);

	time1 = *((long double *)f1);
	time2 = *((long double *)f2);
	time3 = *((long double *)f3);
	time4 = *((long double *)f4);

	// flops = (no of threads * total floating point operations for each thread)/ (average of time taken by threads in second)
	time1 = (time1 + time2);
	time3 = (time3 + time4);
	time1 = (time1 + time3) / noOfThreads;

	totalOps = noOfThreads * noOfOp;
	flops =  totalOps / time1;

	printf("\n\n For number of Thread = %d, floating point operations per second = %Lf FLOPS\n ", noOfThreads,flops);

	//convert flops to giga flops 
	flops = flops / CONVERTIONFACTOR;
	printf("\n For number of Thread = %d, giga floating point operations per second = %Lf Giga FLOPS\n ", noOfThreads,flops);

	free(f1);
	free(f2);
	free(f3);
	free(f4);
}

/*
This function is called by threads and 
it calculates the integer operations per second
*/
void *calculateIOPS(void *p1){
	
	int a= 124, b = 21, c = 23, d = 23, e= 2.3412, f = 123, g = 1231, h =567, j = 34, k =24, l =342,
	 m= 324, n = 51, o = 242, p = 254, q= 112, r = 853, s = 31, t =67, u = 34, v =4, w =3.24, x =89, y =123, z =123,
	 v1 =12, v2 = 3, v3 = 56, v4 = 88, v5 = 787.43, v6 = 0, v7 = 0, v8 =0, v9 = 0, v10 = 1, v11 = 54, v12 = 12, v13= 45, v14 = 5, v15 = 123, v16 =1,
	 v17 =1, v18 = 12, v19 =12, v20 = 12, v21 = 1, v22 = 12;

	 long double iops = 0;
	 struct timeval beforeTime, afterTime; 

	 // get initial time
	 gettimeofday (&beforeTime, NULL);

	for(int i = 0; i < LOOPVARIABLE; i++)
	{
		a = a + b;
		c = d + e;
		f = g * h;
		m = m + n;
		j = k * l;


		q = o + p;
		s = r + s;
		v = t * u;
		m = k + n;
		j = w * l;

		x = x * y;
		v6 = v1 + v2;
		v7 = v3 * v4;
		v8 = v5 * v5;
		v9 = g * k;
	}	
	// get end time	
	gettimeofday (&afterTime, NULL);

	// calculate the difference between initial time and end time in seconds
	long double totalTime = ((afterTime.tv_sec - beforeTime.tv_sec)*1000L) + ((double)(afterTime.tv_usec - beforeTime.tv_usec)/1000L);
	totalTime = totalTime/1000;

	// pass the time in second into main thread as a return value
	long double *value = (long double *)malloc(sizeof(long double));
	*value = totalTime;
	pthread_exit(value);
}

/*
* This functions creates 1, 2, 4 threads and do calculations of iops/giga iops
*/

void calIOPS(){
	pthread_t memThreads[4];
	void* nullTime;
	void* f1, * f2 , * f3, *f4;
	int noOfThreads = 1;
	long double  iops = 0, time1 = 0, time2 =0 , time3 = 0, time4= 0; 

	/*one loop has total 33 instructions : 
		inside loop - 15 arithmatic + 15 assignment instuctions
		in for - 1 loop condition and 2 ( addition and assignment of i) post loop instructions  
		2 more - loop condition at last time + intialization of i

	There are FLOOPVARIABLE intereation hence total instructions = (33 * LOOPVARIABLE) + 2
	*/
	long double noOfOp =  33 * FLOOPVARIABLE, totalOps = 0;
	noOfOp = noOfOp + 2;

	//Create 1 thread  
	pthread_create(&memThreads[0], NULL, calculateIOPS, NULL);

	// complete the created thread
	pthread_join(memThreads[0], &f1);

	time1 = *((long double *)f1);
	iops = noOfOp / time1;
	printf("\n\n For number of Thread =  %d, Integers operations per second = %Lf IOPS\n ", noOfThreads,iops);

	//convert flops to giga iops 
	iops = iops / CONVERTIONFACTOR;

	printf("\n For number of Thread = %d, Giga Integers operations per second = %Lf Giga IOPS\n ", noOfThreads,iops);
	free(f1);

	noOfThreads = 2;
	iops = 0;
	time1 =0;
	
	//Create 2 threads  
	pthread_create(&memThreads[0], NULL, calculateIOPS, NULL);
	pthread_create(&memThreads[1], NULL, calculateIOPS, NULL);

	// complete the created threads
	pthread_join(memThreads[0], &f1);
	pthread_join(memThreads[1], &f2);

	time1 = *((long double *)f1);
	time2 = *((long double *)f2);

	// iops = (no of threads * total integer operations for each thread)/ (average of time taken by threads in second)
	time1 = (time1 + time2) / noOfThreads;
	totalOps = noOfThreads * noOfOp;
	iops = totalOps / time1;

	printf("\n\n For number of Thread =  %d, Integers operations per second = %Lf IOPS\n ", noOfThreads,iops);

	//convert flops to giga iops 
	iops = iops / CONVERTIONFACTOR;
	printf("\n For number of Thread = %d, Giga Integers operations per second = %Lf Giga IOPS\n ", noOfThreads,iops);

	free(f1);
	free(f2);

	noOfThreads = 4;
	iops = 0;
	time1 = 0;
	time2 = 0;

	//Create 4 thread  
	pthread_create(&memThreads[0], NULL, calculateIOPS, NULL);
	pthread_create(&memThreads[1], NULL, calculateIOPS, NULL);
	pthread_create(&memThreads[2], NULL, calculateIOPS, NULL);
	pthread_create(&memThreads[3], NULL, calculateIOPS, NULL);

	// complete the created threads
	pthread_join(memThreads[0], &f1);
	pthread_join(memThreads[1], &f2);
	pthread_join(memThreads[2], &f3);
	pthread_join(memThreads[3], &f4);

	// iops = (no of threads * total integer operations for each thread)/ (average of time taken by threads in second)

	time1 = *((long double *)f1);
	time2 = *((long double *)f2);
	time3 = *((long double *)f3);
	time4 = *((long double *)f4);

	time1 = (time1 + time2);
	time3 = (time3 + time4);
	time1 = (time1 + time3) / noOfThreads;

	totalOps = noOfThreads * noOfOp;
	iops = totalOps / time1;

	printf("\n\n For number of Thread =  %d, Integers operations per second = %Lf IOPS\n ", noOfThreads,iops);

	//convert flops to giga iops 
	iops = iops / CONVERTIONFACTOR;
	printf("\n For number of Thread = %d, Giga Integers operations per second = %Lf Giga IOPS\n ", noOfThreads,iops);

	free(f1);
	free(f2);
	free(f3);
	free(f4);
}