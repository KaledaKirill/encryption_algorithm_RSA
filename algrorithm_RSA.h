#ifndef ALGORITHM_RSA_H
#define ALGORITHM_RSA_H

#include "keys.h"

char* decrypt(const private_key private_key, int* cipher);

int* encrypt(const public_key public_key, char* message);

keys_info generate_keys_info(void);

public_key generate_public_key(const keys_info keys_info);

private_key generate_private_key(const keys_info keys_info);

#endif