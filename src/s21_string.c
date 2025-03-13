#include "s21_string.h"

#ifdef __linux__
#include "linux_errors.h"
#elif defined(__APPLE__)
#include "mac_errors.h"
#endif

int is_valid_error(int errnum, size_t error_count);
char *s21_strcpy(char *restrict dest, const char *restrict src);
int is_trim_char(char c, const char *trim_chars);

// Support functions
int is_valid_error(int errnum, size_t error_count) {
  return errnum >= 0 && errnum < (int)error_count;
}

char *s21_strcpy(char *restrict dest, const char *restrict src) {
  char *dest_start = dest;
  while (*src) {
    *dest++ = *src++;
  }
  *dest = '\0';
  return dest_start;
}

int is_trim_char(char c, const char *trim_chars) {
  while (*trim_chars) {
    if (*trim_chars == c) {
      return 1;
    }

    trim_chars++;
  }

  return 0;
}

// Path 1
// 1
void *s21_memchr(const void *str, int c, s21_size_t n) {
  const unsigned char *ptr = (const unsigned char *)str;
  unsigned char ch = (unsigned char)c;
  void *res;
  res = S21_NULL;

  for (size_t i = 0; i < n; i++) {
    if (ptr[i] == ch) {
      res = (void *)(ptr + i);
      break;
    }
  }

  return res;
}

// 2
int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const unsigned char *ptr1 = (const unsigned char *)str1;
  const unsigned char *ptr2 = (const unsigned char *)str2;
  int res = 0;

  for (s21_size_t i = 0; i < n; i++) {
    if (ptr1[i] != ptr2[i]) {
      res = ptr1[i] - ptr2[i];
      break;
    }
  }

  return res;
}

// 3
void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char *dest_buf = dest;
  const char *src_buf = src;

  for (int i = 0; i < (int)n; i++) {
    *(dest_buf + i) = *(src_buf + i);
  }

  return dest;
}

// 4
void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *ptr = (unsigned char *)str;
  for (s21_size_t i = 0; i < n; i++) {
    ptr[i] = (unsigned char)c;
  }
  return str;
}

// 5
char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  if (!dest || !src) {
    return S21_NULL;
  }

  char *dest_start = dest;

  while (*dest) {
    dest++;
  }

  while (*src && n > 0) {
    *dest++ = *src++;
    n--;
  }

  *dest = '\0';

  return dest_start;
}

// 6
char *s21_strchr(const char *str, int c) {
  char *res;
  res = S21_NULL;

  while (*str != '\0') {
    if (*str == (char)c) {
      res = (char *)str;
      break;
    }
    str++;
  }

  if (c == '\0') {
    res = (char *)str;
  }

  return res;
}

// 7
int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int res = 0;
  for (s21_size_t i = 0; i < n; i++) {
    if (str1[i] != str2[i] || str1[i] == '\0') {
      res = (unsigned char)str1[i] - (unsigned char)str2[i];
      break;
    }
  }
  return res;
}

// 8
char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t i;

  for (i = 0; i < n && src[i] != '\0'; i++) {
    dest[i] = src[i];
  }

  for (; i < n; i++) {
    dest[i] = '\0';
  }

  return dest;
}

// 9
s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t count = 0;
  int found = 0;

  for (; str1[count] != '\0' && !found; count++) {
    for (s21_size_t j = 0; str2[j] != '\0'; j++) {
      if (str1[count] == str2[j]) {
        found = 1;
        break;
      }
    }
  }

  return found ? count - 1 : count;
}

// 10
char *s21_strerror(int errnum) {
  static char error_message[BUFFER_SIZE];

#ifdef __linux__
  const char **errors = linux_errors;
  size_t error_count = LINUX_ERROR_COUNT;
#elif defined(__APPLE__)
  const char **errors = mac_errors;
  size_t error_count = MAC_ERROR_COUNT;
#else
  return "Unknown operating system";
#endif

  if (is_valid_error(errnum, error_count)) {
    snprintf(error_message, BUFFER_SIZE, "%s", errors[errnum]);
  } else {
#ifdef __linux__
    snprintf(error_message, BUFFER_SIZE, "Unknown error %d", errnum);
#elif defined(__APPLE__)
    snprintf(error_message, BUFFER_SIZE, "Unknown error: %d", errnum);
#endif
  }
  return error_message;
}

// 11
s21_size_t s21_strlen(const char *str) {
  s21_size_t len = 0;
  while (str[len]) {
    len++;
  }
  return len;
}

// 12
char *s21_strpbrk(const char *str1, const char *str2) {
  const char *ptr1 = str1;
  const char *res = S21_NULL;

  while (*ptr1) {
    for (const char *ptr2 = str2; *ptr2; ptr2++) {
      if (*ptr1 == *ptr2) {
        res = ptr1;
        break;
      }
    }

    if (res) {
      break;
    }
    ptr1++;
  }

  return (char *)res;
}

// 13
char *s21_strrchr(const char *str, int c) {
  unsigned char c_char = (unsigned char)c;
  int length = s21_strlen(str) + 1;
  char *last_char_pos = S21_NULL;

  for (int i = 0; i < length; i++) {
    if (str[i] == c_char) {
      last_char_pos = (char *)(str + i);
    }
  }

  return last_char_pos;
}

// 14
char *s21_strstr(const char *haystack, const char *needle) {
  if (*needle == '\0') {
    return (char *)haystack;
  }

  while (*haystack != '\0') {
    const char *h = haystack;
    const char *n = needle;

    while (*h != '\0' && *n != '\0' && *h == *n) {
      h++;
      n++;
    }

    if (*n == '\0') {
      return (char *)haystack;
    }

    haystack++;
  }

  return S21_NULL;
}

// 15
char *s21_strtok(char *str, const char *delim) {
  static char *save_ptr = S21_NULL;
  if (str == S21_NULL) {
    str = save_ptr;
  }

  if (str == S21_NULL) {
    return S21_NULL;
  }

  while (*str && s21_strchr(delim, *str)) {
    str++;
  }

  if (*str == '\0') {
    save_ptr = S21_NULL;
    return S21_NULL;
  }

  char *token_start = str;

  while (*str && !s21_strchr(delim, *str)) {
    str++;
  }

  if (*str) {
    *str = '\0';
    save_ptr = str + 1;
  } else {
    save_ptr = S21_NULL;
  }

  return token_start;
}

// Path 2
// 1
void *s21_to_upper(const char *str) {
  if (str == S21_NULL) {
    return S21_NULL;
  }

  s21_size_t len = s21_strlen(str);
  char *str_copy = (char *)malloc((len + 1) * sizeof(char));

  if (str_copy == S21_NULL) {
    return S21_NULL;
  }

  for (s21_size_t i = 0; i < len; i++) {
    if (str[i] >= 'a' && str[i] <= 'z') {
      str_copy[i] = str[i] - 32;
    } else {
      str_copy[i] = str[i];
    }
  }

  str_copy[len] = '\0';

  return str_copy;
}

// 2
void *s21_to_lower(const char *str) {
  if (!str) {
    return S21_NULL;
  }

  s21_size_t len = s21_strlen(str);

  char *res = (char *)malloc((len + 1) * sizeof(char));

  if (!res) {
    return S21_NULL;
  }

  for (s21_size_t i = 0; i < len; i++) {
    if (str[i] >= 'A' && str[i] <= 'Z') {
      res[i] = str[i] + 32;
    } else {
      res[i] = str[i];
    }
  }

  res[len] = '\0';

  return res;
}

// 3
void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  if (!src || !str) {
    return S21_NULL;
  }

  s21_size_t len_src = s21_strlen(src);
  s21_size_t len_str = s21_strlen(str);

  if (start_index > len_src) {
    return S21_NULL;
  }

  s21_size_t len_total = len_src + len_str;

  char *new_str = (char *)malloc((len_total + 1) * sizeof(char));
  if (!new_str) {
    return S21_NULL;
  }

  for (s21_size_t i = 0; i < start_index; i++) {
    new_str[i] = src[i];
  }

  for (s21_size_t i = 0; i < len_str; i++) {
    new_str[start_index + i] = str[i];
  }

  for (s21_size_t i = start_index; i < len_src; i++) {
    new_str[len_str + i] = src[i];
  }

  new_str[len_total] = '\0';

  return new_str;
}

// 4
void *s21_trim(const char *src, const char *trim_chars) {
  if (!src) {
    return S21_NULL;
  }

  if (!trim_chars) {
    return S21_NULL;
  }

  s21_size_t str_len = s21_strlen(src);

  if (str_len == 0) {
    char *empty_res = (char *)malloc(sizeof(char));
    if (empty_res) {
      empty_res[0] = '\0';
    }

    return empty_res;
  }

  s21_size_t start = 0;
  s21_size_t end = str_len;

  while (start < end && is_trim_char(src[start], trim_chars)) {
    start++;
  }

  while (end > start && is_trim_char(src[end - 1], trim_chars)) {
    end--;
  }

  s21_size_t res_len = end > start ? end - start : 0;

  char *res_str = (char *)malloc((res_len + 1) * sizeof(char));

  if (!res_str) {
    return S21_NULL;
  }

  s21_memcpy(res_str, src + start, res_len);

  res_str[res_len] = '\0';

  return res_str;
}
