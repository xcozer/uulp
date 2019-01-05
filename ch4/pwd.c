//
// Created by xuechi on 2019-01-04.
//
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

ino_t get_inode(char *);

void print_path_to(ino_t);

void inum_to_name(ino_t, char *, int);

int main() {
    print_path_to(get_inode("."));
    putchar('\n');

    return 0;
}

void print_path_to(ino_t i_node) {
    ino_t my_inode;
    char its_name[BUFSIZ];

    if (get_inode("..") != i_node) {
        chdir("..");
        inum_to_name(i_node, its_name, BUFSIZ);
        my_inode = get_inode(".");
        print_path_to(my_inode);
        printf("/%s", its_name);
    }
}

void inum_to_name(ino_t inode_to_find, char *name_buf, int buf_len) {
    DIR *dir_ptr;
    struct dirent *dirent_ptr;

    dir_ptr = opendir(".");
    if (dir_ptr == NULL) {
        perror(".");
        exit(1);
    }

    while ((dirent_ptr = readdir(dir_ptr)) != NULL) {
        if (dirent_ptr->d_ino == inode_to_find) {
            strncpy(name_buf, dirent_ptr->d_name, buf_len);
            name_buf[buf_len - 1] = '\0';
            closedir(dir_ptr);
            return;
        }
    }

    fprintf(stderr, "error looking for inum: %lld\n", inode_to_find);
    exit(1);
}

ino_t get_inode(char *file_name) {
    struct stat info;
    if (stat(file_name, &info) == -1) {
        fprintf(stderr, "Cannot stat ");
        perror(file_name);
        exit(1);
    }

    return info.st_ino;
}