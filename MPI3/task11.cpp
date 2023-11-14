#include <iostream>
#include <mpi.h>
#include <valarray>

int main(int argc, char** argv) {

    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int const n = 100;
    int const part = 20;
    int x[n];
    int y[part];

    if (rank == 0) {
        printf("x: ");
        for (int i = 0; i < n; i++) {
            x[i] = i * 2 * pow(-1,i);
            printf("%d ", x[i]);
        }
        printf("\n\n");
    }

    MPI_Scatter(&x[0], part, MPI_INT, &y[0], part, MPI_INT, 0, MPI_COMM_WORLD);

    int sum = 0;
    for (int i = 0; i < part; i++) {
        sum += abs(y[i]);
    }

    int result;
    MPI_Reduce(&sum, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("||x||: %d\n\n", result);
    }

    MPI_Finalize();

    return 0;
}