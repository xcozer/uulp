//
// Created by xuechi on 2019-01-01.
//
#include <fcntl.h>
#include <unistd.h>

#include "utmplib.h"

static char buf[NRECS * UTSIZE];
static int num_recs;
static int cur_rec;
static int fd_utmp = -1;

int utmp_open(char *filename) {
    fd_utmp = open(filename, O_RDONLY);
    cur_rec = num_recs = 0;
    return fd_utmp;
}

static int utmp_reload() {
    ssize_t amt_read;
    amt_read = read(fd_utmp, buf, NRECS * UTSIZE);
    num_recs = amt_read / UTSIZE;
    cur_rec = 0;
    return num_recs;
}

struct utmp *utmp_next() {
    struct utmp *recp;
    if (fd_utmp == -1)
        return NULLUT;
    if (cur_rec == num_recs && utmp_reload() == 0)
        return NULLUT;

    recp = (struct utmp *)&buf[cur_rec * UTSIZE];
    cur_rec++;
    return recp;
}

void utmp_close() {
    if (fd_utmp != -1)
        close(fd_utmp);
}