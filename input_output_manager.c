#include "input_output_manager.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//all functions must return NULL if error is happend and print error message, 

static void* my_realloc(void* ptr, int size)
{
    void* tmp_ptr;

    tmp_ptr = realloc(ptr, size);
    if(tmp_ptr != NULL)
    {
        return tmp_ptr;
    }
    else
    {
        free(ptr);
        printf("\nMemory allocation error!\n");
        exit(EXIT_FAILURE);
    }
}

static char* cut_back_string(char* string, int full_length)
{
    char ch;

    while(string[full_length - 1] != '\0')
    {
        full_length--;
    }

    string = (char*)my_realloc(string, full_length * sizeof(char));

    return string;
}


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


static long get_file_lenth(const char* file_path)
{ 
    FILE* file_ptr = open_file(file_path, "rb");
    if(file_ptr == NULL) return -1;

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
        printf("\nYour file does't have a .txt extension!\n");
        return 0;
    }
}


char* read_message_from_file(const char* file_path)
{
    long file_length;
    char* string;

    if(is_file_txt(file_path) == 0) return NULL;
    file_length = get_file_lenth(file_path);
    if(file_length == -1) return NULL;
    if(file_length == 0) 
    {
        printf("\nFile is empty!\n");
        return NULL;
    }

    FILE* file_ptr = open_file(file_path, "r");
    if(file_ptr == NULL) return NULL;

    string = (char*)malloc(file_length + 1);
    if(string == NULL)
    {
        printf("\nMemory allocation error!\n");
        fclose(file_ptr);
        return NULL;
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


char* read_message_from_stdin(void)
{
    char ch;
    int count = 0;
    int buf_size = 16;
    int delta = 16;
    char* string = (char*)malloc(buf_size * sizeof(char));
    if(string == NULL)
    {
        printf("\nMemory allocation error!\n");
        return NULL;
    }
    while((ch = getc(stdin)) != '\n')
    {
        string[count] = ch;
        count++;
        if(count == buf_size)
        {
            buf_size += delta;
            string = (char*)my_realloc(string, buf_size * sizeof(char));
        }
    }
    string[count] = '\0';
    cut_back_string(string, buf_size);

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


int main(void)
{
    //char* string = read_message_from_file("data.txt");
    char* string = read_message_from_stdin();
    printf("\n%s\n", string);
    //write_message_to_file("res.txt", string);
    free(string);

    return 0;
}