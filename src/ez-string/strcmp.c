#include <stdint.h>
#include <stddef.h>
#include "ez-string.h"

int ez_strcmp(const char *str1, const char *str2)
{
    if(str1 == NULL || str2 == NULL) return 1;
    int16_t diff = 0;
    const unsigned char *ptr1 = (const unsigned char*)str1, *ptr2 = (const unsigned char*)str2;
    while(*ptr1 != '\0' && *ptr2 != '\0')
    {
        diff = *ptr1 - *ptr2;
        if(diff != 0) break;
        ptr1++, ptr2++;
    }
    if(*ptr1 || *ptr2) diff = *ptr1 - *ptr2;
    return diff;
}
