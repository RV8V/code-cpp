#include <stdio.h>
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

#define SERVER_IP "127.0.0.1"
#define DEFAULT_PORT 1603
#define BUFFER_SIZE 1024
#define SERVER_CLOSE_CONNECTION_SYMBOL '#'

bool is_client_connection_close(const char*);

int main(int, const char**) {
  int client;

  struct sockaddr_in server_address;

  client = socket(AF_INET, SOCK_STREAM, 0);
  if (client < 0) {
    printf("%s\n", "error while establishing socket config");
    exit(0);
  }

  server_address.sin_port = htons(DEFAULT_PORT);
  server_address.sin_family = AF_INET;
  inet_pton(AF_INET, SERVER_IP, &server_address.sin_addr);

  printf("%s\n", "client socket created");

  int ret = connect(client, (const struct sockaddr*)&server_address, sizeof(server_address));
  if (ret == 0)
    printf("%s%s%s%d\n", "-> connect to server ", inet_ntoa(server_address.sin_addr), " with port number: ", DEFAULT_PORT);

  char buffer[BUFFER_SIZE];
  printf("%s\n", "-> wait for server confirmation... (server connected)");
  recv(client, buffer, BUFFER_SIZE, 0);
  printf("%s\n%s%c%s\n", "-> connection established", "enter ", SERVER_CLOSE_CONNECTION_SYMBOL, " for close the connection");

  while(true) {
    printf("%s", "client: ");
    std::cin.getline(buffer, BUFFER_SIZE);
    send(client, buffer, BUFFER_SIZE, 0);
    if (is_client_connection_close(buffer))
      break;

    printf("%s", "server: ");
    recv(client, buffer, BUFFER_SIZE, 0);
    printf("%s\n", buffer);
    if (is_client_connection_close(buffer))
      break;
    printf("\n");
  }

  close(client);
  printf("\n%s\n", "goodbye...");

  return 0;
}

bool is_client_connection_close(const char* message) {
  for (int i = 0; i < strlen(message); ++i) {
    if (*(message + i) == SERVER_CLOSE_CONNECTION_SYMBOL) return true;
  }
  return false;
}
