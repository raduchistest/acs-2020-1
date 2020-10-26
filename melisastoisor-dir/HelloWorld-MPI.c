#include <mpi.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len, n = 0;
    MPI_Get_processor_name(processor_name, &name_len);

	MPI_Request* request;
	MPI_Status* status;

	printf(" nProcesses: %d \n", nProcesses);

	int vectorLength = 10000;
	int* vector = new int[vectorLength];
	int sum = 0, sumRez = 0;
	double total_my_bcast_time = 0;
	if (processorRank == ROOT)
	{
		//read file
		FILE *pFile; 
		pFile = fopen ("vector.txt", "w+");
		fscanf
		int read_ct = 0;
		char* buffer = new char[10];

		while (!file.eof())
		{
			fscanf(pFile, "%s", buffer); 
			*(vector + read_ct) = atoi(buffer);
			read_ct++;
		}
		total_my_bcast_time -= MPI_Wtime();
	}	
	MPI_Bcast(vector, vectorLength, MPI_INT, ROOT, MPI_COMM_WORLD);

	request = new MPI_Request[nProcesses];
	status = new MPI_Status[nProcesses];

	//check if each process gets the same number of jobs
	if ((vectorLength % nProcesses) == 0)
	{
		n = vectorLength / nProcesses;
	}
	else
	{
		n = vectorLength / nProcesses + 1;
	}
	for (int i = 0; i < n; i++)
	{
		if ((i + (vectorLength / nProcesses) * processorRank) >= vectorLength)
		{
			continue;
		}
		sum += vector[i + (vectorLength / nProcesses) * processorRank];
	}

	if (processorRank == ROOT)
	{
		sumRez += sum;

		for (int k = 1; k < nProcesses; k++)
		{
			//receiveSum from proc k
			MPI_Recv(&sum, 1, MPI_INT, k, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			sumRez += sum;
		}
		printf("Suma: %d \n", sumRez);
		total_my_bcast_time += MPI_Wtime();
		printf("Exec time: %f \n", total_my_bcast_time); 
	}
	else
	{
		//Send
		MPI_Isend(&sum, 1, MPI_FLOAT, 0, 123, MPI_COMM_WORLD, &request[processorRank]);
	}
    // Finalize the MPI environment.
    MPI_Finalize();
}