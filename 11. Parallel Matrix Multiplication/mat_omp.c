#include<omp.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#define size 800
int N=size;

int main(int argc,char* argv[])
{
	 //Initializing the variables
	 struct timeval tv1, tv2;
	 struct timezone tz;
	 double elapsed;
	 int A[size][size];
	 int B[size][size];
	 int i=0,j=0,k=0;


	 for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                A[i][j] = i * N + j + 1;  // Initialize A
                B[i][j] = (i + j) % N + 1;  // Initialize B
            }
        }
	 int C[size][size];
	 clock_t t;
	 int nthreads,tid;
	 gettimeofday(&tv1, &tz); //Calculate the current time in the system
	 //Begin of parallel threads
	 
	 #pragma omp parallel for private(i,j,k) shared(A,B,C)
	 for (i = 0; i < size; ++i) {
		 for (j = 0; j < size; ++j) {
			 for (k = 0; k < size; ++k) {
			 	C[i][j] += A[i][k] * B[k][j];
			 }
		 }
	 } //End of parallel threads

	 gettimeofday(&tv2, &tz);//Calculate the current time in the system
	 elapsed = (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
	 printf("elapsed time = %f seconds.\n", elapsed);
	 return 0;
}