#include "global.h"
#include "compare.h"
#include "check.h"
#include <stdlib.h>
#include "replace.h"
#include <stdio.h>

void *input(void *arg)
{
    struct buffer *buf = (struct buffer *)arg;

    while (1)
    {
        pthread_mutex_lock(&buf->mut);

        if (buf->str[0] != '\0')
        {
            pthread_mutex_unlock(&buf->mut);
            continue;
        }

        scanf("%s", buf->str);

        if (check(buf->str) != 0)
        {
            buf->str[0] = '\0';
            pthread_mutex_unlock(&buf->mut);
            continue;
        }

        qsort(buf->str, strlen(buf->str), sizeof(char), compare);
        replace(buf->str);

        pthread_mutex_unlock(&buf->mut);
        pthread_cond_signal(&buf->cond);
    }

    return NULL;
}
