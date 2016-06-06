#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>
#include <sys/time.h>
#include <unistd.h>
#include <fstream>

using namespace std;

/**
This programs runs the 4 threads for 10 min and take the total 600 samples (flops). 

**/
void calFLOPS();
void *calculateFLOPS(void *p);
const long double CONVERTIONFACTOR = 1000000000;

int main(){
	
	printf("Experiment for Floating point operations per second 600 samples");
	calFLOPS();
	return 0;
}

void *calculateFLOPS(void *p1){
	double a= 124.23525, b = 21.2412, c = 2342.23432, d = 23.324, e= 2.3412, f = 123.21, g = 1231.12, h =567.4, j = 34.4, k =24, l =342.24,
	 m= 324.23525, n = 51.2412, o = 242.23432, p = 254.324, q= 112.3412, r = 853.21, s = 31.12, t =67.4, u = 34.4, v =4, w =3.24, x =89.131, y =123.23, z =123.123,
	 v1 =12.3, v2 = 3, v3 = 56.5, v4 = 88.56, v5 = 787.43, v6 = 0, v7 = 0, v8 =0, v9 = 0, v10 = 1, v11 = 54, v12 = 12, v13= 45, v14 = 5.66, v15 = 123.12, v16 =1 ,
	 v17 =1, v18 = 12, v19 =12, v20 = 12.1, v21 = 1.1, v22 = 12;

	/* total operations = 33
		inside loop : 16 arithmatic and 17 assignment operations
		while loop : 1 loop condition 
	*/
	long noOfOperations = 0, loopOperations = 33;
	int timeSec = 0;


	// run the loop
	while(true)
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

		// calculate total number of floating point operations
		noOfOperations = noOfOperations + loopOperations;		
		*((long *)p1) = noOfOperations;
	}
}

/** 
 This function calculates the 600 samples of flops for 4 threads.
*/
void calFLOPS(){
	pthread_t memThreads[4];
	long flops1[600], flops2[600], flops3[600], flops4[600];
	int noOfThreads = 4;
	long flops = 0, tFlops1 = 0, tFlops2 =0 , tFlops3 = 0, tFlops4= 0, prevFlops1 = 0, prevFlops2 =0 , prevFlops3 = 0, prevFlops4= 0; 

	//Calculates the 600 flops samples for 4 threads
	for(int i = 0 ; i < 600; i++)
	{

		if(i == 0)
		{

			// create 4 threads
			pthread_create(&memThreads[0], NULL, calculateFLOPS, &tFlops1);
			pthread_create(&memThreads[1], NULL, calculateFLOPS, &tFlops2);
			pthread_create(&memThreads[2], NULL, calculateFLOPS, &tFlops3);
			pthread_create(&memThreads[3], NULL, calculateFLOPS, &tFlops4);
		}

		// sleep the main thread for 1 second
		sleep(1);


		// calculate the flops for 1 second
		// as tflops1 is addlition of all the flops till i th second , we need to substract  addition of flops till (i -1), 
		//to get flops for only i the second 
		flops1[i] = tFlops1 - prevFlops1;
		prevFlops1 = tFlops1;

		flops2[i] = tFlops2 - prevFlops2;
		prevFlops2 = tFlops2;

		flops3[i] = tFlops3 - prevFlops3;
		prevFlops3 = tFlops3;

		flops4[i] = tFlops4 - prevFlops4;
		prevFlops4 = tFlops4;
	}

	//cancel all the created threads
	pthread_cancel(memThreads[0]);

	pthread_cancel(memThreads[1]);

	pthread_cancel(memThreads[2]);

	pthread_cancel(memThreads[3]);

	// create the file and write 600 samples addition as flops for each second in file 
    ofstream file("flopsExp.txt");

    if(!file)
      {
            cout << "Can not open file" <<endl;
      }	
    else{
    	cout<< "Writting total flops of 4 threads in flopsExp.txt and printing 600 values on screen"<<endl;
      int temp = 0;
      for (int i = 0; i < 600; i++)
      {
            flops = flops1[i]+ flops2[i]+ flops3[i]+ flops4[i];
            printf("\n counter %d -- Thread 1 = %ld  Thread 2 = %ld  Thread 3 = %ld Thread 4 = %ld Total Flops = %ld",(i +1),flops1[i], flops2[i], flops3[i], flops4[i], flops );
            file<<flops<<endl;

      }
      file.close();
	}
}

