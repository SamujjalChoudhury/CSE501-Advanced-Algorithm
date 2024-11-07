#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#define SIZE 801
int N = SIZE;
int main()
{
    struct timeval tv1, tv2;
    struct timezone tz;
    double elapsed;
    int i,j,k,n;
    float A[SIZE][SIZE];
    float c,x[SIZE-1],sum=0.0;
    n = SIZE-1;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = i * N + j + 1;  // Example initialization
        }
    }

      
    gettimeofday(&tv1, &tz);
    #pragma omp parallel for private(i,j,k) shared(A)
    for(j=1; j<=n; j++)
    {
        for(i=1; i<=n; i++)
        {
            if(i>j)
            {
                c=A[i][j]/A[j][j];
                for(k=1; k<=n+1; k++)
                {
                    A[i][k]=A[i][k]-c*A[j][k];
                }
            }
        }
    }
    x[n]=A[n][n+1]/A[n][n];
    /* this loop is for backward substitution*/
    for(i=n-1; i>=1; i--)
    {
        sum=0;
        for(j=i+1; j<=n; j++)
        {
            sum=sum+A[i][j]*x[j];
        }
        x[i]=(A[i][n+1]-sum)/A[i][i];
    }
    gettimeofday(&tv2, &tz);
    elapsed = (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
    printf("elapsed time = %f seconds.\n", elapsed);
    return 0;
}