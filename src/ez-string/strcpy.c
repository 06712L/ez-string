#include <stddef.h>
#include <stdlib.h>
#include "ez-string.h"

char* ez_strcpy(char *target, const char *str)
{
    const char *str_ptr = str;
    char *target_ptr = target;
    if(str == NULL) return NULL;
    else if(target == NULL)
    {
        target_ptr = malloc(ez_strlen(str) + 1);
        if(target_ptr == NULL) return NULL;
        target = target_ptr;
    }

    while(*str_ptr != '\0')
    {
        *target_ptr = *str_ptr;
        target_ptr++, str_ptr++;
    }
    *target_ptr = '\0';
    return target;
}
