#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

long int gcd(long int a, long int b)
{
    if (a == 0)
        return b;
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

long int isPrime(long int a)
{
    for (int i = 2; i < a; i++)
    {
        if (a % i == 0)
            return 0;
    }
    return 1;
}

long int encrypt(char ch, long int n, long int e)
{
    long int temp = ch;
    for (int i = 1; i < e; i++)
        temp = (temp * ch) % n;
    return temp;
}

char decrypt(char ch, long int n, long int d)
{
    long int temp = ch;
    for (int i = 1; i < d; i++)
        ch = (temp * ch) % n;
    return ch;
}

int main()
{
    int i, len;
    long int p, q, n, phi, e, d, cipher[50];
    char text[50];
    printf("Enter text to be encrypted: ");
    scanf("%s", &text);
    len = strlen(text);
    do
    {
        p = rand() % 30;
    } while (!isPrime(p));
    do
    {
        q = rand() % 30;
    } while (!isPrime(q));
    n = p * q;
    phi = (p - 1) * (q - 1);
    do
    {
        e = rand() % phi;
    } while (gcd(phi, e) != 1);
    do
    {
        d = rand() % phi;
    } while (((d * e) % phi) != 1);
    printf("Two prime numbers are: %ld and %ld\n", p, q);
    printf("n(p*q) = %ld\n", p * q);
    printf("(p-1)*(q-1) = %ld\n", phi);
    printf("Public key (n,e): (%ld,%ld)\n", n, e);
    printf("Public key (n,d): (%ld,%ld)\n", n, d);
    for (i = 0; i < len; i++)
        cipher[i] = encrypt(text[i], n, e);
    printf("Encrypted message:\n");
    for (i = 0; i < len; i++)
        printf("%ld", cipher[i]);
    for (i = 0; i < len; i++)
        text[i] = encrypt(text[i], n, e);
}