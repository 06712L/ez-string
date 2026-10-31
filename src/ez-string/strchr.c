#include <stddef.h>
#include "ez-string.h"

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
