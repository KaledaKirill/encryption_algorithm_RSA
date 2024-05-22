#ifndef INPUT_OUTPUT_MANAGER_H
#define INPUT_OUTPUT_MANAGER_H

char* read_message_from_file(const char* file_path);

char* read_line();

int write_message_to_file(const char* file_path, char* message);

int write_ints_to_file(const char* file_path, int* arr);

int* read_ints_from_file(const char* file_path);

#endif