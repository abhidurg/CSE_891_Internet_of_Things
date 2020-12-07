#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <pthread.h>

#include "HttpRequest.h"
#include "HttpResponse.h"

#define MAX_BUFFER_SIZE 256
#define PORT 8080

int main() {
    int server_fd, client_fd; //socket descriptor for server and client
    struct sockaddr_in local; //local = server
    struct sockaddr remote; //remote = client
    socklen_t addrlen = sizeof(struct sockaddr);
    int reuse = 1;
    pthread_t tid;
    char client_message[1000];
    int read_size;

    // Create a socket.
	server_fd = socket(AF_INET , SOCK_STREAM , 0);
	
	if (server_fd == -1)
	{
		printf("Could not create socket");
	}

	//Prepare the sockaddr_in structure
	local.sin_family = AF_INET;
	//local.sin_addr.s_addr = INADDR_ANY;
	local.sin_addr.s_addr = inet_addr("127.0.0.1");
	local.sin_port = htons( 8080 );
	
	//bind
	if( bind(server_fd,(struct sockaddr *)&local , addrlen) < 0)
	{
	puts("bind failed");
	}
	puts("bind done");
	puts("Waiting for incoming connections...");
    
    // Listen to port 8080.
	listen(server_fd, 3);
		
	

    // Create connections and dispatch requests.
    while (1) {
		client_fd = accept(server_fd, (struct sockaddr *)&remote, &addrlen);
		if (client_fd<0){
			perror("accecpt failed");
			exit(-1);
			}
		puts("Connection accepted");
		//printf("%d", client_fd);
			
		//message = "Greetings! I am your connection handler\n";
		//write(server_fd , message , strlen(message));	
		
		
		
		//read(client_fd, client_message, 500); //THIS WORKS!!	
		recv(client_fd, client_message, 1000, 0);
		
		//if(recv(client_fd 
		
		//printf(client_message);
		//struct HttpRequest *request = malloc(sizeof(request));


//this block of code works!!!	------------------------------------------	
/*		
		struct HttpRequest *request = (struct HttpRequest*)malloc(sizeof(request));
		request = parse_http_request(client_message, strlen(client_message));
		char *original_path = "./web";
		char *requested_path = request->request_file;
		printf("The requested path is: %s", request->request_file); 
		
		
		
		char *final_path = (char *)malloc(1+strlen(original_path) + strlen(requested_path));
		strcpy(final_path, original_path);
		strcat(final_path, requested_path);
		printf("The final path is: %s", final_path); 
		
		FILE *file_pointer = fopen(final_path, "rb");
		if (!file_pointer){
			perror("The file was not opened");
			exit(1);
			
			}
		//printf("The file was opened");
		//free_http_request(request);
		//get file length
		//fseek(file_pointer, 0, SEEK_END);
		//long file_length = ftell(file_pointer);
		//fseek(file_pointer, 0, SEEK_SET);
		long file_length;
		if (fseek(file_pointer, 0, SEEK_END) == -1){
			perror("The file was not seeked");
			//exit(1);			
			}
		file_length = ftell(file_pointer);
		//file_length = 452;
		if(file_length == -1){
			perror("The file size was not recieved");
			exit(1);
			}
		rewind(file_pointer);
		
		//printf("The file size is %ld\n", file_length);
		char *buffer;
		buffer=(char *)malloc(file_length);
		if (!buffer)
			{
			fprintf(stderr, "THe file buffer was not allocated - error!");
			fclose(file_pointer);
			exit(1);
			}
		if(fread(buffer, file_length, 1, file_pointer) != 1){
			perror("The file was not able to fread");
			//exit(1);
			}
		fclose(file_pointer);
		
		//printf("%s\n", buffer);
		 write(client_fd, "HTTP/1.1 200 OK\n", 16);
		 write(client_fd, "Content-length: 453\n", 20); //fix this to have variable size later
		 write(client_fd, "Content-Type: text/html\n\n", 25);
		if(send(client_fd, buffer, file_length, 0) > 0){
			printf("success");
			}
			else{
				printf("failed");
				}
		 
		*/
		 
		
			
	//-----------------------------	
	struct HttpRequest *request = malloc(sizeof *request);
	request = parse_http_request(client_message, strlen(client_message));
	//printf("This is the request file returned in main:%s", request->request_file);
	
	
	struct HttpResponse *response = malloc(sizeof *response);
	//printf("This is the request file returned in main after response allocation:%s", request->request_file);
	response = get_response(request);
	//printf("%s", response->content);
	//send_http_response(response, client_fd);	
	close(client_fd);
	//close(server_fd);
	//printf("%s",response->content);
	//free_http_request(request);
	//free_http_response(response);
			
    }
    return 0;
}
