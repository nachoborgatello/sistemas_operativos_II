/* Envío y recepción simples */
#include <stdio.h>
#include <mpi.h>
int main(int argc, char **argv)
{
    int myrank;
    double a[100];
    MPI_Status status;
    MPI_Init(&argc, &argv); /* Inicialización MPI */
    /* Obtención del rango */
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    if (myrank == 0) /* Envío del mensaje */
        MPI_Send(a, 100, MPI_DOUBLE, 1, 17,
                 MPI_COMM_WORLD);
    else if (myrank == 1) /* Recepción del mensaje */
        MPI_Recv(a, 100, MPI_DOUBLE, 0, 17,
                 MPI_COMM_WORLD, &status);
    MPI_Finalize(); /* Finalización MPI */
}