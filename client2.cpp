#include<unistd.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#define PORT 8080

int main(int argc, char *argv[]){
	struct sockaddr_in address;

	int sock, valread;
	struct sockaddr_in serv_addr;

	char *msg = "message from client 2";
	char buffer[1024] = {0};


	if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("\n Error establishing socket\n");
		return -1;
	}

	memset(&serv_addr, '0', sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	if(inet_pton(AF_INET, "127.0.0.1",&serv_addr.sin_addr) < 0){
		perror("unsupported address");
		return -1;
	}

	if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
		perror("connection failed");
		return -1;
	}

	send(sock, msg, strlen(msg), 0);
	printf("[client2] message sent");
	valread = read(sock, buffer, 1024);
	printf("[client2] %s recieved", buffer);
	return 0;
}
