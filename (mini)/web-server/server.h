#ifndef _SERVER_H_
#define _SERVER_H_

#define SERVER_PORT "8000"
#define MAX_CONNECTION 1000
#define LENGTH_OF_BODY 255

int create_socket(const char*);
void* get_client_addr(struct sockaddr*);

typedef enum {
  HTTP_UNKNOWN = 0,
  HTTP_CONNECT,
  HTTP_DELETE,
  HTTP_GET,
  HTTP_HEAD,
  HTTP_OPTIONS,
  HTTP_PATCH,
  HTTP_POST,
  HTTP_PUT,
  HTTP_TRANCE,
} http_method;

typedef struct {
  http_method type;
  char path[LENGTH_OF_BODY];
} http_header;

void http_request(int);
void parse_http_request(const char*, http_header*);
void send_message(int, const char*);
void send_404(int);

#endif
