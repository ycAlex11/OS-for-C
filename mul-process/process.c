#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <fcntl.h> 
#include <semaphore.h>
#include <signal.h>
#include "process.h"

/*calc() is the function compute martix C and insert to shared memory matrixC, also create shared memory of subtotal and calcuate each row's subtotal
  import int m, int n, int k: the M,N,K from assignment specification
  import const char* martixA,const char* martixB,const char* martixC: the name of shared memory matrix A,B and C
  import int sizeC,int sizeB,int sizeA: the size of shared memory matrix A ,B and C
*/

void calc(int m,int n,int k,const char* martixA,const char* martixB,const char* martixC,int sizeC,int sizeB,int sizeA)
{
	////pointer to shared memory matrixA,B and C
	int(*ptrA)[n];
	int(*ptrB)[k];
	int(*ptrC)[k];
	//shared memory file descriptor for matrixA , B and C
	int shm_fdA,shm_fdB,shm_fdC;
	//shared memory file descriptor for subtotal
	int shm_fdS;
	int i,j,l; pid_t pid ; 
	////name of the shared memory for subtotal
	const char* name ="SubtotalMemory"; 
	//get the subtotalMemory size	
	int subtotalSize = (1*sizeof(Subtotal)); Subtotal* subtotal;
	int subtotals,total;
	//// Create semaphores to be used	
	sem_t *mutex; const char* semM ="mutex";
	sem_t *empty; const char* semE ="empty";
	sem_t *full; const char* semF ="full";
	
	//open the shared memory matrixA,B; and memory map the shared memory matrixA and B
	shm_fdA = shm_open(martixA, O_CREAT|O_RDWR,0666);
	ftruncate(shm_fdA,sizeA);
	ptrA = mmap(0,sizeA,PROT_WRITE,MAP_SHARED,shm_fdA,0);
	shm_fdB = shm_open(martixB, O_CREAT|O_RDWR,0666);
	ftruncate(shm_fdB,sizeB);	
	ptrB = mmap(0,sizeB,PROT_WRITE,MAP_SHARED,shm_fdB,0);
	//open the shared memory matrix C
	shm_fdC = shm_open(martixC, O_CREAT|O_RDWR,0666);
	ftruncate(shm_fdC,sizeC);
	//memory map the shared memory matrixA and B
	ptrC = mmap(0,sizeC,PROT_WRITE,MAP_SHARED,shm_fdC,0);

	//create shared memory subtotal
	shm_fdS= shm_open(name, O_CREAT|O_RDWR,0666);
	////configure the size of the shared memory object
	ftruncate(shm_fdS,subtotalSize);
	//memory map the shared memory subtotal
	subtotal =mmap(0, subtotalSize, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fdS, 0);

	 // Opening the semaphores in read and write mode and set mutex is 1,empty is 1, full is 0
	mutex = sem_open(semM, O_CREAT, S_IRUSR | S_IWUSR, 1);
	full = sem_open(semF, O_CREAT, S_IRUSR | S_IWUSR, 0);
	empty = sem_open(semE, O_CREAT, S_IRUSR | S_IWUSR, 1);

	i=0;
	//computer each row 'M' with child processes 	
	while(i<m)
	{
		subtotals =0;
		//fork the child process
		pid = fork();	
		//if can not fork, show error msg	
		if(pid<0)
		{
			printf("error,can not create child process\n");
			exit(1);
		}
		//if create child successed
		else if(pid ==0)
		{	
			//computer each row for matrixC
			for(j=0;j<k;j++)
			{
				ptrC[i][j]=0;
				for(l=0;l<n;l++)
				{
					
					ptrC[i][j]=ptrC[i][j]+(ptrA[i][l]*ptrB[l][j]);
				}
				//get each row's subtotal
				subtotals = subtotals+ ptrC[i][j];
			}
				
				//wait on a semaphore,wait the subtotal is empty, set empty,mutex from 1 to 0, otherwise wait
				sem_wait(empty);
				sem_wait(mutex);
				
        			// start critical section  Add the subtotal to the running total
				subtotal->subtotal=subtotals;
				subtotal->id =getpid();
				//end of critical section
				// increment the value of a semaphore,set mutex back to one 
				sem_post(mutex);
				// increment the value of a semaphore,set the full from 0 to 1 and signal that the subtotal is not empty
				sem_post(full);
			
				 // Close the semaphores
				sem_close(mutex);
   		 		sem_close(empty);
   	 			sem_close(full);
		
			exit(0);
			
		}
		i++;
	
	}
	i=0; total =0;
	while(i<m)
	{
		/****Consumer process****/
		//wait on a semaphore,wait the subtotal is full, set full from 1 to 0,
		sem_wait(full);
		//set mutex from 1 to 0
		sem_wait(mutex);
		//start critical section
		printf("Subtotal produced by process with ID %d: %d\n",subtotal->id,subtotal->subtotal);
		total= total+subtotal->subtotal;
		//edn critical section
		 // increment the value of a semaphore,set mutex back to one 
		sem_post(mutex);
		// increment the value of a semaphore,set empty is one singl producer can produce stuff.
		sem_post(empty);
		
		
		i++;
	}
	printf("the total is:%d\n",total);
	//free subtotal shared memory 
	shm_unlink(name);
	//Close semaphores
	sem_close(mutex);
   	sem_close(empty);
   	sem_close(full);
	//free all semaphores's memory
	sem_unlink(semM);
    	sem_unlink(semE);
    	sem_unlink(semF);
   

    	
					
	wait(NULL);
}




