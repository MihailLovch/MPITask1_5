#include <iostream>
#include <cstdlib>
#include <ctime>
#include <mpi.h>

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 2) {
        std::cerr << "This program should be run with exactly 2 processes." << std::endl;
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    if (rank == 0) {
        const int array_size = 10;
        int a[array_size];

        srand(time(NULL));
        for (int i = 0; i < array_size; i++) {
            a[i] = rand() % 100;
        }

        MPI_Send(a, array_size, MPI_INT, 1, 0, MPI_COMM_WORLD);
    } else if (rank == 1) {
        const int array_size = 10;
        int received_array[array_size];

        MPI_Recv(received_array, array_size, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        std::cout << "Received array on process 1:" << std::endl;
        for (int i = 0; i < array_size; i++) {
            std::cout << received_array[i] << " ";
        }
        std::cout << std::endl;
    }

    MPI_Finalize();

    return 0;
}
