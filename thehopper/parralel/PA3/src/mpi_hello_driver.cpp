// OpenMP program to print Hello World
// using C language
 
//MPI Header
#include <mpi.h>

#include <stdio.h>
#include <stdlib.h>
 
int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);

    // How many of us are there?
    int processor_n;
    MPI_Comm_size(MPI_COMM_WORLD, &processor_n);

    //Get my rank
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    printf("Hello world from processor %s, rank %d out of %d processors\n", processor_name, my_rank, processor_n);

    MPI_Finalize();
}