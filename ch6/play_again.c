//
// Created by xuechi on 2019-01-06.
//
#include <stdio.h>
#include <fcntl.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <termios.h>

#define ASK "Do you want another transaction"
#define TRIES 3
#define SLEEPTIME 2
#define BEEP putchar('\a')

int get_response(char *, int);

int get_ok_char();

void tty_mode(int);

void set_cr_noecho_mode();

void set_nodelay_mode();

void ctrl_c_handler(int);

int main() {
    int response;

    tty_mode(0);
    set_cr_noecho_mode();
    set_nodelay_mode();
    signal(SIGINT, ctrl_c_handler);
    signal(SIGQUIT, SIG_IGN);

    response = get_response(ASK, TRIES);

    tty_mode(1);

    return response;
}

int get_response(char *question, int max_tries) {
    int input;
    printf("%s (y/n)?", question);
    fflush(stdout);
    while (1) {
        sleep(SLEEPTIME);
        input = tolower(get_ok_char());
        if (input == 'y') {
            return 0;
        }
        if (input == 'n') {
            return 1;
        }
        if (max_tries-- == 0) {
            return 2;
        }
        BEEP;
    }
}

void tty_mode(int how) {
    static struct termios original_mode;
    static int original_flags;
    if (how == 0) {
        tcgetattr(0, &original_mode);
        original_flags = fcntl(0, F_GETFL);
    } else {
        tcsetattr(0, TCSANOW, &original_mode);
        fcntl(0, F_SETFL, original_flags);
    }
}

void set_cr_noecho_mode() {
    struct termios info;
    tcgetattr(0, &info);
    info.c_lflag &= ~ICANON;
    info.c_lflag &= ~ECHO;
    info.c_cc[VMIN] = 1;
    tcsetattr(0, TCSANOW, &info);
}

int get_ok_char() {
    int c;
    while ((c = getchar()) != EOF && strchr("yYnN", c) == NULL)
        ;

    return c;
}

void set_nodelay_mode() {
    int term_flags;
    term_flags = fcntl(0, F_GETFL);
    term_flags |= O_NDELAY;
    fcntl(0, F_SETFL, term_flags);
}

void ctrl_c_handler(int signum) {
    tty_mode(1);
    exit(1);
}