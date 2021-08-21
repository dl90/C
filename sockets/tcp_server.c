#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

  char *message = "message";

  // create socket
  int server_socket;
  server_socket = socket(AF_INET, SOCK_STREAM, 0);

  // define server address
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(3000);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  // bind address to socket
  bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
  listen(server_socket, 1);

  // getting client socket
  int client_socket;
  client_socket = accept(server_socket, NULL, NULL);

  send(client_socket, message, sizeof(message), 0);
  close(server_socket);

  return 0;
}