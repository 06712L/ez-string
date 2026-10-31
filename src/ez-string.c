#include "ez-string.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
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

static void strmove(char *str_head, ssize_t move_dist)
{
    if(move_dist == 0) return;
    char *str_tail = ez_strchr(str_head, '\0');

    // Decide moving drc
    enum
    {
        RIGHT = 1,
        LEFT = -1,
    };
    const int8_t  motion = (move_dist > 0) ? RIGHT:LEFT;

    for(; move_dist != 0; move_dist -= motion)
    {
        char *ptr = (move_dist > 0) ? str_tail:str_head;
        const char *end_flag = (move_dist > 0) ? str_head:str_tail + 1;
        str_head += motion;
        str_tail += motion;
        while(ptr != end_flag)
        {
            ptr[motion] = *ptr;
            ptr -= motion;
        }
    }
}

char* ez_strreplace(char *str, const char *replace_str, const char *target_str, int replace_mode, bool in_place, bool auto_realloc)
{
    // Check arg
    if(str == NULL || replace_str == NULL || target_str == NULL) return NULL;
    if(str[0] == '\0') return NULL;
    if(replace_str[0] == '\0') return NULL;
    if(replace_mode < EZ_STRREPLACE_FIRST || replace_mode > EZ_STRREPLACE_ALL) return NULL;

    // Set MEM about
    size_t str_mem_size = ez_strlen(str) + 1;
    const bool ip_ar = (!in_place || auto_realloc);
    if(ip_ar)
    {
        if(!in_place)
        {
            char *tmp = malloc(str_mem_size);
            if(tmp == NULL) return NULL;
            str = ez_strcpy(tmp, str);
        }
    }

    // Backup
    char *backup_str = NULL;
    if(in_place)
    {
        backup_str = malloc(str_mem_size);
        if(backup_str == NULL) return NULL;
        (void)ez_strcpy(backup_str, str);
    }

    // Start replace
    char *str_ptr = str;
    const size_t replace_str_len = ez_strlen(replace_str);
    const size_t target_str_len = ez_strlen(target_str);
    const ssize_t rt_diff_size = (ssize_t)target_str_len - (ssize_t)replace_str_len;
    while(*str_ptr != '\0')
    {
        str_ptr = ez_strstr(str_ptr, replace_str);
        if(str_ptr == NULL)
        {
            if(!in_place) free(str);
            else
            {
                str = ez_strcpy(str, backup_str);
                free(backup_str);
            }
            return NULL;
        }
        const char *end_flag = str_ptr + replace_str_len;
        if(rt_diff_size != 0 || ip_ar)
        {
            // Handle possible address changes caused by realloc
            const size_t end_flag_dist = end_flag - str;
            const size_t str_ptr_dist = str_ptr - str;

            str_mem_size += rt_diff_size;
            if(rt_diff_size < 0) strmove((char*)end_flag, rt_diff_size);
            char *tmp_ptr = realloc(str, str_mem_size);
            if(tmp_ptr == NULL)
            {
                if(!in_place) free(str);
                else
                {
                    str = ez_strcpy(str, backup_str);
                    free(backup_str);
                }
                return NULL;
            }
            str = tmp_ptr;
            str_ptr = str + str_ptr_dist;
            end_flag = str + end_flag_dist;
            if(rt_diff_size > 0) strmove((char*)end_flag, rt_diff_size);
        }
        // TODO: Implement replace logic
    }
}
