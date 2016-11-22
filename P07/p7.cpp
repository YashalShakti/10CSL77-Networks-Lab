#include<stdio.h>
#include<iostream>
#include<string.h>
using namespace std;

int crc(char input[], char output[],const char gp[], int mode) {
    
    strcpy(output, input);
    
    if (mode) {
        for (int i=1;i<strlen(gp);i++) {
            strcat(output,"0");
        }
    }
    
    for (int j=0; j<strlen(input); j++) {
        if (output[j] == '1') {
            for (int k = 0;k<strlen(gp);k++) {
                if (output[j+k] == '0' && gp[k]== '0' || output[j+k] == '1' && gp[k] == '1') {
                    output[j+k] = '0';
                } else {
                    output[j+k] = '1';
                }
            }
        }
    }
    
    cout << "\nThe checksum calculated is " << output + strlen(input);
    for (int j = 0; j<strlen(output);j++) {
        if (output[j] == '1') {
            return 0;
        }
    }
    
    return 1;
}

int main() {
    char input[50], output[50], recieve[50];
    
    const char gp[18] = "10001000000100001";
    
    cout << "\nEnter the message in binary\n";
    cin >> input;
    
    crc(input, output, gp, 1);
    
    cout << "\nThe message sent is " << input<<output+strlen(input);
    
    cout << "\nEnter the recieved message\n";
    cin >> recieve;
    
    if(crc(recieve,output,gp,0)){
        cout << "\nThe message has no error\n";
    } else {
        cout << "\nThe message has error\n";
    }
    
    return 0;
}
