#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <mpi.h>

using namespace std;


int f(int i)
{
    if (i % 13 == 0)
    {
        return 0;
    } else
    {
        return 1;
    }
    
}

int search(int a, int b, int c, int id, int p, int *v)
{
    int i, k = 0;
    for (i = a + id; i <= b; i = i + p)
    {
        if (f(i) == c)
        {
            v[k++] = i;
        }
    }

    return k;
}

int main(int argc, char *argv[])
{
    int a = 1, b = 5467, c = 0, id, k, p, *v;
    v = new int[100];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    double wtime = MPI_Wtime();

    k = search(a, b, c, id, p, v);

    if (k > 0)
    {
        for (int i = 0; i < k; i++)
        {
            cout << "f( " << v[i] << " )=0; De la procesul " << id << "\n";
        }        
    }

    wtime = MPI_Wtime ( ) - wtime;

    MPI_Finalize();
    if (id == 0)
    {
        cout << " END in " << wtime << "\n";
    }

    return 0;
}
