#include<stdio.h>
#include<fcntl.h>
#include<arpa/inet.h>

int main(){
    int sd, n;
    char fname[50], buffer[256];
    struct sockaddr_in address;
    
    address.sin_family = AF_INET;
    address.sin_port = htons(15000);
    address.sin_addr.s_addr = INADDR_ANY;
    
    sd = socket(AF_INET, SOCK_STREAM, 0);
    connect(sd,  (struct sockaddr*)&address, sizeof(address));
    
    printf("Enter a filename: ");
    scanf("%s", fname);
    
    printf("Sending request... \n");
    send(sd,fname, sizeof(fname),0);
    
    printf("Recieved response: \n");
    while((n = recv(sd, buffer, sizeof(buffer),0))>0){
        write(1, buffer, n);
    }
    
    return 0;
}
