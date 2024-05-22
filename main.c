#include <stdio.h>
#include <string.h>

#include "keys.h"
#include "algrorithm_RSA.h"
#include "common.h"
#include "input_output_manager.h"

int check_message_validity(const char* message, int n) {
    int length = strlen(message);
    for (int i = 0; i < length; i++) {
        if ((unsigned char)message[i] >= n) {
            return 0; // Символ больше или равен n, сообщение не подходит для шифрования
        }
    }
    return 1; // Все символы подходят для шифрования
}


int main()
{
    int mode = 0;
    keys_info keys_info = generate_keys_info();
    private_key private_key = generate_private_key(keys_info);
    public_key public_key = generate_public_key(keys_info);

    printf("d: %d, e: %d, n: %d", private_key.d, public_key.e, keys_info.n);

    while(1)
    {
        printf("\n1. Encrypt message\n2. Decrypt message\n3. Exit\n");
        mode = enter_int_number_in_range(1, 3);
        if(mode == 3) break;

        if(mode == 1)
        {
            int choice = 0;
            char* message;
            printf("\nEnter the path where you want to save the encrypted message:\n");
            char* encrypted_file_path = read_line();
            printf("\n1. Read message from file(for large text)\n2. Enter message from keyboard(for a short message)\n");
            choice = enter_int_number_in_range(1, 2);
            if(choice == 1)
            {
                printf("\nEnter the path to the file containing the message: ");
                char* message_file_path = read_line();
                message = read_message_from_file(message_file_path);
            }
            else if(choice == 2)
            {
                message = read_line();
                printf("\nvalidity: %d\n", check_message_validity(message, keys_info.n));
            }
            int* encrypted_message = encrypt(public_key, message);
            write_ints_to_file(encrypted_file_path, encrypted_message);
        }
        else if(mode == 2)
        {
            int choice = 0;
            printf("\nEnter the path to the file containing the encrypted message:\n");
            char* encrypted_file_path = read_line();
            int* encrypted_message = read_ints_from_file(encrypted_file_path);
            char* decrypted_message = decrypt(private_key, encrypted_message);
            printf("\n1. Write message to file(for large text)\n2. Print a message to the console(for a short message)\n");
            choice = enter_int_number_in_range(1, 2);
            if(choice == 1)
            {
                printf("\nEnter the path to the file where you want to save the decrypted message:\n");
                char* message_file_path = read_line();
                write_message_to_file(message_file_path, decrypted_message);
            }
            else if(choice == 2)
                printf("decrypted message:\n%s", decrypted_message);
        }
    }
   
    return 0;
}