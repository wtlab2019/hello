#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
int main(int argc,char * argv[])
{
        int numtasks,rank,dest,source,rc;
        int count,tag=1;
        char inmsg,outmsg='x';
        MPI_Status stat;
        MPI_Init(&argc,&argv);
        MPI_Comm_size(MPI_COMM_WORLD,&numtasks);
        MPI_Comm_rank(MPI_COMM_WORLD,&rank);
        if(rank==0)
        {
                if(numtasks>2)
                printf("Number of tasks=%d. Only two needed ignore the extra \n",numtasks);
                dest=1;
                source=1;
                rc=MPI_Send(&outmsg,1,MPI_CHAR,dest,tag,MPI_COMM_WORLD);
                rc=MPI_Recv(&inmsg,1,MPI_CHAR,source,tag,MPI_COMM_WORLD,&stat);
        }
        else if (rank==1)
        {
                dest=0;
                source=0;
                rc=MPI_Recv(&inmsg,1,MPI_CHAR,source,tag,MPI_COMM_WORLD,&stat);
                rc=MPI_Send(&outmsg,1,MPI_CHAR,dest,tag,MPI_COMM_WORLD);
        }
        if(rank<2)
        {
                rc=MPI_Get_count(&stat,MPI_CHAR,&count);
                printf("Task %d = Received %d char(s) from task %d with tag
%d\n",rank,count,stat.MPI_SOURCE,stat.MPI_TAG);
        }
        MPI_Finalize();
}