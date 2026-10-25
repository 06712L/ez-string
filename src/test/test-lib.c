#include "test-lib.h"
#include <stdint.h>
#include <stddef.h>

const char *test_string[] =
{
    "aab",
    "ababc",
    "aaaaaaaaaaaabc",
    "哎哎哎哎哎哎哎哎喲",
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

signed int sign(const int64_t num)
{
    if(num < 0) return -1;
    else if(num > 0) return 1;
    else return 0;
}
