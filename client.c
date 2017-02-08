#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include "timer.h"

int thread_count;  
long port;
long arraySize;
int* seed;
pthread_mutex_t mutex;

void *readWriteMessage(void* rank);  /* Thread function */

int main(int argc, char* argv[])
{

	long       thread;  /* Use long in case of a 64-bit system */
	pthread_t* thread_handles; 
	int i;
	double start, finish, elapsed;	

	thread_count = 5; 
	port = strtol(argv[1], NULL, 10);
	arraySize = strtol(argv[2], NULL, 10);
	/* Intializes random number generators */
	seed = malloc(thread_count*sizeof(int));
	for (i = 0; i < thread_count; i++)
		seed[i] = i;
   
	thread_handles = malloc (thread_count*sizeof(pthread_t)); 

	GET_TIME(start); 
	for (thread = 0; thread < thread_count; thread++)  
		pthread_create(&thread_handles[thread], NULL, readWriteMessage, (void*) thread);  

	for (thread = 0; thread < thread_count; thread++) 
		pthread_join(thread_handles[thread], NULL); 
	GET_TIME(finish);

	elapsed = finish - start;

	free(thread_handles);

	return 0;
}

void *readWriteMessage(void* rank) {

	long my_rank = (long) rank;
	
	// Find a random position in theArray for read or write
	uint16_t pos = htons(rand_r(&seed[my_rank]) % arraySize); //random position to read/write from in array
	int randNum = rand_r(&seed[my_rank]) % 20;	// write with 5% probability

	uint8_t readOrWrite; //1 for write 0 for read

	struct sockaddr_in sock_var;
	int clientFileDescriptor=socket(AF_INET,SOCK_STREAM,0);
	char str_ser[20];

// <<<<<<< HEAD
// 	sock_var.sin_addr.s_addr=inet_addr("142.244.5.74");
// 	sock_var.sin_port=2222;
// =======
	sock_var.sin_addr.s_addr=inet_addr("127.0.0.1");
	sock_var.sin_port=port;
// >>>>>>> 69d7aad6ffe22a5bd10ce267a56c42295fda1d3a
	sock_var.sin_family=AF_INET;
	int errorcode = connect(clientFileDescriptor,(struct sockaddr*)&sock_var,sizeof(sock_var));
	printf("error code no %d\n",errorcode);
	if(errorcode >=0 ) 
	{
		if (randNum >= 19) { // 5% are write operations, others are reads
			readOrWrite = 1;
			write(clientFileDescriptor, &readOrWrite, sizeof(readOrWrite));
			write(clientFileDescriptor, &pos, sizeof(pos));
		} else {
			readOrWrite = 0;
			write(clientFileDescriptor, &readOrWrite, sizeof(readOrWrite));
			write(clientFileDescriptor, &pos, sizeof(pos));
			//read(clientFileDescriptor, str_ser, sizeof(str_ser));
		}
	}
	else{
		printf("socket creation failed");
	}
		
	return NULL;
}