#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <fcntl.h> 
#include "read.h"

/*
	create function is for create the shared memory for matrix A,B,C
	import int rows, int clums:the rows, and clunms 
	import const char* name:the name of the shared memory
	import a pointer for the size, so can change the size in create function

*/
void create(int rows,int clums,const char* name,int* size)
{

		//calcuate the size for each shared memory
		 *size = rows*clums*(sizeof(int));

		//shared memory file descriptor 
		int shm_fd;
		//create the shared memory object
		shm_fd = shm_open(name, O_CREAT|O_RDWR,0666);
		
		//configure the size of the shared memory object
		ftruncate(shm_fd,*size);		
}
/*
	read function is for read the data from readfile, and insert to shared memory
	import a char pointer of char* file: the name of readfile
	import int rows, int clums:the rows, and clunms 
	import const char* name:the name of the shared memory
	import int size: size of the shared memory
*/

void read(char* file, int rows, int clums,const char* name,int size)
{
	FILE* fl;
	//read the readfile
	fl = fopen(file,"r");
	//if file does not exist, show error msg	
	if(fl==NULL)
	{
		perror("error, the file is not exist");
	}
	else
	{	//pointer to shared memory object
		int(*ptr)[clums]; 
		int i, j;
		int shm_fd;
		shm_fd = shm_open(name, O_CREAT|O_RDWR,0666);
		//memory map the shared memory object
		ptr = mmap(0,size,PROT_WRITE,MAP_SHARED,shm_fd,0);
		
		//read data from read file and fill into shared memory  
		for(i=0;i<rows;i++)
		{
			for(j=0;j<clums;j++)
				{
					fscanf(fl,"%d ",&ptr[i][j]);
					
					
				}
	
	
			
		}	
		
	}
	fclose(fl);
	
}
