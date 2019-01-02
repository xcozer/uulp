//
// Created by xuechi on 2019-01-02.
//
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>

void do_ls(char []);

int main(int argc, char *argv[]) {
    if (argc == 1) {
        do_ls(".");
    } else {
        while (--argc) {
            printf("%s:\n", *++argv);
            do_ls(*argv);
        }
    }
}

void do_ls(char dirname[]) {
    DIR *dir_ptr;
    struct dirent *dirent_ptr;

    if ((dir_ptr = opendir(dirname)) == NULL) {
        fprintf(stderr, "ls: cannot open %s\n", dirname);
    } else {
        while ((dirent_ptr = readdir(dir_ptr)) != NULL) {
            printf("%s\n", dirent_ptr->d_name);
        }
        closedir(dir_ptr);
    }
}