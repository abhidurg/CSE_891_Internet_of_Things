#include "HttpRequest.h"
#include <ctype.h>
#include <stdio.h>


struct HttpRequest* parse_http_request(const char* str, int len) {
    struct HttpRequest *request = malloc(sizeof *request);
    
	//printf(str);
	char *pointertoget = strstr(str, "GET");
	char *pointertohttp = strstr(str, "HTTP");
	if (pointertoget != NULL) {
		request->http_method = GET;		

		
		int string_length = strlen(pointertoget) - strlen(pointertohttp) - 5; //subtract 5 because "GET" is 3 characters, and 2 more for the 2 spaces
	/*
		int starting_position = 5;
		int count = 0;
		char substring[256];
		while(count < string_length){
			substring[count] = str[starting_position-1+count];
			count++;
			}
		substring[count] = '\0';
		//printf("%s",substring);
		request->request_file = substring;
		
		*/
		char *mutable_str  = (char *)malloc(sizeof *str+1);
		strcpy(mutable_str, str);
		//int count = 0;
		//for (count = 0; count < string_length; count++){
			//*(mutable_str+count) = *(mutable_str+2); //+5 because "GET " takes 4 spaces
			//mutable_str++;
			//}
		int count = 0;	
		*(mutable_str+string_length+4) = '\0';
		for (count = 0; count < string_length; count++){
		*(mutable_str+count) = *(mutable_str+4+count);
		}
		*(mutable_str+string_length) = '\0';
		//printf(mutable_str);
		
		//request->request_file = "index.html";
		request->request_file = mutable_str;
		//printf("The request file is saved as:%s:",request->request_file);
		}
	

			
	//free_http_request(request);
	//free(request);
   return request;
}

void free_http_request(struct HttpRequest* request) {
    if(!request) return;
    if(request->request_file) free(request->request_file);
    request->request_file = NULL;
    if(request->query_string) free(request->query_string);
    request->query_string = NULL;
    if(request->request_body) free(request->request_body);
    request->request_body = NULL;
    free(request);
}
