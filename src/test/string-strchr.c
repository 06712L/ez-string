#include "ez-string.h"
#include "test/test-lib.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

struct test_results
{
    char *string_head;
    char *test1;
    char *test2;
    uint8_t i;
    bool error;
};

struct test_results test_strchr(void)
{
    struct test_results results = {NULL, NULL, NULL, 0, false};
    char* test_strchr[] =
    {
        "a",
        "c",
        "a",
        "\0",
        "T",
        "o",
        " ",
        "!",
        "-",
        "*",
        NULL
    };
    for(results.i = 0; test_strchr[results.i] != NULL && test_string[results.i]; results.i++)
    {
        results.string_head = (char*)test_string[results.i];
        results.test1 = ez_strchr(test_string[results.i], test_strchr[results.i][0]);
        results.test2 = strchr(test_string[results.i], test_strchr[results.i][0]);
        if(results.test1 != results.test2)
        {
            results.error = true;
            return results;
        }
        results.test1 = NULL;
        results.test2 = NULL;
    }
    if((results.test1 = ez_strchr(NULL, '\0')) != NULL)
    {
        results.error = true;
        return results;
    }
    return (struct test_results){NULL, NULL, NULL, 0, false};
}

int main(void)
{
    struct test_results results = test_strchr();
    if(results.error)
    {
        puts("string-strchr:");
        printf("fail code: %d\nstring head: %p\ntest1 results: %p\ntest2 results: %p\n", results.i, results.string_head, results.test1, results.test2);
    }
    return results.error;
}
