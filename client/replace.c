#include "global.h"
#include <stdlib.h>

void replace(char *str)
{
    int len = strlen(str);
    // char *tmp = (char *)malloc(BUF_LEN);
    char tmp[BUF_LEN];

    int j = 0;
    for (int i = 0; i < len; i++)
    {
        if ((str[i] - '0') % 2 == 0)
        {
            tmp[j++] = 'K';
            tmp[j++] = 'B';
        }
        else
        {
            tmp[j++] = str[i];
        }
    }
    tmp[j] = '\0';

    strcpy(str, tmp);
    // free(tmp);
}
