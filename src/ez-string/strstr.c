#include <stdint.h>
#include <stddef.h>
#include "ez-string.h"

char* ez_strstr(const char *haystack, const char *needle)
{
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
    const size_t needle_len = ez_strlen(needle);
    const size_t needle_len_m1 = needle_len - 1;
    while(uhaystack[needle_len_m1] != '\0')
    {
        flag = uhaystack;
        for(size_t i = 0; i < needle_len; i++)
        {
            if(uhaystack[i] != uneedle[i])
            {
                flag = NULL;
                break;
            }
        }
        if(flag == NULL) uhaystack++;
        else break;
    }
    return (char*)flag;
}
