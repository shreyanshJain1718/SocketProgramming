#include<unistd.h>
#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>

#define MAX_CONN 2
#define PORT 8080
int main(int argc, char const *argv[]){
	int server_fd, new_socket, valread;
	
	//new_socket to store the file descriptor for the client socket when connection is accepted
	//for multiple clients multiple file descriptors are required
	
	// socket() return a file handler to manipulate the socket options which is stored in server_fd 
	//server_fd : file handler for the socket created 

	struct sockaddr_in address;
	
	int opt = 1;
	
	int addrlen = sizeof(address);
	
	char buffer[1024] = {0};
	
	char *hello = "Hello from server";

	//AF_INET to set the domain to internet protocols, address from internet IP address

	//create socket file descriptor 
	if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
		perror("socket failed");
		exit(EXIT_FAILURE);
	}


	if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){
		perror("setsockpot");
		exit(EXIT_FAILURE);
	}
	
	address.sin_family = AF_INET;
	//INADDR_ANY binds the socket to all available interfaces. 
	//if the socket is to be connnected by a client on the host the IP for localhost can be used "127.0.0.1" as used in clint in this example
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);
	

	//attach socket to the port 8080
	if(bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0){
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	if(listen(server_fd, MAX_CONN) < 0){
		perror("listen");
		exit(EXIT_FAILURE);
	}

	if((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0){
		perror("accept");
		exit(EXIT_FAILURE);
	}
	int client2;
	if((client2 = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0){
		perror("accepting second failed");
		exit(EXIT_FAILURE);
	}
	


	valread = read(new_socket, buffer, 1024);
	printf("%s\n", buffer);
	send(new_socket, hello, strlen(hello), 0);
	printf("Hello message sent\n");
	while(strcmp(buffer, "exit") != 0){
		read(new_socket, buffer, 1024);
		printf("[server] %s recieved.\n", buffer);
		send(new_socket, "hey", 4, 0);
	}
	return 0;
}
