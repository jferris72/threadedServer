#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>

long port;
long arraySize;

void *ServerEcho(void *args)
{
	int clientFileDescriptor=(int)args;
	//char str[20];

	// recieve thead id
	char str_ser[5];
	bzero(str_ser, 5);
	strncpy(str_ser, "hello", 5);
	uint8_t isRead = 0;
	uint16_t arrayPosNBO = 0;
	uint16_t arrayPos = 0;
	recv(clientFileDescriptor,&isRead,sizeof(isRead), 0);
	recv(clientFileDescriptor,&arrayPosNBO,sizeof(arrayPosNBO), 0);
	arrayPos = ntohs(arrayPosNBO);

	if(!isRead){
		send(clientFileDescriptor, str_ser, 5, 0);		
		printf("Read request\n");
	}else{
		printf("Write request\n");
	}
	
	//printf("array position: %d\n",(int) arrayPos);
	// printf("nreading from client:%s \n",str);
	// write(clientFileDescriptor,str,20);
	// printf("nechoing back to client \n");


// // <<<<<<< HEAD
// // =======
// 	read(clientFileDescriptor,str,20);
// 	printf("nreading from client:%s\n",str);
// 	write(clientFileDescriptor,str,20);
// 	printf("nechoing back to client\n");
// >>>>>>> 69d7aad6ffe22a5bd10ce267a56c42295fda1d3a
	close(clientFileDescriptor);
}


int main(int argc, char* argv[])
{
	struct sockaddr_in sock_var;
	int serverFileDescriptor=socket(AF_INET,SOCK_STREAM,0);
	int clientFileDescriptor;
	int i;
	pthread_t t[20];

	port = strtol(argv[1], NULL, 10);
	arraySize = strtol(argv[2], NULL, 10);

	sock_var.sin_addr.s_addr;
	sock_var.sin_port=port;
	sock_var.sin_family=AF_INET;
	printf("Hello\n");

	if(bind(serverFileDescriptor,(struct sockaddr*)&sock_var,sizeof(sock_var))>=0)
	{
		printf("nsocket has been created\n");
		listen(serverFileDescriptor,2000); 
		while(1)        //loop infinity
		{
			for(i=0;i<50;i++)      //can support 20 clients at a time
			{
				clientFileDescriptor=accept(serverFileDescriptor,NULL,NULL);
				printf("File descripter num %d\n",clientFileDescriptor);
				printf("nConnected to client %d\n",clientFileDescriptor);
				pthread_create(&t,NULL,ServerEcho,(void *)clientFileDescriptor);
			}
		}
		close(serverFileDescriptor);
	}
	else{
		printf("nsocket creation failed\n");
	}
	return 0;
}