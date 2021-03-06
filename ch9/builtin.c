//
// Created by xuechi on 2019-01-12.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "smsh.h"
#include "varlib.h"

int assign(char *);

int okname(char *);

int builtin_command(char **args, int *resultp) {
    int rv = 0;

    if (strcmp(args[0], "set") == 0) {
        VLlist();
        *resultp = 0;
        rv = 1;
    } else if (strchr(args[0], '=') != NULL) {
        *resultp = assign(args[0]);
        if (*resultp != -1) {
            rv = 1;
        }
    } else if (strcmp(args[0], "export") == 0) {
        if (args[1] != NULL && okname(args[1])) {
            *resultp = VLexport(args[1]);
        } else {
            *resultp = 1;
        }
        rv = 1;
    } else if (strcmp(args[0], "exit") == 0) {
        exit(0);
    }

    return rv;
}

int assign(char *str) {
    char *cp;
    int rv;

    cp = strchr(str, '=');
    *cp = '\0';
    rv = (okname(str) ? VLstore(str, cp + 1) : -1);
    *cp = '=';

    return rv;
}

int okname(char *name) {
    char *cp;

    for (cp = name; *cp; cp++) {
        if ((isdigit(*cp) && cp == name) || !(isalnum(*cp) || *cp == '_')) {
            printf("wrong name: %s\n", name);
            return 0;
        }
    }

    return cp != name;
}