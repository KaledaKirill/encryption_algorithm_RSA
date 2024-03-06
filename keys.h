#ifndef KEYS_H
#define KEYS_H

typedef struct
{
    int d;
    int n;
} private_key;

typedef struct
{
    int e;
    int n;
} public_key;

typedef struct
{
    int e;
    int d;
    int n;
    int phi;
} keys_info;


#endif