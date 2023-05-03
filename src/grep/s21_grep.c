#include "grep.h"

void parse(int argc, char** argv, stF* flag, char* reg, int* indexFile) {
    for (int cnt = 1; cnt < argc; cnt++) {
        if (argv[cnt][0] == '-') {
            for (int smbl = 1; argv[cnt][smbl] != '\0'; smbl++) {
                if (argv[cnt][smbl] == 'e') {
                    flag->e = 1;
                    flagE(argv, &cnt, reg, &smbl);
                }
                if (argv[cnt][smbl] == 'i') flag->i = 1;
                if (argv[cnt][smbl] == 'v') flag->v = 1;
                if (argv[cnt][smbl] == 'c') flag->c = 1;
                if (argv[cnt][smbl] == 'l') flag->l = 1;
                if (argv[cnt][smbl] == 'n') flag->n = 1;
                if (argv[cnt][smbl] == 'h') flag->h = 1;
                if (argv[cnt][smbl] == 's') flag->s = 1;
                if (argv[cnt][smbl] == 'f') {
                    flag->f = 1;
                    cnt++;
                    flagF(argv, &cnt, reg);
                }
                if (argv[cnt][smbl] == 'o') flag->o = 1;
            }
        } else {
            if (!(reg[0])) {
                zamena(reg, argv[cnt]);
            } else {
                indexFile[cnt] = 1;
            }
        }
    }
}

void zamena(char* reg, char* shabu) {
    if (reg[0] == '\0') {
        // printf("%s", reg);
        snprintf(reg, 5000, "%s", shabu);
    } else {
        snprintf(strchr(reg, 0), 5000, "|%s", shabu);
    }
}

void regex_magic(int argc, char** argv, stF* flag, char* reg, const int* indexFile) {
    int res, number = 0, sym_num = 0, nf = 0;
    size_t buf_line = 0;
    regex_t buf_reg;
    FILE* txt = NULL;
    char* wr_line = NULL;
    int flagIorALL = REG_EXTENDED;
    for (int i = 0; i < 24; i++) nf += indexFile[i];
    for (int c = 1; c < argc; c++) {
        if (indexFile[c] == 1) {
            if ((txt = fopen(argv[c], "r")) != NULL) {
                if (flag->i == 1) flagIorALL = REG_EXTENDED | REG_ICASE;
                regcomp(&buf_reg, reg, flagIorALL);
                while (getline(&wr_line, &buf_line, txt) != EOF) {
                    number++;
                    res = regexec(&buf_reg, wr_line, 0, NULL, 0);
                    if (flag->v == 1) res = !res;
                    if (res == 0) {
                        if (flag->o == 1) {
                            size_t nmatch = 1;
                            regmatch_t pmatch;
                            char* ptr = wr_line;
                            while (res == 0) {
                                res =
                                    regexec(&buf_reg, ptr, nmatch, &pmatch, 0);
                                if (res == 0) {
                                    if (flag->c != 1 && flag->l != 1) {
                                        if (flag->h != 1 && nf > 1)
                                            printf("%s:", argv[c]);
                                        if (flag->n == 1) printf("%d:", number);
                                        for (int i = pmatch.rm_so;
                                             i < pmatch.rm_eo; i++) {
                                            printf("%c", ptr[i]);
                                        }
                                        printf("\n");
                                        ptr = ptr + pmatch.rm_eo;
                                    }
                                }
                            }
                        } else {
                            sym_num++;
                            if (flag->c != 1 && flag->l != 1) {
                                if (flag->h != 1 && nf > 1)
                                    printf("%s:", argv[c]);
                                if (flag->n == 1) printf("%d:", number);
                                printf("%s", wr_line);
                            }
                        }
                    }
                }
                number = 0;
                if ((flag->l == 1 && sym_num > 0)) printf("%s\n", argv[c]);
                if (flag->c == 1) {
                    if (nf > 1) printf("%s:", argv[c]);
                    printf("%d\n", sym_num);
                }
                sym_num = 0;
                fclose(txt);
                regfree(&buf_reg);
            } else {
                if (flag->s != 1)
                    fprintf(stderr, "s21_grep: %s: No such file or directory\n",
                            argv[c]);
            }
        }
    }
    if (wr_line) free(wr_line);
}

void flagE(char** argv, int* cnt, char* reg, int* smbl) {
    (*smbl)++;
    if (argv[*cnt][*smbl] != '\0') {
        zamena(reg, argv[*cnt] + *smbl);
    } else {
        (*cnt)++;
        zamena(reg, argv[*cnt]);
        *smbl = strlen(argv[*cnt]);
    }
}

void flagF(char** argv, const int* cnt, char* reg) {
    FILE* txt_reg = NULL;
    char *ff_line = NULL;
    size_t ff_buf = 0;
    if ((txt_reg = fopen(argv[*cnt], "r")) != NULL) {
        while (getline(&ff_line, &ff_buf, txt_reg) != EOF) {
            char *perepennaya;
            perepennaya = strchr(ff_line, '\n');
            if (perepennaya != NULL && strlen(ff_line) > 1) {
                *perepennaya = '\0';
            }
            zamena(reg, ff_line);
        }
        if (ff_line) free(ff_line);
        fclose(txt_reg);
    } else {
        fprintf(stderr, "s21_grep: %s: No such file or directory\n",
                argv[*cnt]);
    }
}

int main(int argc, char** argv) {
    stF flag = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    char reg[5000] = {'\0'};
    int indexFile[24];
    for (int i = 0; i < 24; i++) indexFile[i] = 0;
    parse(argc, argv, &flag, reg, indexFile);
    regex_magic(argc, argv, &flag, reg, indexFile);
}
