//
// Created by xuechi on 2019-01-06.
//
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#define INPUTLEN 100

void int_handler(int);

void quit_handler(int);

int main(int argc, char *argv[]) {
    char input[INPUTLEN];
    ssize_t nchars;

    signal(SIGINT, int_handler);
    signal(SIGQUIT, quit_handler);

    do {
        printf("\nType a message\n");
        nchars = read(0, input, INPUTLEN - 1);
        if (nchars == -1) {
            perror("read returned an error");
        } else {
            input[nchars] = '\0';
            printf("You typed: %s", input);
        }
    } while (strncmp(input, "quite", 4) != 0);
}

void int_handler(int signum) {
    printf("Received signal: %d.. waiting\n", signum);
    sleep(2);
    printf("Leaving int_handler\n");
}

void quit_handler(int signum) {
    printf("Received signal: %d.. waiting\n", signum);
    sleep(3);
    printf("Leaving quit_handler\n");
}
