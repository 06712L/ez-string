#include "string.h"
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "tests_lib.h"

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
    const char *test_str[] =
    {
        "Goo Goo Bird Tool",
        "meow meow",
        "meow meow meow",
        "OH MY LINUX!",
        "idiot-tic-tac-toe",
        "int main(int argc, char *argv[]);",
        "+-*/=",
        "snake_case",
        "哎喲！",
        "海水倒灌了！",
        "0123456789.",
        "test\rtest\n",
        "67%",
        "Don't give up!",
        "2^3=?",
        "test@test.test",
        "~/Download/test.mp4",
        "long long long long long long long long long long long long long long long long long long long long long long",
        "\0",
        "\0",
        NULL
    };
    test(test_str[results.i] != NULL, ez_strcmp(test_str[results.i], test_str[results.i]), strcmp(test_str[results.i], test_str[results.i]));
    test(test_str[results.i + 1] != NULL, ez_strcmp(test_str[results.i], test_str[results.i + 1]), strcmp(test_str[results.i], test_str[results.i + 1]));
    return (struct test_results){0, 0, 0, 0};
}
#undef test

int main(void)
{
    struct test_results results = test_strcmp();
    if(results.code != 0) printf("fail code:%d\ntest1 results:%ld\ntest2 results:%ld\ni = %d\n", results.code, results.test1, results.test2, results.i);
    return results.code;
}
