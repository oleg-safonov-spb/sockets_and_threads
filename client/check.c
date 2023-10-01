#include <stdio.h>
#include <string.h>
#include <ctype.h>

int check(const char *str)
{
    int len = strlen(str);

    for (int i = 0; i < len; i++)
    {
        if (!isdigit(str[i]))
        {
            fprintf(stderr, "error: the character is not a decimal digit\n");
            return 1;
        }
    }

    if (len > 64)
    {
        fprintf(stderr, "error: the length of the string is more than 64 characters\n");
        return 1;
    }

    return 0;
}
