#ifndef COMMON_H
#define COMMON_H

void* safe_realloc(void* ptr, int size);
void* safe_malloc(int size);

int enter_int_number_in_range(int min, int max);

int generate_random_num(int min, int max); 

void free_string_array(char** array, int size);

#endif