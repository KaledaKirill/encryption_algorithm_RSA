#include <stdio.h>


#include "keys.h"
#include "algrorithm_RSA.h"
#include "common.h"
#include "Enter_output_manager.h"

int main()
{
    int mode = 0;
    keys_info keys_info;
    private_key private_key;
    public_key public_key;

    keys_info = generate_keys_info();
    private_key = generate_private_key(keys_info);
    public_key = generate_public_key(keys_info);

    while(1)
    {
        printf("\n1. Encrypt message\n2. Decrypt message\n3. Exit\n");
        mode = enter_int_number_in_range(1, 3);
        if(mode == 3) break;

        if(mode == 1)// TODO: divide on func
        {
            int choice = 0;
            char* message;
            printf("\nEnter the path where you want to save the encrypted message:\n");
            char* encrypted_file_path = read_line();
            printf("\n1. Read message from file(for large text)\n2. Enter message from keyboard(for a short message)\n");
            choice = enter_int_number_in_range(1, 2);
            if(choice == 1)
            {
                printf("\nEnter the path to the file containing the message:\n");
                char* message_file_path = read_line();
                message = read_message_from_file(message_file_path);
            }
            else if(choice == 2)
            {
                message = read_line();
            }
            int* encrypted_message = encrypt(public_key, message);
            //some code to save encrypted message to file
        }
        else if(mode == 2)
        {
            int choice = 0;
            int* encrypted_message;
            printf("\nEnter the path to the file containing the encrypted message:\n");
            char* encrypted_file_path = read_line();
            printf("\n1. Write message to file(for large text)\n2. Print a message to the console(for a short message)\n");
            choice = enter_int_number_in_range(1, 2);
            if(choice == 1)
            {
                printf("\nEnter the path to the file containing the message:\n");
                char* message_file_path = read_line();
                message = read_message_from_file(message_file_path);
            }
            else if(choice == 2)
            {
                message = read_line();
            }
            int* encrypted_message = encrypt(public_key, message);
            //some code to save encrypted message to file
        }
    }
   
    return 0;
}