#include<omp.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#define size 800

int main(int argc,char* argv[])
{
	 //Initializing the variables
	 struct timeval tv1, tv2;
	 struct timezone tz;
	 double elapsed;
	 int A[size][size];
	 int B[size][size];
	 int i=0,j=0,k=0;
	 FILE *file_ptr; //Reading the matrix values from TXT file
	 char ch;
	 file_ptr = fopen("myfile.txt", "r");
	
	 if (NULL == file_ptr) {
		 printf("file can't be opened \n");
		 return EXIT_FAILURE;
	 }
	
	 while ((ch = fgetc(file_ptr)) != EOF) {
		 int t = ch - '0';
		 if(j==size){
			 j=0;
			 i++;
		 }
		 A[i][j] = t;
		 B[i][j] = t;
		 j++;
	 }

	 fclose(file_ptr);
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