#include<stdio.h>
#include<fcntl.h>

/**
 * Using message queues or FIFOs as IPC channels, write a client-server program to make client sending the file name
 * and the server to send back the contents of the requested file if present.
 *
 * The client takes a filename as input and sends it to server. The server recieves this filename, opens the file and
 * send the contents of the file back to client. The client recieves the contents and writes in onto the console.
 *
 * This file contains the code for the server
 */


int main() {
  char fname[50], buffer[1025];
  int request, response, file, n;

  mkfifo("request.fifo", 0777);
  mkfifo("response.fifo", 0777);

  request = open("request.fifo", O_RDONLY);
  response = open("response.fifo", O_WRONLY);

  printf("Waiting for request\n");
  read(request, fname, sizeof(fname), 0);
  printf("Received request for '%s' \n", fname);

  file = open(fname, O_RDONLY);
  if (file < 0) {
    write(response, "File not found. \n", 18, 0);
  } else {
    while ((n = read(file, buffer, sizeof(buffer), 0)) > 0) {
      write(response, buffer, n, 0);
    }
  }
  printf("Response sent\n");

  close(response);
  close(request);
  close(file);

  unlink("request.fifo");
  unlink("response.fifo");

  return 0;
}
