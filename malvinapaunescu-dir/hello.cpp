#include <stdio.h>
#include <mpi.h>
int main (){
	MPI_Init(NULL, NULL);
	printf("Hello world!\n");
	return 0;
	MPI_Finalize();
}
