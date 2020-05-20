
//Global variables are used for threads and parent process synchronisation
pthread_mutex_t mutex;		
pthread_cond_t empty,full;

//Global variables of struct of each row's subtotal and thread ID
typedef struct
{
	int subtotal;
	unsigned long id;
}Subtotal;
Subtotal subtotals;

//createThread function is creates the thread and assigns task
pthread_t* createThread(int m,int n,int k);
/* producter function:defines each thread's tast. A thread is compute each row of matrixC and clacuate each rows's subtotal. 
   import void* data: the data of the row to compute and how many clunms for matrix C, the row and clunms of matrix A and B
 */
void* producter(void* data);

/* consumer function: defines the parent process's task.  The process waits when the subtotal struct is empty,when the thread stores a value in the subtotal struct the process retrieves this value and prints, at the end calcuate the total of subtotals 
 import int m:the number of threads to compute matrixC and calculate the subtotals		
*/
void* consumer(int m);
