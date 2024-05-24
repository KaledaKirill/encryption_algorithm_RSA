#include <stdio.h>
#include <stdlib.h>


void* safe_realloc(void* ptr, int size)
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


int enter_int_number_in_range(int min, int max)
{
    int scanf_res = 0;
    int num;

    do
    {
        printf("<%d - %d> --> ", min, max);
        fflush(stdin);
        scanf_res = scanf("%d", &num);
    }
    while(scanf_res != 1 || (num < min || num > max));

    return num;
}

int generate_random_num(int min, int max) 
{
    return rand() % (max - min + 1) + min;
}