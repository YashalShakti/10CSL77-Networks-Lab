#include<stdio.h>
#include<iostream>
#include<string.h>
using namespace std;

int crc(char input[], char output[], const char gp[], int mode) {

  // Copy input string to output string
  strcpy(output, input);

  // There are two modes Mode==1 for calculating/sending and Mode==0 for testing/receiving
  // For Mode==1 0's are appended to the output string (Equal to 1 less than length of GP)
  if (mode) {
    for (int i = 1; i < strlen(gp); i++) {
      strcat(output, "0");
    }
  }

  for (int j = 0; j < strlen(input); j++) {
    if (output[j] == '1') {
      for (int k = 0; k < strlen(gp); k++) {
        // XOR operation for every bit following 1 for the division
        if ((output[j + k] == '0' && gp[k] == '0') || (output[j + k] == '1' && gp[k] == '1')) {
          output[j + k] = '0';
        } else {
          output[j + k] = '1';
        }
      }
    }
  }

  // This is necessary only for when mode==0; ie. the testing/receiving phase.
  // The transmitted message should result in output containing only 0's
  for (int j = 0; j < strlen(output); j++) {
    if (output[j] == '1') {
      return 0;
    }
  }

  return 1;
}

int main() {
  char input[50], output[50], receive[50];

  // GP here stands for the Generator Polynomial which acts as the divisor
  const char gp[18] = "10001000000100001";

  cout << "\nEnter the message in binary\n";
  cin >> input;

  crc(input, output, gp, 1);

  // The checksum calculated will be the 'output' excluding the 'input'; ie. by ignoring the first 'strlen(input)' chars
  cout << "\nThe checksum calculated is " << (output + strlen(input));
  cout << "\nThe message sent is " << input << (output + strlen(input)) << endl;

  // If the received messages is same as the one sent it will not give error
  cout << "\nEnter the received message\n";
  cin >> receive;

  // Check if the received message has any error
  if (crc(receive, output, gp, 0)) {
    cout << "\nThe message has no error\n";
  } else {
    cout << "\nThe message has error\n";
  }

  return 0;
}
