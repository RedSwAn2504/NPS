#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

long int gcd(long int a, long int b)
{
    if (b == 0)
        return a;
    if (a == 0)
        return b;
    return gcd(b, a % b);
}

long int isPrime(long int a)
{
    for (long int i = 2; i < a; i++)
    {
        if (a % i == 0)
            return 0;
    }
    return 1;
}

long int encrypt(char ch, long int n, long int e)
{
    long int temp = ch;
    for (long int i = 1; i < e; i++)
        temp = (temp * ch) % n;
    return temp;
}

char decrypt(long int ch, long int n, long int d)
{
    long int temp = ch;
    for (long int i = 1; i < d; i++)
        ch = (temp * ch) % n;
    return ch;
}

int main()
{
    long int p, q, phi, d, e, ciphertext[50], n;
    char text[50];
    printf("Enter text : ");
    scanf("%s", text);
    long int len = strlen(text);

    do
    {
        p = rand() % 100;
    } while (!isPrime(p));

    do
    {
        q = rand() % 100;
    } while (!isPrime(q));

    n = p * q;
    phi = (p - 1) * (q - 1);

    do
    {
        e = rand() % phi;
    } while (gcd(e, phi) != 1);

    do
    {
        d = rand() % phi;
    } while ((d * e) % phi != 1);

    printf("Two prime numbers are : %ld and %ld\n", p, q);
    printf("Value of n : %ld\n", n);
    printf("Value of Euler's Totient phi : %ld\n", phi);
    printf("Public key (n, e) : (%ld, %ld)\n", n, e);
    printf("Public key (n, d) : (%ld, %ld)\n", n, d);

    for (long int i = 0; i < len; i++)
    {
        ciphertext[i] = encrypt(text[i], n, e);
    }
    printf("Encrypted message : ");
    for (long int i = 0; i < len; i++)
    {
        printf("%ld", ciphertext[i]);
    }
    for (long int i = 0; i < len; i++)
    {
        text[i] = decrypt(ciphertext[i], n, d);
    }
    printf("\n");
    printf("Decrypted Message : ");
    for (long int i = 0; i < len; i++)
    {
        printf("%c", text[i]);
    }
    printf("\n");
    return 0;
}