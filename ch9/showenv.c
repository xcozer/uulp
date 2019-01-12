//
// Created by xuechi on 2019-01-12.
//
#include <stdio.h>

extern char **environ;

int main() {
    int i;

    for (i = 0; environ[i]; ++i) {
        printf("%s\n", *(environ + i));
    }

    return 0;
}