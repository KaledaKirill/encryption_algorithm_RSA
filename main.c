#include <stdio.h>
#include "keys.h"
#include "generate_keys.h"
#include "encrypt.h"
#include "decrypt.h"

static int is_mode_correct(int mode)
{
    return mode <= 3 && mode >= 1;
}

int main()
{
    int mode = 0;
    keys_info keys_info;
    private_key private_key;
    public_key public_key;

    keys_info = generate_keys_info();
    private_key = generate_private_key(keys_info);
    public_key = generate_public_key(keys_info);

    printf("\n1. Encrypt message\n2. Decrypt message\n3. Exit\n");

    while(1)
    {
        printf("\nWhat do you want to do?\n");
        scanf("%d", &mode);
        if(!is_mode_correct(mode)) continue;
        switch(mode)
        {
            case 1:
                encrypt(public_key);
                break;
            case 2:
                decrypt(private_key);
                break;
            case 3:
                return 0;
        }
    }
   
    return 0;
}