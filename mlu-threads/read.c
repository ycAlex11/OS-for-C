#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read.h"
void read(int rows,int clums,char* file,int** matrix)
{
	FILE* fl;
	fl =fopen(file,"r"); int i,j;
	//if readfile does not exist then error msg
	if(fl==NULL)
	{
		perror("error, the read file does not exist!!!!\n");
	}
	else
	{
		//read the data from readfile and insert into matrix A and B
		for(i=0;i<rows;i++)
		{
			for(j=0;j<clums;j++)
			{
				fscanf(fl,"%d ",&matrix[i][j]);
				
			}
			
		}
		
	}
	//close readfile
	fclose(fl);
}

