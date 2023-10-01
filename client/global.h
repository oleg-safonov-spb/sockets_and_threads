#ifndef GLOBAL_H
#define GLOBAL_H

#include <sys/un.h>
#include <pthread.h>

#define BUF_LEN 128
#define SOCK_NAME "mysocket"

struct buffer
{
    int sock;
    struct sockaddr_un saddr;

    char *str;

    pthread_mutex_t mut;
    pthread_cond_t cond;
    // pthread_mutexattr_t mattr;
};

#endif
