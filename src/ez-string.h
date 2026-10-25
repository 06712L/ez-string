#ifndef EZ_STRING_H
#define EZ_STRING_H

#include <stddef.h>

size_t ez_strlen(const char *str);
int ez_strcmp(const char *str1, const char *str2);
char *ez_strcpy(char *target, const char *str);
char *ez_strstr(const char *haystack, const char *needle);
char *ez_strchr(const char *s, const char c);

#endif
