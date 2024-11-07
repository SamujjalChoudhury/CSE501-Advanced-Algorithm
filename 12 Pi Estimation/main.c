#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
#include <omp.h>

double estimate_pi(int num_points) {
    int inside_circle = 0;

    #pragma omp parallel
    {
        unsigned int seed = time(NULL) ^ omp_get_thread_num();
        int local_inside_circle = 0;

        #pragma omp for
        for (int i = 0; i < num_points; i++) {
            double x = (double)rand_r(&seed) / RAND_MAX * 2 - 1;
            double y = (double)rand_r(&seed) / RAND_MAX * 2 - 1;

            if (x * x + y * y <= 1) {
                local_inside_circle++;
            }
        }

        #pragma omp atomic
        inside_circle += local_inside_circle;
    }

    return inside_circle;
}

int main(int argc, char *argv[]) {
    int num_points = 1000000;
    int rank, size, points_per_process, inside_circle, global_inside_circle;
    double pi_estimate;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double start_time = MPI_Wtime();

    points_per_process = num_points / size;
    inside_circle = estimate_pi(points_per_process);

    MPI_Reduce(&inside_circle, &global_inside_circle, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        pi_estimate = 4.0 * global_inside_circle / num_points;
        double end_time = MPI_Wtime();
        printf("Estimated value of pi: %f\n", pi_estimate);
        printf("Execution time: %f seconds\n", end_time - start_time);
    }

    MPI_Finalize();
    return 0;
}