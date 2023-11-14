#include <iostream>
#include <mpi.h>

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        int* received_values = new int[size];
        for (int sender_rank = 1; sender_rank < size; sender_rank++) {
            MPI_Recv(&received_values[sender_rank], 1, MPI_INT, sender_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        for (int sender_rank = 1; sender_rank < size; sender_rank++) {
            std::cout << "Received value " << received_values[sender_rank] << " from process " << sender_rank << std::endl;
        }

    } else {
        int value = rank * 10;
        MPI_Send(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}
