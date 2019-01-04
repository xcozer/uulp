//
// Created by xuechi on 2019-01-04.
//
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

ino_t get_inode(char *);

void print_path_to(ino_t);

void inum_to_name(ino_t, char *, int);

int main() {
    print_path_to(get_inode("."));
    putchar('\n');

    return 0;
}