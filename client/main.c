#include "global.h"
#include <sys/socket.h>
#include "input.h"
#include "output.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    struct buffer *buf = (struct buffer *)malloc(sizeof(struct buffer));
    if (buf == NULL)
    {
        fprintf(stderr, "error: unable to allocate dynamic memory\n");
        return 1;
    }

    buf->sock = socket(PF_UNIX, SOCK_DGRAM, 0);
    if (buf->sock == -1)
    {
        fprintf(stderr, "error: unable to create an endpoint for communication\n");
        return 1;
    }

    buf->saddr.sun_family = AF_UNIX;
    strcpy(buf->saddr.sun_path, SOCK_NAME);

    buf->str = (char *)malloc(BUF_LEN);
    if (buf->str == NULL)
    {
        fprintf(stderr, "error: unable to allocate dynamic memory\n");
        return 1;
    }

    // pthread_mutexattr_init(&buf->mattr);
    // pthread_mutexattr_settype(&buf->mattr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&buf->mut, NULL);
    pthread_cond_init(&buf->cond, NULL);

    pthread_t t1, t2;

    if (pthread_create(&t1, NULL, input, (void *)buf) != 0)
    {
        fprintf(stderr, "error: unable to create a new thread\n");
        return 1;
    }
    if (pthread_create(&t2, NULL, output, (void *)buf) != 0)
    {
        fprintf(stderr, "error: unable to create a new thread\n");
        return 1;
    }

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    close(buf->sock);
    free(buf->str);
    // pthread_mutexattr_destroy(&buf->mattr);
    pthread_mutex_destroy(&buf->mut);
    pthread_cond_destroy(&buf->cond);
    free(buf);

    return 0;
}
