#include<stdio.h>
#include<fcntl.h>
#include<arpa/inet.h>

/**
 * Using TCP/IP sockets, write a client-server program to make client sending the file name
 * and the server to send back the contents of the requested file if present.
 *
 * The client takes a filename as input and sends it to server. The server recieves this filename, opens the file and
 * send the contents of the file back to client. The client recieves the contents and writes in onto the console.
 *
 * This file contains the code for the server
 */


int main() {
  int sd, source, fd, n;
  char fname[50], buffer[256];
  struct sockaddr_in address;

  address.sin_family = AF_INET;
  address.sin_port = htons(15000);
  address.sin_addr.s_addr = INADDR_ANY;

  printf("Waiting for request... \n");

  // Prepare
  sd = socket(AF_INET, SOCK_STREAM, 0);
  bind(sd, (struct sockaddr *) &address, sizeof(address));
  listen(sd, 3);

  // Receive the request
  source = accept(sd, NULL, NULL);
  recv(source, fname, sizeof(fname), 0);
  printf("Received request for: %s \n", fname);

  // Open the file
  fd = open(fname, O_RDONLY);
  if (fd < 0) {
    send(source, "File not found. \n", 18, 0);
  } else {
    // Send the response
    while ((n = read(fd, buffer, sizeof(buffer))) > 0) {
      send(source, buffer, n, 0);
    }
  }
  printf("Response sent\n");

  close(fd);

  return 0;
}
