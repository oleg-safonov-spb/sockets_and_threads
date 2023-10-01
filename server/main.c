#include <sys/un.h>
#include <sys/socket.h>
#include <stdio.h>
#include "global.h"
#include <unistd.h>
#include <stdlib.h>
#include "check.h"

int main(int argc, char const *argv[])
{
    int sock;
    struct sockaddr_un saddr;
    char *buf;
    int count;

    sock = socket(PF_UNIX, SOCK_DGRAM, 0);
    if (sock == -1)
    {
        fprintf(stderr, "error: unable to create an endpoint for communication\n");
        return 1;
    }

    saddr.sun_family = AF_UNIX;
    strcpy(saddr.sun_path, SOCK_NAME);

    buf = (char *)malloc(BUF_LEN);
    if (buf == NULL)
    {
        fprintf(stderr, "error: unable to allocate dynamic memory\n");
        return 1;
    }

    if (access(SOCK_NAME, F_OK) == 0)
    {
        unlink(SOCK_NAME);
    }

    if (bind(sock, (struct sockaddr *)&saddr, SUN_LEN(&saddr)) == -1)
    {
        fprintf(stderr, "error: unable to bind a name to a socket\n");
        return 1;
    }

    while (1)
    {
        count = recvfrom(sock, buf, BUF_LEN - 1, 0, NULL, NULL);
        if (count == -1)
        {
            fprintf(stderr, "error: unable to receive a message from a socket\n");
            return 1;
        }
        buf[count] = '\0';

        if (check(buf) == 0)
        {
            printf("%s\n", buf);
        }
    }

    free(buf);
    close(sock);
    unlink(SOCK_NAME);
    return 0;
}
