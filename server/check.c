#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int check(const char *str)
{
    if (strlen(str) < 2)
    {
        fprintf(stderr, "error: there are less than 2 characters in the string\n");
        return 1;
    }

    if (atoi(str) % 32 != 0)
    {
        fprintf(stderr, "error: the value is not a multiple of 32\n");
        return 1;
    }

    return 0;
}
