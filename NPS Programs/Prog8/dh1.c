#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    long long int p, g;
    long long int a, b;
    long long int A, B;

    printf("Enter a Prime number p : ");
    scanf("%lld", &p);
    printf("Enter primitive root of p (g) : ");
    scanf("%lld", &g);

    printf("Enter A's private key : ");
    scanf("%lld", &a);
    printf("Enter B's private key : ");
    scanf("%lld", &b);

    A = (long long int)pow(g, a) % p;
    B = (long long int)pow(g, b) % p;

    long long int keyA = (long long int)pow(B, a) % p;
    long long int keyB = (long long int)pow(A, b) % p;

    printf("A's shared key is %lld\n", keyA);
    printf("B's shared key is %lld\n", keyB);

    return 0;
}