#include <stdio.h>
#include <string.h>

#include "keys.h"
#include "algrorithm_RSA.h"
#include "common.h"
#include "input_output_manager.h"

static void save_encrypted_file_path(char*** array, int* size, char* new_string) 
{
    *array = safe_realloc(*array, (*size + 1) * sizeof(char*));

    (*array)[*size] = safe_malloc(strlen(new_string) + 1);
    strcpy((*array)[*size], new_string);

    (*size)++;
}

static char* choose_encrypted_file_path(char** array, int size)
{
    printf("\nChoose file path with encrypted message:\n");

    for(int i = 0; i < size; i++)
        printf("\n%d - %s", i + 1, array[i]);
    printf("\n");

    int choice = enter_int_number_in_range(1, size + 1) - 1;

    return array[choice];
} 

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
            printf("\nEnter the path to the file containing the message: ");
            message_file_path = read_file_path();
            if(message_file_path == NULL)
                continue;
            message = read_message_from_file(message_file_path);
        }
        while(message == NULL);
    }
    else if(choice == 2)
    {
        printf("\nEnter the message you want to encrypt: ");
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
            printf("\nEnter the path to the file where you want to save the decrypted message: ");
            message_file_path = read_file_path();
        }
        while(message_file_path == NULL);
        write_message_to_file(message_file_path, message);
    }
    else if(choice == 2)
        printf("\ndecrypted message:\n%s\n", message);
}

static int validate_str_len(char* str)
{
    if(strlen(str) == 0)
    {
        printf("\nMessage is empty. Try again!\n");
        return 0;
    }
    else    
        return 1;
}

static void encrypt_message(public_key public_key, char*** array, int* size)
{
    char* message;
    do
    {
        message = get_message();
    }
    while(validate_str_len(message) == 0);
    int* encrypted_message = encrypt(public_key, message);
    int writing_res = -1;

    char* encrypted_file_path;
    do
    {
        printf("\nEnter the path where you want to save the encrypted message: ");
        encrypted_file_path = read_file_path();
        if(encrypted_file_path == NULL)
            continue;
        writing_res = write_ints_to_file(encrypted_file_path, encrypted_message);
    }
    while(writing_res == -1);
     save_encrypted_file_path(array, size, encrypted_file_path);
}

static void decrypt_message(private_key private_key, char** array, int size)
{
    int* encrypted_message = NULL;

    do
    {
        char* encrypted_file_path = choose_encrypted_file_path(array, size);
            if(encrypted_file_path == NULL)
                continue;  
        encrypted_message = read_ints_from_file(encrypted_file_path);
    }
    while(encrypted_message == NULL);
    
    char* decrypted_message = decrypt(private_key, encrypted_message);
    save_or_print_message(decrypted_message);
}

int main()
{
    int mode = 0;
    char** encrypted_file_paths = NULL;
    int size = 0;
    keys_info keys_info = generate_keys_info();
    private_key private_key = generate_private_key(keys_info);
    public_key public_key = generate_public_key(keys_info);

    while(1)
    {
        printf("\n1. Encrypt message\n2. Decrypt message\n3. Exit\n");
        mode = enter_int_number_in_range(1, 3);
        if(mode == 3) 
        {
            free_string_array(encrypted_file_paths, size);
            break;
        }

        if(mode == 1)
           encrypt_message(public_key, &encrypted_file_paths, &size);
        else if(mode == 2)
            decrypt_message(private_key, encrypted_file_paths, size);
    }
   
    return 0;
}