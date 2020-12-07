#ifndef __HTTP_RESPONSE_H_
#define __HTTP_RESPONSE_H_

#include <stdio.h>
#include <time.h>
#include <sys/socket.h>
#include "HttpRequest.h"

enum ContentType{
    HTML,
    ICO,
    CSS,
};

struct HttpResponse {
    enum ContentType type;
    int content_length;
    char* content;
};

struct HttpResponse* get_response(struct HttpRequest*);
void send_http_response(struct HttpResponse*, int);
void free_http_response(struct HttpResponse*);

#endif // __HTTP_RESPONSE_H_
