#ifndef SRC_GREP_GREP_H_
#define SRC_GREP_GREP_H_

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct flag {
    int e;
    int i;
    int v;
    int c;
    int l;
    int n;
    int h;
    int s;
    int f;
    int o;
} stF;

int main(int argc, char** argv);
void parse(int argc, char** argv, stF* flag, char* reg, int* indexFile);
void regex_magic(int argc, char** argv, stF* flag, char* reg, const int* indexFile);
void zamena(char* reg, char* shabu);
void flagE(char** argv, int* cnt, char* reg, int* smbl);
void flagF(char** argv, const int* cnt, char* reg);

#endif  //  SRC_GREP_GREP_H_
