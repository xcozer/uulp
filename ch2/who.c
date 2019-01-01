#include <stdio.h>
#include <stdlib.h>

#ifdef __linux__
#include <utmp.h>
#elif __APPLE__

#include <utmpx.h>

#endif

#include <fcntl.h>
#include <unistd.h>
#include <utmp.h>

#define SHOWHOST

#ifdef __linux__
void showTime(time_t t);

void showInfo(struct utmp *);
#endif

//read /var/run/utmp
int main(int argc, char *argv[]) {

#ifdef __APPLE__
    struct utmpx *currentRecord;
    setutxent();
    while ((currentRecord = getutxent()) != NULL) {
        printf("%-8.8s", currentRecord->ut_user);
        printf("%-8.8s", currentRecord->ut_line);
        printf("%s", currentRecord->ut_host);
        putchar('\n');
    }
    endutxent();
#elif __linux__
    struct utmp currentRecord;
    int utmpFd;
    size_t recLen = sizeof(currentRecord);

    if ((utmpFd = open(UTMP_FILE, O_RDONLY)) == -1) {
        perror(UTMP_FILE);
        exit(1);
    }

    while (read(utmpFd, &currentRecord, recLen) == recLen) {
        showInfo(&currentRecord);
    }
    close(utmpFd);
#endif
    return 0;
}

#ifdef __linux__
void showInfo(struct utmp *p) {
    if (p->ut_type != USER_PROCESS) {
        return;
    }

    printf("%-8.8s", p->ut_name);
    printf("");
    printf("%-8.8s", p->ut_line);
    printf("");
    showTime(p->ut_time);
    printf("");
#ifdef SHOWHOST
    if (p->ut_host[0] != '\0')
        printf("(%s)", p->ut_host);
#endif
    printf("\n");
}

void showTime(time_t t) {
    char *cp;
    cp = ctime(&t);
    printf("%12.12s", cp + 4);
}
#endif