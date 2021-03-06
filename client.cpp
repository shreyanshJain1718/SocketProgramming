#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#define PORT 8080

int main(int argc, char const *argv[]){
	//socket for the clinet
	struct sockaddr_in address;

	int sock = 0, valread;

	//socket for the server
	struct sockaddr_in serv_addr;
	char *hello = "Hello from clinet";
	char buffer[1024] = {0};
	
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("\n Socket creation error \n");
		return -1;
	}
	
	memset(&serv_addr, '0', sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	//inet_pton
	//convert the IP address (IPv4 or IPv6 to binary form
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0){
		printf("\nInvalid address/ Addresss not supported \n");
		return -1;
	}
	
	if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
		printf("\n Connection failed \n");
		return -1;
	}
	char *msgs[] = {"hello", "hey", "hi", "how are you?", "i'm fine thanks for asking", "exit"};
	for(int i=0;i<6;i++){
		send(sock, msgs[i], strlen(msgs[i]), 0);
		printf("%d message sent\n", i);
		valread = read(sock, buffer, 1024);
		printf("[server]%s\n", buffer);
	}
	return 0;
}
