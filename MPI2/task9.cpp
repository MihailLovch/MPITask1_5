#include <iostream>
#include <mpi.h>

int main(int argc, char** argv) {

    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Status status;

    int count;

    srand(time(nullptr));
    const int N = 10;
    const int PART = 5;

    if (rank == 0) {
        int a[N][N];
        int b[N][N];
        int c[N][N];

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                a[i][j] = rand() % 9 + 1;
                b[i][j] = rand() % 9 + 1;
            }
        }

        printf("A:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d ", a[i][j]);
            }
            printf("\n");
        }

        printf("B:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d ", b[i][j]);
            }
            printf("\n");
        }

        int n = 1;
        int j = 0;
        for (int i = 0; i < N; i+=PART, n++) {
            MPI_Send(&a[i][j], PART * N, MPI_INT, n, 10, MPI_COMM_WORLD);
            MPI_Send(&b[j][j], N * N, MPI_INT, n, 10, MPI_COMM_WORLD);
        }

        n = 1;
        for (int i = 0; i < N; i+=PART, n++) {
            MPI_Recv(&c[i][j], PART * N, MPI_INT, n, 10, MPI_COMM_WORLD, &status);
        }

        printf("C:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d ", c[i][j]);
            }
            printf("\n");
        }
    } else {
        MPI_Probe(0, 10, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &count);
        int a[PART][N];
        int b[N][N];
        int c[PART][N];

        for (int i = 0; i < PART; i++) {
            for (int j = 0; j < N; j++) {
                c[i][j] = 0;
            }
        }

        MPI_Recv(&a[0][0], PART * N, MPI_INT, 0, 10, MPI_COMM_WORLD, &status);
        MPI_Recv(&b[0][0], N * N, MPI_INT, 0, 10, MPI_COMM_WORLD, &status);

        for (int i = 0; i < PART; i++) {
            for (int j = 0; j < N; j++) {
                for (int k = 0; k < N; k++) {
                    c[i][j] += a[i][k] * b[k][j];
                }
            }
        }
        MPI_Send(&c, PART * N, MPI_INT, 0, 10, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}