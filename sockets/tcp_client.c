#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

  // create socket
  int network_socket;
  network_socket = socket(AF_INET, SOCK_STREAM, 0);

  // specify socket address
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(3000);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  // -1 connection error
  int status = connect(network_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
  printf("%d\n", status);

  // get response
  char response[512];
  recv(network_socket, &response, sizeof(response), 0);
  printf("%s\n", response);

  close(network_socket);

  return 0;
}
