#include "input_output_manager.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//all functions must return NULL if error is happend and print error message 

int is_file_txt(const char *filepath) 
{
    const char *extension = strrchr(filepath, '.');
    if(!extension || extension == filepath) return 0;

    if(strcmp(extension, ".txt") == 0) 
        return 1;
    else 
        return 0;
}


char* read_message_from_file(char* file_path)
{
    if(is_file_txt(file_path) == 0)
    {
        printf("\nYour file does't have a .txt extension!\n");
        return NULL;
    }   

    FILE* file_ptr = fopen(file_path, "r");
    if(file_ptr == NULL)
    {
        printf("\nFile opening error!\n");
        return NULL;
    }


    fclose(file_ptr);
}


char* read_message_from_stdin()
{

}


void write_message_to_file(char* file_path, char* message)
{

}