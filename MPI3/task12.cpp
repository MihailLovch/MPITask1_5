#include <iostream>
#include <mpi.h>
#include <random>

int main(int argc, char **argv) {

    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int const n = 100;
    int const part = 20;

    int x[n];
    int x_part[part];
    int y[n];
    int y_part[part];

    if (rank == 0) {
        for (int i = 0; i < n; ++i) {
            x[i] = i * pow(-1, i);
            y[i] = i * 2;
        }
    }

    MPI_Scatter(&x[0], part, MPI_INT, &x_part[0], part, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(&y[0], part, MPI_INT, &y_part[0], part, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("x : ");
        for (int i = 0; i < n; ++i) {
            if (i% 50 == 0){
                printf("\n");
            }
            printf("%d ", x[i]);
        }
        printf("\n\n");

        printf("y : ");
        for (int i = 0; i < n; ++i) {
            if (i% 50 == 0){
                printf("\n");
            }
            printf("%d ", y[i]);
        }
        printf("\n\n");
    }

    int sum = 0;
    for (int i = 0; i < part; ++i) {
        sum += x_part[i] * y_part[i];
    }

    int result;
    MPI_Reduce(&sum, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Result = %d\n\n", result);
    }

    MPI_Finalize();

    return 0;
}