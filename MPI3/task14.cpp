#include <mpi.h>
#include <iostream>

int main(int argc, char** argv) {

    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int result;

    const int n = 100;
    const int part = 20;

    int A[n][n];
    int a[part][n];

    srand(time(nullptr));

    MPI_Scatter(&A[rank * part][0], part * n, MPI_INT, &a[0][0], part * n, MPI_INT, 0, MPI_COMM_WORLD);

    int sum = 0;
    int max = 0;
    for (int i = 0; i < part; i++) {
        sum = 0;
        for (int j = 0; j < n; j++) {
            sum += abs(a[i][j]);
        }
        if (sum > max) {
            max = sum;
        }
    }

    MPI_Reduce(&max, &result, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("||A||: %d\n", result);
    }

    MPI_Finalize();

    return 0;
}