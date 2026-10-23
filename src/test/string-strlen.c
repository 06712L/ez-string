#include "test-lib.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "ez-string.h"

struct test_results
{
    size_t test1;
    size_t test2;
    uint8_t i;
    bool error;
};

struct test_results test_strlen()
{
    struct test_results results = {0, 0, 0, false};
    for(results.i = 0; test_string[results.i] != NULL; results.i++)
    {
        results.test1 = ez_strlen(test_string[results.i]);
        results.test2 = strlen(test_string[results.i]);
        if(results.test1 != results.test2)
        {
            results.error = true;
            return results;
        }
        results.test1 = 0;
        results.test2 = 0;
    }
    if((results.test1 = ez_strlen(NULL)) != 0)
    {
        results.error = true;
        return results;
    }
    return (struct test_results){0, 0, 0, false};
}

int main(void)
{
    struct test_results results = test_strlen();
    if(results.error)
    {
        puts("string-strlen:");
        printf("fail code:%d\ntest1 results:%zu\ntest2 results:%zu\n", results.i, results.test1, results.test2);
    }
    return results.error;
}
