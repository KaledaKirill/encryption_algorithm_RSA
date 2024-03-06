#include <stdio.h>
#include "keys.h"
#define P 7
#define Q 11

keys_info generate_keys_info()
{
    keys_info keys_info;

    

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