//
// Created by xuechi on 2019-01-13.
//
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int pid;
    int fd;
    printf("About to run who into a file\n");

    if ((pid = fork()) == -1) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        close(1);
        fd = creat("userlist", 0644);
        execlp("who", "who", NULL);
        perror("execlp");
        exit(1);
    } else {
        wait(NULL);
        printf("Done running who, results in userlist\n");
    }
}