//
// Created by xuechi on 2019-01-02.
//
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

void show_stat_info(char *, struct stat *);

void mode_to_letters(int, char []);

int main(int argc, char *argv[]) {
    struct stat info;

    if (argc > 1) {
        if (stat(argv[1], &info) != -1) {
            show_stat_info(argv[1], &info);
            return 0;
        } else {
            perror(argv[1]);
        }
    }

    return 1;
}

void show_stat_info(char *filename, struct stat *stat_ptr) {
//    printf("    mode: %o\n", buf->st_mode);
    char buf[10] = {};
    mode_to_letters(stat_ptr->st_mode, buf);
    printf("    mode: %s\n", buf);
    printf("   links: %d\n", stat_ptr->st_nlink);
    printf("    user: %d\n", stat_ptr->st_uid);
    printf("   group: %d\n", stat_ptr->st_gid);
    printf("    size: %lld\n", stat_ptr->st_size);
    printf(" modtime: %ld\n", stat_ptr->st_mtimespec.tv_sec);
    printf("    name: %s\n", filename);
}

void mode_to_letters(int mode, char str[]) {
    strcpy(str, "----------");

    if (S_ISDIR(mode)) str[0] = 'd';
    if (S_ISCHR(mode)) str[0] = 'c';
    if (S_ISBLK(mode)) str[0] = 'b';

    if (mode & S_IRUSR) str[1] = 'r';
    if (mode & S_IWUSR) str[2] = 'w';
    if (mode & S_IXUSR) str[3] = 'x';

    if (mode & S_IRGRP) str[4] = 'r';
    if (mode & S_IWGRP) str[5] = 'w';
    if (mode & S_IXGRP) str[6] = 'x';

    if (mode & S_IROTH) str[7] = 'r';
    if (mode & S_IWOTH) str[8] = 'w';
    if (mode & S_IXOTH) str[9] = 'x';
}