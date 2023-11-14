#include <iostream>
#include <mpi.h>

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
            x[i] = i + 1;
            printf("%d ", x[i]);
        }
        printf("\n\n");
    }

    MPI_Scatter(&x[0], part, MPI_INT, &y[0], part, MPI_INT, 0, MPI_COMM_WORLD);

    int local_max = 0;
    for (int i = 0; i < part; i++) {
        if (y[i] > local_max) {
            local_max = y[i];
        }
    }

    int local_max_to_rank[2];
    int global_result;

    local_max_to_rank[0] = local_max;
    local_max_to_rank[1] = rank;
    int result[size][2];

    MPI_Gather(local_max_to_rank, 2, MPI_INT, result, 2, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Reduce(&local_max_to_rank, &global_result, 1, MPI_2INT, MPI_MAXLOC, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        for (int i = 0; i < size; i++) {
            printf("Local max for %d: %d\n", result[i][1], result[i][0]);
        }
        printf("Global max: %d\n", global_result);
    }

    MPI_Finalize();

    return 0;
}