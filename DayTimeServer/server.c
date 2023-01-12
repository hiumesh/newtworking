#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#define MAXLINE 256

int main(int argc, char *argv[]) {
  int listionfd, connfd;
  struct sockaddr_in server_address;
  int returnStatus = 0;
  time_t ticks;
  char buffer[MAXLINE];

  if (argc != 3) {
    printf("Usage: a.out <IPAddress> <Port>\n");
    exit(1);
  }

  listionfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (listionfd == -1) {
    printf("Failed To Create Socked!\n");
    exit(1);
  } else {
    printf("Socket Created!\n");
  }

  memset(&server_address, 0, sizeof(server_address));
  server_address.sin_family = AF_INET;
  inet_ntop(AF_INET, &server_address.sin_addr.s_addr, argv[1], sizeof(argv[1]));
  server_address.sin_port = htons(atoi(argv[2]));

  returnStatus = bind(listionfd, (struct sockaddr *)&server_address, sizeof(server_address));

  if (returnStatus == 0) {
    printf("Bind Completed!\n");
  } else {
    printf("Failed To Bind the Socket!\n");
    exit(1);
  }

  returnStatus = listen(listionfd, 6);
  if (returnStatus == -1) {
    printf("Failed to Listion!\n");
    exit(1);
  } else {
    printf("Listing...\n");
  }

  for ( ; ; ) {
    connfd = accept(listionfd, (struct sockaddr *) NULL, NULL);
    ticks = time(NULL);
    snprintf(buffer, sizeof(buffer), "%.24s\r\n", ctime(&ticks));
    write(connfd, buffer, strlen(buffer));
    close(connfd);
  }

  close(listionfd);

  return 0;
}