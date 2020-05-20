#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <fcntl.h> 
#include "process.h"
#include "read.h"

int main(int argc, char* argv[])
{
	// the command line arguments should be 6.
	if(argc==6)
	{
		//declare variable for M,N,K
		int m,n,k; 
		int i,j;
		//set the size for shared memory of matrixA, B and C
		int sizeA=0,sizeB=0,sizeC=0; 
		//get the rows and clunms from command line
		m = atoi(argv[3]);
		n = atoi(argv[4]);
		k = atoi(argv[5]);
		//the rows and clunms should be great 0
		if(m>0&&n>0&&k>0)
		{
			//name of the shared memory for matrix A,B and C
			const char* martixA ="martixA";
			const char* martixB= "martixB";
			const char* martixC = "martixC";
		
			//call the create function to create shared memory for matrix A,B	
			create(m,n,martixA,&sizeA);
			create(n,k,martixB,&sizeB);
	
			//call read() function to read the data from readfiles for A,B and put into shared memory matrixB and A 
			read(argv[1],m,n,martixA,sizeA);
			read(argv[2],n,k,martixB,sizeB);
			
			//create shared memory for matrix C
			create(m,k,martixC,&sizeC);
			
			//the calc() function to compute matrixC by create process and calcuate each subtotals and the total  
			calc(m,n,k,martixA,martixB,martixC,sizeC,sizeB,sizeA);
			
			//free shared memory of matrix A, B and C
			shm_unlink(martixA);
			shm_unlink(martixB);
			shm_unlink(martixC);
		}		
		else
		{
			printf("error, the rows and columns must be great than 0\n");
			
		}
	}
	else
	{
		printf("error,it should be 6 command line arguments!!!\n");
	}
	return 0;
}
