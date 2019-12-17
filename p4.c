#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
typedef long long ABC;
int main(int argc,char *argv[])
{
        int n=0;
        int size,rank,first,last,i;
        ABC prod=1,result,root=0;
        MPI_Init(&argc,&argv);
        MPI_Comm_size(MPI_COMM_WORLD,&size);
        MPI_Comm_rank(MPI_COMM_WORLD,&rank);
        if(rank==root)
        {
                printf("\nEnter the value of n\n");
                scanf("%d",&n);
        }
        MPI_Bcast(&n,1,MPI_LONG_LONG,root,MPI_COMM_WORLD);
        first=(rank*n)/size;
        last=((rank+1)*n)/size;
        for(i=first+1;i<=last;i++)
                prod*=i;
        MPI_Reduce(&prod,&result,1,MPI_LONG_LONG,MPI_PROD,root,MPI_COMM_WORLD);
        if(rank==root)
                printf("The factorial of %d is %d\n",n,result);
        MPI_Finalize();
}


