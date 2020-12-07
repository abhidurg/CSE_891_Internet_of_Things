#include "HttpResponse.h"

#define BUFFER_SIZE 256

static char* wday_str[] = {"Sun","Mon","Tue","Wed","Thr","Fri","Sat"};
static char* mon_str[] = {"Jan","Feb","Mar","Apr","May","Jun",
                          "Jul","Aug","Sep","Oct","Nov","Dec"};

static char* content_type[] = {"text/html", "image/vnd.microsoft.icon", "text/css"};

struct HttpResponse* get_response(struct HttpRequest* request) {

    struct HttpResponse *response = malloc(sizeof *response);

    
    if(request->http_method == 0){ //need to respond to GET
		char *pointerto_dothtm = strstr(request->request_file, ".htm");
		if(pointerto_dothtm != NULL)
		{
			printf("the term .htm exists");
			char *original_path = "./web";
			char *requested_path = request->request_file;
			char *final_path = (char *)malloc(1+strlen(original_path) + strlen(requested_path));
			strcpy(final_path, original_path);
			strcat(final_path, requested_path);
			response->type = 0;					//show it is a html
			printf("The final path is: %s", final_path);
			
			
			//char buff[500];
			FILE *file_pointer = fopen("./web/index.html", "r");
			if (!file_pointer){
			perror("The file was not opened");
			exit(1);
			
			}
			printf("The file was opened");
			
			
			fseek(file_pointer, 0, SEEK_END);
			long file_length = ftell(file_pointer);
			fseek(file_pointer, 0, SEEK_SET);
			printf("The file size is: %d", file_length);
			response->content_length = file_length;
			
			/*
			char buffer[file_length];
			fread(buffer, sizeof(buffer), 1, file_pointer);
			//printf("%s",buffer);
			//response->content = buffer;
			strcpy(response->content, buffer);
			printf("%s",buffer);*/

			}
		
		}


    return response;
}

void send_http_response(struct HttpResponse* response, int client_fd) {
    char buff[BUFFER_SIZE * 8], t_buff[BUFFER_SIZE];
    char* result;
    long current_time;
    int len = 0;
    struct tm *tt;
    memset(buff, 0, sizeof(buff));
    memset(t_buff, 0, sizeof(t_buff));
    strcpy(buff, "HTTP/1.1 200 OK\r\n");
    strcat(buff, "Content-Type: ");
    strcat(buff, content_type[response->type]);
    strcat(buff, "\r\n");
    strcat(buff, "Content-Length: ");
    sprintf(t_buff, "%d", response->content_length);
    strcat(buff, t_buff);
    strcat(buff, "\r\n");
    tt = gmtime(&current_time);
    sprintf(t_buff,"%s, %d %s %d %02d:%02d:%02d GMT",wday_str[tt->tm_wday]
            ,tt->tm_mday,mon_str[tt->tm_mon],1900+tt->tm_year,tt->tm_hour,tt->tm_min,tt->tm_sec);
    strcat(buff, "Date: ");
    strcat(buff, t_buff);
    strcat(buff, "\r\n");
    strcat(buff, "Connection: Keep-Alive\r\n\r\n");
    send(client_fd, buff, strlen(buff), 0);
    send(client_fd, response->content, response->content_length, 0);
}

void free_http_response(struct HttpResponse* response) {
    if(!response) return;
    if(response->content) free(response->content);
    response->content = NULL;
    free(response);
}
