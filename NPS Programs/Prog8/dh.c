#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    long long int p, g;
    long long int a, b; // Private Keys
    long long int A, B; // Public Keys
    printf("Enter prime no. p: ");
    scanf("%lld", &p);
    printf("Enter primitive root of p (g): ");
    scanf("%lld", &g);
    printf("Enter A's private key: ");
    scanf("%lld", &a);
    printf("Enter B's private key: ");
    scanf("%lld", &b);
    A = (long long int)pow(g, a) % p;
    B = (long long int)pow(g, b) % p;
    long long int keyA = (long long int)pow(B, a) % p;
    long long int keyB = (long long int)pow(A, b) % p;
    printf("A's secret key is %lld\nB's secret key is %lld\n\n", keyA, keyB);
    return 0;
}