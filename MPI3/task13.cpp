#include <mpi.h>
#include <iostream>

int main(int argc, char** argv) {

    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int n = 100;
    const int part = 20;

    int b[n];
    int a[n][n];
    int a_part[part][n];

    srand(time(nullptr));

    if (rank == 0) {
        for (int i = 0; i < n; ++i) {
            b[i] = i;
            for (int j = 0; j < n; ++j) {
                a[i][j] = rand() % 9 + 1;
            }
        }
    }

    MPI_Bcast(b, n, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(a, part * n, MPI_INT, a_part, part * n, MPI_INT, 0, MPI_COMM_WORLD);

    int result[part];

    for (int i = 0; i < part; i++) {
        result[i] = 0;
        for (int j = 0; j < n; j++) {
            result[i] += a_part[i][j] * b[j];
        }
    }

    int result_all[n];

    MPI_Gather(result, part, MPI_INT, result_all, part, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Result: ");
        for (int i = 0; i < n; ++i) {
            printf("%d ", result_all[i]);
        }
        printf("\n");
    }

    MPI_Finalize();

    return 0;
}