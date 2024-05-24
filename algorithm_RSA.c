#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "keys.h"
#include "common.h"

#define P 101
#define Q 179

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

    *x = y1 - (b / a) * x1;
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
        return -1; // Если НОД(e, phi) не равен 1, то нет мультипликативно обратного элемента
    else 
    {
        int d = (x % phi + phi) % phi;
        if (d == 1) 
        {
            for (int i = 2; i < phi; i++) 
            {
                d = (i * x % phi + phi) % phi;
                if (d != 1) 
                {
                    return d;
                }
            }
            return -1; 
        } 
        else
            return d;
    }
}

static int get_gcd(int num1, int num2) 
{
    return num2 ? get_gcd(num2, num1 % num2) : num1;
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
    } while (!are_coprime(phi, e));

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
    d = generate_d(e, phi);

    while (d == 1) 
    {
        e = generate_e(phi);
        d = generate_d(e, phi);
    }

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


static long long power_mod(long long base, long long exponent, long long mod) 
{
    long long result = 1;
    base %= mod;
    while (exponent > 0)
    {
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

    int length = strlen(message);
    cipher = (int*)malloc((length + 1) * sizeof(int)); //TODO: add safe func

    for(i = 0; message[i]; i++)
        cipher[i] = power_mod(message[i], public_key.e, public_key.n);

    cipher[length] = -1;
    return cipher;
}

char* decrypt(const private_key private_key, int* cipher)
{
    char* message = NULL;
    int i;
    int length;

    for(length = 0; cipher[length] != -1; length++);

    message = (char*)malloc((length + 1) * sizeof(char)); //TODO: add safe func

    for(i = 0; i < length; i++)
        message[i] = (char)power_mod(cipher[i], private_key.d, private_key.n);
        
    message[length] = '\0';
    return message;
}