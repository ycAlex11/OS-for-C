
// Global variables matrix A,B and C are used for inter-thread communication
int** matrixB;
int** matrixA;
int** matrixC;

/*the struct include the rows and clunms(M,N,K) are used for keep track for which row and how many clunms of matrixC of the thread is computing, also which row and how many clunms of matrix A and B are using*/ 
typedef struct
{
	int m;
	int n;
	int k;

}Data;
//declare a pointer to Data struct and can change the vaule of m,n,k
Data* data;

//read function for read the data from readfile and insert data into martix A and B
//import int rows, int clums: the rows and clums of matrix A and B
//imprt char* file : a char pointer point to the file name;
//import int** matrix: the pointer point to martix A and B
void read(int rows,int clums,char* file,int** matrix);

