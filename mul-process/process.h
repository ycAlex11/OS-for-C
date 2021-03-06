
//declare a struct that include subtotal and process ID
typedef struct {
	int subtotal;
	int id;
}Subtotal;

/*calc() is the function compute martix C and insert to shared memory matrixC, also create shared memory of subtotal and calcuate each row's subtotal
  import int m, int n, int k: the M,N,K from assignment specification
  import const char* martixA,const char* martixB,const char* martixC: the name of shared memory matrix A,B and C
  import int sizeC,int sizeB,int sizeA: the size of shared memory matrix A ,B and C
*/
void calc(int m,int n,int k,const char* matrixC,const char* matrixA,const char* matrixB,int sizeC,int sizeB,int sizeA);

