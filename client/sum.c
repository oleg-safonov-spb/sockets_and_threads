#include <string.h>
#include <ctype.h>

int sum(const char *str)
{
    int len = strlen(str);
    int total = 0;

    for (int i = 0; i < len; i++)
    {
        if (isdigit(str[i]))
        {
            total += str[i] - '0';
        }
    }

    return total;
}
