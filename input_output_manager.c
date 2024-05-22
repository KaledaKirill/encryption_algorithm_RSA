#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input_output_manager.h"
#include "common.h"

#define MAX_WORD_LENGTH 255

//all functions must return NULL if error is happend and print error message, but if error is rare we have to end programm

// static char* cut_back_string(char* string, int full_length)
// // {
// //     while(string[full_length - 1] != '\0')
// //     {
// //         full_length--;
// //     }

// //     string = (char*)save_realloc(string, full_length * sizeof(char));

// //     return string;
// // }


static FILE* open_file(const char* file_path, char* mode)
{
    FILE* file_ptr = fopen(file_path, mode);
    if(file_ptr == NULL)
    {
        printf("\nFile opening error!\n");
        return NULL;
    }
    return file_ptr;
}


static long get_file_length(const char* file_path)
{ 
    FILE* file_ptr = open_file(file_path, "rb");
    if(file_ptr == NULL)
        return -1;

    fseek(file_ptr, 0, SEEK_END);
    long file_size = ftell(file_ptr);

    fclose(file_ptr);

    return file_size;
}


static int is_file_txt(const char *filepath) 
{
    const char *extension = strrchr(filepath, '.');
    if(!extension || extension == filepath) return 0;

    if(strcmp(extension, ".txt") == 0) 
        return 1;
    else 
    {
        printf("\nYour file doesn't have a .txt extension!\n");
        return 0;
    }
}


char* read_message_from_file(const char* file_path)
{
    long file_length;
    char* string;

    if(is_file_txt(file_path) == 0) 
        return NULL;
    file_length = get_file_length(file_path);
    if(file_length == -1) 
        return NULL;
    if(file_length == 0) 
    {
        printf("\nFile is empty!\n");
        return NULL;
    }

    FILE* file_ptr = open_file(file_path, "r");
    if(file_ptr == NULL) 
        return NULL;

    string = (char*)malloc(file_length + 1);
    if(string == NULL)
    {
        printf("\nMemory allocation error!\n");
        fclose(file_ptr);
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < file_length; i++)
    {
        char ch = getc(file_ptr);
        if(ch == '\n') ch = ' ';
        string[i] = ch;
    }
    string[file_length] = '\0';

    fclose(file_ptr);
    return string;
}


// char* read_line(void)
// {
//     char ch;
//     int count = 0;
//     int buf_size = 16;
//     int delta = 16;
//     char* string = (char*)malloc(buf_size * sizeof(char));
//     if(string == NULL)
//     {
//         printf("\nMemory allocation error!\n");
//         exit(EXIT_FAILURE);
//     }
//     while((ch = getc(stdin)) != '\n')
//     {
//         string[count] = ch;
//         count++;
//         if(count == buf_size)
//         {
//             buf_size += delta;
//             string = (char*)save_realloc(string, buf_size * sizeof(char));
//         }
//     }
//     string[count] = '\0';
//     cut_back_string(string, buf_size);

//     return string;
// }

char* cut_back_string(char* string)
{
    int size = strlen(string);
    string = (char*)safe_realloc(string, (size + 1) * sizeof(char));
    return string;
}

char* read_line()
{
    char* string = (char*)malloc(MAX_WORD_LENGTH);
    fflush(stdin);
    if (fgets(string, MAX_WORD_LENGTH, stdin) == NULL)
    {
        printf("\nString reading failed!\n");
        exit(EXIT_FAILURE);
    }

    int stringLen = strlen(string);
    if (stringLen > 0 && string[stringLen - 1] == '\n')
        string[stringLen - 1] = '\0';

    string = cut_back_string(string);
    return string;
}

int write_message_to_file(const char* file_path, char* message)
{
    if(is_file_txt(file_path) == 0) 
        return -1;

    FILE* file_ptr = open_file(file_path, "wb");
    if(file_ptr == NULL) 
        return -1;

    if(fputs(message, file_ptr) == EOF)
        return -1;
    fclose(file_ptr);

    return 0;
}


int write_ints_to_file(const char* file_path, int* arr) 
{
    if(is_file_txt(file_path) == 0) 
        return -1;

    FILE* file_ptr = fopen(file_path, "wb");
    if(file_ptr == NULL) 
        return -1;

    int i = 0;
    while(1)
    {
        if(fprintf(file_ptr, "%d ", arr[i]) < 0)
        {
            fclose(file_ptr);
            return -1;
        }
        if(arr[i] == -1)
            break;
        i++;
    }
    fclose(file_ptr);

    return 0;
}


int* read_ints_from_file(const char* file_path) 
{
    if(is_file_txt(file_path) == 0) 
        return NULL;

    FILE* file_ptr = fopen(file_path, "rb");
    if(file_ptr == NULL) 
        return NULL;

    int* arr = malloc(sizeof(int) * 100); 
    int arr_size = 0;

    while(fscanf(file_ptr, "%d", &arr[arr_size]) != EOF) 
    {
        arr_size++;
        if(arr_size % 100 == 0)
        {
            arr = realloc(arr, sizeof(int) * (arr_size + 100)); 
        }
        if(arr[arr_size - 1] == -1)
            break;
    }
    fclose(file_ptr);

    return arr;
}