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
        int a_transposed[n][n];

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                a[i][j] = rand() % 9 + 1;
            }
        }

        printf("A initial:\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("%d ", a[i][j]);
            }
            printf("\n");
        }

        int k = 1;
        int j = 0;
        int a_temp[n][elements_per_process];
        for (int i = 0; i < n; i+=elements_per_process) {
            for (int q = 0; q < n; q++) {
                for (int g = 0; g < elements_per_process; g++) {
                    a_temp[q][g] = a[q][g + elements_per_process * (k - 1)];
                }
            }
            MPI_Send(&a_temp[j][j], elements_per_process * n, MPI_INT, k, 10, MPI_COMM_WORLD);
            k++;
        }

        k = 1;
        for (int i = 0; i < n; i+=elements_per_process) {
            MPI_Recv(&a_transposed[i][j], elements_per_process * n, MPI_INT, k, 10, MPI_COMM_WORLD, &status);
            k++;
        }

        printf("A Transposed:\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("%d ", a_transposed[i][j]);
            }
            printf("\n");
        }
    } else {
        MPI_Probe(0, 10, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &count);
        int a[n][elements_per_process];
        int a_transposed[elements_per_process][n];

        for (int i = 0; i < elements_per_process; i++) {
            for (int j = 0; j < n; j++) {
                a_transposed[i][j] = 0;
            }
        }

        MPI_Recv(&a[0][0], elements_per_process * n, MPI_INT, 0, 10, MPI_COMM_WORLD, &status);

        for (int i = 0; i < elements_per_process; i++) {
            for (int j = 0; j < n; j++) {
                a_transposed[i][j] = a[j][i];
            }
        }
        MPI_Send(&a_transposed, elements_per_process * n, MPI_INT, 0, 10, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}