#ifndef S21_STRING_H
#define S21_STRING_H

typedef long unsigned int s21_size_t;
#define S21_NULL ((void *)0)

#define BUFFER_SIZE 256

#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Path 1
void *s21_memchr(const void *str, int c, s21_size_t n);             // 1
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);   // 2
void *s21_memcpy(void *dest, const void *src, s21_size_t n);        // 3
void *s21_memset(void *str, int c, s21_size_t n);                   // 4
char *s21_strncat(char *dest, const char *src, s21_size_t n);       // 5
char *s21_strchr(const char *str, int c);                           // 6
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);  // 7
char *s21_strncpy(char *dest, const char *src, s21_size_t n);       // 8
s21_size_t s21_strcspn(const char *str1, const char *str2);         // 9
char *s21_strerror(int errnum);                                     // 10
s21_size_t s21_strlen(const char *str);                             // 11
char *s21_strpbrk(const char *str1, const char *str2);              // 12
char *s21_strrchr(const char *str, int c);                          // 13
char *s21_strstr(const char *haystack, const char *needle);         // 14
char *s21_strtok(char *str, const char *delim);                     // 15

// Path 5
void *s21_to_upper(const char *str);  // 1
void *s21_to_lower(const char *str);  // 2
void *s21_insert(const char *src, const char *str,
                 s21_size_t start_index);                 // 3
void *s21_trim(const char *src, const char *trim_chars);  // 4

// Support functions
int is_trim_char(char c, const char *trim_chars);
int is_valid_error(int errnum, size_t error_count);
int s21_strcmp(const char *str1, const char *str2);
char *s21_strcpy(char *restrict dest, const char *restrict src);

typedef struct {
  int left_justification;
  int sign;
  int space;
  int hash;
  int leading_zeros;

  int width;

  int dot;
  int precision;

  int short_h;
  int long_l;
  int long_long_L;

  char *result;
  int alloc_size;
  int size;

  int numeral_system;
  int upper_case;
  int count_symb;
  int added_size;
  int is_allocated;
  int is_reversed;
  int general;
  long double general_num;
  int error;
  char error_message[BUFFER_SIZE];
} Specifier;

int s21_sprintf(char *str, const char *format, ...);

typedef struct {
  int width;

  int short_h;
  int long_l;
  int long_long_L;

  char *data;
  int alloc_size;
  int size;

  int numeral_system;
  int upper_case;
  int count_var;
  int count_symb;
  int error;
  char error_message[BUFFER_SIZE];
  int skip;
} Specifier_sscanf;

int s21_sscanf(const char *str, const char *format, ...);

#endif