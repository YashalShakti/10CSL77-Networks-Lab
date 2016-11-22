#include<iostream>
#include<stdio.h>

using namespace std;

/**
 * Write a program for simple RSA algorithm to encrypt and decrypt the data.
 *
 */

// Find the GCD of two numbers
int gcd(int a, int b) {
  if (a == 0) return b;
  if (b == 0) return a;
  return gcd(b, a % b);
}

// Check if a number is prime
int isPrime(int a) {
  if (a == 2 || a == 3) {
    return 1;
  }

  for (int i = 2; i < a; i++) {
    if (a % i == 0) return 0;
  }
  return 1;
}

// Get a random prime number
int getPrimeNum() {
  int p;
  do {
    p = rand() % 30;
  } while (!isPrime(p));
  return p;
}

// Used for encrypting and decrypting - Calculates a^e mod n )
long int crypt(long int a, int e, int n) {
  long int temp = a;
  for (int i = 1; i < e; i++) {
    temp = (temp * a) % n;
  }
  return temp;
}

int main() {
  char text[50];
  long int cipher[50], p, q, phi, e, d, n;

  cout << "Enter the text to be encrypted \n";
  cin >> text;

  // Find p, q, n and phi
  p = getPrimeNum();
  q = getPrimeNum();
  n = p * q;
  phi = (p - 1) * (q - 1);

  // Find e
  do {
    e = rand() % phi;
  } while (gcd(e, phi) != 1);

  // Find d
  do {
    d = rand() % phi;
  } while ((d * e) % phi != 1);

  int len = strlen(text);
  cout << "\nEncrypted message: ";
  for (int i = 0; i < len; i++) {
    cipher[i] = crypt(text[i], e, n); // Encrypt
    cout << cipher[i];
    text[i] = crypt(cipher[i], d, n); // Decrypt
  }
  text[len] = '\0'; // Append null to print as a string

  cout << "\nDecrypted message: " << text << endl;
  return 0;
}
