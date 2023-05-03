#ifndef SRC_CAT_CAT_H_
#define SRC_CAT_CAT_H_

#include <stdio.h>
#include <getopt.h>

typedef struct flag {
    int b;
    int e;
    int n;
    int s;
    int t;
    int v;
} stF;

static struct option long_flag[] = {
    {"number-nonblank", 0, 0, 'b'},
    {"number", 0 , 0, 'n'},
    {"squeeze-blank", 0, 0, 's'},
    {0, 0, 0, 0}
};

int main(int argc, char** argv);
int parser(int argc, char** argv, stF* flag);
void read_file(char** argv, stF* flag, int coutnFl);
void processing(char ch, stF* flag, int* num, int* fl, int* memS);

#endif  //  SRC_CAT_CAT_H_
