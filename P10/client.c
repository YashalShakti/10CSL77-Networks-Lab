#include<stdio.h>
#include<fcntl.h>

/**
 * Using message queues or FIFOs as IPC channels, write a client-server program to make client sending the file name
 * and the server to send back the contents of the requested file if present.
 *
 * The client takes a filename as input and sends it to server. The server recieves this filename, opens the file and
 * send the contents of the file back to client. The client recieves the contents and writes in onto the console.
 *
 * This file contains the code for the client
 */


int main() {

  char fname[10], buffer[256];
  int request, response, n;

  request = open("request.fifo", O_WRONLY);
  response = open("response.fifo", O_RDONLY);

  printf("Enter the file name\n");
  scanf("%s", fname);

  printf("Sending request\n");
  write(request, fname, sizeof(fname), 0);

  printf("Recieved response\n");
  while ((n = read(response, buffer, sizeof(buffer), 0)) > 0) {
    write(1, buffer, n);
  }

  close(response);
  close(request);
  return 0;
}
