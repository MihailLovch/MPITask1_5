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
        int a[n][n];
        int b[n][n];
        int c[n][n];

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                a[i][j] = rand() % 9 + 1;
                b[i][j] = rand() % 9 + 1;
            }
        }

        printf("A:\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("%d ", a[i][j]);
            }
            printf("\n");
        }

        printf("B:\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("%d ", b[i][j]);
            }
            printf("\n");
        }

        int k = 1;
        int j = 0;
        for (int i = 0; i < n; i+=5) {
            MPI_Send(&a[i][j], elements_per_process * n, MPI_INT, k, 10, MPI_COMM_WORLD);
            MPI_Send(&b[i][j], elements_per_process * n, MPI_INT, k, 10, MPI_COMM_WORLD);
            k++;
        }

        k = 1;
        for (int i = 0; i < n; i+=5) {
            MPI_Recv(&c[i][j], elements_per_process * n, MPI_INT, k, 10, MPI_COMM_WORLD, &status);
            k++;
        }

        printf("C:\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("%d ", c[i][j]);
            }
            printf("\n");
        }
    } else {
        MPI_Probe(0, 10, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &count);
        int a[elements_per_process][n];
        int b[elements_per_process][n];
        int c[elements_per_process][n];

        MPI_Recv(&a[0][0], count, MPI_INT, 0, 10, MPI_COMM_WORLD, &status);
        MPI_Recv(&b[0][0], count, MPI_INT, 0, 10, MPI_COMM_WORLD, &status);

        for (int i = 0; i < elements_per_process; i++) {
            for (int j = 0; j < n; j++) {
                c[i][j] = a[i][j] * b[i][j];
            }
        }
        MPI_Send(&c, count, MPI_INT, 0, 10, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}