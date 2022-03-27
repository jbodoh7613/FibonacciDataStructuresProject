#include <stdio.h>
#include <limits.h>
#include "Fibonacci.h"

int main()
{
    HugeInteger *p;
    unsigned int *q;
    p = parseString("0");
    q = toUnsignedInt(p);
    printf("%u\n",*q);
    free(p->digits);
    free(p);
}
