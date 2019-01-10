//
// Created by xuechi on 2019-01-08.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include "smsh.h"

#define DFL_PROMPT ">"

static void setup();

int main() {
    char *cmdline, *prompt, **arglist;
    int result;

    prompt = DFL_PROMPT;
    setup();

    while ((cmdline = next_cmd(prompt, stdin)) != NULL) {
        if ((arglist = splitline(cmdline)) != NULL) {
            result = execute(arglist);
            freelist(arglist);
        }
        free(cmdline);
    }

    return 0;
}

void setup() {
    signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, SIG_IGN);
}

void fatal(char *s1, char *s2, int n) {
    fprintf(stderr, "Error: %s, %s\n", s1, s2);
    exit(n);
}