//
// Created by xuechi on 2019-01-06.
//
#include <stdio.h>
#include <termios.h>

#define QUESTION "Do you want another transaction"

int get_response(char *);

void tty_mode(int);

void set_cr_noecho_mode();

int main() {
    int response;

    tty_mode(0);
    set_cr_noecho_mode();

    response = get_response(QUESTION);

    tty_mode(1);

    return response;
}

int get_response(char *question) {
    int input;
    printf("%s (y/n)?", question);
    while (1) {
        switch (input = getchar()) {
            case 'y':
            case 'Y':
                return 0;
            case 'n':
            case 'N':
            case EOF:
                return 1;
        }
    }
}

void tty_mode(int how) {
    static struct termios original_mode;
    if (how == 0) {
        tcgetattr(0, &original_mode);
    } else {
        tcsetattr(0, TCSANOW, &original_mode);
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