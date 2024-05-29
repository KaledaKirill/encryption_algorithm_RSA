#include <stdio.h>
#include <string.h>

#include "keys.h"
#include "algrorithm_RSA.h"
#include "common.h"
#include "input_output_manager.h"

static char* get_message(void)
{
    int choice = 0;
    char* message = NULL;

    printf("\n1. Read message from file(for large text)\n2. Enter message from keyboard(for a short message)\n");
    choice = enter_int_number_in_range(1, 2);

    if(choice == 1)
    {
        char* message_file_path = NULL;
        do
        {
            printf("\nEnter the path to the file containing the message: "); // TODO: maybe divide on funcs
            message_file_path = read_file_path();
            if(message_file_path == NULL)
                continue;
            message = read_message_from_file(message_file_path);
        }
        while(message == NULL);
    }
    else if(choice == 2)
    {
        printf("\nEnter the message you want to encrypt\n");
        message = read_line();
    }

    return message;
}

static void save_or_print_message(char* message)
{
    int choice = 0;
    printf("\n1. Write message to file(for large text)\n2. Print a message to the console(for a short message)\n");
    choice = enter_int_number_in_range(1, 2);

    if(choice == 1)
    {
        char* message_file_path = NULL;
        do
        {
            printf("\nEnter the path to the file where you want to save the decrypted message: ");// TODO: maybe divide on funcs
            message_file_path = read_file_path();
        }
        while(message_file_path == NULL);
        write_message_to_file(message_file_path, message);
    }
    else if(choice == 2)
        printf("\ndecrypted message:\n%s\n", message);
}

int main()
{
    int mode = 0;
    keys_info keys_info = generate_keys_info();
    private_key private_key = generate_private_key(keys_info);
    public_key public_key = generate_public_key(keys_info);

    while(1)
    {
        printf("\n1. Encrypt message\n2. Decrypt message\n3. Exit\n");
        mode = enter_int_number_in_range(1, 3);
        if(mode == 3) break;

        if(mode == 1)
        {
            char* message = get_message();
            int* encrypted_message = encrypt(public_key, message);
            int writing_res = -1;
            do
            {
                printf("\nEnter the path where you want to save the encrypted message: ");// TODO: maybe divide on funcs
                char* encrypted_file_path = read_file_path();
                if(encrypted_file_path == NULL)
                    continue;
                writing_res = write_ints_to_file(encrypted_file_path, encrypted_message);
            }
            while(writing_res == -1);
        }
        else if(mode == 2)
        {
            int* encrypted_message = NULL;
            do
            {
                printf("\nEnter the path to the file containing the encrypted message: ");// TODO: maybe divide on funcs
                char* encrypted_file_path = read_file_path();
                    if(encrypted_file_path == NULL)
                        continue;  
                encrypted_message = read_ints_from_file(encrypted_file_path);
            }
            while(encrypted_message == NULL);
            char* decrypted_message = decrypt(private_key, encrypted_message);
            save_or_print_message(decrypted_message);
        }
    }
   
    return 0;
}