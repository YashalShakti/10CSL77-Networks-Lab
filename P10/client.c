#include<stdio.h>
#include<fcntl.h>

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
