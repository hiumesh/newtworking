#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAXLINE 256


int main(int argc, char *argv[]) {
  int socket_fd = 0;
  int returnStatus = 0;
  char buffer[MAXLINE] = "";
  int n;
  struct sockaddr_in server_address;

  if (argc != 3) {
    printf("Usage: a.out <IPaddress> <Port>");
  }

  socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (socket_fd == -1) {
    printf("Could not create Socket!\n");
    exit(1);
  } else {
    printf("Socket Created!\n");
  }

  memset(&server_address, 0, sizeof(server_address));
  server_address.sin_family = AF_INET;
  inet_ntop(AF_INET, &server_address.sin_addr.s_addr, argv[1], sizeof(argv[1]));
  server_address.sin_port = htons(atoi(argv[2]));

  returnStatus = connect(socket_fd, (struct sockaddr *)&server_address, sizeof(server_address));

  if (returnStatus == -1) {
    printf("Failed to Connect to server!\n");
    exit(1);
  } else printf("Connected to the server!\n");

  while(1) {
    n = read(socket_fd, buffer, MAXLINE-1);
    if (n < 0) {
      printf("Failed To read!\n");
      exit(1);
    }
    if (n == 0) break;
    buffer[n] = 0;
    printf("%s", buffer);
  }

  return 0;
}