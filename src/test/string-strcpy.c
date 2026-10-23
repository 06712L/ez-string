#include "test-lib.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ez-string.h"

struct test_results
{
    char *test1;
    char *test2;
    uint8_t i;
    bool error;
};

struct test_results test_strcpy()
{
    struct test_results results = {NULL, NULL, 0, false};
    for(results.i = 0; test_string[results.i] != NULL; results.i++)
    {
        results.test1 = ez_strcpy(NULL, test_string[results.i]);
        if(results.test1 == NULL)
        {
            results.error = true;
            return (struct test_results){"ERROR", "MEM", 1, true};
        }
        results.test2 = malloc(strlen(test_string[results.i]) + 1);
        if(results.test2 == NULL)
        {
            results.error = true;
            free(results.test1);
            return (struct test_results){"ERROR", "MEM", 1, true};
        }
        if(strcmp(results.test1, strcpy(results.test2, test_string[results.i])))
        {
            results.error = true;
            free(results.test1);
            free(results.test2);
            return results;
        }
        free(results.test1);
        free(results.test2);
        results.test1 = NULL;
        results.test2 = NULL;
    }
    return (struct test_results){NULL, NULL, 0, false};
}

int main(void)
{
    struct test_results results = test_strcpy();

    if(results.error)
    {
        puts("string-strcpy:");
        if(!strcmp(results.test1, "ERROR") && !strcmp(results.test2, "MEM"))
        {
            puts("ERROR MEM");
            return 1;
        }
        printf("fail code:%d\ntest1 results:%s\ntest2 results:%s\n", results.i, results.test1, results.test2);
    }
    return results.error;
}
