#include <iostream>
#include <mpi.h>

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        std::cerr << "This program should be run with at least 2 processes." << std::endl;
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    if (rank == 1) {
        const int array_size = 10;
        int data_to_send[array_size];
        for (int i = 0; i < array_size; i++) {
            data_to_send[i] = i * 10;
        }

        for (int dest = 0; dest < size; dest++) {
            if (dest != 1) {
                MPI_Send(data_to_send, array_size, MPI_INT, dest, 0, MPI_COMM_WORLD);
            }
        }
    } else {
        int source = 1;
        MPI_Status status;
        MPI_Probe(source, 0, MPI_COMM_WORLD, &status);

        int count;
        MPI_Get_count(&status, MPI_INT, &count);

        int* received_data = new int[count];
        MPI_Recv(received_data, count, MPI_INT, source, 0, MPI_COMM_WORLD, &status);


        std::cout << "Received array on process " << rank << ":" << std::endl;
        for (int i = 0; i < count; i++) {
            std::cout << received_data[i] << " ";
        }
        std::cout << std::endl;

        delete[] received_data;
    }

    MPI_Finalize();

    return 0;
}
