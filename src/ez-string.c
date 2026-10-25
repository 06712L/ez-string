#include "ez-string.h"
#include <stdbool.h>
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

char* ez_strstr(const char *haystack, const char *needle)
{
    if(haystack == NULL || needle == NULL || !ez_strcmp(needle, "\0")) return (char*)haystack;
    const char *flag = NULL;
    const char *haystack_ptr = haystack;
    const char *needle_ptr = needle;
    bool next = true;
    while(*haystack_ptr != '\0' && *needle_ptr != '\0')
    {
        if(*haystack_ptr == *needle_ptr)
        {
            if(flag == NULL) flag = haystack_ptr;
            needle_ptr++;
            next = true;
        }
        else
        {
            flag = NULL;
            needle_ptr = needle;
            next ^= true;
        }
        if(next) haystack_ptr++;
    }
    if(*needle_ptr != '\0') flag = NULL;
    return (char*)flag;
}

char* ez_strchr(const char *s, const char c)
{
    if(s == NULL) return NULL;
    if(c == '\0') return (char*)s + ez_strlen(s);
    const unsigned char *us = (const unsigned char*)s;
    const unsigned char uc = (const unsigned char)c;
    while(*us != '\0')
    {
        if(*us == uc) return (char*)us;
        us++;
    }
    return NULL;
}
