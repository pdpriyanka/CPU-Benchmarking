#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>
#include <sys/time.h>
#include <unistd.h>
#include <fstream>

using namespace std;

/**
This programs runs the 4 threads for 10 min and take the total 600 samples (iops). 

**/
void calIOPS();
void *calculateIOPS(void *p);
const long double CONVERTIONFACTOR = 1000000000;

int main(){
	
	
	printf("\nExperiment for Integer operations per second 600 samples");
	calIOPS();

	return 0;
}

/*
This function calculates the IOPS. 
*/
void *calculateIOPS(void *p1){
	
	int a= 124, b = 21, c = 23, d = 23, e= 2.3412, f = 123, g = 1231, h =567, j = 34, k =24, l =342,
	 m= 324, n = 51, o = 242, p = 254, q= 112, r = 853, s = 31, t =67, u = 34, v =4, w =3.24, x =89, y =123, z =123,
	 v1 =12, v2 = 3, v3 = 56, v4 = 88, v5 = 787.43, v6 = 0, v7 = 0, v8 =0, v9 = 0, v10 = 1, v11 = 54, v12 = 12, v13= 45, v14 = 5, v15 = 123, v16 =1,
	 v17 =1, v18 = 12, v19 =12, v20 = 12, v21 = 1, v22 = 12;

	 /* total operations = 36 
		inside loop : 17 arithmatic and 18 assignment operations
		while loop : 1 loop condition 
	*/
	
	long noOfOperations = 0, loopOperations = 33;
	int timeSec = 0;

	//get intial time
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

		noOfOperations = noOfOperations + loopOperations;		
		*((long *)p1) = noOfOperations;
	}
}

/**
This function will calculates the 600 ipos samples for 4 threads
*/
void calIOPS()
{
	pthread_t memThreads[4];
	long iops1[600], iops2[600], iops3[600], iops4[600];
	int noOfThreads = 4;
	long iops = 0, tIops1 = 0, tIops2 =0 , tIops3 = 0, tIops4= 0, prevIops1 = 0, prevIops2 =0 , prevIops3 = 0, prevIops4= 0; 

	// calculate 600 iops samples
	for(int i = 0 ; i < 600; i++)
	{

		if(i == 0)
		{

			//creates 4 threads
			pthread_create(&memThreads[0], NULL, calculateIOPS, &tIops1);
			pthread_create(&memThreads[1], NULL, calculateIOPS, &tIops2);
			pthread_create(&memThreads[2], NULL, calculateIOPS, &tIops3);
			pthread_create(&memThreads[3], NULL, calculateIOPS, &tIops4);
		}

		// sleep the main thread for 1 second
		sleep(1);

		// calculate the flops for 1 second
		// as tiops1 is addlition of all the iops till i th second , we need to substract  addition of iops till (i -1), 
		//to get iops for only ith second 
	
		iops1[i] = tIops1 - prevIops1;
		prevIops1 = tIops1;

		iops2[i] = tIops2 - prevIops2;
		prevIops2 = tIops2;

		iops3[i] = tIops3 - prevIops3;
		prevIops3 = tIops3;

		iops4[i] = tIops4 - prevIops4;
		prevIops4 = tIops4;
	}

	//complete the created threads
	//cancel all the created threads
	pthread_cancel(memThreads[0]);

	pthread_cancel(memThreads[1]);

	pthread_cancel(memThreads[2]);

	pthread_cancel(memThreads[3]);


	// create the file and write 600 samples addition as iops for each second in file
    ofstream file("iopsExp.txt");

    if(!file)
      {
            cout << "Can not open file" <<endl;
      }	
    else{
    	cout<< "Writting total IOPS of 4 threads in iopsExp.txt and printing 600 values on screen"<<endl;
      int temp = 0;
      for (int i = 0; i < 600; i++)
      {
            iops = iops1[i]+ iops2[i]+ iops3[i]+ iops4[i];
            printf("\n counter %d -- Thread 1 = %ld  Thread 2 = %ld  Thread 3 = %ld Thread 4 = %ld Total Iops = %ld",(i+1),iops1[i], iops2[i], iops3[i], iops4[i], iops );
            file<<iops<<endl;

      }
      file.close();
	}
	
}