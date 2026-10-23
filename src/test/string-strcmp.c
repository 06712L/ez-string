#include "ez-string.h"
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "test-lib.h"

struct test_results
{
    ssize_t test1;
    ssize_t test2;
    int code;
    uint8_t i;
};

#define test(condition, test_1, test_2) for(results.i = 0; condition; results.i++) { \
    results.test1 = test_1; \
    results.test2 = test_2; \
    if(sign(results.test1) != sign(results.test2)) return results; \
} \
results.code++;

struct test_results test_strcmp()
{
    struct test_results results = {0, 0, 1, 0};
    test(test_string[results.i] != NULL, ez_strcmp(test_string[results.i], test_string[results.i]), strcmp(test_string[results.i], test_string[results.i]));
    test(test_string[results.i + 1] != NULL, ez_strcmp(test_string[results.i], test_string[results.i + 1]), strcmp(test_string[results.i], test_string[results.i + 1]));
    return (struct test_results){0, 0, 0, 0};
}
#undef test

int main(void)
{
    struct test_results results = test_strcmp();
    if(results.code != 0) printf("fail code:%d\ntest1 results:%ld\ntest2 results:%ld\ni = %d\n", results.code, results.test1, results.test2, results.i);
    return results.code;
}
