#include<stdio.h>
#include<fcntl.h>
#include<arpa/inet.h>

int main(){
    int sd, source, fd, n;
    char fname[50], buffer[256];
    struct sockaddr_in address;
    
    address.sin_family = AF_INET;
    address.sin_port = htons(15000);
    address.sin_addr.s_addr = INADDR_ANY;
    
    printf("Waiting for request... \n");

    sd = socket(AF_INET, SOCK_STREAM, 0);
    bind(sd, (struct sockaddr*) &address, sizeof(address));
    listen(sd, 3);
    
    source = accept(sd, NULL, NULL);
    recv(source, fname, sizeof(fname), 0);
    printf("Received request for: %s \n", fname);
    fd = open(fname, O_RDONLY);

    if (fd < 0) {
        send(source, "File not found. \n", 18,  0);
    } else {
        while((n =read(fd,buffer, sizeof(buffer)))> 0){
            send(source, buffer, n, 0);
        }
    }
    printf("Response sent\n");
    close(fd);
    return 0;
}
