#ifndef EZ_STRING_H
#define EZ_STRING_H

#include <stddef.h>

size_t ez_strlen(const char *str);
int ez_strcmp(const char *str1, const char *str2);
char *ez_strcpy(char *target, const char *str);

#endif
