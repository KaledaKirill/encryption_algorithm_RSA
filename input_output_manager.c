#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input_output_manager.h"
#include "common.h"

static FILE* open_file(const char* file_path, char* mode)
{
    FILE* file_ptr = fopen(file_path, mode);
    if(file_ptr == NULL)
    {
        printf("\nFile opening error! Try using a different file path\n");
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
    if(!extension || extension == filepath)
    {
        printf("\nInvalid file path! Try using a different file path\n");
        return 0;
    } 

    if(strcmp(extension, ".txt") == 0) 
        return 1;
    else 
    {
        printf("\nYour file doesn't have a .txt extension! Try using a different file path\n");
        return 0;
    }
}


char* read_message_from_file(const char* file_path)
{
    long file_length = 0;
    char* string = NULL;

    file_length = get_file_length(file_path);
    if(file_length == -1) 
        return NULL;
    if(file_length == 0) 
    {
        printf("\nFile is empty! Try using a different file path\n");
        return NULL;
    }
    

    FILE* file_ptr = open_file(file_path, "r");
    if(file_ptr == NULL) 
        return NULL;

    string = (char*)safe_malloc(file_length + 1);

    for(int i = 0; i < file_length; i++)
    {
        char ch = getc(file_ptr);
        if(ch == '\n')
            ch = ' ';
        string[i] = ch;
    }
    string[file_length] = '\0';

    fclose(file_ptr);
    return string;
}


static char* cut_back_string(char* string, int full_length)
{
    while(string[full_length - 1] != '\0')
    {
        full_length--;
    }

    string = (char*)safe_realloc(string, full_length * sizeof(char));

    return string;
}

char* read_line(void)
{
    char ch;
    int count = 0;
    int buf_size = 16;
    int delta = 16;
    char* string = (char*)safe_malloc(buf_size * sizeof(char));

    fflush(stdin);
    while((ch = getc(stdin)) != '\n')
    {
        string[count] = ch;
        count++;
        if(count == buf_size)
        {
            buf_size += delta;
            string = (char*)safe_realloc(string, buf_size * sizeof(char));
        }
    }
    string[count] = '\0';
    cut_back_string(string, buf_size);

    return string;
}


char* read_file_path(void)
{
    char* file_path = read_line();
    if(is_file_txt(file_path) == 0)
        return NULL; 
    return file_path;
}


int write_message_to_file(const char* file_path, char* message)
{
    FILE* file_ptr = open_file(file_path, "wb");
    if(file_ptr == NULL) 
        return -1;

    if(fputs(message, file_ptr) == EOF)
    {
        fclose(file_ptr);
        exit(EXIT_FAILURE);
    }
    fclose(file_ptr);

    return 0;
}


int write_ints_to_file(const char* file_path, int* arr) 
{
    FILE* file_ptr = fopen(file_path, "wb");
    if(file_ptr == NULL) 
        return -1;

    int i = 0;
    while(1)
    {
        if(fprintf(file_ptr, "%d ", arr[i]) < 0)
        {
            fclose(file_ptr);
            exit(EXIT_FAILURE);
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
    long file_length = get_file_length(file_path);
    if(file_length == -1) 
        return NULL;
    if(file_length == 0) 
    {
        printf("\nFile is empty! Try using a different file path\n");
        return NULL;
    }

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