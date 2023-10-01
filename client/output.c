#include "global.h"
#include <stdio.h>
#include "sum.h"
#include <sys/socket.h>

void *output(void *arg)
{
    struct buffer *buf = (struct buffer *)arg;
    char tmp[BUF_LEN];

    while (1)
    {
        pthread_mutex_lock(&buf->mut);

        while (buf->str[0] == '\0')
        {
            pthread_cond_wait(&buf->cond, &buf->mut);
            // pthread_mutex_unlock(&buf->mut);
            // continue;
        }

        sprintf(tmp, "%s", buf->str);
        buf->str[0] = '\0';

        pthread_mutex_unlock(&buf->mut);

        printf("%s\n", tmp);
        sprintf(tmp, "%d", sum(tmp));

        if (sendto(buf->sock, tmp, strlen(tmp),
                   0, (struct sockaddr *)&buf->saddr, SUN_LEN(&buf->saddr)) == -1)
        {
            fprintf(stderr, "error: unable to send a message on a socket\n");
        }
    }

    return NULL;
}
