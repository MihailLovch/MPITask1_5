cmake_minimum_required(VERSION 3.26)
project(MPITask1_5)

set(CMAKE_CXX_STANDARD 17)

find_package(MPI REQUIRED)

add_executable(project MPI1/main.cpp)
target_link_libraries(project PUBLIC MPI::MPI_CXX)

add_executable(task1 MPI1/task1.cpp)
target_link_libraries(task1 PUBLIC MPI::MPI_CXX)

add_executable(task2 MPI1/task2.cpp)
target_link_libraries(task2 PUBLIC MPI::MPI_CXX)

add_executable(task3 MPI1/task3.cpp)
target_link_libraries(task3 PUBLIC MPI::MPI_CXX)

add_executable(task4 MPI1/task4.cpp)
target_link_libraries(task4 PUBLIC MPI::MPI_CXX)

add_executable(task5 MPI1/task5.cpp)
target_link_libraries(task5 PUBLIC MPI::MPI_CXX)

add_executable(task6 MPI2/task6.cpp)
target_link_libraries(task6 PUBLIC MPI::MPI_CXX)

add_executable(task7 MPI2/task7.cpp)
target_link_libraries(task7 PUBLIC MPI::MPI_CXX)

add_executable(task8 MPI2/task8.cpp)
target_link_libraries(task8 PUBLIC MPI::MPI_CXX)

add_executable(task9 MPI2/task9.cpp)
target_link_libraries(task9 PUBLIC MPI::MPI_CXX)

add_executable(task10 MPI2/task10.cpp)
target_link_libraries(task10 PUBLIC MPI::MPI_CXX)

add_executable(task11 MPI3/task11.cpp)
target_link_libraries(task11 PUBLIC MPI::MPI_CXX)

add_executable(task12 MPI3/task12.cpp)
target_link_libraries(task12 PUBLIC MPI::MPI_CXX)

add_executable(task13 MPI3/task13.cpp)
target_link_libraries(task13 PUBLIC MPI::MPI_CXX)

add_executable(task14 MPI3/task14.cpp)
target_link_libraries(task14 PUBLIC MPI::MPI_CXX)

add_executable(task15 MPI3/task15.cpp)
target_link_libraries(task15 PUBLIC MPI::MPI_CXX)
