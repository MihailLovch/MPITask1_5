#include <stdio.h>
#include <mpi.h>
#include <iostream>

int main(int argc, char** argv) {

    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Status status;

    int count;

    const int n = 10;
    const int elems_per_process = 5;

    int a = 2;
    int b = 3;

    if (rank == 0) {
        int x[n];
        int y[n];
        int z[n];

        for (int i = 0; i < n; i++) {
            x[i] = i + 1;
            y[i] = i * 2;
        }

        std::cout << "x: ";
        for (int i = 0; i < n; i++) {
            printf("%d ", x[i]);
        }
        std::cout << std::endl;

        std::cout << "y: ";;
        for (int i = 0; i < n; i++) {
            printf("%d ", y[i]);
        }
        std::cout << std::endl;

        int k = 1;
        for (int i = 0; i < n; i += elems_per_process) {
            MPI_Send(&x[i], elems_per_process, MPI_INT, k, 10, MPI_COMM_WORLD);
            MPI_Send(&y[i], elems_per_process, MPI_INT, k, 10, MPI_COMM_WORLD);
            k++;
        }

        k = 1;
        for (int i = 0; i < n; i += elems_per_process) {
            MPI_Recv(&z[i], elems_per_process, MPI_INT, k, 10, MPI_COMM_WORLD, &status);
            k++;
        }

        for (int i = 0; i < n; i++) {
            printf("%d ", z[i]);
        }
    } else {
        MPI_Probe(0, 10, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &count);

        int x[elems_per_process];
        int y[elems_per_process];
        int z[elems_per_process];

        MPI_Recv(&x[0], count, MPI_INT, 0, 10, MPI_COMM_WORLD, &status);
        MPI_Recv(&y[0], count, MPI_INT, 0, 10, MPI_COMM_WORLD, &status);

        for (int i = 0; i < count; i++) {
            z[i] = a * x[i] + b * y[i];
        }

        MPI_Send(&z, count, MPI_INT, 0, 10, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}