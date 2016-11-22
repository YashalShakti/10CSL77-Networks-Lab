#include<iostream>
#include<stdio.h>

using namespace std;

int gcd(int a, int b) {
    if (a == 0) return b;
    if (b == 0) return a;
    return gcd(b, a%b);
}

int isprime(int a) {
    if (a == 2 || a == 3){
        return 1;
    }
    
    for (int i = 2; i<a; i++) {
        if (a % i == 0) return 0;
    }
    return 1;
}

int encrypt(char ch,int e, int n) {
    long int temp = ch;
    for (int i=1;i<e;i++) {
        temp = (temp*ch) % n;
    }
    return temp;
}

char decrypt(long int ch,int e, int n) {
    long int temp = ch;
    for (int i=1;i<e;i++) {
        temp = (temp*ch) % n;
    }
    return temp;
}

int main() {
    char text[50];
    
    cout << "Enter the text to be encrypted \n";
    cin >> text;
    int len = strlen(text);
    
    long int p,q,phi,e,d,n, cipher[50];
    
    // Find p
    do {
        p = rand()%30;
    }while(!isprime(p));

    // Find q
    do {
        q = rand() % 30;
    }while(!isprime(q));
    
    n = p * q;
    phi = (p-1) * (q-1);
    
    // Find e
    do {
        e = rand() % phi;
    }while(gcd(phi,e)!=1);
    
    // Find d
    do {
        d = rand() % phi;
    }while((d * e) % phi !=1);
    
    
    cout<<"\n\nTwo prime numbers (p and q) are: "<<p<<" and "<<q<<endl;
    cout<<"n(p*q) = "<<p<<" * "<<q<<" = "<<p*q<<endl;
    cout<<"Φ(p-1)(q-1) = ("<<p<<"-1) * ("<<q<<"-1) = "<<(p-1)*(q-1)<<endl;
    cout<<"Public key (n, e): ("<<n<<", "<<e<<")\n";
    cout<<"Private key (Φ, d): ("<<phi<<", "<<d<<")\n";
    
    for (int i=0;i<len;i++) {
        cipher[i] = encrypt(text[i],e,n);
    }
    
    cout<<"\n\nEncrypted message: ";
    for(int i=0; i<len; i++)
        cout<<cipher[i];
    
    
    for (int i=0;i<len;i++) {
        text[i] = decrypt(cipher[i],d,n);
    }
    text[len] = '\0';
    cout<<"\nDecrypted message: "<<text<<endl;
    return 0;
}
