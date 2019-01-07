//
// Created by xuechi on 2019-01-07.
//
#include <stdio.h>
#include <unistd.h>

int main() {
    printf("my pid is %d\n", getpid());
    fork();
    fork();
    fork();
    printf("my pid is %d. Over.\n", getpid());
}