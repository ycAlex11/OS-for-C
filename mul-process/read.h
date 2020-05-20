
/*create function is for create the shared memory for matrix A,B,C
  import int rows, int clums:the rows, and clunms 
  import const char* name:the name of the shared memory
  import a pointer for the size, so can change the size in create function
*/
void create(int rows,int clums,const char* name,int* size);

/*read function is for read the data from readfile, and insert to shared memory
  import a char pointer of char* file: the name of readfile
  import int rows, int clums:the rows, and clunms 
  import const char* name:the name of the shared memory
  import int size: size of the shared memory
*/
void read(char* file, int rows, int clums,const char* name,int size);
