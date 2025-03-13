# Compiler and flags
OS := $(shell uname)
COMPILER := gcc

CFLAGS = -std=c11 -Wall -Wextra -Werror

GCOVFLAGS := -fprofile-arcs -ftest-coverage
LDFLAGS := -lcheck -lm -lpthread -lsubunit
LIB_NAME := s21_string.a

ifeq ($(OS), Darwin)
    CFLAGS += -I/opt/homebrew/include
    LDFLAGS += -L/opt/homebrew/lib
endif

.PHONY: all clean test s21_string.a gcov_report clang-format-formating clang-format-check valgrind

all: s21_string.a

test: s21_tests.o $(LIB_NAME)
	$(COMPILER) $(CFLAGS) s21_tests.o -L. -l:s21_string.a -o s21_tests $(LDFLAGS)

s21_tests.o:
	$(COMPILER) $(CFLAGS) -c s21_tests.c -o s21_tests.o

s21_string.a: s21_string.o s21_sprintf.o s21_sscanf.o
	ar rcs $(LIB_NAME) s21_string.o s21_sprintf.o s21_sscanf.o
	ranlib $(LIB_NAME)

s21_string.o: s21_string.c
	$(COMPILER) $(CFLAGS) -c s21_string.c -o s21_string.o

s21_sprintf.o: s21_sprintf.c 
	$(COMPILER) $(CFLAGS) -c s21_sprintf.c -o s21_sprintf.o

s21_sscanf.o: s21_sscanf.c 
	$(COMPILER) $(CFLAGS) -c s21_sscanf.c -o s21_sscanf.o

gcov_s21_tests.o: 
	$(COMPILER) $(CFLAGS) -fprofile-arcs -ftest-coverage -c s21_tests.c -o s21_tests.o

gcov_report: CFLAGS += -fprofile-arcs -ftest-coverage
gcov_report: rebuild gcov_s21_tests.o test
	./s21_tests
	mkdir -p coverage
	lcov --capture --directory . --output-file coverage/coverage.info --include '*/s21_string.c' --include '*/s21_sprintf.c' --include '*/s21_sscanf.c'
	genhtml coverage/coverage.info --output-directory coverage/html
	

clang-format-formating:
	clang-format -i *.c *.h
	
clang-format-check:    
	clang-format -n *.c *.h

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./s21_tests

open:
	open coverage/html/index.html

clean:
	rm -f *.o s21_tests $(LIB_NAME) *.gcda *.gcno *.info
	rm -rf coverage

rebuild: clean all