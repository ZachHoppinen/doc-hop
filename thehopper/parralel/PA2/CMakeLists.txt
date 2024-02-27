set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_SRC_DIR ${CMAKE_HOME_DIRECTORY}/src)
set(CMAKE_INCLUDE_PATH ${CMAKE_HOME_DIRECTORY}/include)
set(CMAKE_TEST_DIR ${CMAKE_HOME_DIRECTORY}/tests)
set(CMAKE_SRC_DIR ${CMAKE_HOME_DIRECTORY}/src)

cmake_minimum_required(VERSION 3.9)
project(CS530-PA1)

find_package(OpenMP)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

include_directories(${CMAKE_INCLUDE_PATH})
include_directories(${CMAKE_SRC_DIR})

add_executable( fib ${CMAKE_SRC_DIR}/fib_driver.cpp ${CMAKE_SRC_DIR}/fib.cpp)
target_link_libraries(fib PUBLIC OpenMP::OpenMP_CXX)

add_executable( pi_leibniz ${CMAKE_SRC_DIR}/pi_leibniz_driver.cpp ${CMAKE_SRC_DIR}/pi_leibniz.cpp ${CMAKE_SRC_DIR}/utilities.cpp)
target_link_libraries(pi_leibniz PUBLIC OpenMP::OpenMP_CXX)

add_executable( pi_mc ${CMAKE_SRC_DIR}/pi_mc_driver.cpp ${CMAKE_SRC_DIR}/pi_mc.cpp ${CMAKE_SRC_DIR}/utilities.cpp)
target_link_libraries( pi_mc PUBLIC OpenMP::OpenMP_CXX)

add_executable( matrix_vector_mul ${CMAKE_SRC_DIR}/matrix_vector_mul_driver.cpp ${CMAKE_SRC_DIR}/utilities.cpp)
target_link_libraries( matrix_vector_mul PUBLIC OpenMP::OpenMP_CXX)

add_executable( matrix_mul ${CMAKE_SRC_DIR}/matrix_mul_driver.cpp ${CMAKE_SRC_DIR}/utilities.cpp)
target_link_libraries( matrix_mul PUBLIC OpenMP::OpenMP_CXX)

add_executable( matrix_mul_tester ${CMAKE_SRC_DIR}/matrix_mul_driver_tester.cpp ${CMAKE_SRC_DIR}/utilities.cpp)
target_link_libraries( matrix_mul_tester PUBLIC OpenMP::OpenMP_CXX)

add_executable( matrix_vector_mul_tester ${CMAKE_SRC_DIR}/matrix_vector_mul_driver_tester.cpp ${CMAKE_SRC_DIR}/utilities.cpp)
target_link_libraries( matrix_vector_mul_tester PUBLIC OpenMP::OpenMP_CXX)

add_executable( openmp_test ${CMAKE_SRC_DIR}/openmp_hello_driver.cpp)
target_link_libraries( openmp_test PUBLIC OpenMP::OpenMP_CXX)

include(GoogleTest)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin_test)

file(GLOB_RECURSE SRCS ${CMAKE_INCLUDE_PATH} "src/*.cpp")
list(FILTER SRCS EXCLUDE REGEX "driver.cpp$")
list(FILTER SRCS EXCLUDE REGEX "driver_tester.cpp$")

file(GLOB TESTS RELATIVE ${CMAKE_SRC_DIR} "tests/*.cpp")
foreach(test_fp ${TESTS})
  string( REPLACE ".cpp" "" name ${test_fp} )
  string( REPLACE "../tests/" "" name ${name} )
  string( CONCAT src_fp "tests/" ${test_fp})
  add_executable( ${name} ${src_fp} ${SRCS})
  target_link_libraries( ${name} GTest::gtest_main )
  gtest_discover_tests(${name})
endforeach()
