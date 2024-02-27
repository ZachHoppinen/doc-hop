# Set directories up
# this is where binaries will be saved to
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# these are directories that are included or searched through
set(CMAKE_SRC_DIR ${CMAKE_HOME_DIRECTORY}/src)
set(CMAKE_INCLUDE_PATH ${CMAKE_HOME_DIRECTORY}/include)
set(CMAKE_TEST_DIR ${CMAKE_HOME_DIRECTORY}/tests)
set(CMAKE_SRC_DIR ${CMAKE_HOME_DIRECTORY}/src)

# Set CMake Required Version
cmake_minimum_required(VERSION 3.9)
project(CS530-PA3)

# Find OpenMP and MPI
find_package(OpenMP)
# enable_language(Fortran)
find_package(MPI REQUIRED COMPONENTS CXX)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Collect gtest package
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Set up testing
enable_testing()

## Create exectuables
# Set up include directories
include_directories(${CMAKE_INCLUDE_PATH})
include_directories(${CMAKE_SRC_DIR})

# Pi Leibniz executable creation.
add_executable( pi_leibniz ${CMAKE_SRC_DIR}/pi_leibniz_driver.cpp ${CMAKE_SRC_DIR}/pi_leibniz.cpp ${CMAKE_SRC_DIR}/utilities.cpp)
target_link_libraries(pi_leibniz PUBLIC OpenMP::OpenMP_CXX)
target_link_libraries(pi_leibniz PUBLIC MPI::MPI_CXX)
# Pi MC executable creation
add_executable( pi_mc ${CMAKE_SRC_DIR}/pi_mc_driver.cpp ${CMAKE_SRC_DIR}/pi_mc.cpp ${CMAKE_SRC_DIR}/utilities.cpp)
target_link_libraries( pi_mc PUBLIC OpenMP::OpenMP_CXX)
target_link_libraries(pi_mc PUBLIC MPI::MPI_CXX)
# MVM executable creation
add_executable( matrix_vector_mul ${CMAKE_SRC_DIR}/matrix_vector_mul_driver.cpp ${CMAKE_SRC_DIR}/utilities.cpp)
target_link_libraries( matrix_vector_mul PUBLIC OpenMP::OpenMP_CXX)
target_link_libraries(matrix_vector_mul PUBLIC MPI::MPI_CXX)
# MMM executable creation
add_executable( matrix_mul ${CMAKE_SRC_DIR}/matrix_mul_driver.cpp ${CMAKE_SRC_DIR}/utilities.cpp)
target_link_libraries( matrix_mul PUBLIC OpenMP::OpenMP_CXX)
target_link_libraries(matrix_mul PUBLIC MPI::MPI_CXX)
# MMM Cannon executable creation
add_executable( cannon ${CMAKE_SRC_DIR}/cannon_driver.cpp ${CMAKE_SRC_DIR}/cannon.cpp ${CMAKE_SRC_DIR}/utilities.cpp)
target_link_libraries( cannon PUBLIC OpenMP::OpenMP_CXX)
target_link_libraries(cannon PUBLIC MPI::MPI_CXX)
# Create tester exectuable for MM
add_executable( matrix_mul_tester ${CMAKE_SRC_DIR}/matrix_mul_driver_tester.cpp ${CMAKE_SRC_DIR}/utilities.cpp)
target_link_libraries( matrix_mul_tester PUBLIC OpenMP::OpenMP_CXX)
target_link_libraries(matrix_mul_tester PUBLIC MPI::MPI_CXX)
# Create tester exectuable for MV
add_executable( matrix_vector_mul_tester ${CMAKE_SRC_DIR}/matrix_vector_mul_driver_tester.cpp ${CMAKE_SRC_DIR}/utilities.cpp)
target_link_libraries( matrix_vector_mul_tester PUBLIC OpenMP::OpenMP_CXX)
target_link_libraries(matrix_vector_mul_tester PUBLIC MPI::MPI_CXX)
# Add exectuable to test MPI functionality
add_executable( mpi_test ${CMAKE_SRC_DIR}/mpi_hello_driver.cpp)
target_link_libraries( mpi_test PUBLIC OpenMP::OpenMP_CXX)
target_link_libraries(mpi_test PUBLIC MPI::MPI_CXX)
# MPI MVM executable creation
add_executable( mpi_matrix_vector_mul ${CMAKE_SRC_DIR}/mpi_mat_vector_mul_driver.cpp ${CMAKE_SRC_DIR}/utilities.cpp)
target_link_libraries( mpi_matrix_vector_mul PUBLIC OpenMP::OpenMP_CXX)
target_link_libraries(mpi_matrix_vector_mul PUBLIC MPI::MPI_CXX)
# MPI MM executable creation
add_executable( mpi_matrix_mul ${CMAKE_SRC_DIR}/mpi_mat_mul_driver.cpp ${CMAKE_SRC_DIR}/utilities.cpp)
target_link_libraries( mpi_matrix_mul PUBLIC OpenMP::OpenMP_CXX)
target_link_libraries(mpi_matrix_mul PUBLIC MPI::MPI_CXX)

## Set up Testing
# Include gtest with everything
include(GoogleTest)
# set output directory for testing binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin_test)

# search through src files for not driver files to link to tests
file(GLOB_RECURSE SRCS ${CMAKE_INCLUDE_PATH} "src/*.cpp")
list(FILTER SRCS EXCLUDE REGEX "driver.cpp$")
list(FILTER SRCS EXCLUDE REGEX "driver_tester.cpp$")
#list(FILTER SRCS EXCLUDE REGEX "cannon.cpp$")
# Find all test files
file(GLOB TESTS RELATIVE ${CMAKE_SRC_DIR} "tests/*.cpp")
# loop through each test and link it to all src files to be able to test them
foreach(test_fp ${TESTS})
  string( REPLACE ".cpp" "" name ${test_fp} )
  string( REPLACE "../tests/" "" name ${name} )
  string( CONCAT src_fp "tests/" ${test_fp})
  add_executable( ${name} ${src_fp} ${SRCS})
  target_link_libraries( ${name} PUBLIC GTest::gtest_main MPI::MPI_CXX)
  gtest_discover_tests(${name})
endforeach()
# End of CMake

