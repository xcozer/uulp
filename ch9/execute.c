//
// Created by xuechi on 2019-01-08.
//
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

#include "smsh.h"
#include "varlib.h"

int execute(char **argv) {
    int pid, child_info = -1;

    if (argv[0] == NULL) {
        return 0;
    }

    if ((pid = fork()) == -1) {
        perror("fork");
    } else if (pid == 0) {
        environ = VLtable2envrion();

        signal(SIGQUIT, SIG_DFL);
        signal(SIGINT, SIG_DFL);
        execvp(argv[0], argv);
        perror("Cannot execute command");
        exit(1);
    } else {
        if (wait(&child_info) == -1) {
            perror("wait");
        }

    }
    return child_info;
}