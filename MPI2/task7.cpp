#include <iostream>
#include <mpi.h>

int main(int argc, char** argv) {

    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Status status;
    int count;

    srand(time(nullptr));

    const int n = 10;
    const int elements_per_process = 5;

    if (rank == 0) {
        int matrix[n][n];
        int b[n];
        int c[n];

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                matrix[i][j] = rand() % 9 + 1;
            }
            b[i] = rand() % 9 + 1;
        }

        printf("matrix A:\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("%d ", matrix[i][j]);
            }
            printf("\n");
        }

        printf("b:\n");
        for (int i = 0; i < n; i++) {
            printf("%d ", b[i]);
        }

        int k = 1;
        int j = 0;
        for (int i = 0; i < n; i+=5) {
            MPI_Send(&matrix[i][j], elements_per_process * n, MPI_INT, k, 10, MPI_COMM_WORLD);
            MPI_Send(&b[j], n, MPI_INT, k, 10, MPI_COMM_WORLD);
            k++;
        }

        k = 1;
        for (int i = 0; i < n; i+=5) {
            MPI_Recv(&c[i], elements_per_process, MPI_INT, k, 10, MPI_COMM_WORLD, &status);
            k++;
        }

        printf("\nC:\n");
        for (int i = 0; i < n; i++) {
            printf("%d ", c[i]);
        }
    } else {
        MPI_Probe(0, 10, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &count);
        int matrix[elements_per_process][n];
        int b[n];
        int c[elements_per_process];

        for (int i = 0; i < elements_per_process; i++) {
            c[i] = 0;
        }

        MPI_Recv(&matrix[0][0], elements_per_process * n, MPI_INT, 0, 10, MPI_COMM_WORLD, &status);
        MPI_Recv(&b[0], n, MPI_INT, 0, 10, MPI_COMM_WORLD, &status);

        for (int i = 0; i < elements_per_process; i++) {
            for (int j = 0; j < n; j++) {
                c[i] += matrix[i][j] * b[j];
            }
        }
        MPI_Send(&c, elements_per_process, MPI_INT, 0, 10, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}