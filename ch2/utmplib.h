//
// Created by xuechi on 2019-01-01.
//

#ifndef REMOTE_DEMO_UTMPLIB_H
#define REMOTE_DEMO_UTMPLIB_H

#include <utmp.h>

#define NRECS 16
#define NULLUT ((struct utmp *)NULL)
#define UTSIZE (sizeof(struct utmp))

int utmp_open(char *filename);
struct utmp *utmp_next();
void utmp_close();

#endif //REMOTE_DEMO_UTMPLIB_H
