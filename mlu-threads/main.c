#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read.h"
#include "thread.h"
int main(int argc,char* argv[])
{
	if(argc==6)	
	{
		int m = atoi(argv[3]);
		int n = atoi(argv[4]);
		int k = atoi(argv[5]);
		//rows and clunms must be greater than 0
		if(m>0&&n>0&&k>0)
		{
		int i,j;
		pthread_t* threads;
		//malloc the memory for matrix A,B and C
		matrixA=(int**)malloc(m*sizeof(int*));
		for(i=0;i<m;i++)
		{
			matrixA[i]=(int*)malloc(n*sizeof(int));
		}
		matrixB=(int**)malloc(n*sizeof(int*));
		for(j=0;j<n;j++)
		{
			matrixB[j]=(int*)malloc(k*sizeof(int));
		}
		matrixC=(int**)malloc(m*sizeof(int*));
		for(i=0;i<m;i++)
		{
			matrixC[i]=(int*)malloc(k*sizeof(int));
		}
		
		//read the data from read file and insert into matrix A and B
		read(m,n,argv[1],matrixA);
		read(n,k,argv[2],matrixB);
		 // Initialize the mutex and condition variables
		pthread_mutex_init(&mutex,NULL);
		pthread_cond_init(&empty, NULL);		
  		pthread_cond_init(&full, NULL);
		
		//call createThread function that create threads to computer matrixC 
		threads = createThread(m,n,k);
		//clacuate each subtotals and total. like consumer
		consumer(m);	
		
		//join on each thread	
		for(i=0;i<m;i++)
		{
			pthread_join(threads[i],NULL);
		}

		//free each thread
		free(threads);
                // Destroying the conditional variables and mutex used
                pthread_cond_destroy(&empty);
                pthread_cond_destroy(&full);
                pthread_mutex_destroy(&mutex);
		//free the memory of matrix A,B and C
		for(i=0;i<m;i++)
		{
			free(matrixC[i]);
			
		}	
		free(matrixC);
		for(i=0;i<m;i++)
		{
			free(matrixA[i]);
		}
		free(matrixA);
		for(i=0;i<n;i++)
		{
			free(matrixB[i]);
		}
		free(matrixB);
		}
		//error msg for if rows and clunms are less than 0
		else
		{
			printf("error, rows and clunms must be greater than 0");
		}
				
	}
	//error msg for command line arguments
	else
	{
		printf("error, must be six command line arguments\n");
	}	

}

