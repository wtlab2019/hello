#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<string.h>

const int max=1024;

void insert_sorted(long * sorted,int count,long value)
{
	int i=0;
	sorted[count]=value;
	if(count==0)
		return;
	for(i=count;i>=0;i--)
	{
		if(value<sorted[i-1])
			sorted[i]=sorted[i-1];
		else
			break;
	}
	sorted[i]=value;
}

int main(int argc,char * argv[])
{
	int temp[10],size,rank,gath_buf[10];
	FILE *infile=NULL;
	long sorted[1024];
	long value,count=0,err,tot,i=0;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	infile=fopen("abc.txt","r");
	if(NULL==infile)
	{
		perror("fopen");
		return -1;
	}
	err=MPI_Scatter(&infile,1,MPI_INT,&tot,1,MPI_INT,0,MPI_COMM_WORLD);
	while(!feof(infile))
	{
		fscanf(infile,"%d\n",&value);
		insert_sorted(sorted,count,value);
		++count;
	}
	for(i=0;i<count;i++)
	{
		temp[i]=sorted[i];
	}
	err=MPI_Gather(&temp,1,MPI_INT,&gath_buf,1,MPI_INT,0,MPI_COMM_WORLD);
	if(rank==0)
	{
		for(i=0;i<count;i++)
		{
			printf("result from all processors is %d\n",sorted[i]);
		
		}
	}
	if(infile)
	{
		fclose(infile);
		infile=NULL;
	}
	MPI_Finalize();
	return 0;
}