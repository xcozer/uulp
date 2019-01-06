//
// Created by xuechi on 2019-01-06.
//
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#define INPUTLEN 10

void int_handler(int);

int main() {
    struct sigaction new_handler;
    sigset_t blocked;

    char x[INPUTLEN];

    new_handler.__sigaction_u.__sa_handler = int_handler;
    new_handler.sa_flags = SA_RESETHAND | SA_RESTART;
//    new_handler.sa_flags = SA_NODEFER | SA_RESTART;

    sigemptyset(&blocked);
    sigaddset(&blocked, SIGQUIT);
    new_handler.sa_mask = blocked;

    if (sigaction(SIGINT, &new_handler, NULL) == -1) {
        perror("sigaction");
    } else {
        while (1) {
            fgets(x, INPUTLEN, stdin);
            printf("input: %s", x);
        }
    }
}

void int_handler(int signum) {
    printf("Called with signal %d\n", signum);
    sleep(signum);
    printf("done handling signal %d\n", signum);
}