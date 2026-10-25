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
    // FIXME: 遇到aab類型的Unicode如"哎哎喲"返回NULL而非第2個字元內存位址，只要a的數量為偶數就可能發生：可能是因為在UTF-8中，"哎哎喲"類似這樣[1 2 1][1 2 1][1 3 2] (一個數字代表一字節) 導致目前的搜索算法返回NULL(找不到)
    if(haystack == NULL || needle == NULL || needle[0] == '\0') return (char*)haystack;
    const unsigned char *uhaystack = (const unsigned char*)haystack, *uneedle = (const unsigned char*)needle;
    uhaystack = (const unsigned char*)ez_strchr((const char*)uhaystack, uneedle[0]);
    if(uhaystack == NULL) return NULL;
    if(uneedle[1] == '\0') return (char*)uhaystack;
    else if(uneedle[2] == '\0')
    {
        uint16_t ne = (uneedle[0] << 8) | uneedle[1];
        uint16_t hs = (uhaystack[0] << 8) | uhaystack[1];
        if(ne == hs) return (char*)uhaystack;
    }
    else if(uneedle[3] == '\0')
    {
        uint32_t ne = (uneedle[0] << 16) | (uneedle[1] << 8) | uneedle[2];
        uint32_t hs = (uhaystack[0] << 16) | (uhaystack[1] << 8) | uhaystack[2];
        if(ne == hs) return (char*)uhaystack;
    }
    const unsigned char *flag = NULL;
    const unsigned char *haystack_ptr = uhaystack;
    const unsigned char *needle_ptr = uneedle;
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
            needle_ptr = uneedle;
            next = !next;
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
