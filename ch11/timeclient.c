//
// Created by xuechi on 2019-01-20.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

#define oops(msg) {perror(msg);exit(1);}

int main(int argc, char *argv[]) {
    struct sockaddr_in servadd;
    struct hostent *hp;
    int sock_fd, sock_id;
    char message[BUFSIZ];
    int messlen;

    sock_id = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_id == 0) {
        oops("socket")
    }

    memset(&servadd, 0, sizeof(servadd));
    hp = gethostbyname(argv[1]);
    if (hp == NULL) {
        oops(argv[1])
    }

    memcpy((struct sockaddr *)&servadd.sin_addr, hp->h_addr, hp->h_length);
    servadd.sin_port = htons(atoi(argv[2]));
    servadd.sin_family = AF_INET;

    if (connect(sock_id, (struct sockaddr *) &servadd, sizeof(servadd)) != 0) {
        oops("connect")
    }

    messlen = read(sock_id, message, BUFSIZ);
    if (messlen == -1) {
        oops("read")
    }
    if (write(1, message, messlen) != messlen) {
        oops("write")
    }
    close(sock_id);
}