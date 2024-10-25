#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define N 800  // Size of the matrices

void multiply_row_by_matrix(int *row, int *B, int *result_row, int n) {
    for (int j = 0; j < n; j++) {
        result_row[j] = 0;
        for (int k = 0; k < n; k++) {
            result_row[j] += row[k] * B[k * n + j];  // Dot product of row and column
        }
    }
}

int main(int argc, char** argv) {
    int rank, size;
    int A[N][N], B[N][N], C[N][N];  // Matrices
    int local_A[N];  // Buffer for scattered rows of A
    int local_C[N];  // Buffer for result row of C
    double start_time, end_time;  // Variables to store start and end times

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    start_time = MPI_Wtime();

    if (rank == 0) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                A[i][j] = i * N + j + 1;  // Initialize A
                B[i][j] = (i + j) % N + 1;  // Initialize B
            }
        }
    }
    MPI_Bcast(B, N * N, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(A, N, MPI_INT, local_A, N, MPI_INT, 0, MPI_COMM_WORLD);
    multiply_row_by_matrix(local_A, (int*)B, local_C, N);
    MPI_Gather(local_C, N, MPI_INT, C, N, MPI_INT, 0, MPI_COMM_WORLD);

    end_time = MPI_Wtime();

    if (rank == 0) {
        printf("Time taken for matrix multiplication: %f seconds\n", end_time - start_time);
    }

    MPI_Finalize();
    return 0;
}
