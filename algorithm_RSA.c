#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


#include "keys.h"
#include "common.h"


#define P 7
#define Q 11

static int gcd_extended(int a, int b, int *x, int *y) 
{
    if (a == 0) 
    {
        *x = 0;
        *y = 1;
        return b;
    }
    
    int x1, y1;
    int gcd = gcd_extended(b % a, a, &x1, &y1);
    
    *x = y1 - (b/a) * x1;
    *y = x1;
    
    return gcd;
}


static int generate_d(int e, int phi) 
{
    int x;
    int y;
    int gcd;
    
    gcd = gcd_extended(e, phi, &x, &y);
    
    if (gcd != 1) 
    {
        return -1;
    } 
    else 
    {
        int result = (x % phi + phi) % phi;
        return result;
    }
}


static int generate_random_num(int min, int max)
{
    return rand() % (max - min + 1) + min;
}


static int get_gcd(int num1, int num2)
{
    return num2 ? get_gcd (num2, num1 % num2) : num1;
}


static int are_coprime(int num1, int num2)
{
    return get_gcd(num1, num2) == 1;
}


static int generate_e(int phi)
{
    int e; 

    do
    {
        e = generate_random_num(1, phi - 1);
    }
    while(!are_coprime(phi, e));

    return e;
}


keys_info generate_keys_info(void)
{
    keys_info keys_info;    
    int n;
    int e;
    int d;
    int phi;

    n = P * Q;
    phi = (P - 1) * (Q - 1);
    e = generate_e(phi);
    d = generate_d(phi, e);

    keys_info.n = n;
    keys_info.e = e;
    keys_info.d = d;
    keys_info.phi = phi;

    return keys_info;
}


public_key generate_public_key(const keys_info keys_info)
{
    public_key public_key;

    public_key.e = keys_info.e;
    public_key.n = keys_info.n;

    return public_key;
}


private_key generate_private_key(const keys_info keys_info)
{
    private_key private_key;

    private_key.d = keys_info.d;
    private_key.n = keys_info.n;

    return private_key;
}


static long long power_mod(long long base, long long exponent, long long mod) {
    long long result = 1;
    base %= mod;
    while (exponent > 0) {
        if (exponent & 1)
            result = (result * base) % mod;
        exponent >>= 1;
        base = (base * base) % mod;
    }
    return result;
}

int* encrypt(const public_key public_key, char* message)
{
    int* cipher = NULL;
    int i;

    for(i = 0; message[i]; i++)
    {
        cipher = (int*)save_realloc(cipher, (i + 1) * sizeof(int)); // TODO: what better?
        cipher[i] = power_mod(message[i], public_key.e, public_key.n);
    }

    cipher[i + 1] = INT_MAX;
    return cipher;
}

char* decrypt(const private_key private_key, int* cipher)
{
    char* message = NULL;
    int i;

    for(i = 0; cipher[i] != INT_MAX; i++)
    {
        message = (char*)save_realloc(message, (i + 1) * sizeof(char));
        message[i] = power_mod(cipher[i], private_key.d, private_key.n);
    }

    message[i + 1] = '\0';
    return message;
}