#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "ez-string.h"

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
