cmake_minimum_required(VERSION 3.16)
project(MPI_Sync_Exercises
  VERSION 0.0.1
  LANGUAGES CXX
)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(MPI REQUIRED)

# add_subdirectory(source)

add_executable(ucl_1 ucl_1.cpp)
target_link_libraries(ucl_1 PUBLIC MPI::MPI_CXX)
add_executable(ucl_2 ucl_2.cpp)
target_link_libraries(ucl_2 PUBLIC MPI::MPI_CXX)
add_executable(ucl_3 ucl_3.cpp)
target_link_libraries(ucl_3 PUBLIC MPI::MPI_CXX)