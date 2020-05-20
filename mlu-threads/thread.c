#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "read.h"
#include "thread.h"

int buffersize =0;

//function to create thread
pthread_t* createThread(int m,int n,int k)
{
	int i;
	
	pthread_t* tid;
	pthread_attr_t attr;
	//get the default attributes
	pthread_attr_init(&attr);
	 //malloc the memory to store all threads created
	tid = (pthread_t*)malloc(m*sizeof(pthread_t));
	 
	for(i=0;i<m;i++)
	{	//assigns which row and clunms to be computed for each thread
		data = (Data*)malloc(sizeof(Data));
		data->m=i;
		data->n = n;
		data->k =k;
		//create threads
		pthread_create(&tid[i],&attr,producter,data);
	}
	
	
	return tid;
}

void* producter(void* data)
{
	int subtotal,m,n,k;
	// retrieves the row, clumns of matrix A,B and C from Data
	m =((Data*)data)->m;
	n = ((Data*)data)->n;
	k =((Data*)data)->k;
	int i,j;
	//compute matrixC
	for(i=0;i<k;i++)
	{
		matrixC[m][i]=0;
		 for(j=0;j<n;j++)
		{
		
			matrixC[m][i] = matrixC[m][i]+(matrixA[m][j]*matrixB[j][i]);
			
		}
			
	}
	// clacuate each row's subtotal
	subtotal =0;
	for(i=0;i<k;i++)
	{
		subtotal = subtotal+matrixC[m][i];
	}
	
	///lock buffer
	pthread_mutex_lock(&mutex);
	 //If there is something in the buffer then wait
	while (buffersize!=0 )
	{pthread_cond_wait(&full,&mutex);}

	//into critical section
	subtotals.subtotal= subtotal;
	subtotals.id = pthread_self();
	buffersize =1;
	// wake up consumer
	pthread_cond_signal(&empty);
	// release the buffer 
	pthread_mutex_unlock(&mutex);
	//free the data struct
	free(data);
	
}

void* consumer(int m)
{
	int i; int total=0;
	for(i=0;i<m;i++)
	{
		// protect buffer 
		pthread_mutex_lock(&mutex);
		///* If there is nothing in the buffer then wait
		while(buffersize==0)
		{
			pthread_cond_wait(&empty,&mutex);		
		}
		//into critical section
		printf("Subtotal produced by thread with ID %lu:%d\n",subtotals.id,subtotals.subtotal);
		total = total+subtotals.subtotal;
		buffersize =0;
		// wake up producer
		pthread_cond_signal(&full);
		// release the buffer 
		pthread_mutex_unlock(&mutex);
		
	}
	
	printf("the total is:%d\n",total);
}
