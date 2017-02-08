#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>

#define STR_LEN 64

long port;
long arraySize;
char **theArray;
pthread_mutex_t *mutex;

void *ServerEcho(void *args)
{
	int clientFileDescriptor=(int)args;
	//char str[20];

	// recieve thead id
	char str_ser[STR_LEN];
	bzero(str_ser, STR_LEN);
	strncpy(str_ser, "hello", STR_LEN);
	uint8_t isRead = 0;
	uint16_t arrayPosNBO = 0;
	uint16_t arrayPos = 0;
	recv(clientFileDescriptor,&isRead,sizeof(isRead), 0);
	recv(clientFileDescriptor,&arrayPosNBO,sizeof(arrayPosNBO), 0);
	arrayPos = ntohs(arrayPosNBO) % arraySize;

	if (!isRead) {
        pthread_mutex_lock(&mutex[arrayPos]);
		send(clientFileDescriptor, theArray[arrayPos], STR_LEN, 0);		
		//printf("Read request %s\n", theArray[arrayPos]);
        pthread_mutex_unlock(&mutex[arrayPos]);
	} else {
        pthread_mutex_lock(&mutex[arrayPos]);
		//printf("Array index: %d\n", arrayPos);
        bzero(theArray[arrayPos], STR_LEN);
		sprintf(theArray[arrayPos],"String %d has been modified by a write request", arrayPos);	
        send(clientFileDescriptor, theArray[arrayPos], STR_LEN, 0);			
		pthread_mutex_unlock(&mutex[arrayPos]);
	}

	close(clientFileDescriptor);
}


int main(int argc, char* argv[])
{
	struct sockaddr_in sock_var;
	int serverFileDescriptor=socket(AF_INET,SOCK_STREAM,0);
	int clientFileDescriptor;
	int i;
	pthread_t t[1000];

	port = strtol(argv[1], NULL, 10);
	arraySize = strtol(argv[2], NULL, 10);

	sock_var.sin_addr.s_addr;
	sock_var.sin_port=port;
	sock_var.sin_family=AF_INET;
	printf("Hello\n");

	theArray = malloc(sizeof(*theArray)*arraySize);
    mutex = malloc(sizeof(mutex)*arraySize);
	for (i = 0; i < arraySize; i++) {
		theArray[i] = malloc(sizeof(*theArray[i]) * STR_LEN);
        pthread_mutex_init(&mutex[i], NULL);
	}

	for (i = 0; i < arraySize; i ++) {
		sprintf(theArray[i], "String %d: the intial value", i);
		//printf("%s\n", theArray[i]);
	}

	if (bind(serverFileDescriptor,(struct sockaddr*)&sock_var,sizeof(sock_var))>=0) {
		//printf("nsocket has been created\n");
		listen(serverFileDescriptor,2000); 
		while(1) {
			for(i=0;i<1000;i++) {
				clientFileDescriptor=accept(serverFileDescriptor,NULL,NULL);
				//printf("File descripter num %d\n",clientFileDescriptor);
				//printf("nConnected to client %d\n",clientFileDescriptor);
				pthread_create(&t,NULL,ServerEcho,(void *)clientFileDescriptor);
			}
		}
		close(serverFileDescriptor);
	}
	else {
		printf("nsocket creation failed\n");
	}
	pthread_mutex_destroy(&mutex);
	return 0;
}