/*
Resources used: https://iq.opengenus.org/cannon-algorithm-distributed-matrix-multiplication/
https://www.bu.edu/tech/support/research/training-consulting/online-tutorials/mpi/more/mpi_cart_create/
https://www.mpich.org/static/docs/v3.2/www3/MPI_Cart_shift.html
https://stackoverflow.com/questions/59157665/scattering-and-gathering-scatterv-gatherv-portions-of-a-2d-array-using-c-mpi
https://www.mpich.org/static/docs/v3.1/www3/MPI_Type_create_subarray.html

*/
#include "cannon.h"

int main(int argc, char** argv) {

    int rows;
    if (argc == 2) rows = atoi(argv[1]);
    else{
        printf("Incorrect number of arguments.");
        // MPI_Finalize();
        return -1;
    }
    
    int *final;

    final = cannon(rows, argc, argv);
    MPI_Finalize();
    return 0;
}
