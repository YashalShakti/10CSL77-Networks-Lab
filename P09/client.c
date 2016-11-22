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
 * This file contains the code for the client
 */


int main() {
  int sd, n;
  char fname[50], buffer[256];
  struct sockaddr_in address;

  address.sin_family = AF_INET;
  address.sin_port = htons(15000);
  address.sin_addr.s_addr = INADDR_ANY;

  // Prepare
  sd = socket(AF_INET, SOCK_STREAM, 0);
  connect(sd, (struct sockaddr *) &address, sizeof(address));

  // Get the filename
  printf("Enter a filename: ");
  scanf("%s", fname);

  // Send the request
  printf("Sending request... \n");
  send(sd, fname, sizeof(fname), 0);

  // Receive the response
  printf("Received response: \n");
  while ((n = recv(sd, buffer, sizeof(buffer), 0)) > 0) {
    write(1, buffer, n);
  }

  return 0;
}
