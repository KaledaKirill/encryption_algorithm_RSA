#include "input_output_manager.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//all functions must return NULL if error is happend and print error message 

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
    if(file_ptr == NULL) return 0;

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
    char ch;

    if(is_file_txt(file_path) == 0) 
        return NULL;

    FILE* file_ptr = open_file(file_path, "r");
    if(file_ptr == NULL) 
        return NULL;

    file_length = get_file_lenth(file_path);
    if(file_length == 0) 
    {
        printf("\nFile is empty or doesn't exist\n");
        return NULL;
    }

    string = (char*)malloc(file_length + 1);
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


char* read_message_from_stdin()
{

}


void write_message_to_file(const char* file_path, char* message)
{

}

int main(void)
{
    char* string = read_message_from_file("data.txt");
    printf("\n%s\n", string);
    free(string);

    return 0;
}