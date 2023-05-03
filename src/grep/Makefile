CC= gcc -std=c11
CFLAGS = -Wall -Werror -Wextra
LFLAGS = -lcheck
OS = $(shell uname -s)
ifeq ($(OS), Linux)
CFLAGS += -D_GNU_SOURCE
	LFLAGS += -pthread  -pthread -lrt -lsubunit 
endif

all: s21_grep test

rebuild: clean all

s21_grep: s21_grep.c
	$(CC) $(CFLAGS) s21_grep.c -o s21_grep

test: s21_grep
	sh test.sh

clean:
	$(RM) -rf  *.o *.a *.out
	$(RM) -rf s21_grep

checks: linter cppcheck

linter: s21_grep
	python3 ../../materials/linters/cpplint.py --extensions=c *.c
	python3 ../../materials/linters/cpplint.py --extensions=c *.h

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c 
