#ifndef EZ_STRING_H
#define EZ_STRING_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

enum
{
    // Replace mode
    EZ_STRREPLACE_FIRST = 0,
    EZ_STRREPLACE_LAST = 1,
    EZ_STRREPLACE_ALL = 2,
};

size_t ez_strlen(const char *str);
int ez_strcmp(const char *str1, const char *str2);
char *ez_strcpy(char *target, const char *str);
char *ez_strstr(const char *haystack, const char *needle);
char *ez_strchr(const char *s, const char c);
char *ez_strreplace(char *str, const char *replace_str, const char *target_str, int replace_mode, bool in_place, bool auto_realloc);

#endif
