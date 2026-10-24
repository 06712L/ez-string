#include "ez-string.h"
#include "test/test-lib.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

struct test_results
{
    const char *string_head;
    const char *test1;
    const char *test2;
    uint8_t i;
    bool error;
};

struct test_results test_strstr(void)
{
    struct test_results resilts = {NULL, NULL, NULL, 0, false};
    const char *test_strstr[] =
    {
        "ab",
        "Tool",
        " meow",
        "喵",
        "OH",
        "-",
        ";",
        "OH MY DISK!!!!!!!!!!!!",
        "\0",
        "！喲",
        "倒灌",
        ".",
        "\n",
        "%",
        "Give up!",
        "2<3=?",
        NULL
    };
    for(resilts.i = 0; test_strstr[resilts.i] != NULL && test_string[resilts.i] != NULL; resilts.i++)
    {
        resilts.string_head = test_string[resilts.i];
        resilts.test1 = ez_strstr(test_string[resilts.i], test_strstr[resilts.i]);
        resilts.test2 = strstr(test_string[resilts.i], test_strstr[resilts.i]);
        if(resilts.test1 != resilts.test2)
        {
            resilts.error = true;
            return resilts;
        }
        resilts.string_head = NULL;
        resilts.test1 = NULL;
        resilts.test2 = NULL;
    }
    resilts.string_head = test_string[0];
    if((resilts.test1 = ez_strstr(test_string[0], NULL)) != resilts.string_head)
    {
        resilts.error = true;
        return resilts;
    }
    return (struct test_results){NULL, NULL, NULL, 0, false};
}

int main(void)
{
    struct test_results results = test_strstr();
    if(results.error)
    {
        puts("string-strstr:");
        printf("fail code: %d\nstring head: %p\ntest1 results: %p\ntest2 results: %p\n", results.i, results.string_head, results.test1, results.test2);
    }
    return results.error;
}
