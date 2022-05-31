#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include "mpi.h"



int main(int argc, char* argv[])
{
    std::srand(time(NULL));
    int niter = 100;
    double x, y;
    int i, j, count = 0, mycount; 
    double z;
    double pi;
    int myid, numprocs, proc;
    MPI_Status status;
    int master = 0;
    int tag = 123;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

   
    mycount = 0;
    for (i = 0; i < niter; i++) {
        x = (double)(rand() / float(RAND_MAX));
        y = (double)(rand() / float(RAND_MAX));
        z = x * x + y * y;
        if (z <= 1)
        {
            mycount++;
           
        }
    }
    if (myid == 0) { 
        count = mycount;
        for (proc = 1; proc < numprocs; proc++) {
            MPI_Recv(&mycount, 1, MPI_REAL, proc, tag, MPI_COMM_WORLD, &status);
            count += mycount;
        }
        pi = 4.*((double)count / (niter * numprocs));
        printf("\n # liczba prob= %d , przyblizenie pi = %g \n", niter * numprocs, pi);
    }
    else { 
        printf("Procesor %d przesyla rezultat= %d do glownego procesu\n", myid, mycount
        );
        MPI_Send(&mycount, 1, MPI_REAL, master, tag, MPI_COMM_WORLD);
    }

    MPI_Finalize();            
    return 0;
}