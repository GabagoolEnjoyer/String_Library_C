#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

void test_strlen_helper(const char *str, const char *test_name) {
  s21_size_t s21_res = s21_strlen(str);
  s21_size_t std_res = strlen(str);

  printf("=== Тестирование функции path 1.11: s21_strlen ===\n");
  printf("Тест: %s\n", test_name);
  printf("Входные данные: '%s'\n", str);
  printf("Результат s21_strlen: %lu\n", s21_res);
  printf("Результат strlen:     %lu\n", std_res);
  printf("--------------------------\n");

  ck_assert_int_eq(s21_res, std_res);
}

START_TEST(test_s21_strlen_simple) {
  test_strlen_helper("Hello", "Строка ASCII-символов");
}
END_TEST

START_TEST(test_s21_strlen_empty) { test_strlen_helper("", "Пустая строка"); }
END_TEST

START_TEST(test_s21_strlen_unicode) {
  test_strlen_helper("Привет", "Строка UNICODE-символов");
}
END_TEST

START_TEST(test_s21_strlen_special) {
  test_strlen_helper("Hel\tlo", "Строка со специальными символами");
}
END_TEST

START_TEST(test_s21_strlen_spaces) {
  test_strlen_helper("       ", "Строка пробелов");
}
END_TEST

Suite *s21_strlen_suite(void) {
  Suite *s = suite_create("s21_strlen");
  TCase *tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_s21_strlen_simple);
  tcase_add_test(tc_core, test_s21_strlen_empty);
  tcase_add_test(tc_core, test_s21_strlen_unicode);
  tcase_add_test(tc_core, test_s21_strlen_special);
  tcase_add_test(tc_core, test_s21_strlen_spaces);

  suite_add_tcase(s, tc_core);

  return s;
}

void test_memchr_helper(const char *str, int c, s21_size_t n,
                        const char *test_name) {
  void *s21_res = s21_memchr(str, c, n);
  void *std_res = memchr(str, c, n);

  printf("=== Тестирование функции path 1.1: s21_memchr ===\n");
  printf("Тест: %s\n", test_name);
  printf(
      "Входные данные: строка: '%s', символ: '%c', количество символов: %lu\n",
      str, c, n);
  printf("Результат s21_memchr: %p\n", &s21_res);
  printf("Результат memchr:     %p\n", &std_res);
  printf("--------------------------\n");

  ck_assert_ptr_eq(s21_res, std_res);
}

START_TEST(test_s21_memchr_first_symbol) {
  test_memchr_helper("Hello", 'H', 3, "Символ в пределах диапазона поиска");
}
END_TEST

START_TEST(test_s21_memchr_out_of_range) {
  test_memchr_helper("Hello", 'o', 3, "Символ за пределами диапазона поиска");
}
END_TEST

START_TEST(test_s21_memchr_null_symbol) {
  test_memchr_helper("Hello", '\0', 6, "Нулевой символ в простой строке");
}
END_TEST

START_TEST(test_s21_memchr_empty_line) {
  test_memchr_helper("", 'H', 3, "Ненулевой символ в пустой строке");
}
END_TEST

START_TEST(test_s21_memchr_special) {
  test_memchr_helper(" .,.!^%&(\\/)^(*)^(\\/)", '\\', 20, "Специальный символ");
}
END_TEST

START_TEST(test_s21_memchr_null_symbol_2) {
  test_memchr_helper("hello\t^%&(\\/)", '\0', 10,
                     "Нулевой символ в строке специальных символов");
}
END_TEST

Suite *s21_memchr_suite(void) {
  Suite *s = suite_create("s21_memchr");
  TCase *tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_s21_memchr_first_symbol);
  tcase_add_test(tc_core, test_s21_memchr_out_of_range);
  tcase_add_test(tc_core, test_s21_memchr_null_symbol);
  tcase_add_test(tc_core, test_s21_memchr_empty_line);
  tcase_add_test(tc_core, test_s21_memchr_special);
  tcase_add_test(tc_core, test_s21_memchr_null_symbol_2);

  suite_add_tcase(s, tc_core);

  return s;
}

void test_strchr_helper(const char *str, int c, const char *test_name) {
  char *s21_res = s21_strchr(str, c);
  char *std_res = strchr(str, c);

  printf("=== Тестирование функции path 1.6: s21_strchr ===\n");
  printf("Тест: %s\n", test_name);
  printf("Входные данные: строка: '%s', символ: '%c'\n", str, c);
  printf("Результат s21_strchr: %p\n", &s21_res);
  printf("Результат strchr:     %p\n", &std_res);
  printf("--------------------------\n");

  ck_assert_ptr_eq(s21_res, std_res);
}

START_TEST(test_s21_strchr_simple) {
  test_strchr_helper("Hello", 'o', "Символ, входящий в строку");
}
END_TEST

START_TEST(test_s21_strchr_none) {
  test_strchr_helper("Hello", 'd', "Символ, не входящий в строку");
}
END_TEST

START_TEST(test_s21_strchr_null_symbol) {
  test_strchr_helper("Hello", '\0', "Нулевой символ");
}
END_TEST

START_TEST(test_s21_strchr_empty_line) {
  test_strchr_helper("", 'l', "Ненулевой символ в пустой строке");
}
END_TEST

START_TEST(test_s21_strchr_special) {
  test_strchr_helper("hello\t^%&(\\/)", '\t',
                     "Специальный символ (одно вхождение)");
}
END_TEST

START_TEST(test_s21_strchr_special_2) {
  test_strchr_helper(" .,.!^%&(\\/)^(*)^(\\/)", '\\',
                     "Специальный символ (два вхождения)");
}
END_TEST

Suite *s21_strchr_suite(void) {
  Suite *s = suite_create("s21_strchr");
  TCase *tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_s21_strchr_simple);
  tcase_add_test(tc_core, test_s21_strchr_none);
  tcase_add_test(tc_core, test_s21_strchr_null_symbol);
  tcase_add_test(tc_core, test_s21_strchr_empty_line);
  tcase_add_test(tc_core, test_s21_strchr_special);
  tcase_add_test(tc_core, test_s21_strchr_special_2);

  suite_add_tcase(s, tc_core);

  return s;
}

START_TEST(test_s21_strerror_single) {
  int errnum = _i;

  char *result_s21 = s21_strerror(errnum);

  char *result_original = strerror(errnum);

  printf("=== Тестирование функции path 1.10: s21_strerror ===\n");
  printf("Значение errnum=%d\n", errnum);
  printf("s21_strerror: '%s'\n", result_s21);
  printf("strerror:     '%s'\n", result_original);
  printf("--------------------------\n");

  ck_assert_msg(strcmp(result_s21, result_original) == 0,
                "Mismatch for errnum=%d: s21_strerror='%s', strerror='%s'",
                errnum, result_s21, result_original);
}
END_TEST

Suite *s21_strerror_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_strerror");

  tc_core = tcase_create("Core");

  for (int i = 0; i <= 150; i++) {
    tcase_add_loop_test(tc_core, test_s21_strerror_single, i, i + 1);
  }

  suite_add_tcase(s, tc_core);

  return s;
}

void test_strncat_helper(const char *initial_dest, const char *src, int n,
                         const char *message) {
  char dest_s21[50];
  char dest_original[50];
  strcpy(dest_s21, initial_dest);
  strcpy(dest_original, initial_dest);

  s21_strncat(dest_s21, src, n);
  strncat(dest_original, src, n);

  printf("=== Тестирование функции path 1.5: s21_strncat ===\n");
  printf("Тест: %s\n", message);
  printf("Входные данные: dest = '%s', src = '%s', n = %d\n", initial_dest, src,
         n);
  printf("Результат s21_strncat: '%s'\n", dest_s21);
  printf("Результат strncat:     '%s'\n", dest_original);
  printf("--------------------------\n");

  ck_assert_str_eq(dest_s21, dest_original);
}

START_TEST(test_s21_strncat_simple_concat) {
  test_strncat_helper("Hello, ", "world!", 6, "Простая конкатенация");
}
END_TEST

START_TEST(test_s21_strncat_partial_concat) {
  test_strncat_helper("Hello, ", "world!", 3, "Конкатенация части строки");
}
END_TEST

START_TEST(test_s21_strncat_empty_src) {
  test_strncat_helper("Hello, ", "", 5, "Конкатенация пустой строки");
}
END_TEST

START_TEST(test_s21_strncat_empty_dest) {
  test_strncat_helper("", "world!", 6, "Конкатенация в пустую строку");
}
END_TEST

START_TEST(test_s21_strncat_large_n) {
  test_strncat_helper("Hello, ", "world!", 50,
                      "Длина n больше длины строки-источника");
}
END_TEST

START_TEST(test_s21_strncat_null_args) {
  printf("=== Тестирование функции: s21_strncat ===\n");
  printf("Тест: S21_NULL аргументы\n");

  char src[] = "world!";
  printf("Входные данные: dest = NULL, src = '%s', n = 3\n", src);
  ck_assert_ptr_eq(s21_strncat(S21_NULL, src, 3), S21_NULL);

  printf("Входные данные: dest = 'Hello, ', src = S21_NULL, n = 3\n");
  char dest[50] = "Hello, ";
  ck_assert_ptr_eq(s21_strncat(dest, S21_NULL, 3), S21_NULL);
}
END_TEST

Suite *s21_strncat_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_strncat");

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_strncat_simple_concat);
  tcase_add_test(tc_core, test_s21_strncat_partial_concat);
  tcase_add_test(tc_core, test_s21_strncat_empty_src);
  tcase_add_test(tc_core, test_s21_strncat_empty_dest);
  tcase_add_test(tc_core, test_s21_strncat_large_n);
  tcase_add_test(tc_core, test_s21_strncat_null_args);

  suite_add_tcase(s, tc_core);

  return s;
}

void test_strtok_helper(const char *input, const char *delim,
                        const char *message) {
  char str_s21[100];
  char str_original[100];
  strcpy(str_s21, input);
  strcpy(str_original, input);

  printf("=== Тестирование функции path 1.15: s21_strtok ===\n");
  printf("Тест: %s\n", message);
  printf("Входные данные: input = '%s', delim = '%s'\n", input, delim);

  char *token_s21 = s21_strtok(str_s21, delim);
  char *token_original = strtok(str_original, delim);

  while (token_s21 != S21_NULL || token_original != S21_NULL) {
    printf("Токен s21_strtok: '%s', Токен strtok: '%s'\n", token_s21,
           token_original);

    ck_assert_msg(token_s21 != S21_NULL && token_original != S21_NULL,
                  "Один из токенов S21_NULL");

    ck_assert_str_eq(token_s21, token_original);

    token_s21 = s21_strtok(S21_NULL, delim);
    token_original = strtok(S21_NULL, delim);
  }

  printf("--------------------------\n");
}

START_TEST(test_s21_strtok_simple_split) {
  test_strtok_helper("Hello world", " ", "Простое разделение");
}
END_TEST

START_TEST(test_s21_strtok_complex_delimiters) {
  test_strtok_helper("Hello, world! This is C.", " ,.!?",
                     "Сложные разделители");
}
END_TEST

START_TEST(test_s21_strtok_continuous_delimiters) {
  test_strtok_helper(",,Hello,,world!!", ",!", "Непрерывные разделители");
}
END_TEST

START_TEST(test_s21_strtok_no_tokens) {
  test_strtok_helper(",,,", ",", "Нет токенов (только разделители)");
}
END_TEST

START_TEST(test_s21_strtok_no_delimiters) {
  test_strtok_helper("HelloWorld", " ", "Нет разделителей");
}
END_TEST

START_TEST(test_s21_strtok_edge_case_spaces) {
  test_strtok_helper(" Hello  world ", " ", "Лишние пробелы в начале и конце");
}
END_TEST

Suite *s21_strtok_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_strtok");

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_strtok_simple_split);
  tcase_add_test(tc_core, test_s21_strtok_complex_delimiters);
  tcase_add_test(tc_core, test_s21_strtok_continuous_delimiters);
  tcase_add_test(tc_core, test_s21_strtok_no_tokens);
  tcase_add_test(tc_core, test_s21_strtok_no_delimiters);
  tcase_add_test(tc_core, test_s21_strtok_edge_case_spaces);

  suite_add_tcase(s, tc_core);

  return s;
}

void test_memcpy_helper(const char *src, s21_size_t n, const char *test_name) {
  char dest1[100] = {0};
  char dest2[100] = {0};

  s21_memcpy(dest1, src, n);
  memcpy(dest2, src, n);

  printf("=== Тестирование функции path 1.3: s21_memcpy ===\n");
  printf("Тест: %s\n", test_name);
  printf("Входные данные: src='%s', n=%lu\n", src, n);
  printf("Результат s21_memcpy: %s\n", dest1);
  printf("Результат memcpy:     %s\n", dest2);
  printf("--------------------------\n");

  ck_assert_mem_eq(dest1, dest2, n);
}

START_TEST(test_s21_memcpy_simple) {
  test_memcpy_helper("Hello", 5, "Простое копирование");
}
END_TEST

START_TEST(test_s21_memcpy_small_to_large) {
  test_memcpy_helper("Hello", 5,
                     "Копирование маленькой строки в больший буфер");
}
END_TEST

START_TEST(test_s21_memcpy_empty) {
  test_memcpy_helper("", 0, "Копирование пустой строки");
}
END_TEST

START_TEST(test_s21_memcpy_unicode) {
  test_memcpy_helper("привет", 12, "Копирование Unicode символов");
}
END_TEST

START_TEST(test_s21_memcpy_special) {
  test_memcpy_helper(" 123 ", 5, "Копирование специальных символов");
}
END_TEST

START_TEST(test_s21_memcpy_special2) {
  test_memcpy_helper(" .,.!^%&(\\/)^(*)^(\\/)", 21,
                     "Копирование большего количества специальных символов");
}
END_TEST

START_TEST(test_s21_memcpy_special3) {
  test_memcpy_helper("hello\t\n", 7,
                     "Копирование строк с escape-последовательностями");
}
END_TEST

START_TEST(test_s21_memcpy_non_string_data) {
  int src[] = {1, 2, 3, 4, 5};
  int dest1[5] = {0};
  int dest2[5] = {0};

  s21_memcpy(dest1, src, sizeof(src));
  memcpy(dest2, src, sizeof(src));

  printf("=== Тестирование функции: s21_memcpy ===\n");
  printf("Тест: Копирование не string формата\n");
  printf("Входные данные: src array={1, 2, 3, 4, 5}, n=%zu\n", sizeof(src));
  printf("Результат s21_memcpy: {");
  for (size_t i = 0; i < 5; i++) {
    printf("%d", dest1[i]);
    if (i < 4) printf(", ");
  }
  printf("}\n");
  printf("Результат memcpy:     {");
  for (size_t i = 0; i < 5; i++) {
    printf("%d", dest2[i]);
    if (i < 4) printf(", ");
  }
  printf("}\n");
  printf("--------------------------\n");

  ck_assert_mem_eq(dest1, dest2, sizeof(src));
}
END_TEST

Suite *s21_memcpy_suite(void) {
  Suite *s = NULL;
  TCase *tc_core = NULL;

  s = suite_create("s21_memcpy");

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_memcpy_simple);
  tcase_add_test(tc_core, test_s21_memcpy_small_to_large);
  tcase_add_test(tc_core, test_s21_memcpy_empty);
  tcase_add_test(tc_core, test_s21_memcpy_unicode);
  tcase_add_test(tc_core, test_s21_memcpy_special);
  tcase_add_test(tc_core, test_s21_memcpy_special2);
  tcase_add_test(tc_core, test_s21_memcpy_special3);
  tcase_add_test(tc_core, test_s21_memcpy_non_string_data);

  suite_add_tcase(s, tc_core);

  return s;
}

void test_strncpy_helper(const char *src, s21_size_t n, const char *test_name) {
  char dest1[100] = {0};
  char dest2[100] = {0};

  s21_strncpy(dest1, src, n);
  strncpy(dest2, src, n);

  printf("=== Тестирование функции path 1.8: s21_strncpy ===\n");
  printf("Тест: %s\n", test_name);
  printf("Входные данные: src='%s', n=%lu\n", src, n);
  printf("Результат s21_strncpy: %s\n", dest1);
  printf("Результат strncpy:     %s\n", dest2);
  printf("--------------------------\n");

  ck_assert_mem_eq(dest1, dest2, n);
}

START_TEST(test_s21_strncpy_simple) {
  test_strncpy_helper("hello", 10, "Простое копирование");
}
END_TEST

START_TEST(test_s21_strncpy_partial_copy) {
  test_strncpy_helper("hello", 3, "Частичное копирование");
}
END_TEST

START_TEST(test_s21_strncpy_padding) {
  test_strncpy_helper("hello", 10, "Копирование с заполнением");
}
END_TEST

START_TEST(test_s21_strncpy_non_string_data) {
  int src[] = {1, 2, 3, 4, 5};
  int dest1[5] = {0};
  int dest2[5] = {0};

  s21_strncpy((char *)dest1, (char *)src, sizeof(src));
  strncpy((char *)dest2, (char *)src, sizeof(src));

  printf("=== Тестирование функции path 1.8: s21_strncpy ===\n");
  printf("Тест: Копирование не string формата\n");
  printf("Входные данные: src array={1, 2, 3, 4, 5}, n=%zu\n", sizeof(src));
  printf("Результат s21_strncpy: {");
  for (size_t i = 0; i < 5; i++) {
    printf("%d", dest1[i]);
    if (i < 4) printf(", ");
  }
  printf("}\n");
  printf("Результат strncpy:     {");
  for (size_t i = 0; i < 5; i++) {
    printf("%d", dest2[i]);
    if (i < 4) printf(", ");
  }
  printf("}\n");
  printf("--------------------------\n");

  ck_assert_mem_eq(dest1, dest2, sizeof(src));
}
END_TEST

Suite *s21_strncpy_suite(void) {
  Suite *s = NULL;
  TCase *tc_core = NULL;

  s = suite_create("s21_strncpy");

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_strncpy_simple);
  tcase_add_test(tc_core, test_s21_strncpy_partial_copy);
  tcase_add_test(tc_core, test_s21_strncpy_padding);
  tcase_add_test(tc_core, test_s21_strncpy_non_string_data);

  suite_add_tcase(s, tc_core);

  return s;
}

void test_strrchr_helper(const char *str, int c, const char *test_name) {
  char *s21_result = s21_strrchr(str, c);
  char *basic_result = strrchr(str, c);

  printf("=== Тестирование функции 1.13: s21_strrchr ===\n");
  printf("Тест: %s\n", test_name);
  printf("Входные данные: str='%s', c='%c'\n", str, c);
  printf("Результат s21_strrchr: %s\n", s21_result ? s21_result : "NULL");
  printf("Результат strrchr:     %s\n", basic_result ? basic_result : "NULL");
  printf("--------------------------\n");

  ck_assert_ptr_eq(s21_result, basic_result);
}

START_TEST(test_s21_strrchr_normal) {
  test_strrchr_helper("hello", 'o', "Нормальный случай");
}
END_TEST

START_TEST(test_s21_strrchr_no_character_found) {
  test_strrchr_helper("hello", 'z', "Символ не найден");
}
END_TEST

START_TEST(test_s21_strrchr_multiple_same_chars) {
  test_strrchr_helper("lllllllllll", 'l', "Несколько одинаковых символов");
}
END_TEST

START_TEST(test_s21_strrchr_null_terminator) {
  test_strrchr_helper("hello", '\0', "Символ - нулевой терминатор");
}
END_TEST

START_TEST(test_s21_strrchr_empty_string) {
  test_strrchr_helper("", 'a', "Пустая строка");
}
END_TEST

Suite *s21_strrchr_suite(void) {
  Suite *s = NULL;
  TCase *tc_core = NULL;

  s = suite_create("s21_strrchr");

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_strrchr_normal);
  tcase_add_test(tc_core, test_s21_strrchr_no_character_found);
  tcase_add_test(tc_core, test_s21_strrchr_multiple_same_chars);
  tcase_add_test(tc_core, test_s21_strrchr_null_terminator);
  tcase_add_test(tc_core, test_s21_strrchr_empty_string);

  suite_add_tcase(s, tc_core);

  return s;
}

void test_insert_helper(const char *src, const char *str,
                        s21_size_t start_index, char *correct_result,
                        const char *test_name) {
  char *result = (char *)s21_insert(src, str, start_index);

  printf("=== Тестирование функции path 2.3: s21_insert ===\n");
  printf("Тест: %s\n", test_name);
  printf("Входные данные: '%s'\n", str);
  printf("Результат s21_insert: %s\n", result);
  printf("Результат insert:     %s\n", correct_result);
  printf("--------------------------\n");

  ck_assert_str_eq(result, correct_result);
  free(result);
}

START_TEST(test_s21_insert_normal_case) {
  test_insert_helper("Hello, World!", "Beautiful ", 7,
                     "Hello, Beautiful World!", "Обычный случай");
}
END_TEST

START_TEST(test_s21_insert_at_the_beginning_case) {
  test_insert_helper("World!", "Hello, ", 0, "Hello, World!",
                     "Вставка в начало");
}
END_TEST

START_TEST(test_s21_insert_at_the_end_case) {
  test_insert_helper("Hello, ", "World!", 7, "Hello, World!",
                     "Вставка в конец");
}
END_TEST

START_TEST(test_s21_insert_empty_string_case) {
  test_insert_helper("Hello, World!", "", 7, "Hello, World!",
                     "Вставка пустой строки");
}
END_TEST

START_TEST(test_s21_insert_empty_src_case) {
  test_insert_helper("", "Hello, World!", 0, "Hello, World!",
                     "Вставка в пустую строку");
}
END_TEST

Suite *s21_insert_suite(void) {
  Suite *s = NULL;
  TCase *tc_core = NULL;

  s = suite_create("s21_insert");

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_insert_normal_case);
  tcase_add_test(tc_core, test_s21_insert_at_the_beginning_case);
  tcase_add_test(tc_core, test_s21_insert_at_the_end_case);
  tcase_add_test(tc_core, test_s21_insert_empty_string_case);
  tcase_add_test(tc_core, test_s21_insert_empty_src_case);

  suite_add_tcase(s, tc_core);

  return s;
}

void test_to_upper_helper(const char *str, char *correct_result,
                          const char *test_name) {
  char *result = (char *)s21_to_upper(str);

  printf("=== Тестирование функции path 2.1: s21_to_upper ===\n");
  printf("Тест: %s\n", test_name);
  printf("Входные данные: '%s'\n", str);
  printf("Результат s21_to_upper: %s\n", result);
  printf("Результат insert:     %s\n", correct_result);
  printf("--------------------------\n");

  ck_assert_str_eq(result, correct_result);
  free(result);
}

START_TEST(test_s21_to_upper_normal_case) {
  test_to_upper_helper("hello", "HELLO", "Обычный случай");
}
END_TEST

START_TEST(test_s21_to_upper_some_capital_letters_case) {
  test_to_upper_helper("HeLlO", "HELLO", "Некоторые буквы заглавные");
}
END_TEST

START_TEST(test_s21_to_upper_no_changes_case) {
  test_to_upper_helper("HELLO", "HELLO", "Без изменений");
}
END_TEST

START_TEST(test_s21_to_upper_empty_case) {
  test_to_upper_helper("", "", "Пустая строка");
}
END_TEST

START_TEST(test_s21_to_upper_int_case) {
  test_to_upper_helper("12345", "12345", "Обработка цифр");
}
END_TEST

Suite *s21_to_upper_suite(void) {
  Suite *s = NULL;
  TCase *tc_core = NULL;

  s = suite_create("s21_to_upper");

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_to_upper_normal_case);
  tcase_add_test(tc_core, test_s21_to_upper_some_capital_letters_case);
  tcase_add_test(tc_core, test_s21_to_upper_no_changes_case);
  tcase_add_test(tc_core, test_s21_to_upper_empty_case);
  tcase_add_test(tc_core, test_s21_to_upper_int_case);

  suite_add_tcase(s, tc_core);

  return s;
}

void test_strcspn_helper(const char *s1, const char *s2,
                         const char *test_name) {
  s21_size_t s21_res = s21_strcspn(s1, s2);
  s21_size_t std_res = strcspn(s1, s2);

  printf("=== Тестирование функции path 1.9: s21_strcspn ===\n");
  printf("Тест: %s\n", test_name);
  printf("Входные данные: s1='%s', s2='%s'\n", s1, s2);
  printf("Результат s21_strcspn: %lu\n", s21_res);
  printf("Результат strcspn:     %lu\n", std_res);
  printf("--------------------------\n");

  ck_assert_int_eq(s21_res, std_res);
}

START_TEST(test_s21_strcspn_basic) {
  test_strcspn_helper("Hello, World!", "W",
                      "Базовый тест: один символ есть в середине строки");
}
END_TEST

START_TEST(test_s21_strcspn_no_common) {
  test_strcspn_helper("ABCDEF", "xyz", "Нет общих символов");
}
END_TEST

START_TEST(test_s21_strcspn_empty_s2) {
  test_strcspn_helper("Hello", "", "Пустая строка во втором аргументе");
}
END_TEST

START_TEST(test_s21_strcspn_empty_s1) {
  test_strcspn_helper("", "ABC", "Пустая строка в первом аргументе");
}
END_TEST

START_TEST(test_s21_strcspn_first_char_match) {
  test_strcspn_helper("12345", "1", "Первый символ сразу совпадает");
}
END_TEST

START_TEST(test_s21_strcspn_all_match) {
  test_strcspn_helper("ABC", "ABC", "Все символы совпадают");
}
END_TEST

START_TEST(test_s21_strcspn_middle_match) {
  test_strcspn_helper("abcdXYZ", "ZYX", "Совпадение где-то в середине");
}
END_TEST

Suite *s21_strcspn_suite(void) {
  Suite *s = suite_create("s21_strcspn");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_strcspn_basic);
  tcase_add_test(tc_core, test_s21_strcspn_no_common);
  tcase_add_test(tc_core, test_s21_strcspn_empty_s2);
  tcase_add_test(tc_core, test_s21_strcspn_empty_s1);
  tcase_add_test(tc_core, test_s21_strcspn_first_char_match);
  tcase_add_test(tc_core, test_s21_strcspn_all_match);
  tcase_add_test(tc_core, test_s21_strcspn_middle_match);

  suite_add_tcase(s, tc_core);

  return s;
}

void test_memset_helper(const char *init_str, int c, size_t n,
                        const char *test_name) {
  char s21_buf[100] = {0};
  char std_buf[100] = {0};

  strncpy(s21_buf, init_str, sizeof(s21_buf) - 1);
  strncpy(std_buf, init_str, sizeof(std_buf) - 1);

  s21_memset(s21_buf, c, n);
  memset(std_buf, c, n);

  printf("=== Тестирование функции path 1.4: s21_memset ===\n");
  printf("Тест: %s\n", test_name);
  printf("Изначальная строка: '%s'\n", init_str);
  printf("Символ для заполнения: '%c' (код %d)\n", (char)c, c);
  printf("Число байт (n): %zu\n", n);
  printf("Результат s21_memset: '%.*s'\n", (int)sizeof(s21_buf), s21_buf);
  printf("Результат memset:     '%.*s'\n", (int)sizeof(std_buf), std_buf);
  printf("--------------------------\n");

  ck_assert_mem_eq(s21_buf, std_buf, sizeof(s21_buf));
}

START_TEST(test_s21_memset_basic) {
  test_memset_helper("Hello, World!", 'A', 5, "Базовый тест");
}
END_TEST

START_TEST(test_s21_memset_zero_len) {
  test_memset_helper("Hello, World!", 'A', 0, "n=0");
}
END_TEST

START_TEST(test_s21_memset_with_zero_char) {
  test_memset_helper("Hello, World!", '\0', 5, "Заполнение нулевым символом");
}
END_TEST

START_TEST(test_s21_memset_greater_n) {
  test_memset_helper("Hello", 'X', 10, "Длина больше, чем сама строка");
}
END_TEST

START_TEST(test_s21_memset_empty_str) {
  test_memset_helper("", 'Y', 1, "Пустая строка");
}
END_TEST

Suite *s21_memset_suite(void) {
  Suite *s = suite_create("s21_memset");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_memset_basic);
  tcase_add_test(tc_core, test_s21_memset_zero_len);
  tcase_add_test(tc_core, test_s21_memset_with_zero_char);
  tcase_add_test(tc_core, test_s21_memset_greater_n);
  tcase_add_test(tc_core, test_s21_memset_empty_str);

  suite_add_tcase(s, tc_core);
  return s;
}

void test_strstr_helper(const char *haystack, const char *needle,
                        ptrdiff_t expected_offset, const char *test_name) {
  char *res1 = s21_strstr(haystack, needle);
  char *res2 = strstr(haystack, needle);

  printf("=== Тестирование функции 1.14: s21_strstr ===\n");
  printf("Тест: %s\n", test_name);
  printf("Входные данные: haystack=\"%s\", needle=\"%s\"\n", haystack, needle);
  printf("Результат s21_strstr (res1) = %p\n", (void *)res1);
  printf("Результат strstr    (res2) = %p\n", (void *)res2);

  ck_assert_ptr_eq(res1, res2);

  if (expected_offset >= 0) {
    ck_assert_ptr_eq(res1, haystack + expected_offset);
  } else {
    ck_assert_ptr_eq(res1, (char *)S21_NULL);
  }
  printf("--------------------------\n");
}

START_TEST(test_s21_strstr_basic) {
  test_strstr_helper("Hello, World!", "World", 7,
                     "Базовый тест: World найден в позиции 7");
}
END_TEST

START_TEST(test_s21_strstr_empty_needle) {
  test_strstr_helper("Hello, World!", "", 0,
                     "Пустая строка needle: возврат всей строки");
}
END_TEST

START_TEST(test_s21_strstr_not_found) {
  test_strstr_helper("Hello, World!", "XYZ", -1, "Подстрока 'XYZ' не найдена");
}
END_TEST

START_TEST(test_s21_strstr_match_start) {
  test_strstr_helper("Hello, World!", "Hello", 0,
                     "Подстрока 'Hello' в начале haystack");
}
END_TEST

START_TEST(test_s21_strstr_full_match) {
  test_strstr_helper("12345", "12345", 0,
                     "Подстрока совпадает со всей строкой целиком");
}
END_TEST

START_TEST(test_s21_strstr_needle_longer) {
  test_strstr_helper("Hi", "Hello", -1, "Needle длиннее haystack => NULL");
}
END_TEST

START_TEST(test_s21_strstr_first_occurrence) {
  test_strstr_helper("abcdabcabc", "abc", 0,
                     "Первое вхождение 'abc' в начале 'abcdabcabc'");
}
END_TEST

START_TEST(test_s21_strstr_partial_match) {
  test_strstr_helper("ababc", "abc", 2,
                     "Подстрока 'abc' в 'ababc' с позиции 2");
}
END_TEST

Suite *s21_strstr_suite(void) {
  Suite *s = suite_create("s21_strstr");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_strstr_basic);
  tcase_add_test(tc_core, test_s21_strstr_empty_needle);
  tcase_add_test(tc_core, test_s21_strstr_not_found);
  tcase_add_test(tc_core, test_s21_strstr_match_start);
  tcase_add_test(tc_core, test_s21_strstr_full_match);
  tcase_add_test(tc_core, test_s21_strstr_needle_longer);
  tcase_add_test(tc_core, test_s21_strstr_first_occurrence);
  tcase_add_test(tc_core, test_s21_strstr_partial_match);

  suite_add_tcase(s, tc_core);
  return s;
}

void test_s21_memcmp_helper(const char *str1, const char *str2, int n,
                            const char *test_name) {
  int s21_res = s21_memcmp(str1, str2, n);
  int std_res = memcmp(str1, str2, n);

  printf("=== Тестирование функции path 1.2: s21_memcmp ===\n");
  printf("Тест: %s\n", test_name);
  printf("Входные данные: %s, %s\n", str1, str2);
  printf("Результат s21_memcmp: %d\n", s21_res);
  printf("Результат memcmp:     %d\n", std_res);
  printf("------------------------\n");

  if (s21_res >= 0) {
    ck_assert_int_ge(s21_res, std_res);
  } else {
    ck_assert_int_le(s21_res, std_res);
  }
}

START_TEST(test_s21_memcmp_simple) {
  test_s21_memcmp_helper("Hello", "Hello", 5, "простое сравнение");
}
END_TEST

START_TEST(test_s21_memcmp_diff_lesser) {
  test_s21_memcmp_helper("Hello", "Helso", 5,
                         "сравнение c отрицательным значением");
}
END_TEST

START_TEST(test_s21_memcmp_diff_greater) {
  test_s21_memcmp_helper("Hello", "Hallo", 5,
                         "сравнение c положительным значением");
}
END_TEST

START_TEST(test_s21_memcmp_empty) {
  test_s21_memcmp_helper("", "", 0, "сравнение пустых строк");
}
END_TEST

START_TEST(test_s21_memcmp_unicode) {
  test_s21_memcmp_helper("привет", "привет", 6, "сравнение юникод символов");
}
END_TEST

START_TEST(test_s21_memcmp_special) {
  test_s21_memcmp_helper(" 123 ", " 123 ", 5, "сравнение спец символов");
}
END_TEST

START_TEST(test_s21_memcmp_special2) {
  test_s21_memcmp_helper(" .,.!^%&(\\/)^(*)^(\\/)", " .,.!^%&(\\/)^(*)^(\\/)",
                         21, "сравнение спец символов");
}
END_TEST

START_TEST(test_s21_memcmp_special3) {
  test_s21_memcmp_helper("hello\t\n", "hello\t\n", 7,
                         "сравнение спец символов");
}
END_TEST

Suite *s21_memcmp_suite(void) {
  Suite *s = suite_create("s21_memcmp");
  TCase *tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_s21_memcmp_simple);
  tcase_add_test(tc_core, test_s21_memcmp_diff_lesser);
  tcase_add_test(tc_core, test_s21_memcmp_diff_greater);
  tcase_add_test(tc_core, test_s21_memcmp_empty);
  tcase_add_test(tc_core, test_s21_memcmp_unicode);
  tcase_add_test(tc_core, test_s21_memcmp_special);
  tcase_add_test(tc_core, test_s21_memcmp_special2);
  tcase_add_test(tc_core, test_s21_memcmp_special3);

  suite_add_tcase(s, tc_core);

  return s;
}

void test_s21_strncmp_helper(const char *str1, const char *str2, int n,
                             const char *test_name) {
  int s21_res = s21_strncmp(str1, str2, n);
  int std_res = strncmp(str1, str2, n);

  printf("=== Тестирование функции path 1.7: s21_strncmp ===\n");
  printf("Тест: %s\n", test_name);
  printf("Входные данные: %s, %s\n", str1, str2);
  printf("Результат s21_strncmp: %d\n", s21_res);
  printf("Результат strncmp:     %d\n", std_res);
  printf("------------------------\n");

  if (s21_res >= 0) {
    ck_assert_int_ge(s21_res, std_res);
  } else {
    ck_assert_int_le(s21_res, std_res);
  }
}

START_TEST(test_s21_strncmp_simple) {
  test_s21_strncmp_helper("Hello", "Hello", 5, "простое сравнение");
}
END_TEST

START_TEST(test_s21_strncmp_diff_lesser) {
  test_s21_strncmp_helper("Hello", "Helso", 5,
                          "сравнение c отрицательным значением");
}
END_TEST

START_TEST(test_s21_strncmp_diff_greater) {
  test_s21_strncmp_helper("Hello", "Hallo", 5,
                          "сравнение c положительным значением");
}
END_TEST

START_TEST(test_s21_strncmp_empty) {
  test_s21_strncmp_helper("", "", 0, "сравнение пустых строк");
}
END_TEST

START_TEST(test_s21_strncmp_unicode) {
  test_s21_strncmp_helper("привет", "привет", 6, "сравнение юникод символов");
}
END_TEST

START_TEST(test_s21_strncmp_special) {
  test_s21_strncmp_helper(" 123 ", " 123 ", 5, "сравнение спец символов");
}
END_TEST

START_TEST(test_s21_strncmp_special2) {
  test_s21_strncmp_helper(" .,.!^%&(\\/)^(*)^(\\/)", " .,.!^%&(\\/)^(*)^(\\/)",
                          21, "сравнение спец символов");
}
END_TEST

START_TEST(test_s21_strncmp_special3) {
  test_s21_strncmp_helper("hello\t\n", "hello\t\n", 7,
                          "сравнение спец символов");
}
END_TEST

Suite *s21_strncmp_suite() {
  Suite *s = suite_create("s21_strncmp");
  TCase *tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_s21_strncmp_simple);
  tcase_add_test(tc_core, test_s21_strncmp_diff_lesser);
  tcase_add_test(tc_core, test_s21_strncmp_diff_greater);
  tcase_add_test(tc_core, test_s21_strncmp_empty);
  tcase_add_test(tc_core, test_s21_strncmp_unicode);
  tcase_add_test(tc_core, test_s21_strncmp_special);
  tcase_add_test(tc_core, test_s21_strncmp_special2);
  tcase_add_test(tc_core, test_s21_strncmp_special3);

  suite_add_tcase(s, tc_core);

  return s;
}

void test_s21_strpbrk_helper(const char *str1, const char *str2,
                             const char *test_name) {
  char *s21_res = s21_strpbrk(str1, str2);
  char *std_res = strpbrk(str1, str2);

  printf("=== Тестирование функции path 1.12: s21_strpbrk ===\n");
  printf("Тест: %s\n", test_name);
  printf("Входные данные: %s, %s\n", str1, str2);
  printf("Результат s21_strpbrk: %s\n", s21_res);
  printf("Результат strpbrk:     %s\n", std_res);
  printf("------------------------\n");

  ck_assert_ptr_eq(s21_res, std_res);
}

START_TEST(test_s21_strpbrk_simple) {
  test_s21_strpbrk_helper("Hello", "e", "простой поиск");
}
END_TEST

START_TEST(test_s21_strpbrk_empty) {
  test_s21_strpbrk_helper("Hello", "", "поиск пустой строки");
}
END_TEST

START_TEST(test_s21_strpbrk_empty2) {
  test_s21_strpbrk_helper("", "H", "поиск в пустой строке");
}
END_TEST

START_TEST(test_s21_strpbrk_equal) {
  test_s21_strpbrk_helper("Hello", "Hello", "поиск в одинаковых строках");
}
END_TEST

START_TEST(test_s21_strpbrk_no_matched) {
  test_s21_strpbrk_helper("Hello", "asdfG", "поиск без совпадений");
}
END_TEST

START_TEST(test_s21_strpbrk_unicode) {
  test_s21_strpbrk_helper("привет", "в", "поиск с юникод символами");
}

START_TEST(test_s21_strpbrk_number) {
  test_s21_strpbrk_helper("Hel7lo", "7", "поиск цифры");
}
END_TEST

START_TEST(test_s21_strpbrk_special) {
  test_s21_strpbrk_helper("Hel\tlo", "\t", "поиск спец символа");
}
END_TEST

START_TEST(test_s21_strpbrk_space) {
  test_s21_strpbrk_helper("Hell o", " ", "поиск пробела");
}
END_TEST

Suite *s21_strpbrk_suite() {
  Suite *s = suite_create("s21_strpbrk");
  TCase *tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_s21_strpbrk_simple);
  tcase_add_test(tc_core, test_s21_strpbrk_empty);
  tcase_add_test(tc_core, test_s21_strpbrk_empty2);
  tcase_add_test(tc_core, test_s21_strpbrk_equal);
  tcase_add_test(tc_core, test_s21_strpbrk_no_matched);
  tcase_add_test(tc_core, test_s21_strpbrk_unicode);
  tcase_add_test(tc_core, test_s21_strpbrk_number);
  tcase_add_test(tc_core, test_s21_strpbrk_special);
  tcase_add_test(tc_core, test_s21_strpbrk_space);

  suite_add_tcase(s, tc_core);

  return s;
}

void test_s21_to_lower_helper(const char *str1, const char *str2,
                              const char *test_name) {
  char *s21_res = s21_to_lower(str1);

  printf("=== Тестирование функции path 2.2: s21_to_lower ===\n");
  printf("Тест: %s\n", test_name);
  printf("Изначальная строка: %s\n", str1);
  printf("Результат s21_to_lower: %s\n", s21_res);
  printf("Необходимый результат:  %s\n", str2);
  printf("--------------------------\n");

  if (str2) {
    ck_assert_str_eq(s21_res, str2);
  } else {
    ck_assert_ptr_eq(s21_res, str2);
  }

  free(s21_res);
}

START_TEST(test_s21_to_lower_simple) {
  test_s21_to_lower_helper("HELLO", "hello", "тест со всеми заглавными");
}
END_TEST

START_TEST(test_s21_to_lower_empty) {
  test_s21_to_lower_helper("", "", "тест с пустой строкой");
}
END_TEST

Suite *s21_to_lower_suite() {
  Suite *s = suite_create("s21_to_lower");
  TCase *tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_s21_to_lower_simple);
  tcase_add_test(tc_core, test_s21_to_lower_empty);

  suite_add_tcase(s, tc_core);

  return s;
}

void test_s21_trim_helper(const char *str1, const char *trim_char,
                          const char *str2, const char *test_name) {
  char *s21_res = s21_trim(str1, trim_char);

  printf("=== Тестирование функции path 2.4: s21_trim ===\n");
  printf("Тест: %s\n", test_name);
  printf("Изначальная строка: %s\n", str1);
  printf("Символы для удаления: %s\n", trim_char);
  printf("Результат s21_trim: %s\n", s21_res);
  printf("Необходимый результат:  %s\n", str2);
  printf("--------------------------\n");

  if (str2) {
    ck_assert_str_eq(s21_res, str2);
  } else {
    ck_assert_ptr_eq(s21_res, str2);
  }

  free(s21_res);
}

START_TEST(test_s21_trim_simple) {
  test_s21_trim_helper("*** HELLO ***", "*", " HELLO ",
                       "удаление одного символа");
}
END_TEST

START_TEST(test_s21_trim_diff_symbols) {
  test_s21_trim_helper("*-+ HELLO $%%^", "*-+$%%^", " HELLO ",
                       "удаление разных символов");
}
END_TEST

START_TEST(test_s21_trim_empty) {
  test_s21_trim_helper("", "*-+$%%^", "", "удаление в пустой строке");
}
END_TEST

START_TEST(test_s21_trim_symbols_in_string) {
  test_s21_trim_helper("**-Hell*-$^o%%$^", "*-+$%%^", "Hell*-$^o",
                       "удаление символов встречающихся в середине строки");
}
END_TEST

Suite *s21_trim_suite() {
  Suite *s = suite_create("s21_trim");
  TCase *tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_s21_trim_simple);
  tcase_add_test(tc_core, test_s21_trim_diff_symbols);
  tcase_add_test(tc_core, test_s21_trim_empty);
  tcase_add_test(tc_core, test_s21_trim_symbols_in_string);

  suite_add_tcase(s, tc_core);

  return s;
}

int string_tests() {
  int number_failed = 0;

  Suite *memchr_s = s21_memchr_suite();
  Suite *memcmp_s = s21_memcmp_suite();
  Suite *memcpy_s = s21_memcpy_suite();
  Suite *memset_s = s21_memset_suite();
  Suite *strncat_s = s21_strncat_suite();
  Suite *strchr_s = s21_strchr_suite();
  Suite *strncmp_s = s21_strncmp_suite();
  Suite *strncpy_s = s21_strncpy_suite();
  Suite *strcspn_s = s21_strcspn_suite();
  Suite *strerror_s = s21_strerror_suite();
  Suite *strlen_s = s21_strlen_suite();
  Suite *strpbrk_s = s21_strpbrk_suite();
  Suite *strrchr_s = s21_strrchr_suite();
  Suite *strstr_s = s21_strstr_suite();
  Suite *strtok_s = s21_strtok_suite();
  Suite *to_upper_s = s21_to_upper_suite();
  Suite *to_lower_s = s21_to_lower_suite();
  Suite *insert_s = s21_insert_suite();
  Suite *trim_s = s21_trim_suite();

  SRunner *sr = srunner_create(memchr_s);
  srunner_add_suite(sr, memcmp_s);
  srunner_add_suite(sr, memcpy_s);
  srunner_add_suite(sr, memset_s);
  srunner_add_suite(sr, strncat_s);
  srunner_add_suite(sr, strchr_s);
  srunner_add_suite(sr, strncmp_s);
  srunner_add_suite(sr, strncpy_s);
  srunner_add_suite(sr, strcspn_s);
  srunner_add_suite(sr, strerror_s);
  srunner_add_suite(sr, strlen_s);
  srunner_add_suite(sr, strpbrk_s);
  srunner_add_suite(sr, strrchr_s);
  srunner_add_suite(sr, strstr_s);
  srunner_add_suite(sr, strtok_s);

  srunner_add_suite(sr, to_upper_s);
  srunner_add_suite(sr, to_lower_s);
  srunner_add_suite(sr, insert_s);
  srunner_add_suite(sr, trim_s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}

void test_s21_sprintf_c_helper(const char *format, char ch,
                               const char *test_name) {
  char s21_res[20];
  char std_res[20];

  s21_sprintf(s21_res, format, ch);
  sprintf(std_res, format, ch);

  printf("=== Тестирование функции: s21_sprintf со спецификатором 1 - с ===\n");
  printf("Тест: %s\n", test_name);
  printf("Результат s21_sprintf: %s\n", s21_res);
  printf("Результат sprintf:     %s\n", std_res);
  printf("--------------------------\n");

  ck_assert_str_eq(s21_res, std_res);
}

START_TEST(test_s21_sprintf_c_simple) {
  test_s21_sprintf_c_helper(
      "Hello%c World!", ',',
      "простой тест спецификатора с на обработку одного символа");
}
END_TEST

START_TEST(test_s21_sprintf_c_width) {
  test_s21_sprintf_c_helper(
      "Hello%2c World!", ',',
      "тест спецификатора с на обработку одного символа с шириной");
}
END_TEST

START_TEST(test_s21_sprintf_c_align_width) {
  test_s21_sprintf_c_helper("Hello%-2c World!", ',',
                            "тест спецификатора с на обработку одного символа "
                            "с шириной и выравниваем");
}
END_TEST

Suite *s21_sprintf_c_suite(void) {
  Suite *s = suite_create("s21_sprintf_c");
  TCase *tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_s21_sprintf_c_simple);
  tcase_add_test(tc_core, test_s21_sprintf_c_width);
  tcase_add_test(tc_core, test_s21_sprintf_c_align_width);

  suite_add_tcase(s, tc_core);

  return s;
}

void simple_test_d_specifier_helper(const char *format, int num,
                                    const char *message, char specifier) {
  char s21_res[256] = {0};
  char std_res[256] = {0};

  s21_sprintf(s21_res, format, num);
  sprintf(std_res, format, num);

  printf("=== Тестирование спецификатора: %c ===\n", specifier);
  printf("Тест: %s\n", message);
  printf("Входные данные: num = %d, format = '%s'\n", num, format);
  printf("Результат s21_sprintf: '%s'\n", s21_res);
  printf("Результат sprintf:     '%s'\n", std_res);

  ck_assert_str_eq(s21_res, std_res);

  printf("--------------------------\n");
}

START_TEST(test_s21_sprintf_d_simple_positive) {
  simple_test_d_specifier_helper("%d", 12345, "Простое положительное число",
                                 'd');
}
END_TEST

START_TEST(test_s21_sprintf_d_simple_negative) {
  simple_test_d_specifier_helper("%d", -12345, "Простое отрицательное число",
                                 'd');
}
END_TEST

START_TEST(test_s21_sprintf_d_left_justification) {
  simple_test_d_specifier_helper("%-10d", 123, "Выравнивание по левому краю",
                                 'd');
}
END_TEST

START_TEST(test_s21_sprintf_d_leading_zeros) {
  simple_test_d_specifier_helper("%010d", 123, "Заполнение нулями", 'd');
}
END_TEST

START_TEST(test_s21_sprintf_d_precision) {
  simple_test_d_specifier_helper(
      "%.5d", 123, "Вывод с точностью 5 (дополняется нулями слева)", 'd');
}
END_TEST

START_TEST(test_s21_sprintf_d_sign_positive) {
  simple_test_d_specifier_helper(
      "%+d", 123, "Явное указание знака для положительного числа", 'd');
}
END_TEST

START_TEST(test_s21_sprintf_d_conflicting_flags) {
  simple_test_d_specifier_helper(
      "%+ 10d", 123, "Конфликтующие флаги: '+' и ' ' (пробел)", 'd');
}
END_TEST

START_TEST(test_s21_sprintf_d_zero) {
  simple_test_d_specifier_helper("%d", 0, "Вывод нуля", 'd');
}
END_TEST

START_TEST(test_s21_sprintf_d_combination) {
  simple_test_d_specifier_helper("%+010.5d", -123,
                                 "Комбинация флагов: '+', '0', точность", 'd');
}
END_TEST

Suite *s21_sprintf_d_suite(void) {
  Suite *s = suite_create("s21_sprintf_d_suite");
  TCase *tc = tcase_create("tc_s21_sprintf_d");

  tcase_add_test(tc, test_s21_sprintf_d_simple_positive);
  tcase_add_test(tc, test_s21_sprintf_d_simple_negative);
  tcase_add_test(tc, test_s21_sprintf_d_left_justification);
  tcase_add_test(tc, test_s21_sprintf_d_leading_zeros);
  tcase_add_test(tc, test_s21_sprintf_d_precision);
  tcase_add_test(tc, test_s21_sprintf_d_sign_positive);
  tcase_add_test(tc, test_s21_sprintf_d_conflicting_flags);
  tcase_add_test(tc, test_s21_sprintf_d_zero);
  tcase_add_test(tc, test_s21_sprintf_d_combination);

  suite_add_tcase(s, tc);
  return s;
}

void simple_test_i_specifier_helper(const char *format, int num,
                                    const char *message, char specifier) {
  char s21_res[256] = {0};
  char std_res[256] = {0};
  s21_sprintf(s21_res, format, num);
  sprintf(std_res, format, num);
  printf("=== Тестирование спецификатора: %c ===\n", specifier);
  printf("Тест: %s\n", message);
  printf("Входные данные: num = %d, format = '%s'\n", num, format);
  printf("Результат s21_sprintf: '%s'\n", s21_res);
  printf("Результат sprintf:     '%s'\n", std_res);
  ck_assert_str_eq(s21_res, std_res);
  printf("--------------------------\n");
}

START_TEST(test_s21_sprintf_i_simple_positive) {
  simple_test_i_specifier_helper("%i", 12345, "Простое положительное число",
                                 'i');
}
END_TEST

START_TEST(test_s21_sprintf_i_simple_negative) {
  simple_test_i_specifier_helper("%i", -12345, "Простое отрицательное число",
                                 'i');
}
END_TEST

START_TEST(test_s21_sprintf_i_left_justification) {
  simple_test_i_specifier_helper("%-10i", 123, "Выравнивание по левому краю",
                                 'i');
}
END_TEST

START_TEST(test_s21_sprintf_i_leading_zeros) {
  simple_test_i_specifier_helper("%010i", 123, "Заполнение нулями", 'i');
}
END_TEST

START_TEST(test_s21_sprintf_i_precision) {
  simple_test_i_specifier_helper(
      "%.5i", 123, "Вывод с точностью 5 (дополняется нулями слева)", 'i');
}
END_TEST

START_TEST(test_s21_sprintf_i_sign_positive) {
  simple_test_i_specifier_helper(
      "%+i", 123, "Явное указание знака для положительного числа", 'i');
}
END_TEST

START_TEST(test_s21_sprintf_i_conflicting_flags) {
  simple_test_i_specifier_helper(
      "%+ 10i", 123, "Конфликтующие флаги: '+' и ' ' (пробел)", 'i');
}
END_TEST

START_TEST(test_s21_sprintf_i_zero) {
  simple_test_i_specifier_helper("%i", 0, "Вывод нуля", 'i');
}
END_TEST

START_TEST(test_s21_sprintf_i_combination) {
  simple_test_i_specifier_helper("%+010.5i", -123,
                                 "Комбинация флагов: '+', '0', точность", 'i');
}
END_TEST

Suite *s21_sprintf_i_suite(void) {
  Suite *s = suite_create("s21_sprintf_i_suite");
  TCase *tc = tcase_create("tc_s21_sprintf_i");
  tcase_add_test(tc, test_s21_sprintf_i_simple_positive);
  tcase_add_test(tc, test_s21_sprintf_i_simple_negative);
  tcase_add_test(tc, test_s21_sprintf_i_left_justification);
  tcase_add_test(tc, test_s21_sprintf_i_leading_zeros);
  tcase_add_test(tc, test_s21_sprintf_i_precision);
  tcase_add_test(tc, test_s21_sprintf_i_sign_positive);
  tcase_add_test(tc, test_s21_sprintf_i_conflicting_flags);
  tcase_add_test(tc, test_s21_sprintf_i_zero);
  tcase_add_test(tc, test_s21_sprintf_i_combination);
  suite_add_tcase(s, tc);
  return s;
}

void simple_test_feg_specifier_helper(const char *format, long double num,
                                      const char *message, char specifier) {
  char s21_res[256];
  char std_res[256];

  s21_sprintf(s21_res, format, num);
  sprintf(std_res, format, num);

  printf("=== Тестирование спецификатора: %c ===\n", specifier);
  printf("Тест: %s\n", message);
  printf("Входные данные: num = %Lf, format = '%s'\n", num, format);
  printf("Результат s21_sprintf: '%s'\n", s21_res);
  printf("Результат sprintf: '%s'\n", std_res);

  ck_assert_str_eq(s21_res, std_res);

  printf("--------------------------\n");
}

START_TEST(test_s21_sprintf_f_long_double) {
  simple_test_feg_specifier_helper("%Lf", 123.456, "Число с плавающей точкой",
                                   'f');
}
END_TEST

START_TEST(test_s21_sprintf_f_left_justification) {
  simple_test_feg_specifier_helper("%-10Lf", 123.456,
                                   "Выравнивание по левому краю", 'f');
}
END_TEST

START_TEST(test_s21_sprintf_f_leding_zeros) {
  simple_test_feg_specifier_helper("%010Lf", 123.456,
                                   "Число с лидирующими нулями", 'f');
}
END_TEST

START_TEST(test_s21_sprintf_f_sign) {
  simple_test_feg_specifier_helper("%+Lf", 123.456,
                                   "Явное указание знака числа", 'f');
}
END_TEST

START_TEST(test_s21_sprintf_f_precision) {
  simple_test_feg_specifier_helper("%.4Lf", 123.456789,
                                   "Вывод числа с точностью 4", 'f');
}
END_TEST

START_TEST(test_s21_sprintf_f_hash) {
  simple_test_feg_specifier_helper("%#.0Lf", -123.0,
                                   "Флаг # при нулевой точности", 'f');
}
END_TEST

START_TEST(test_s21_sprintf_f_conflicting_flags_1) {
  simple_test_feg_specifier_helper("%+ 7.2Lf", 123.456,
                                   "Конфликтующие флаги: '+' и ' '", 'f');
}
END_TEST

START_TEST(test_s21_sprintf_f_conflicting_flags_2) {
  simple_test_feg_specifier_helper("%-07.2Lf", 123.456,
                                   "Конфликтующие флаги: '-' и '0'", 'f');
}
END_TEST

START_TEST(test_s21_sprintf_f_combination_1) {
  simple_test_feg_specifier_helper("%+0#10.3Lf", -123.456789,
                                   "Комбинация флагов: '+', '0' и '#'", 'f');
}
END_TEST

START_TEST(test_s21_sprintf_f_combination_2) {
  simple_test_feg_specifier_helper("%- 6.1Lf", 123.456,
                                   "Комбинация флагов: '-' и ' '", 'f');
}
END_TEST

Suite *s21_sprintf_f_suite(void) {
  Suite *s;
  TCase *tc_f;

  s = suite_create("s21_sprintf_f");

  tc_f = tcase_create("f specifier");
  tcase_add_test(tc_f, test_s21_sprintf_f_long_double);
  tcase_add_test(tc_f, test_s21_sprintf_f_left_justification);
  tcase_add_test(tc_f, test_s21_sprintf_f_leding_zeros);
  tcase_add_test(tc_f, test_s21_sprintf_f_sign);
  tcase_add_test(tc_f, test_s21_sprintf_f_precision);
  tcase_add_test(tc_f, test_s21_sprintf_f_hash);
  tcase_add_test(tc_f, test_s21_sprintf_f_conflicting_flags_1);
  tcase_add_test(tc_f, test_s21_sprintf_f_conflicting_flags_2);
  tcase_add_test(tc_f, test_s21_sprintf_f_combination_1);
  tcase_add_test(tc_f, test_s21_sprintf_f_combination_2);

  suite_add_tcase(s, tc_f);

  return s;
}

START_TEST(test_s21_sprintf_e_simple_1) {
  simple_test_feg_specifier_helper(
      "%Le", 0.000000001, "Число в научной нотации, нижний регистр", 'e');
}
END_TEST

START_TEST(test_s21_sprintf_e_simple_2) {
  simple_test_feg_specifier_helper(
      "%Le", -0.00123456, "Число в научной нотации, нижний регистр", 'e');
}
END_TEST

START_TEST(test_s21_sprintf_e_left_justification) {
  simple_test_feg_specifier_helper("%-10Le", 12.3,
                                   "Выравнивание по левому краю", 'e');
}
END_TEST

START_TEST(test_s21_sprintf_e_leading_zeros) {
  simple_test_feg_specifier_helper("%010Le", 12.3, "Число с лидирующими нулями",
                                   'e');
}
END_TEST

START_TEST(test_s21_sprintf_e_sign) {
  simple_test_feg_specifier_helper("%+Le", 12.3, "Явное указание знака числа",
                                   'e');
}
END_TEST

START_TEST(test_s21_sprintf_e_precision) {
  simple_test_feg_specifier_helper("%.5Le", 12.3, "Вывод числа с точностью 5",
                                   'e');
}
END_TEST

START_TEST(test_s21_sprintf_e_hash) {
  simple_test_feg_specifier_helper("%#.0Le", -123.0,
                                   "Флаг # при нулевой точности", 'e');
}
END_TEST

START_TEST(test_s21_sprintf_e_conflicting_flags_1) {
  simple_test_feg_specifier_helper("%+ 7.2Le", 123.456,
                                   "Конфликтующие флаги: '+' и ' '", 'e');
}
END_TEST

START_TEST(test_s21_sprintf_e_conflicting_flags_2) {
  simple_test_feg_specifier_helper("%-07.2Le", 123.456,
                                   "Конфликтующие флаги: '-' и '0'", 'e');
}
END_TEST

START_TEST(test_s21_sprintf_e_combination_1) {
  simple_test_feg_specifier_helper("%0#+12.3Le", -123.456789,
                                   "Комбинация флагов: '+', '0' и '#'", 'e');
}
END_TEST

START_TEST(test_s21_sprintf_e_combination_2) {
  simple_test_feg_specifier_helper("%- 6.1Le", 123.456,
                                   "Комбинация флагов: '-' и ' '", 'e');
}
END_TEST

START_TEST(test_s21_sprintf_e_upper_case_1) {
  simple_test_feg_specifier_helper(
      "%LE", 123.456, "Число в научной нотации, верхний регистр", 'E');
}
END_TEST

START_TEST(test_s21_sprintf_e_upper_case_2) {
  simple_test_feg_specifier_helper(
      "%LE", -0.00123456, "Число в научной нотации, верхний регистр", 'E');
}
END_TEST

START_TEST(test_s21_sprintf_e_upper_case_combination) {
  simple_test_feg_specifier_helper("%+0#5.2LE", 0.00123456,
                                   "Комбинация флагов, верхний регистр", 'E');
}
END_TEST

Suite *s21_sprintf_e_suite(void) {
  Suite *s;
  TCase *tc_e;

  s = suite_create("s21_sprintf_e");

  tc_e = tcase_create("e specifier");
  tcase_add_test(tc_e, test_s21_sprintf_e_simple_1);
  tcase_add_test(tc_e, test_s21_sprintf_e_simple_2);
  tcase_add_test(tc_e, test_s21_sprintf_e_left_justification);
  tcase_add_test(tc_e, test_s21_sprintf_e_leading_zeros);
  tcase_add_test(tc_e, test_s21_sprintf_e_sign);
  tcase_add_test(tc_e, test_s21_sprintf_e_precision);
  tcase_add_test(tc_e, test_s21_sprintf_e_hash);
  tcase_add_test(tc_e, test_s21_sprintf_e_conflicting_flags_1);
  tcase_add_test(tc_e, test_s21_sprintf_e_conflicting_flags_2);
  tcase_add_test(tc_e, test_s21_sprintf_e_combination_1);
  tcase_add_test(tc_e, test_s21_sprintf_e_combination_2);
  tcase_add_test(tc_e, test_s21_sprintf_e_upper_case_1);
  tcase_add_test(tc_e, test_s21_sprintf_e_upper_case_2);
  tcase_add_test(tc_e, test_s21_sprintf_e_upper_case_combination);

  suite_add_tcase(s, tc_e);

  return s;
}

START_TEST(test_s21_sprintf_g_simple_1) {
  simple_test_feg_specifier_helper(
      "%Lg", 0.000000001, "Число в научной нотации, нижний регистр", 'g');
}
END_TEST

START_TEST(test_s21_sprintf_g_simple_2) {
  simple_test_feg_specifier_helper(
      "%Lg", -0.00123456, "Число в научной нотации, нижний регистр", 'g');
}
END_TEST

START_TEST(test_s21_sprintf_g_left_justification) {
  simple_test_feg_specifier_helper("%-10Lg", 12.3,
                                   "Выравнивание по левому краю", 'g');
}
END_TEST

START_TEST(test_s21_sprintf_g_leading_zeros) {
  simple_test_feg_specifier_helper("%010Lg", 12.3, "Число с лидирующими нулями",
                                   'g');
}
END_TEST

START_TEST(test_s21_sprintf_g_sign) {
  simple_test_feg_specifier_helper("%+Lg", 12.3, "Явное указание знака числа",
                                   'g');
}
END_TEST

START_TEST(test_s21_sprintf_g_precision) {
  simple_test_feg_specifier_helper("%.5Lg", 12.3, "Вывод числа с точностью 5",
                                   'g');
}
END_TEST

START_TEST(test_s21_sprintf_g_hash) {
  simple_test_feg_specifier_helper("%#.0Lg", -123.0,
                                   "Флаг # при нулевой точности", 'g');
}
END_TEST

START_TEST(test_s21_sprintf_g_conflicting_flags_1) {
  simple_test_feg_specifier_helper("%+ 7.2Lg", 123.456,
                                   "Конфликтующие флаги: '+' и ' '", 'g');
}
END_TEST

START_TEST(test_s21_sprintf_g_conflicting_flags_2) {
  simple_test_feg_specifier_helper("%-07.2Lg", 123.456,
                                   "Конфликтующие флаги: '-' и '0'", 'g');
}
END_TEST

START_TEST(test_s21_sprintf_g_combination_1) {
  simple_test_feg_specifier_helper("%+0#10.3Lg", -123.456789,
                                   "Комбинация флагов: '+', '0' и '#'", 'g');
}
END_TEST

START_TEST(test_s21_sprintf_g_combination_2) {
  simple_test_feg_specifier_helper("%- 6.1Lg", 123.456,
                                   "Комбинация флагов: '-' и ' '", 'g');
}
END_TEST

START_TEST(test_s21_sprintf_g_upper_case_1) {
  simple_test_feg_specifier_helper(
      "%LG", 123.456, "Число в научной нотации, верхний регистр", 'G');
}
END_TEST

START_TEST(test_s21_sprintf_g_upper_case_2) {
  simple_test_feg_specifier_helper(
      "%LG", -0.00123456, "Число в научной нотации, верхний регистр", 'G');
}
END_TEST

START_TEST(test_s21_sprintf_g_upper_case_combination) {
  simple_test_feg_specifier_helper("%+0#5.2LG", 0.00123456,
                                   "Комбинация флагов, верхний регистр", 'G');
}
END_TEST

Suite *s21_sprintf_g_suite(void) {
  Suite *s;
  TCase *tc_g;

  s = suite_create("s21_sprintf_g");

  tc_g = tcase_create("g specifier");
  tcase_add_test(tc_g, test_s21_sprintf_g_simple_1);
  tcase_add_test(tc_g, test_s21_sprintf_g_simple_2);
  tcase_add_test(tc_g, test_s21_sprintf_g_left_justification);
  tcase_add_test(tc_g, test_s21_sprintf_g_leading_zeros);
  tcase_add_test(tc_g, test_s21_sprintf_g_sign);
  tcase_add_test(tc_g, test_s21_sprintf_g_precision);
  tcase_add_test(tc_g, test_s21_sprintf_g_hash);
  tcase_add_test(tc_g, test_s21_sprintf_g_conflicting_flags_1);
  tcase_add_test(tc_g, test_s21_sprintf_g_conflicting_flags_2);
  tcase_add_test(tc_g, test_s21_sprintf_g_combination_1);
  tcase_add_test(tc_g, test_s21_sprintf_g_combination_2);
  tcase_add_test(tc_g, test_s21_sprintf_g_upper_case_1);
  tcase_add_test(tc_g, test_s21_sprintf_g_upper_case_2);
  tcase_add_test(tc_g, test_s21_sprintf_g_upper_case_combination);

  suite_add_tcase(s, tc_g);

  return s;
}

void extended_test_feg_specifier_helper(const char *format, long double num1,
                                        long double num2, long double num3,
                                        int width, int precision,
                                        const char *message,
                                        const char *specifiers) {
  char s21_res[256];
  char std_res[256];

  s21_sprintf(s21_res, format, width, precision, num1, num2, num3);
  sprintf(std_res, format, width, precision, num1, num2, num3);

  printf("=== Тестирование спецификаторов: %s ===\n", specifiers);
  printf("Тест: %s\n", message);
  printf("Входные данные: num1 = %Lf, num2 = %Lf, num3 = %Lf, format = '%s'\n",
         num1, num2, num3, format);
  printf("Результат s21_sprintf: '%s'\n", s21_res);
  printf("Результат sprintf: '%s'\n", std_res);

  ck_assert_str_eq(s21_res, std_res);

  printf("--------------------------\n");
}

START_TEST(test_s21_sprintf_feg_simple) {
  extended_test_feg_specifier_helper(
      "%*.*Lf, %Le, %Lg", 123.456, -12.3456, 0.000000002, 5, 2,
      "Комбинация спецификаторов, нижний регистр", "f, e, g");
}
END_TEST

START_TEST(test_s21_sprintf_feg_simple_upper_case) {
  extended_test_feg_specifier_helper(
      "%*.*Lf, %LE, %LG", 123.456, -12.3456, 0.0000000012, 6, 4,
      "Комбинация спецификаторов, верхний регистр", "f, E, G");
}
END_TEST

START_TEST(test_s21_sprintf_feg_simple_combination_1) {
  extended_test_feg_specifier_helper(
      "%+0*.*Lf, %+-.2Le, %0#7.5LG", 123.456, -12.003456, 120.2, 10, 3,
      "Комбинация спецификаторов и флагов", "f, e, G");
}
END_TEST

Suite *s21_sprintf_feg_suite(void) {
  Suite *s;
  TCase *tc_feg;

  s = suite_create("s21_sprintf_feg");

  tc_feg = tcase_create("feg specifier");
  tcase_add_test(tc_feg, test_s21_sprintf_feg_simple);
  tcase_add_test(tc_feg, test_s21_sprintf_feg_simple_upper_case);
  tcase_add_test(tc_feg, test_s21_sprintf_feg_simple_combination_1);

  suite_add_tcase(s, tc_feg);

  return s;
}

void test_s21_sprintf_s_helper(const char *format, const char *str,
                               const char *test_name) {
  char s21_res[200];
  char std_res[200];

  s21_sprintf(s21_res, format, str);
  sprintf(std_res, format, str);

  printf("=== Тестирование функции: s21_sprintf ===\n");
  printf("Тест: %s\n", test_name);
  printf("Результат s21_sprintf: %s\n", s21_res);
  printf("Результат sprintf:     %s\n", std_res);
  printf("--------------------------\n");

  ck_assert_str_eq(s21_res, std_res);
}

START_TEST(test_s21_sprintf_s_simple) {
  test_s21_sprintf_s_helper("Hello, %s", "World!",
                            "простой тест спецификатора s");
}
END_TEST

START_TEST(test_s21_sprintf_s_width) {
  test_s21_sprintf_s_helper("Hello, %10s", "World!",
                            "тест спецификатора s с шириной 10");
}
END_TEST

START_TEST(test_s21_sprintf_s_precison) {
  test_s21_sprintf_s_helper("Hello, %.2s", "World!",
                            "тест спецификатора s с точностью 2");
}
END_TEST

START_TEST(test_s21_sprintf_s_precison_0) {
  test_s21_sprintf_s_helper("Hello, %.0s", "World!",
                            "тест спецификатора s с точностью 0");
}
END_TEST

START_TEST(test_s21_sprintf_s_align_width) {
  test_s21_sprintf_s_helper("Hello, %-10s", "World!",
                            "тест спецификатора s с шириной 10 и выравниваем");
}
END_TEST

START_TEST(test_s21_sprintf_s_width_precision) {
  test_s21_sprintf_s_helper("Hello, %10.3s", "World!",
                            "тест спецификатора s с шириной 10 и точностью 3");
}
END_TEST

START_TEST(test_s21_sprintf_s_align_width_precision) {
  test_s21_sprintf_s_helper(
      "Hello, %-10.3s", "World!",
      "тест спецификатора s с шириной 10 и точностью 3 и выравниваем");
}
END_TEST

Suite *s21_sprintf_s_suite(void) {
  Suite *s = suite_create("s21_sprintf_s");
  TCase *tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_s21_sprintf_s_simple);
  tcase_add_test(tc_core, test_s21_sprintf_s_width);
  tcase_add_test(tc_core, test_s21_sprintf_s_precison);
  tcase_add_test(tc_core, test_s21_sprintf_s_precison_0);
  tcase_add_test(tc_core, test_s21_sprintf_s_align_width);
  tcase_add_test(tc_core, test_s21_sprintf_s_width_precision);
  tcase_add_test(tc_core, test_s21_sprintf_s_align_width_precision);

  suite_add_tcase(s, tc_core);

  return s;
}

void test_specifier_helper(unsigned int num, const char *format,
                           const char *message, char specifier) {
  char str_s21[100];
  char str_original[100];

  s21_sprintf(str_s21, format, num);
  sprintf(str_original, format, num);

  printf("=== Тестирование спецификатора: %c ===\n", specifier);
  printf("Тест: %s\n", message);
  printf("Входные данные: num = %u, format = '%s'\n", num, format);
  printf("Результат s21_sprintf: '%s'\n", str_s21);
  printf("Результат sprintf: '%s'\n", str_original);

  ck_assert_str_eq(str_s21, str_original);

  printf("--------------------------\n");
}

START_TEST(test_s21_sprintf_u_simple) {
  test_specifier_helper(12345, "%u", "Простое беззнаковое десятичное число",
                        'u');
}
END_TEST

START_TEST(test_s21_sprintf_u_zero) {
  test_specifier_helper(0, "%u", "Нулевое значение", 'u');
}
END_TEST

START_TEST(test_s21_sprintf_u_width) {
  test_specifier_helper(123, "%10u", "Ширина 10 символов", 'u');
}
END_TEST

START_TEST(test_s21_sprintf_u_left_justify) {
  test_specifier_helper(123, "%-10u", "Выравнивание по левому краю, ширина 10",
                        'u');
}
END_TEST

START_TEST(test_s21_sprintf_u_leading_zeros) {
  test_specifier_helper(123, "%010u", "Дополнение нулями, ширина 10", 'u');
}
END_TEST

START_TEST(test_s21_sprintf_u_precision) {
  test_specifier_helper(123, "%.5u", "Точность 5 символов", 'u');
}
END_TEST

START_TEST(test_s21_sprintf_u_precision_zero) {
  test_specifier_helper(0, "%.5u", "Точность 5 символов, нулевое значение",
                        'u');
}
END_TEST

START_TEST(test_s21_sprintf_u_width_precision) {
  test_specifier_helper(123, "%10.5u", "Ширина 10, точность 5", 'u');
}
END_TEST

Suite *s21_sprintf_u_suite(void) {
  Suite *s;
  TCase *tc_u;

  s = suite_create("s21_sprintf_u");

  tc_u = tcase_create("u specifier");
  tcase_add_test(tc_u, test_s21_sprintf_u_simple);
  tcase_add_test(tc_u, test_s21_sprintf_u_zero);
  tcase_add_test(tc_u, test_s21_sprintf_u_width);
  tcase_add_test(tc_u, test_s21_sprintf_u_left_justify);
  tcase_add_test(tc_u, test_s21_sprintf_u_leading_zeros);
  tcase_add_test(tc_u, test_s21_sprintf_u_precision);
  tcase_add_test(tc_u, test_s21_sprintf_u_precision_zero);
  tcase_add_test(tc_u, test_s21_sprintf_u_width_precision);
  suite_add_tcase(s, tc_u);

  return s;
}

START_TEST(test_s21_sprintf_o_simple) {
  test_specifier_helper(12345, "%o", "Простое беззнаковое восьмеричное число",
                        'o');
}
END_TEST

START_TEST(test_s21_sprintf_o_zero) {
  test_specifier_helper(0, "%o", "Нулевое значение", 'o');
}
END_TEST

START_TEST(test_s21_sprintf_o_width) {
  test_specifier_helper(123, "%10o", "Ширина 10 символов", 'o');
}
END_TEST

START_TEST(test_s21_sprintf_o_left_justify) {
  test_specifier_helper(123, "%-10o", "Выравнивание по левому краю, ширина 10",
                        'o');
}
END_TEST

START_TEST(test_s21_sprintf_o_leading_zeros) {
  test_specifier_helper(123, "%010o", "Дополнение нулями, ширина 10", 'o');
}
END_TEST

START_TEST(test_s21_sprintf_o_precision) {
  test_specifier_helper(123, "%.5o", "Точность 5 символов", 'o');
}
END_TEST

START_TEST(test_s21_sprintf_o_precision_zero) {
  test_specifier_helper(0, "%.5o", "Точность 5 символов, нулевое значение",
                        'o');
}
END_TEST

START_TEST(test_s21_sprintf_o_width_precision) {
  test_specifier_helper(123, "%10.5o", "Ширина 10, точность 5", 'o');
}
END_TEST

START_TEST(test_s21_sprintf_o_hash_flag) {
  test_specifier_helper(123, "%#o", "Флаг решетки (добавляет 0)", 'o');
}
END_TEST

START_TEST(test_s21_sprintf_o_hash_width) {
  test_specifier_helper(123, "%#10o", "Флаг решетки и ширина 10", 'o');
}
END_TEST

Suite *s21_sprintf_o_suite(void) {
  Suite *s;
  TCase *tc_o;

  s = suite_create("s21_sprintf_o");

  tc_o = tcase_create("o specifier");
  tcase_add_test(tc_o, test_s21_sprintf_o_simple);
  tcase_add_test(tc_o, test_s21_sprintf_o_zero);
  tcase_add_test(tc_o, test_s21_sprintf_o_width);
  tcase_add_test(tc_o, test_s21_sprintf_o_left_justify);
  tcase_add_test(tc_o, test_s21_sprintf_o_leading_zeros);
  tcase_add_test(tc_o, test_s21_sprintf_o_precision);
  tcase_add_test(tc_o, test_s21_sprintf_o_precision_zero);
  tcase_add_test(tc_o, test_s21_sprintf_o_width_precision);
  tcase_add_test(tc_o, test_s21_sprintf_o_hash_flag);
  tcase_add_test(tc_o, test_s21_sprintf_o_hash_width);
  suite_add_tcase(s, tc_o);

  return s;
}

START_TEST(test_s21_sprintf_x_simple) {
  test_specifier_helper(
      12345, "%x", "Простое шестнадцатеричное число в нижнем регистре", 'x');
}
END_TEST

START_TEST(test_s21_sprintf_x_zero) {
  test_specifier_helper(0, "%x", "Нулевое значение", 'x');
}
END_TEST

START_TEST(test_s21_sprintf_x_width) {
  test_specifier_helper(123, "%10x", "Ширина 10 символов", 'x');
}
END_TEST

START_TEST(test_s21_sprintf_x_left_justify) {
  test_specifier_helper(123, "%-10x", "Выравнивание по левому краю, ширина 10",
                        'x');
}
END_TEST

START_TEST(test_s21_sprintf_x_leading_zeros) {
  test_specifier_helper(123, "%010x", "Дополнение нулями, ширина 10", 'x');
}
END_TEST

START_TEST(test_s21_sprintf_x_precision) {
  test_specifier_helper(123, "%.5x", "Точность 5 символов", 'x');
}
END_TEST

START_TEST(test_s21_sprintf_x_precision_zero) {
  test_specifier_helper(0, "%.5x", "Точность 5 символов, нулевое значение",
                        'x');
}
END_TEST

START_TEST(test_s21_sprintf_x_width_precision) {
  test_specifier_helper(123, "%10.5x", "Ширина 10, точность 5", 'x');
}
END_TEST

START_TEST(test_s21_sprintf_x_hash_flag) {
  test_specifier_helper(123, "%#x", "Флаг решетки (добавляет 0x)", 'x');
}
END_TEST

START_TEST(test_s21_sprintf_x_hash_width) {
  test_specifier_helper(123, "%#10x", "Флаг решетки и ширина 10", 'x');
}
END_TEST

Suite *s21_sprintf_x_suite(void) {
  Suite *s;
  TCase *tc_x;

  s = suite_create("s21_sprintf_x");

  tc_x = tcase_create("x specifier");
  tcase_add_test(tc_x, test_s21_sprintf_x_simple);
  tcase_add_test(tc_x, test_s21_sprintf_x_zero);
  tcase_add_test(tc_x, test_s21_sprintf_x_width);
  tcase_add_test(tc_x, test_s21_sprintf_x_left_justify);
  tcase_add_test(tc_x, test_s21_sprintf_x_leading_zeros);
  tcase_add_test(tc_x, test_s21_sprintf_x_precision);
  tcase_add_test(tc_x, test_s21_sprintf_x_precision_zero);
  tcase_add_test(tc_x, test_s21_sprintf_x_width_precision);
  tcase_add_test(tc_x, test_s21_sprintf_x_hash_flag);
  tcase_add_test(tc_x, test_s21_sprintf_x_hash_width);
  suite_add_tcase(s, tc_x);

  return s;
}

START_TEST(test_s21_sprintf_X_simple) {
  test_specifier_helper(
      12345, "%X", "Простое шестнадцатеричное число в верхнем регистре", 'X');
}
END_TEST

START_TEST(test_s21_sprintf_X_zero) {
  test_specifier_helper(0, "%X", "Нулевое значение", 'X');
}
END_TEST

START_TEST(test_s21_sprintf_X_width) {
  test_specifier_helper(123, "%10X", "Ширина 10 символов", 'X');
}
END_TEST

START_TEST(test_s21_sprintf_X_left_justify) {
  test_specifier_helper(123, "%-10X", "Выравнивание по левому краю, ширина 10",
                        'X');
}
END_TEST

START_TEST(test_s21_sprintf_X_leading_zeros) {
  test_specifier_helper(123, "%010X", "Дополнение нулями, ширина 10", 'X');
}
END_TEST

START_TEST(test_s21_sprintf_X_precision) {
  test_specifier_helper(123, "%.5X", "Точность 5 символов", 'X');
}
END_TEST

START_TEST(test_s21_sprintf_X_precision_zero) {
  test_specifier_helper(0, "%.5X", "Точность 5 символов, нулевое значение",
                        'X');
}
END_TEST

START_TEST(test_s21_sprintf_X_width_precision) {
  test_specifier_helper(123, "%10.5X", "Ширина 10, точность 5", 'X');
}
END_TEST

START_TEST(test_s21_sprintf_X_hash_flag) {
  test_specifier_helper(123, "%#X", "Флаг решетки (добавляет 0X)", 'X');
}
END_TEST

START_TEST(test_s21_sprintf_X_hash_width) {
  test_specifier_helper(123, "%#10X", "Флаг решетки и ширина 10", 'X');
}
END_TEST

Suite *s21_sprintf_X_suite(void) {
  Suite *s;
  TCase *tc_X;

  s = suite_create("s21_sprintf_X");

  tc_X = tcase_create("X specifier");
  tcase_add_test(tc_X, test_s21_sprintf_X_simple);
  tcase_add_test(tc_X, test_s21_sprintf_X_zero);
  tcase_add_test(tc_X, test_s21_sprintf_X_width);
  tcase_add_test(tc_X, test_s21_sprintf_X_left_justify);
  tcase_add_test(tc_X, test_s21_sprintf_X_leading_zeros);
  tcase_add_test(tc_X, test_s21_sprintf_X_precision);
  tcase_add_test(tc_X, test_s21_sprintf_X_precision_zero);
  tcase_add_test(tc_X, test_s21_sprintf_X_width_precision);
  tcase_add_test(tc_X, test_s21_sprintf_X_hash_flag);
  tcase_add_test(tc_X, test_s21_sprintf_X_hash_width);

  suite_add_tcase(s, tc_X);

  return s;
}

START_TEST(test_s21_sprintf_all_out) {
  char str_s21[100];
  char str_original[100];

  const char *format = "%#10X %-10u %#8.3o %0#8.4x";
  unsigned int num1, num2, num3, num4;
  num1 = num2 = num3 = num4 = 255;

  s21_sprintf(str_s21, format, num1, num2, num3, num4);
  sprintf(str_original, format, num1, num2, num3, num4);

  printf("=== Тестирование спецификатора: ouxX ===\n");
  printf("Тест: %s\n", "All out");
  printf("Результат s21_sprintf: '%s'\n", str_s21);
  printf("Результат sprintf: '%s'\n", str_original);

  ck_assert_str_eq(str_s21, str_original);

  printf("--------------------------\n");
}
END_TEST

START_TEST(test_s21_sprintf_all_out_minus) {
  char str_s21[100];
  char str_original[100];

  const char *format = "%#10X %-10u %#8.3o %0#8.4x";
  unsigned int num1, num2, num3, num4;
  num1 = num2 = num3 = num4 = -255;

  s21_sprintf(str_s21, format, num1, num2, num3, num4);
  sprintf(str_original, format, num1, num2, num3, num4);

  printf("=== Тестирование спецификатора: ouxX ===\n");
  printf("Тест: %s\n", "All out");
  printf("Результат s21_sprintf: '%s'\n", str_s21);
  printf("Результат sprintf: '%s'\n", str_original);

  ck_assert_str_eq(str_s21, str_original);

  printf("--------------------------\n");
}
END_TEST

START_TEST(test_s21_sprintf_all_out_zero) {
  char str_s21[100];
  char str_original[100];

  const char *format = "%#10X %-10u %#8.3o %0#8.4x";
  unsigned int num1, num2, num3, num4;
  num1 = num2 = num3 = num4 = 0;

  s21_sprintf(str_s21, format, num1, num2, num3, num4);
  sprintf(str_original, format, num1, num2, num3, num4);

  printf("=== Тестирование спецификатора: ouxX ===\n");
  printf("Тест: %s\n", "All out");
  printf("Результат s21_sprintf: '%s'\n", str_s21);
  printf("Результат sprintf: '%s'\n", str_original);

  ck_assert_str_eq(str_s21, str_original);

  printf("--------------------------\n");
}
END_TEST

START_TEST(test_s21_sprintf_all_out_octo) {
  char str_s21[100];
  char str_original[100];

  const char *format = "%#10X %-10u %#8.3o %0#8.4x";
  unsigned int num1, num2, num3, num4;
  num1 = num2 = num3 = num4 = 0123;

  s21_sprintf(str_s21, format, num1, num2, num3, num4);
  sprintf(str_original, format, num1, num2, num3, num4);

  printf("=== Тестирование спецификатора: ouxX ===\n");
  printf("Тест: %s\n", "All out");
  printf("Результат s21_sprintf: '%s'\n", str_s21);
  printf("Результат sprintf: '%s'\n", str_original);

  ck_assert_str_eq(str_s21, str_original);

  printf("--------------------------\n");
}
END_TEST

START_TEST(test_s21_sprintf_all_out_hex) {
  char str_s21[100];
  char str_original[100];

  const char *format = "%#10X %-10u %#8.3o %0#8.4x";
  unsigned int num1, num2, num3, num4;
  num1 = num2 = num3 = num4 = 0x123;

  s21_sprintf(str_s21, format, num1, num2, num3, num4);
  sprintf(str_original, format, num1, num2, num3, num4);

  printf("=== Тестирование спецификатора: ouxX ===\n");
  printf("Тест: %s\n", "All out");
  printf("Результат s21_sprintf: '%s'\n", str_s21);
  printf("Результат sprintf: '%s'\n", str_original);

  ck_assert_str_eq(str_s21, str_original);

  printf("--------------------------\n");
}
END_TEST

Suite *s21_sprintf_uoxX_suite(void) {
  Suite *s;
  TCase *tc_uoxX;

  s = suite_create("s21_sprintf_uoxX");

  tc_uoxX = tcase_create("uoxX specifiers");
  tcase_add_test(tc_uoxX, test_s21_sprintf_all_out);
  tcase_add_test(tc_uoxX, test_s21_sprintf_all_out_minus);
  tcase_add_test(tc_uoxX, test_s21_sprintf_all_out_zero);
  tcase_add_test(tc_uoxX, test_s21_sprintf_all_out_octo);
  tcase_add_test(tc_uoxX, test_s21_sprintf_all_out_hex);

  suite_add_tcase(s, tc_uoxX);

  return s;
}

void simple_test_p_specifier_helper(const char *format, void *ptr,
                                    const char *message, char specifier) {
  char s21_res[256] = {0};
  char std_res[256] = {0};
  s21_sprintf(s21_res, format, ptr);
  sprintf(std_res, format, ptr);
  printf("=== Тест: %s для спецификатора %c ===\n", message, specifier);
  printf("Format: '%s'\n", format);
  printf("s21_sprintf: '%s'\n", s21_res);
  printf("sprintf:     '%s'\n", std_res);
  ck_assert_str_eq(s21_res, std_res);
  printf("--------------------------\n");
}

START_TEST(test_p_null_pointer) {
  simple_test_p_specifier_helper("%p", NULL, "NULL pointer", 'p');
}
END_TEST

START_TEST(test_p_int_pointer) {
  int a = 42;
  simple_test_p_specifier_helper("%p", &a, "Pointer to int", 'p');
}
END_TEST

START_TEST(test_p_char_pointer) {
  char str[] = "Hello";
  simple_test_p_specifier_helper("%p", str, "Pointer to char array", 'p');
}
END_TEST

START_TEST(test_p_double_pointer) {
  double d = 3.14;
  simple_test_p_specifier_helper("%p", &d, "Pointer to double", 'p');
}
END_TEST

Suite *s21_sprintf_p_suite(void) {
  Suite *s = suite_create("s21_sprintf_p_suite");
  TCase *tc = tcase_create("tc_s21_sprintf_p");
  tcase_add_test(tc, test_p_null_pointer);
  tcase_add_test(tc, test_p_int_pointer);
  tcase_add_test(tc, test_p_char_pointer);
  tcase_add_test(tc, test_p_double_pointer);
  suite_add_tcase(s, tc);
  return s;
}

void simple_test_n_length_helper(const char *format, const char *message) {
  char s21_res[256] = {0};
  char std_res[256] = {0};

  short s21_short_count = 0, std_short_count = 0;
  int s21_int_count = 0, std_int_count = 0;
  long s21_long_count = 0, std_long_count = 0;

  s21_sprintf(s21_res, format, &s21_short_count);
  sprintf(std_res, format, &std_short_count);
  printf("=== Тест: %s (hn) ===\n", message);
  printf("Format: '%s'\n", format);
  printf("s21_sprintf: '%s' | count: %hd\n", s21_res, s21_short_count);
  printf("sprintf:     '%s' | count: %hd\n", std_res, std_short_count);
  ck_assert_str_eq(s21_res, std_res);
  ck_assert_int_eq(s21_short_count, std_short_count);

  s21_sprintf(s21_res, format, &s21_int_count);
  sprintf(std_res, format, &std_int_count);
  printf("=== Тест: %s (n) ===\n", message);
  printf("s21_sprintf: '%s' | count: %d\n", s21_res, s21_int_count);
  printf("sprintf:     '%s' | count: %d\n", std_res, std_int_count);
  ck_assert_str_eq(s21_res, std_res);
  ck_assert_int_eq(s21_int_count, std_int_count);

  s21_sprintf(s21_res, format, &s21_long_count);
  sprintf(std_res, format, &std_long_count);
  printf("=== Тест: %s (ln) ===\n", message);
  printf("s21_sprintf: '%s' | count: %ld\n", s21_res, s21_long_count);
  printf("sprintf:     '%s' | count: %ld\n", std_res, std_long_count);
  ck_assert_str_eq(s21_res, std_res);
  ck_assert_int_eq(s21_long_count, std_long_count);

  printf("--------------------------\n");
}

START_TEST(test_n_basic_text) {
  simple_test_n_length_helper("Hello World%hn", "Basic text before %n");
}
END_TEST

START_TEST(test_n_empty_string) {
  simple_test_n_length_helper("%hn", "Empty string before %n");
}
END_TEST

START_TEST(test_n_spaces) {
  simple_test_n_length_helper("     %hn", "Only spaces before %n");
}
END_TEST

START_TEST(test_n_numbers) {
  simple_test_n_length_helper("12345%hn", "Numbers before %n");
}
END_TEST

START_TEST(test_n_mixed) {
  simple_test_n_length_helper("Test 42 is a great number%hn",
                              "Mixed text and numbers before %n");
}
END_TEST

START_TEST(test_n_multiple) {
  char s21_res[256] = {0}, std_res[256] = {0};
  short s21_count1 = 0, s21_count2 = 0;
  short std_count1 = 0, std_count2 = 0;

  s21_sprintf(s21_res, "Hello%hn World%hn", &s21_count1, &s21_count2);
  sprintf(std_res, "Hello%hn World%hn", &std_count1, &std_count2);

  printf("=== Тест: Multiple hn in string ===\n");
  printf("Format: 'Hello%%hn World%%hn'\n");
  printf("s21_sprintf: '%s' | counts: %hd, %hd\n", s21_res, s21_count1,
         s21_count2);
  printf("sprintf:     '%s' | counts: %hd, %hd\n", std_res, std_count1,
         std_count2);

  ck_assert_str_eq(s21_res, std_res);
  ck_assert_int_eq(s21_count1, std_count1);
  ck_assert_int_eq(s21_count2, std_count2);
  printf("--------------------------\n");
}
END_TEST

Suite *s21_sprintf_n_suite(void) {
  Suite *s = suite_create("s21_sprintf_n_suite");
  TCase *tc = tcase_create("tc_s21_sprintf_n");

  tcase_add_test(tc, test_n_basic_text);
  tcase_add_test(tc, test_n_empty_string);
  tcase_add_test(tc, test_n_spaces);
  tcase_add_test(tc, test_n_numbers);
  tcase_add_test(tc, test_n_mixed);
  tcase_add_test(tc, test_n_multiple);

  suite_add_tcase(s, tc);
  return s;
}

void simple_test_percent_specifier_helper(const char *format,
                                          const char *message) {
  char s21_res[256] = {0};
  char std_res[256] = {0};

  s21_sprintf(s21_res, format);
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-security"
  sprintf(std_res, format);
#pragma GCC diagnostic pop

  printf("=== Тест: %s ===\n", message);
  printf("Формат: '%s'\n", format);
  printf("s21_sprintf: '%s'\n", s21_res);
  printf("sprintf:     '%s'\n", std_res);
  ck_assert_str_eq(s21_res, std_res);
  printf("--------------------------\n");
}

START_TEST(test_percent_single) {
  simple_test_percent_specifier_helper("%%", "Одинарный %");
}
END_TEST

START_TEST(test_percent_double) {
  simple_test_percent_specifier_helper("%%%%", "Двойной %%");
}
END_TEST

START_TEST(test_percent_with_text) {
  simple_test_percent_specifier_helper("Процент: %%", "Текст перед %");
}
END_TEST

START_TEST(test_percent_with_numbers) {
  simple_test_percent_specifier_helper("100%% успеха", "Числа перед %");
}
END_TEST

START_TEST(test_percent_at_start) {
  simple_test_percent_specifier_helper("%% начало строки", "% в начале строки");
}
END_TEST

START_TEST(test_percent_at_end) {
  simple_test_percent_specifier_helper("Конец строки %%", "% в конце строки");
}
END_TEST

START_TEST(test_percent_in_middle) {
  simple_test_percent_specifier_helper("Текст %% между словами",
                                       "% между словами");
}
END_TEST

Suite *s21_sprintf_percent_suite(void) {
  Suite *s = suite_create("s21_sprintf_percent_suite");
  TCase *tc = tcase_create("tc_s21_sprintf_percent");

  tcase_add_test(tc, test_percent_single);
  tcase_add_test(tc, test_percent_double);
  tcase_add_test(tc, test_percent_with_text);
  tcase_add_test(tc, test_percent_with_numbers);
  tcase_add_test(tc, test_percent_at_start);
  tcase_add_test(tc, test_percent_at_end);
  tcase_add_test(tc, test_percent_in_middle);

  suite_add_tcase(s, tc);
  return s;
}

START_TEST(test_s21_sprintf_all_specifiers) {
  char s21_res[512] = {0};
  char std_res[512] = {0};
  const char format[] =
      "C:%-3c D:%+5d I:%05i E:%10.4e F:%-10.3f G:%+8.2g O:%#10o S:%-10.4s "
      "U:%010u X:%#10x P:%20p %%";
  const char message[] =
      "Проверка всех спецификаторов с флагами, шириной и точностью";

  char c_val = 'Z';
  int d_val = -42;
  int i_val = 123;
  double e_val = 3.14159;
  double f_val = 2.71828;
  double g_val = 0.00012345;
  unsigned int o_val = 255;
  char s_val[] = "HelloWorld";
  unsigned int u_val = 12345;
  unsigned int x_val = 48879;
  void *p_val = (void *)&d_val;

  s21_sprintf(s21_res, format, c_val, d_val, i_val, e_val, f_val, g_val, o_val,
              s_val, u_val, x_val, p_val);
  sprintf(std_res, format, c_val, d_val, i_val, e_val, f_val, g_val, o_val,
          s_val, u_val, x_val, p_val);

  printf("=== Тест: %s ===\n", message);
  printf("Формат: '%s'\n", format);
  printf("s21_sprintf: '%s'\n", s21_res);
  printf("sprintf:     '%s'\n", std_res);
  ck_assert_str_eq(s21_res, std_res);
  printf("--------------------------\n");
}
END_TEST

Suite *s21_sprintf_all_suite(void) {
  Suite *s = suite_create("s21_sprintf_all_suite");
  TCase *tc = tcase_create("tc_s21_sprintf_all");
  tcase_add_test(tc, test_s21_sprintf_all_specifiers);
  suite_add_tcase(s, tc);
  return s;
}

int sprintf_tests() {
  int number_failed = 0;

  Suite *sprintf_c = s21_sprintf_c_suite();
  Suite *sprintf_d = s21_sprintf_d_suite();
  Suite *sprintf_i = s21_sprintf_i_suite();
  Suite *sprintf_e = s21_sprintf_e_suite();
  Suite *sprintf_f = s21_sprintf_f_suite();
  Suite *sprintf_g = s21_sprintf_g_suite();
  Suite *sprintf_feg = s21_sprintf_feg_suite();
  Suite *sprintf_o = s21_sprintf_o_suite();
  Suite *sprintf_s = s21_sprintf_s_suite();
  Suite *sprintf_u = s21_sprintf_u_suite();
  Suite *sprintf_x = s21_sprintf_x_suite();
  Suite *sprintf_X = s21_sprintf_X_suite();
  Suite *sprintf_uoxX = s21_sprintf_uoxX_suite();
  Suite *sprintf_p = s21_sprintf_p_suite();
  Suite *sprintf_n = s21_sprintf_n_suite();
  Suite *sprintf_percent = s21_sprintf_percent_suite();
  Suite *sprintf_all = s21_sprintf_all_suite();

  SRunner *sr = srunner_create(sprintf_c);
  srunner_add_suite(sr, sprintf_d);
  srunner_add_suite(sr, sprintf_i);
  srunner_add_suite(sr, sprintf_e);
  srunner_add_suite(sr, sprintf_f);
  srunner_add_suite(sr, sprintf_g);
  srunner_add_suite(sr, sprintf_feg);
  srunner_add_suite(sr, sprintf_o);
  srunner_add_suite(sr, sprintf_s);
  srunner_add_suite(sr, sprintf_u);
  srunner_add_suite(sr, sprintf_x);
  srunner_add_suite(sr, sprintf_X);
  srunner_add_suite(sr, sprintf_uoxX);
  srunner_add_suite(sr, sprintf_p);
  srunner_add_suite(sr, sprintf_n);
  srunner_add_suite(sr, sprintf_percent);
  srunner_add_suite(sr, sprintf_all);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}

void test_sscanf_helper(const char *input, const char *format,
                        const char *message, int specifier, ...) {
  va_list args;
  va_start(args, specifier);

  if (specifier == 'u' || specifier == 'o' || specifier == 'x' ||
      specifier == 'X') {
    unsigned long s21_val = 0, std_val = 0;

    int s21_ret = s21_sscanf(input, format, &s21_val);
    int std_ret = sscanf(input, format, &std_val);

    printf("=== Тестирование спецификатора: %c ===\n", specifier);
    printf("Тест: %s\n", message);
    printf("Входные данные: input = '%s', format = '%s'\n", input, format);
    printf("Результат s21_sscanf: %lu (возвращено: %d)\n", s21_val, s21_ret);
    printf("Результат sscanf: %lu (возвращено: %d)\n", std_val, std_ret);

    ck_assert_int_eq(s21_ret, std_ret);
    ck_assert_uint_eq(s21_val, std_val);
  }

  va_end(args);
  printf("--------------------------\n");
}

START_TEST(test_sscanf_u_simple) {
  test_sscanf_helper("12345", "%u", "Простое беззнаковое десятичное число",
                     'u');
}
END_TEST

START_TEST(test_sscanf_u_width) {
  test_sscanf_helper("12345", "%3u", "Ширина 3 символа", 'u');
}
END_TEST

START_TEST(test_sscanf_u_short) {
  test_sscanf_helper("65535", "%hu", "Короткое беззнаковое число", 'u');
}
END_TEST

START_TEST(test_sscanf_u_long) {
  test_sscanf_helper("4294967295", "%lu", "Длинное беззнаковое число", 'u');
}
END_TEST

START_TEST(test_sscanf_u_zero) {
  test_sscanf_helper("0", "%u", "Нулевое значение", 'u');
}
END_TEST

START_TEST(test_sscanf_u_invalid) {
  test_sscanf_helper("abc", "%u", "Неверный ввод", 'u');
}
END_TEST

Suite *s21_sscanf_u_suite(void) {
  Suite *s = suite_create("s21_sscanf_u");
  TCase *tc = tcase_create("Core");
  tcase_add_test(tc, test_sscanf_u_simple);
  tcase_add_test(tc, test_sscanf_u_width);
  tcase_add_test(tc, test_sscanf_u_short);
  tcase_add_test(tc, test_sscanf_u_long);
  tcase_add_test(tc, test_sscanf_u_zero);
  tcase_add_test(tc, test_sscanf_u_invalid);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(test_sscanf_o_simple) {
  test_sscanf_helper("755", "%o", "Простое восьмеричное число", 'o');
}
END_TEST

START_TEST(test_sscanf_o_width) {
  test_sscanf_helper("12345", "%3o", "Ширина 3 символа", 'o');
}
END_TEST

START_TEST(test_sscanf_o_short) {
  test_sscanf_helper("7777", "%ho", "Короткое восьмеричное число", 'o');
}
END_TEST

START_TEST(test_sscanf_o_long) {
  test_sscanf_helper("77777777", "%lo", "Длинное восьмеричное число", 'o');
}
END_TEST

START_TEST(test_sscanf_o_prefix) {
  test_sscanf_helper("0755", "%o", "Восьмеричное число с префиксом 0", 'o');
}
END_TEST

Suite *s21_sscanf_o_suite(void) {
  Suite *s = suite_create("s21_sscanf_o");
  TCase *tc = tcase_create("Core");
  tcase_add_test(tc, test_sscanf_o_simple);
  tcase_add_test(tc, test_sscanf_o_width);
  tcase_add_test(tc, test_sscanf_o_short);
  tcase_add_test(tc, test_sscanf_o_long);
  tcase_add_test(tc, test_sscanf_o_prefix);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(test_sscanf_x_simple) {
  test_sscanf_helper("1a3f", "%x", "Простое шестнадцатеричное число", 'x');
}
END_TEST

START_TEST(test_sscanf_x_width) {
  test_sscanf_helper("1a3f5", "%4x", "Ширина 4 символа", 'x');
}
END_TEST

START_TEST(test_sscanf_x_short) {
  test_sscanf_helper("1a3f", "%hx", "Короткое шестнадцатеричное число", 'x');
}
END_TEST

START_TEST(test_sscanf_x_long) {
  test_sscanf_helper("1a3f1a3f", "%lx", "Длинное шестнадцатеричное число", 'x');
}
END_TEST

START_TEST(test_sscanf_x_prefix) {
  test_sscanf_helper("0x1a3f", "%x", "Шестнадцатеричное число с префиксом 0x",
                     'x');
}
END_TEST

Suite *s21_sscanf_x_suite(void) {
  Suite *s = suite_create("s21_sscanf_x");
  TCase *tc = tcase_create("Core");
  tcase_add_test(tc, test_sscanf_x_simple);
  tcase_add_test(tc, test_sscanf_x_width);
  tcase_add_test(tc, test_sscanf_x_short);
  tcase_add_test(tc, test_sscanf_x_long);
  tcase_add_test(tc, test_sscanf_x_prefix);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(test_sscanf_X_upper) {
  test_sscanf_helper("1A3F", "%X", "Шестнадцатеричное число в верхнем регистре",
                     'X');
}
END_TEST

START_TEST(test_sscanf_X_prefix) {
  test_sscanf_helper("0X1A3F", "%X", "Шестнадцатеричное число с префиксом 0X",
                     'X');
}
END_TEST

Suite *s21_sscanf_X_suite(void) {
  Suite *s = suite_create("s21_sscanf_X");
  TCase *tc = tcase_create("Core");
  tcase_add_test(tc, test_sscanf_X_upper);
  tcase_add_test(tc, test_sscanf_X_prefix);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(test_sscanf_mixed_specifiers) {
  const char *input = "123 0x1a3f 755";
  unsigned int u1, u2, o1;
  unsigned int s21_u1 = 0, s21_u2 = 0, s21_o1 = 0;

  int s21_ret = s21_sscanf(input, "%u %x %o", &s21_u1, &s21_u2, &s21_o1);
  int std_ret = sscanf(input, "%u %x %o", &u1, &u2, &o1);

  printf("=== Тестирование смешанных спецификаторов ===\n");
  printf("Тест: Смешанные спецификаторы\n");
  printf("Входные данные: input = '%s', format = '%%u %%x %%o'\n", input);
  printf("Результат s21_sscanf: %u, %u, %u (возвращено: %d)\n", s21_u1, s21_u2,
         s21_o1, s21_ret);
  printf("Результат sscanf: %u, %u, %u (возвращено: %d)\n", u1, u2, o1,
         std_ret);

  ck_assert_int_eq(s21_ret, std_ret);
  ck_assert_uint_eq(s21_u1, u1);
  ck_assert_uint_eq(s21_u2, u2);
  ck_assert_uint_eq(s21_o1, o1);

  printf("--------------------------\n");
}
END_TEST

Suite *s21_sscanf_mixed_suite(void) {
  Suite *s = suite_create("s21_sscanf_mixed");
  TCase *tc = tcase_create("Core");
  tcase_add_test(tc, test_sscanf_mixed_specifiers);
  suite_add_tcase(s, tc);
  return s;
}

static void test_sscanf_int_helper(const char *input, const char *format,
                                   const char *message, char specifier) {
  int s21_val = 0, std_val = 0;
  int s21_ret = s21_sscanf(input, format, &s21_val);
  int std_ret = sscanf(input, format, &std_val);
  printf("=== Тестирование спецификатора: %c ===\n", specifier);
  printf("Тест: %s\n", message);
  printf("Входные данные: '%s', format: '%s'\n", input, format);
  printf("s21_sscanf: %d (возвращено: %d)\n", s21_val, s21_ret);
  printf("sscanf:     %d (возвращено: %d)\n", std_val, std_ret);
  ck_assert_int_eq(s21_ret, std_ret);
  ck_assert_int_eq(s21_val, std_val);
  printf("--------------------------\n");
}

START_TEST(test_sscanf_d_positive) {
  test_sscanf_int_helper("12345", "%d", "Положительное число", 'd');
}
END_TEST

START_TEST(test_sscanf_d_negative) {
  test_sscanf_int_helper("-6789", "%d", "Отрицательное число", 'd');
}
END_TEST

START_TEST(test_sscanf_d_with_plus) {
  test_sscanf_int_helper("+42", "%d", "Число с явным знаком плюс", 'd');
}
END_TEST

Suite *s21_sscanf_d_suite(void) {
  Suite *s = suite_create("s21_sscanf_d");
  TCase *tc = tcase_create("Core");
  tcase_add_test(tc, test_sscanf_d_positive);
  tcase_add_test(tc, test_sscanf_d_negative);
  tcase_add_test(tc, test_sscanf_d_with_plus);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(test_sscanf_i_decimal) {
  test_sscanf_int_helper("9876", "%i", "Десятичное число без префикса", 'i');
}
END_TEST

START_TEST(test_sscanf_i_octal) {
  test_sscanf_int_helper("0123", "%i", "Восьмеричное число с ведущим 0", 'i');
}
END_TEST

START_TEST(test_sscanf_i_hex) {
  test_sscanf_int_helper("0x1a3f", "%i",
                         "Шестнадцатеричное число с префиксом 0x", 'i');
}
END_TEST

START_TEST(test_sscanf_i_negative) {
  test_sscanf_int_helper("-0xFF", "%i", "Отрицательное шестнадцатеричное число",
                         'i');
}
END_TEST

Suite *s21_sscanf_i_suite(void) {
  Suite *s = suite_create("s21_sscanf_i");
  TCase *tc = tcase_create("Core");
  tcase_add_test(tc, test_sscanf_i_decimal);
  tcase_add_test(tc, test_sscanf_i_octal);
  tcase_add_test(tc, test_sscanf_i_hex);
  tcase_add_test(tc, test_sscanf_i_negative);
  suite_add_tcase(s, tc);
  return s;
}

void test_feg_float_specifier_helper(const char *str, const char *format,
                                     const char *message, char specifier) {
  float s21_res = 0.0, std_res = 0.0;

  int s21_intres = s21_sscanf(str, format, &s21_res);
  int std_intres = sscanf(str, format, &std_res);

  printf("=== Тестирование спецификатора: %c ===\n", specifier);
  printf("Тест: %s\n", message);
  printf("Входные данные: str = '%s', format = '%s'\n", str, format);
  printf("Результат s21_sscanf: '%f' (возвращено: %d)\n", s21_res, s21_intres);
  printf("Результат sscanf: '%f' (возвращено: %d)\n", std_res, std_intres);

  ck_assert_float_eq(s21_res, std_res);
  ck_assert_int_eq(s21_intres, std_intres);

  printf("--------------------------\n");
}

START_TEST(test_s21_sscanf_f) {
  test_feg_float_specifier_helper("123.456", "%f", "Число с плавающей точкой",
                                  'f');
}
END_TEST

START_TEST(test_s21_sscanf_e) {
  test_feg_float_specifier_helper(
      "-1.234e-05", "%e", "Число в научной нотации, нижний регистр", 'e');
}
END_TEST

START_TEST(test_s21_sscanf_E) {
  test_feg_float_specifier_helper(
      "5.678E-09", "%E", "Число в научной нотации, верхний регистр", 'E');
}
END_TEST

START_TEST(test_s21_sscanf_g) {
  test_feg_float_specifier_helper("-0.001245", "%g",
                                  "Общий формат, нижний регистр", 'g');
}
END_TEST

START_TEST(test_s21_sscanf_G) {
  test_feg_float_specifier_helper("7.37E+04", "%G",
                                  "Общий формат, верхний регистр", 'G');
}
END_TEST

void test_feg_double_specifier_helper(const char *str, const char *format,
                                      const char *message, char specifier) {
  double s21_res = 0.0, std_res = 0.0;

  int s21_intres = s21_sscanf(str, format, &s21_res);
  int std_intres = sscanf(str, format, &std_res);

  printf("=== Тестирование спецификатора: %c ===\n", specifier);
  printf("Тест: %s\n", message);
  printf("Входные данные: str = '%s', format = '%s'\n", str, format);
  printf("Результат s21_sscanf: '%lf' (возвращено: %d)\n", s21_res, s21_intres);
  printf("Результат sscanf: '%lf' (возвращено: %d)\n", std_res, std_intres);

  ck_assert_float_eq(s21_res, std_res);
  ck_assert_int_eq(s21_intres, std_intres);

  printf("--------------------------\n");
}

START_TEST(test_s21_sscanf_lf) {
  test_feg_double_specifier_helper("123.456", "%lf",
                                   "Число с плавающей точкой (double)", 'f');
}
END_TEST

START_TEST(test_s21_sscanf_le) {
  test_feg_double_specifier_helper(
      "-1.234e-05", "%le", "Число в научной нотации, нижний регистр (double)",
      'e');
}
END_TEST

START_TEST(test_s21_sscanf_lE) {
  test_feg_double_specifier_helper(
      "5.678765E-09", "%10lE",
      "Число в научной нотации, верхний регистр (double)", 'E');
}
END_TEST

START_TEST(test_s21_sscanf_lg) {
  test_feg_double_specifier_helper(
      "-0.01245567898", "%lg", "Общий формат, нижний регистр (double)", 'g');
}
END_TEST

START_TEST(test_s21_sscanf_lG) {
  test_feg_double_specifier_helper(
      "7.37E+04", "%lG", "Общий формат, верхний регистр (double)", 'G');
}
END_TEST

void test_feg_ldouble_specifier_helper(const char *str, const char *format,
                                       const char *message, char specifier) {
  long double s21_res = 0.0, std_res = 0.0;

  int s21_intres = s21_sscanf(str, format, &s21_res);
  int std_intres = sscanf(str, format, &std_res);

  printf("=== Тестирование спецификатора: %c ===\n", specifier);
  printf("Тест: %s\n", message);
  printf("Входные данные: str = '%s', format = '%s'\n", str, format);
  printf("Результат s21_sscanf: '%Lf' (возвращено: %d)\n", s21_res, s21_intres);
  printf("Результат sscanf: '%Lf' (возвращено: %d)\n", std_res, std_intres);

  ck_assert_float_eq(s21_res, std_res);
  ck_assert_int_eq(s21_intres, std_intres);

  printf("--------------------------\n");
}

START_TEST(test_s21_sscanf_Lf) {
  test_feg_ldouble_specifier_helper(
      "0.1", "%Lf", "Число с плавающей точкой (long double)", 'f');
}
END_TEST

START_TEST(test_s21_sscanf_Le) {
  test_feg_ldouble_specifier_helper(
      "-1.234e-10", "%Le",
      "Число в научной нотации, нижний регистр (long double)", 'e');
}
END_TEST

START_TEST(test_s21_sscanf_LE) {
  test_feg_ldouble_specifier_helper(
      "5.678E-09", "%LE",
      "Число в научной нотации, верхний регистр (long double)", 'E');
}
END_TEST

START_TEST(test_s21_sscanf_Lg) {
  test_feg_ldouble_specifier_helper(
      "-5.678E-09", "%Lg", "Общий формат, нижний регистр (long double)", 'g');
}
END_TEST

START_TEST(test_s21_sscanf_LG) {
  test_feg_ldouble_specifier_helper(
      "1.678E-09", "%LG", "Общий формат, верхний регистр (long double)", 'G');
}
END_TEST

START_TEST(test_s21_sscanf_combination) {
  const char *str = "123.456789 1.234e-05 123.506098 1E-06 567.456123";
  const char *format = "%f %le %Lg %E %LG";

  float num1 = 0.0, num4 = 0.0;
  double num2 = 0.0;
  long double num3 = 0.0, num5 = 0.0;

  char s21_res[256] = {0}, std_res[256] = {0};

  int std_intres = sscanf(str, format, &num1, &num2, &num3, &num4, &num5);
  sprintf(std_res, "%f %lf %Lf %f %Lf", num1, num2, num3, num4, num5);

  int s21_intres = s21_sscanf(str, format, &num1, &num2, &num3, &num4, &num5);
  sprintf(s21_res, "%f %lf %Lf %f %Lf", num1, num2, num3, num4, num5);

  printf("=== Тестирование спецификаторов: f, e, E, g, G ===\n");
  printf("Тест: Комбинация спецификаторов\n");
  printf("Входные данные: str = '%s', format = '%s'\n", str, format);
  printf("Результат s21_sscanf: '%s' (возвращено: %d)\n", s21_res, s21_intres);
  printf("Результат sscanf: '%s' (возвращено: %d)\n", std_res, std_intres);

  ck_assert_str_eq(s21_res, std_res);
  ck_assert_int_eq(s21_intres, std_intres);

  printf("--------------------------\n");
}
END_TEST

Suite *s21_sscanf_feg_suite(void) {
  Suite *s;
  TCase *tc_feg;

  s = suite_create("s21_sscanf_feg");

  tc_feg = tcase_create("f, e, g specifiers");
  tcase_add_test(tc_feg, test_s21_sscanf_f);
  tcase_add_test(tc_feg, test_s21_sscanf_e);
  tcase_add_test(tc_feg, test_s21_sscanf_E);
  tcase_add_test(tc_feg, test_s21_sscanf_g);
  tcase_add_test(tc_feg, test_s21_sscanf_G);
  tcase_add_test(tc_feg, test_s21_sscanf_lf);
  tcase_add_test(tc_feg, test_s21_sscanf_le);
  tcase_add_test(tc_feg, test_s21_sscanf_lE);
  tcase_add_test(tc_feg, test_s21_sscanf_lg);
  tcase_add_test(tc_feg, test_s21_sscanf_lG);
  tcase_add_test(tc_feg, test_s21_sscanf_Lf);
  tcase_add_test(tc_feg, test_s21_sscanf_Le);
  tcase_add_test(tc_feg, test_s21_sscanf_LE);
  tcase_add_test(tc_feg, test_s21_sscanf_Lg);
  tcase_add_test(tc_feg, test_s21_sscanf_LG);
  tcase_add_test(tc_feg, test_s21_sscanf_combination);

  suite_add_tcase(s, tc_feg);

  return s;
}

static void test_sscanf_pointer_helper(const char *input, const char *format,
                                       const char *message, char specifier) {
  void *s21_ptr = NULL, *std_ptr = NULL;
  int s21_ret = s21_sscanf(input, format, &s21_ptr);
  int std_ret = sscanf(input, format, &std_ptr);
  printf("=== Тестирование спецификатора: %c ===\n", specifier);
  printf("Тест: %s\n", message);
  printf("Входные данные: '%s', format: '%s'\n", input, format);
  printf("s21_sscanf: %p (возвращено: %d)\n", s21_ptr, s21_ret);
  printf("sscanf:     %p (возвращено: %d)\n", std_ptr, std_ret);
  ck_assert_int_eq(s21_ret, std_ret);
  ck_assert_uint_eq((uintptr_t)s21_ptr, (uintptr_t)std_ptr);
  printf("--------------------------\n");
}

START_TEST(test_sscanf_p_valid) {
  test_sscanf_pointer_helper(
      "0x1a3f", "%p", "Корректное шестнадцатеричное представление указателя",
      'p');
}
END_TEST

START_TEST(test_sscanf_p_zero) {
  test_sscanf_pointer_helper("0x0", "%p", "Указатель равен нулю", 'p');
}
END_TEST

START_TEST(test_sscanf_p_uppercase) {
  test_sscanf_pointer_helper(
      "0XDEADBEEF", "%p",
      "Корректное представление указателя с заглавными буквами", 'p');
}
END_TEST

START_TEST(test_sscanf_p_invalid) {
  test_sscanf_pointer_helper(
      "not_a_ptr", "%p", "Некорректное представление указателя (нет 0x)", 'p');
}
END_TEST

Suite *s21_sscanf_p_suite(void) {
  Suite *s = suite_create("s21_sscanf_p");
  TCase *tc = tcase_create("Core");
  tcase_add_test(tc, test_sscanf_p_valid);
  tcase_add_test(tc, test_sscanf_p_zero);
  tcase_add_test(tc, test_sscanf_p_uppercase);
  tcase_add_test(tc, test_sscanf_p_invalid);
  suite_add_tcase(s, tc);
  return s;
}

static void test_sscanf_n_helper(const char *input, const char *format,
                                 const char *message, char specifier) {
  int s21_n = -1, std_n = -1;
  int s21_val = 0, std_val = 0;
  int s21_ret = s21_sscanf(input, format, &s21_val, &s21_n);
  int std_ret = sscanf(input, format, &std_val, &std_n);
  printf("=== Тестирование спецификатора: %c ===\n", specifier);
  printf("Тест: %s\n", message);
  printf("Входные данные: '%s', format: '%s'\n", input, format);
  printf("s21_sscanf: value = %d, n = %d (возвращено: %d)\n", s21_val, s21_n,
         s21_ret);
  printf("sscanf:     value = %d, n = %d (возвращено: %d)\n", std_val, std_n,
         std_ret);
  ck_assert_int_eq(s21_ret, std_ret);
  ck_assert_int_eq(s21_val, std_val);
  ck_assert_int_eq(s21_n, std_n);
  printf("--------------------------\n");
}

START_TEST(test_sscanf_n_with_multiple_numbers) {
  int s21_a = 0, s21_b = 0, s21_c = 0, s21_n = -1;
  int std_a = 0, std_b = 0, std_c = 0, std_n = -1;
  int s21_ret =
      s21_sscanf("123 456 789", "%d %d %d%n", &s21_a, &s21_b, &s21_c, &s21_n);
  int std_ret =
      sscanf("123 456 789", "%d %d %d%n", &std_a, &std_b, &std_c, &std_n);
  printf("=== Тестирование спецификатора: n ===\n");
  printf("Тест: Проверка %%n после нескольких чисел\n");
  printf("Входные данные: '123 456 789', format: '%%d %%d %%d%%n'\n");
  printf("s21_sscanf: a = %d, b = %d, c = %d, n = %d (возвращено: %d)\n", s21_a,
         s21_b, s21_c, s21_n, s21_ret);
  printf("sscanf:     a = %d, b = %d, c = %d, n = %d (возвращено: %d)\n", std_a,
         std_b, std_c, std_n, std_ret);
  ck_assert_int_eq(s21_ret, std_ret);
  ck_assert_int_eq(s21_a, std_a);
  ck_assert_int_eq(s21_b, std_b);
  ck_assert_int_eq(s21_c, std_c);
  ck_assert_int_eq(s21_n, std_n);
  printf("--------------------------\n");
}
END_TEST

START_TEST(test_sscanf_n_simple) {
  test_sscanf_n_helper("12345", "%d%n",
                       "Проверка %n: число и количество прочитанных символов",
                       'n');
}
END_TEST

START_TEST(test_sscanf_n_with_text) {
  test_sscanf_n_helper("-42 hello", " %d%n",
                       "Проверка %n с пробелами и текстом", 'n');
}
END_TEST

START_TEST(test_sscanf_n_with_special_characters) {
  test_sscanf_n_helper("42!@# $%^&*()_+", "%d%n",
                       "Проверка %n с числом и специальными символами", 'n');
}
END_TEST

Suite *s21_sscanf_n_suite(void) {
  Suite *s = suite_create("s21_sscanf_n");
  TCase *tc = tcase_create("Core");
  tcase_add_test(tc, test_sscanf_n_simple);
  tcase_add_test(tc, test_sscanf_n_with_text);
  tcase_add_test(tc, test_sscanf_n_with_multiple_numbers);
  tcase_add_test(tc, test_sscanf_n_with_special_characters);
  suite_add_tcase(s, tc);
  return s;
}

static void test_sscanf_char_single_helper(const char *input,
                                           const char *format,
                                           const char *message,
                                           char specifier) {
  char s21_val = '\0';
  char std_val = '\0';
  int s21_ret = s21_sscanf(input, format, &s21_val);
  int std_ret = sscanf(input, format, &std_val);

  printf("=== Тестирование спецификатора: %c ===\n", specifier);
  printf("Тест: %s\n", message);
  printf("Входные данные: '%s', format: '%s'\n", input, format);
  printf("s21_sscanf: '%c' (возвращено: %d)\n", s21_val, s21_ret);
  printf("sscanf:     '%c' (возвращено: %d)\n", std_val, std_ret);

  ck_assert_int_eq(s21_ret, std_ret);
  ck_assert_int_eq(s21_val, std_val);
  printf("--------------------------\n");
}

static void test_sscanf_char_array_helper(const char *input, const char *format,
                                          const char *expected,
                                          const char *message, char specifier) {
  char s21_val[100] = {0};
  char std_val[100] = {0};
  int s21_ret = s21_sscanf(input, format, s21_val);
  int std_ret = sscanf(input, format, std_val);

  size_t width = strlen(expected);
  s21_val[width] = '\0';
  std_val[width] = '\0';

  printf("=== Тестирование спецификатора: %c ===\n", specifier);
  printf("Тест: %s\n", message);
  printf("Входные данные: '%s', format: '%s'\n", input, format);
  printf("s21_sscanf: \"%s\" (возвращено: %d)\n", s21_val, s21_ret);
  printf("sscanf:     \"%s\" (возвращено: %d)\n", std_val, std_ret);

  ck_assert_int_eq(s21_ret, std_ret);
  ck_assert_str_eq(s21_val, std_val);
  printf("--------------------------\n");
}

START_TEST(test_sscanf_c_basic) {
  test_sscanf_char_single_helper("A", "%c", "Обычный символ", 'c');
}
END_TEST

START_TEST(test_sscanf_c_whitespace) {
  test_sscanf_char_single_helper(" ", "%c", "Пробельный символ (пробел)", 'c');
}
END_TEST

START_TEST(test_sscanf_c_newline) {
  test_sscanf_char_single_helper("\n", "%c", "Пробельный символ (новая строка)",
                                 'c');
}
END_TEST

START_TEST(test_sscanf_c_no_skip) {
  test_sscanf_char_single_helper(" \tB", "%c",
                                 "Проверка отсутствия пропуска пробелов", 'c');
}
END_TEST

START_TEST(test_sscanf_c_skip_whitespace) {
  test_sscanf_char_single_helper(
      " \tB", " %c", "Проверка пропуска пробелов с форматом \" %c\"", 'c');
}
END_TEST

START_TEST(test_sscanf_c_width) {
  test_sscanf_char_array_helper("ABC", "%2c", "AB",
                                "Чтение двух символов с шириной 2", 'c');
}
END_TEST

START_TEST(test_sscanf_c_multiple) {
  test_sscanf_char_array_helper("XYZ", "%3c", "XYZ",
                                "Чтение трёх символов с шириной 3", 'c');
}
END_TEST

Suite *s21_sscanf_c_suite(void) {
  Suite *s = suite_create("s21_sscanf_c");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_sscanf_c_basic);
  tcase_add_test(tc, test_sscanf_c_whitespace);
  tcase_add_test(tc, test_sscanf_c_newline);
  tcase_add_test(tc, test_sscanf_c_no_skip);
  tcase_add_test(tc, test_sscanf_c_skip_whitespace);
  tcase_add_test(tc, test_sscanf_c_width);
  tcase_add_test(tc, test_sscanf_c_multiple);

  suite_add_tcase(s, tc);
  return s;
}

static void test_sscanf_s_helper(const char *input, const char *format,
                                 const char *message, char specifier) {
  char s21_val[100] = {0};
  char std_val[100] = {0};
  int s21_ret = s21_sscanf(input, format, s21_val);
  int std_ret = sscanf(input, format, std_val);

  printf("=== Тестирование спецификатора: %c ===\n", specifier);
  printf("Тест: %s\n", message);
  printf("Входные данные: '%s', format: '%s'\n", input, format);
  printf("s21_sscanf: \"%s\" (возвращено: %d)\n", s21_val, s21_ret);
  printf("sscanf:     \"%s\" (возвращено: %d)\n", std_val, std_ret);
  ck_assert_int_eq(s21_ret, std_ret);
  ck_assert_str_eq(s21_val, std_val);
  printf("--------------------------\n");
}

START_TEST(test_sscanf_s_basic) {
  test_sscanf_s_helper("HelloWorld", "%s", "Базовая строка", 's');
}
END_TEST

START_TEST(test_sscanf_s_leading_spaces) {
  test_sscanf_s_helper("   Hello", "%s", "Строка с ведущими пробелами", 's');
}
END_TEST

START_TEST(test_sscanf_s_width) {
  test_sscanf_s_helper("abcdef", "%3s", "Ограничение ширины: 3 символа", 's');
}
END_TEST

START_TEST(test_sscanf_s_stop_at_space) {
  test_sscanf_s_helper("Hello World", "%s", "Считывание до пробела", 's');
}
END_TEST

Suite *s21_sscanf_s_suite(void) {
  Suite *s = suite_create("s21_sscanf_s");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_sscanf_s_basic);
  tcase_add_test(tc, test_sscanf_s_leading_spaces);
  tcase_add_test(tc, test_sscanf_s_width);
  tcase_add_test(tc, test_sscanf_s_stop_at_space);

  suite_add_tcase(s, tc);
  return s;
}

static void test_sscanf_percent_helper(const char *input, const char *format,
                                       const char *message) {
  int s21_ret = s21_sscanf(input, format);
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-security"
  int std_ret = sscanf(input, format);
#pragma GCC diagnostic pop
  printf("=== Тестирование спецификатора: %% ===\n");
  printf("Тест: %s\n", message);
  printf("Входные данные: '%s', format: '%s'\n", input, format);
  printf("s21_sscanf вернул: %d\n", s21_ret);
  printf("sscanf вернул:     %d\n", std_ret);
  ck_assert_int_eq(s21_ret, std_ret);
}

START_TEST(test_sscanf_percent_basic) {
  test_sscanf_percent_helper("%", "%%", "Ожидается символ '%' во входе");
}
END_TEST

START_TEST(test_sscanf_percent_in_text) {
  test_sscanf_percent_helper("abc%def", "abc%%def",
                             "Литеральный процент в середине строки");
}
END_TEST

START_TEST(test_sscanf_percent_fail) {
  test_sscanf_percent_helper(
      "abc", "ab%%c", "Ожидается символ '%', но его нет во входной строке");
}
END_TEST

Suite *s21_sscanf_percent_suite(void) {
  Suite *s = suite_create("s21_sscanf_percent");
  TCase *tc = tcase_create("Core");
  tcase_add_test(tc, test_sscanf_percent_basic);
  tcase_add_test(tc, test_sscanf_percent_in_text);
  tcase_add_test(tc, test_sscanf_percent_fail);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(test_sscanf_star_int) {
  int value_s21 = 0, value_std = 0;
  int ret_s21 = s21_sscanf("123 456", "%*d %d", &value_s21);
  int ret_std = sscanf("123 456", "%*d %d", &value_std);
  printf("=== Тест: Подавление присваивания для int ===\n");
  printf("Входные данные: '123 456', формат: '%%*d %%d'\n");
  printf("s21_sscanf: ret = %d, value = %d\n", ret_s21, value_s21);
  printf("sscanf:     ret = %d, value = %d\n", ret_std, value_std);
  ck_assert_int_eq(ret_s21, ret_std);
  ck_assert_int_eq(value_s21, value_std);
}
END_TEST

START_TEST(test_sscanf_star_string) {
  char buffer_s21[50] = {0};
  char buffer_std[50] = {0};
  int ret_s21 = s21_sscanf("Hello World", "%*s %s", buffer_s21);
  int ret_std = sscanf("Hello World", "%*s %s", buffer_std);
  printf("=== Тест: Подавление присваивания для строки ===\n");
  printf("Входные данные: 'Hello World', формат: '%%*s %%s'\n");
  printf("s21_sscanf: ret = %d, buffer = '%s'\n", ret_s21, buffer_s21);
  printf("sscanf:     ret = %d, buffer = '%s'\n", ret_std, buffer_std);
  ck_assert_int_eq(ret_s21, ret_std);
  ck_assert_str_eq(buffer_s21, buffer_std);
}
END_TEST

START_TEST(test_sscanf_star_combined) {
  int int_val_s21 = 0, int_val_std = 0;
  char str_s21[50] = {0};
  char str_std[50] = {0};
  int ret_s21 = s21_sscanf("100 200 SkipThis KeepThis", "%*d %d %*s %s",
                           &int_val_s21, str_s21);
  int ret_std = sscanf("100 200 SkipThis KeepThis", "%*d %d %*s %s",
                       &int_val_std, str_std);
  printf("=== Тест: Комбинированное подавление присваивания ===\n");
  printf(
      "Входные данные: '100 200 SkipThis KeepThis', формат: '%%*d %%d %%*s "
      "%%s'\n");
  printf("s21_sscanf: ret = %d, int = %d, string = '%s'\n", ret_s21,
         int_val_s21, str_s21);
  printf("sscanf:     ret = %d, int = %d, string = '%s'\n", ret_std,
         int_val_std, str_std);
  ck_assert_int_eq(ret_s21, ret_std);
  ck_assert_int_eq(int_val_s21, int_val_std);
  ck_assert_str_eq(str_s21, str_std);
}
END_TEST

Suite *s21_sscanf_star_suite(void) {
  Suite *s = suite_create("s21_sscanf_star");
  TCase *tc = tcase_create("Core");
  tcase_add_test(tc, test_sscanf_star_int);
  tcase_add_test(tc, test_sscanf_star_string);
  tcase_add_test(tc, test_sscanf_star_combined);
  suite_add_tcase(s, tc);
  return s;
}

int sscanf_tests() {
  int number_failed = 0;

  Suite *sscanf_c = s21_sscanf_c_suite();
  Suite *sscanf_d = s21_sscanf_d_suite();
  Suite *sscanf_i = s21_sscanf_i_suite();
  Suite *sscanf_feg = s21_sscanf_feg_suite();
  Suite *sscanf_o = s21_sscanf_o_suite();
  Suite *sscanf_s = s21_sscanf_s_suite();
  Suite *sscanf_u = s21_sscanf_u_suite();
  Suite *sscanf_x = s21_sscanf_x_suite();
  Suite *sscanf_X = s21_sscanf_X_suite();
  Suite *sscanf_mixed = s21_sscanf_mixed_suite();
  Suite *sscanf_p = s21_sscanf_p_suite();
  Suite *sscanf_n = s21_sscanf_n_suite();
  Suite *sscanf_percent = s21_sscanf_percent_suite();
  Suite *sscanf_star = s21_sscanf_star_suite();

  SRunner *sr = srunner_create(sscanf_c);
  srunner_add_suite(sr, sscanf_d);
  srunner_add_suite(sr, sscanf_i);
  srunner_add_suite(sr, sscanf_feg);
  srunner_add_suite(sr, sscanf_o);
  srunner_add_suite(sr, sscanf_s);
  srunner_add_suite(sr, sscanf_u);
  srunner_add_suite(sr, sscanf_x);
  srunner_add_suite(sr, sscanf_X);
  srunner_add_suite(sr, sscanf_mixed);
  srunner_add_suite(sr, sscanf_p);
  srunner_add_suite(sr, sscanf_n);
  srunner_add_suite(sr, sscanf_percent);
  srunner_add_suite(sr, sscanf_star);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}

int main() {
  if (!string_tests()) {
    printf(
        "\n\n\n\n**************************************************************"
        "*\n");
    printf(
        "\n\n\n\nТесты для простых функций библиотеки стринг прошли "
        "успешно!\n\n\n\n\n");
    printf(
        "***************************************************************"
        "\n\n\n\n");
  } else {
    printf(
        "\n\n\n\n**************************************************************"
        "*\n");
    printf(
        "\n\n\n\nТесты для простых функций библиотеки стринг не "
        "прошли...\n\n\n\n\n");
    printf(
        "***************************************************************"
        "\n\n\n\n");
  }

  if (!sprintf_tests()) {
    printf(
        "\n\n\n\n**************************************************************"
        "*\n");
    printf("\n\n\n\nТесты для sprintf прошли успешно!\n\n\n\n\n");
    printf(
        "***************************************************************"
        "\n\n\n\n");
  } else {
    printf(
        "\n\n\n\n**************************************************************"
        "*\n");
    printf("\n\n\n\nТесты для sprintf не прошли...\n\n\n\n\n");
    printf(
        "***************************************************************"
        "\n\n\n\n");
  }

  if (!sscanf_tests()) {
    printf(
        "\n\n\n\n**************************************************************"
        "*\n");
    printf("\n\n\n\nТесты для sscanf прошли успешно!\n\n\n\n\n");
    printf(
        "***************************************************************"
        "\n\n\n\n");
  } else {
    printf(
        "\n\n\n\n**************************************************************"
        "*\n");
    printf("\n\n\n\nТесты для sscanf не прошли...\n\n\n\n\n");
    printf(
        "***************************************************************"
        "\n\n\n\n");
  }
}
