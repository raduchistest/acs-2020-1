#include <mpi.h>
#include <stdio.h>


int main (int argc, char *argv[]) 
{
  	int rank, nprocs;
	MPI_Init (&argc, &argv);	

	MPI_Comm_rank (MPI_COMM_WORLD, &rank);	

	MPI_Comm_size (MPI_COMM_WORLD, &nprocs);

	printf("Hello world from process %d of %d\n", rank, nprocs);
	MPI_Finalize();			

}
