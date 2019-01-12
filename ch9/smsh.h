//
// Created by xuechi on 2019-01-08.
//

#ifndef UULP_SMSH_H
#define UULP_SMSH_H

#define YES 1
#define NO  0

char *next_cmd(char *, FILE *);

char **splitline(char *);

char *newstr(char *, int);

void freelist(char **);

void *emalloc(size_t);

void *erealloc(void *, size_t);

int execute(char **);

void fatal(char *, char *, int);

int is_control_command(char *);

int do_control_command(char **);

int ok_to_execute();

int process(char **args);

#endif //UULP_SMSH_H
