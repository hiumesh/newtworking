#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

int main(int argc, char *argv[]) {
  int simpleSocket = 0;
  int simplePort = 0;
  int returnStatus = 0;
  char buffer[256] = "";
  struct sockaddr_in simpleServer;

  if (argc != 3) {
    fprintf(stderr, "Usage: %s <server> <port>\n", argv[1]);
    exit(1);  
  }

  simpleSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  if (simpleSocket == -1) {
    fprintf(stderr, "Could not create a socket!\n");
    exit(1);
  } else {
    fprintf(stdout, "Socket Created!\n");
  }

  simplePort = atoi(argv[2]);

  bzero(&simpleServer, sizeof(simpleServer));
  simpleServer.sin_family = AF_INET;
  inet_addr(argv[1], &simpleServer.sin_addr.s_addr);
  simpleServer.sin_port = htons(simplePort);

  returnStatus = connect(simpleSocket, (struct sockaddr *)&simpleServer, sizeof(simpleServer));

  if (returnStatus == 0) fprintf(stdout, "Connection Successful!\n");
  else {
    fprintf(stderr, "Could not connect to address!\n");
    close(simpleSocket);
    exit(1);
  }

  returnStatus = read(simpleSocket, buffer, sizeof(buffer));

  if (returnStatus > 0) printf("%d: %s", returnStatus, buffer);
  else {
    fprintf(stderr, "Return Status = %d \n", returnStatus);
  }

  close(simpleSocket);

  return 0;
}