//
// Created by xuechi on 2019-01-12.
//
#include <stdio.h>

#include "smsh.h"

int process(char **args) {
    int rv = 0;
    if (args[0] == NULL) {
        rv = 0;
    } else if (is_control_command(args[0])) {
        rv = do_control_command(args);
    } else if (ok_to_execute()) {
        if (!builtin_command(args, &rv)) {
            rv = execute(args);
        }
    }

    return rv;
}