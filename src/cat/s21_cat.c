#include "cat.h"

int parser(int argc, char** argv, stF* flag) {
    char res = 0;
    while ((res = getopt_long(argc, argv, "benstv", long_flag, 0)) != -1) {
        if (res == 'b') flag->b = 1;
        if (res == 'n') flag->n = 1;
        if (res == 's') flag->s = 1;
        if (res == 'v') flag->v = 1;
        if (res == 'e') {
            flag->e = 1;
            flag->v = 1;
        }
        if (res == 't') {
            flag->t = 1;
            flag->v = 1;
        }
        if (res == '?') res = -1;
    }
    return res;
}

void processing(char ch, stF* flag, int* num, int* fl, int* memS) {
    if (flag->b == 1) {
        if (ch != 10 && *fl == 1) {
            fprintf(stdout, "%6d\t", *num);
            (*num)++;
        }
    }
    if (flag->n == 1) {
        if (*fl == 1) {
            fprintf(stdout, "%6d\t", *num);
            (*num)++;
        }
    }
    if (flag->s == 1) {
        if (ch == 10 && *fl == 1)
            (*memS)++;
        else
            *memS = 0;
    }
    if (flag->e == 1 && ch == 10) fprintf(stdout, "$");
    if (flag->t == 1 && ch == 9) {
        printf("^");
        ch = 73;
    }
    if (flag->v == 1) {
        if ((ch >= 0 && ch <= 31) && (ch != 9 && ch != 10)) {
            printf("^");
            ch += 64;
        } else if (ch == 127) {
            printf("^");
            ch = 63;
        }
    }
    if (ch == 10)
        *fl = 1;
    else
        *fl = 0;
    if (*memS < 2) {
        printf("%c", ch);
    }
}

void read_file(char** argv, stF* flag, int coutnFl) {
    FILE* txt;
    int num = 1, fl = 1, memS = 0;
    if ((txt = fopen(argv[coutnFl], "r")) != NULL) {
        char ch = 0;
        while ((ch = fgetc(txt)) != EOF) {
            processing(ch, flag, &num, &fl, &memS);
        }
        fclose(txt);
    } else {
        fprintf(stderr, "s21_cat: %s: No such file or directory\n",
                argv[coutnFl]);
    }
}

int main(int argc, char** argv) {
    stF flag = {0, 0, 0, 0, 0, 0};
    parser(argc, argv, &flag);
    for (int coutnFl = 1; coutnFl < argc; coutnFl++) {
        if (argv[coutnFl][0] != '-') read_file(argv, &flag, coutnFl);
    }
}
