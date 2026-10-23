#include "ez-string.h"
#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>

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
