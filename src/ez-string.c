#include "ez-string.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

size_t ez_strlen(const char *str)
{
    if(str == NULL) return 0;
    const char *str_ptr = str;
    size_t len = 0;
    while(*str_ptr != '\0')
    {
        len++, str_ptr++;
    }
    return len;
}

int ez_strcmp(const char *str1, const char *str2)
{
    int16_t diff = 0;
    const char *ptr1 = str1, *ptr2 = str2;
    while(*ptr1 != '\0' && *ptr2 != '\0')
    {
        diff = (uint8_t)*ptr1 - (uint8_t)*ptr2;
        if(diff != 0) break;
        ptr1++, ptr2++;
    }
    if(*ptr1 || *ptr2) diff = (uint8_t)*ptr1 - (uint8_t)*ptr2;
    return diff;
}

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
