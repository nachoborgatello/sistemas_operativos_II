#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
int main(int argc, char *argv[])
{
    int err;
    err = MPI_Init(&argc, &argv);
    if (err)
    {
        perror("MPI_Init");
        exit(1);
    }
    printf("Hello world!\n");
    err = MPI_Finalize();
    if (err)
    {
        perror("MPI_Finalize");
        exit(1);
    }
}
mpicc - o hello hello.c mpirun - np 4 hello #np : número de procesos