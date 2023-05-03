CC= gcc -std=c11
CFLAGS = -Wall -Werror -Wextra
LFLAGS = -lcheck
OS = $(shell uname -s)
ifeq ($(OS), Linux)
	LFLAGS += -pthread  -pthread -lrt -lsubunit 
endif

all: s21_cat test

rebuild: clean all

s21_cat: s21_cat.c
	$(CC) $(CFLAGS) s21_cat.c -o s21_cat

test: s21_cat
	sh test.sh

clean:
	$(RM) -rf  *.o *.a *.out
	$(RM) -rf s21_cat

checks: linter cppcheck

linter: s21_cat
	python3 ../../materials/linters/cpplint.py --extensions=c *.c
	python3 ../../materials/linters/cpplint.py --extensions=c *.h

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c 
