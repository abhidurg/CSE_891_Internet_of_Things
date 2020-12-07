#ifndef __HTTP_REQUEST_H_
#define __HTTP_REQUEST_H_

#include <stdlib.h>
#include <string.h>

enum HttpMethod {
    GET,
    POST,
};

struct HttpRequest{
    enum HttpMethod http_method;
    char* request_file;
    char* query_string;
    char* request_body;
    int content_length;
};

struct HttpRequest* parse_http_request(const char*, int);
void free_http_request(struct HttpRequest*);

#endif // __HTTP_REQUEST_H_
