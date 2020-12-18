#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "server.h"

/* client:
 *  socket()
 *  bind() ?
 *  connect()
 *  ----------------------
 *  write()   | read()
 *  send()    | recv()
 *  sendto()  | recvfrom()
 *  writev()  | readv()
 *  sendmsg() | recvmsg()
 *  ----------------------
 *  close()
*/

/* server:
 *  socket()
 *  bind()
 *  listen()
 *  accept()
 *  ----------------------
 *  write()   | read()
 *  send()    | recv()
 *  sendto()  | recvfrom()
 *  writev()  | readv()
 *  sendmsg() | recvmsg()
 *  ----------------------
 *  close()
*/

int main(int, const char**) {
  int sockfd = create_socket(SERVER_PORT);
  if (sockfd < 0) {
    fprintf(stderr, "%s\n", "error while socket creation");
    return -1;
  }

  fprintf(stdout, "%s\n", "socket created");

  struct sockaddr_storage client_addr;
  int clientfd;
  socklen_t size = sizeof(client_addr);
  while(1) {
    clientfd = accept(sockfd, (struct sockaddr*)&client_addr, &size);

    if (clientfd == -1) {
      fprintf(stderr, "%s\n", "can not accept client socket");
      return -1;
    }

    char ip[INET6_ADDRSTRLEN];
    inet_ntop(client_addr.ss_family, get_client_addr((struct sockaddr*)&client_addr), ip, sizeof ip);
    fprintf(stdout, "%s%s\n", "server got connection from: ", ip);

    http_request(clientfd);
    close(clientfd);
  }

  return 0;
}

int create_socket(const char *port) {
  struct addrinfo hints;
  struct addrinfo *server_info;

  memset(&hints, 0, sizeof(hints));

  hints.ai_family   = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags    = AI_PASSIVE;

  if(int r = getaddrinfo(NULL, port, &hints, &server_info); r != 0) {
    fprintf(stderr, "error getaddrinfo()\n");
    return -1;
  }

  struct addrinfo *p;
  int sockfd, yes;

  for(p = server_info; p != NULL; p = p->ai_next) {
    sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
    if(sockfd == -1)
      continue;

    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
      fprintf(stderr, "error setsockopt\n");
      close(sockfd);
      freeaddrinfo(server_info);
      return -2;
    }

    if(bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
      close(sockfd);
      continue;
    }
    break;
  }

  freeaddrinfo(server_info);

  if(p == NULL) {
    fprintf(stderr, "failed to find address\n");
    return -3;
  }

  if(listen(sockfd, MAX_CONNECTION) == -1) {
    fprintf(stderr, "error listen\n");
    return -4;
  }

  return sockfd;
}

void* get_client_addr(struct sockaddr* address) {
  if (address->sa_family == AF_INET) {
    return &(((struct sockaddr_in*)address)->sin_addr);
  }
  return &(((struct sockaddr_in6*)address)->sin6_addr);
}

void http_request(int socketfd) {
  const int request_body_buffer = 65356;
  char request[request_body_buffer];

  int bytes_recvd = recv(socketfd, request, request_body_buffer - 1, 0);

  if (bytes_recvd < 0) {
    fprintf(stderr, "%s\n", "error while receiving bytes");
    return;
  }

  request[bytes_recvd] = '\0';
  fprintf(stdout, "%s\n", request);

  http_header req;
  parse_http_request(request, &req);

  if (req.type == HTTP_GET)
    send_message(socketfd, "hello world");
  else
    send_404(socketfd);
}

void parse_http_request(const char* request, http_header* header) {
  int type_length = 0;
  char type[255] = {0};
  int index = 0;

  header->type = HTTP_UNKNOWN;

  sscanf(&request[index], "%s", type);
  type_length = strlen(type);

  if (type_length == 3) {
    if (*(type + 0) == 'G' && *(type + 1) == 'E'  && *(type + 2) == 'T')
      header->type = HTTP_GET;

    index += type_length + 1;
    sscanf(&request[index], "%s", header->path);
  }
}

void send_message(int socketfd, const char* message) {
  char buffer[65356] = {0};

  strcat(buffer, "HTTP/1.1 200 OK\n\n");
  strcat(buffer, "<h1>");
  strcat(buffer, message);
  strcat(buffer, "<h1>");

  int length = strlen(buffer);
  send(socketfd, buffer, length, 0);
}

void send_404(int socketfd) {
  const char* buffer = "HTTP/1.1 404 OK\n\n";
  int length = strlen(buffer);
  send(socketfd, buffer, length, 0);
}

/* server: got connection from 127.0.0.1
 * request:
 * GET /index.html HTTP/1.1
 * Host: localhost:3490
 * Connection: keep-alive
 * Upgrade-Insecure-Requests: 1
 * User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Ubuntu Chromium/68.0.3440.75 Chrome/68.0.3440.75 Safari/537.36
 * Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*//*;q=0.8
 * Accept-Encoding: gzip, deflate, br
 * Accept-Language: en-US,en;q=0.9,ru;q=0.8
*/
