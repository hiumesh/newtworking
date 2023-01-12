#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>

const char APRESSMESSAGE[] = "APRESS - For Professionals, by Professionals!\n";

int main(int argc, char *argv[]) {
  int simpleSocket = 0;
  int simplePort = 0;
  int returnStatus = 0;
  struct sockaddr_in simpleServer;

  if (2 != argc) {
    fprintf(stderr, "Usage: %s <port>\n", argv[0]);
    exit(0);
  }

  simpleSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  simplePort = atoi(argv[1]);

  if (simpleSocket == -1) {
    fprintf(stderr, "Could not create a socket!\n");
    exit(0);
  } else {
    fprintf(stderr, "Socket created\n");
  }

  memset(&simpleServer, 0, sizeof(simpleServer));
  simpleServer.sin_family = AF_INET;
  simpleServer.sin_addr.s_addr = htons(INADDR_ANY);
  simpleServer.sin_port = htons(simplePort);

  returnStatus = bind(simpleSocket, (struct sockaddr *) &simpleServer, sizeof(simpleServer));

  if (returnStatus == 0) fprintf(stderr, "Bind Completed!\n");
  else {
    fprintf(stderr, "Could not bind the address!\n");
    close(simpleSocket);
    exit(1);
  }

  returnStatus = listen(simpleSocket, 5);

  if (returnStatus == -1) {
    fprintf(stderr, "Could not listion on the socket\n");
    close(simpleSocket);
    exit(1);
  }
  while(1) {
    struct sockaddr_in clientName = {0};
    int simpleChildSocket = 0;
    int clientNameLength = sizeof(clientName);

    simpleChildSocket = accept(simpleSocket, (struct sockaddr *)&clientName, &clientNameLength);

    if (simpleChildSocket == -1) {
      fprintf(stderr, "Cannot accept connections!\n");
      close(simpleSocket);
      exit(1);
    }
    write(simpleChildSocket, APRESSMESSAGE, strlen(APRESSMESSAGE));
    close(simpleChildSocket);

  }
  close(simpleSocket);
  return 0;
}