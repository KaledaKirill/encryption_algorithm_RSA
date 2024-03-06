#ifndef GENERATE_KEYS_H
#define GENERATE_KEYS_H
#include "keys.h"

keys_info generate_keys_info(void);
public_key generate_public_key(const keys_info keys_info);
private_key generate_private_key(const keys_info keys_info);

#endif