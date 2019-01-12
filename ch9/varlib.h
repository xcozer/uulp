//
// Created by xuechi on 2019-01-12.
//

#ifndef UULP_VARLIB_H
#define UULP_VARLIB_H

int VLstore(char *, char *);

char *VLlookup(char *);

int VLexport(char *);

void VLlist();

int VLenviron2table(char *[]);

char **VLtable2envrion();

#endif //UULP_VARLIB_H
