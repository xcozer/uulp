//
// Created by xuechi on 2019-01-05.
//
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int fd;
    char buf[BUFSIZ];

    if (argc != 2) {
        fprintf(stderr, "usage: write ttyname\n");
        exit(1);
    }

    fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror(argv[1]);
        exit(1);
    }

    while (fgets(buf, BUFSIZ, stdin) != NULL) {
        if (write(fd, buf, BUFSIZ) == -1) {
            break;
        }
    }

    close(fd);

    return 0;
}