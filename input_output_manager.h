#ifndef INPUT_OUTPUT_MANAGER_H
#define INPUT_OUTPUT_MANAGER_H

char* read_message_from_file(char* file_path);
char* read_message_from_stdin();
void write_message_to_file(char* file_path, char* message);

#endif