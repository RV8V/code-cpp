#include <stdio.h>
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

#define ERROR_S "SERVER ERROR: "
#define DEFAULT_PORT 1603
#define BUFFER_SIZE 1024
#define CLIENT_CLOSE_CONNECTION_SYMBOL '#'

bool is_client_connection_close(const char*);
void handle_client(); // todo

int main(int, char const**) {
  int client, server;

  struct sockaddr_in server_address;
  client = socket(AF_INET, SOCK_STREAM, 0);

  if (client < 0) {
    printf("%s%s\n", ERROR_S, "establishing socket error");
    exit(0);
  }
  printf("%s\n", "SERVER: socket for server was created");

  server_address.sin_port = htons(DEFAULT_PORT);
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = htons(INADDR_ANY);

  int ret = bind(client, (struct sockaddr*)&server_address, sizeof(server_address));

  if (ret < 0) {
    printf("%s%s\n", ERROR_S, "binding connection, socket has already been established");
    return -1;
  }

  socklen_t size = sizeof(server_address);
  printf("%s\n", "SERVER: listening clients...");
  listen(client, 1);

  server = accept(client, (struct sockaddr*)&server_address, &size);
  if (server < 0)
    printf("%s\n", "server can not accept client because of corrupted socket of wrong configuration from server side");

  char buffer[BUFFER_SIZE];
  int is_exit = false;
  while (server > 0) {
    strcpy(buffer, "-> server connection\n");
    send(server, buffer, BUFFER_SIZE, 0);
    printf("%s%c%s\n", "connection to the client #1\n enter", CLIENT_CLOSE_CONNECTION_SYMBOL, "to end the connection\n");

    printf("%s", "client: ");
    recv(server, buffer, BUFFER_SIZE, 0);
    printf("%s\n", buffer);

    if (is_client_connection_close(buffer))
      is_exit = true;

    while(!is_exit) {
      printf("%s", "server: ");
      std::cin.getline(buffer, BUFFER_SIZE);
      send(server, buffer, BUFFER_SIZE, 0);
      if (is_client_connection_close(buffer))
        break;

      printf("%s\n", "client: ");
      recv(server, buffer, BUFFER_SIZE, 0);
      printf("%s\n", buffer);
      if (is_client_connection_close(buffer))
        break;
    }

    printf("\n%s\n", "goodbye...");
    is_exit = false;
    exit(1);
  }

  return 0;
}

bool is_client_connection_close(const char* message) {
  for (int i = 0; i < strlen(message); ++i) {
    if (*(message + i) == CLIENT_CLOSE_CONNECTION_SYMBOL) return true;
  }
  return false;
}

void handle_client() {
}
