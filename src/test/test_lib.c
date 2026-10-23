#include "test_lib.h"
#include <stdint.h>

signed int sign(const int64_t num)
{
    if(num < 0) return -1;
    else if(num > 0) return 1;
    else return 0;
}
