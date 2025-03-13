#include "s21_string.h"

int s21_isspace(unsigned char ch) {
  return (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r' || ch == '\v' ||
          ch == '\f');
}

void skip_format_whitespace(char **ptr_format, char **ptr_str) {
  while (**ptr_format && s21_isspace((unsigned char)**ptr_format)) {
    (*ptr_format)++;
    while (**ptr_str && s21_isspace((unsigned char)**ptr_str)) {
      (*ptr_str)++;
    }
  }
}

void get_data(Specifier_sscanf *specs, char **ptr_str) {
  while (**ptr_str && isspace((unsigned char)**ptr_str)) {
    (*ptr_str)++;
  }

  char *ptr_data = specs->data;
  while (**ptr_str && !isspace((unsigned char)**ptr_str)) {
    if (specs->size + 1 >= specs->alloc_size) {
      specs->alloc_size *= 2;
      char *new_data = realloc(specs->data, specs->alloc_size);
      if (!new_data) {
        specs->error = 1;
        s21_strcpy(specs->error_message, s21_strerror(12));
        return;
      }
      specs->data = new_data;
      ptr_data = specs->data + specs->size;
    }
    *ptr_data++ = **ptr_str;
    specs->size++;
    (*ptr_str)++;
  }
  *ptr_data = '\0';
}

int parse_digit(char ch, int base) {
  int digit = -1;

  if (base == 8 || base == 10) {
    char max_num = (base == 8) ? '7' : '9';
    if (ch >= '0' && ch <= max_num) {
      digit = ch - '0';
    }
  } else if (base == 16) {
    if (ch >= '0' && ch <= '9') {
      digit = ch - '0';
    } else if (ch >= 'a' && ch <= 'f') {
      digit = ch - 'a' + 10;
    } else if (ch >= 'A' && ch <= 'F') {
      digit = ch - 'A' + 10;
    }
  }

  return (digit >= 0 && digit < base) ? digit : -1;
}

void get_data_for_c(Specifier_sscanf *specs, char **ptr_str) {
  char *ptr_data = (char *)specs->data;
  int limit = (specs->width > 0) ? specs->width : 1;

  while (**ptr_str && specs->size < limit) {
    if (specs->size + 1 >= specs->alloc_size) {
      specs->alloc_size *= 2;
      specs->data = realloc(specs->data, specs->alloc_size);

      if (!specs->data) {
        return;
      }

      ptr_data = specs->data + specs->size;
    }

    *ptr_data++ = **ptr_str;
    (*ptr_str)++;
    specs->size++;
  }
}

void get_data_for_s(Specifier_sscanf *specs, char **ptr_str) {
  char *ptr_data = (char *)specs->data;
  int limit = (specs->width > 0) ? specs->width : 2147483647;

  while (s21_isspace((unsigned char)**ptr_str)) {
    (*ptr_str)++;
  }

  while (**ptr_str && !s21_isspace((unsigned char)**ptr_str) &&
         specs->size < limit) {
    if (specs->size + 1 >= specs->alloc_size) {
      specs->alloc_size *= 2;
      specs->data = realloc(specs->data, specs->alloc_size);

      if (!specs->data) {
        return;
      }

      ptr_data = specs->data + specs->size;
    }

    *ptr_data++ = **ptr_str;
    (*ptr_str)++;
    specs->size++;
  }
  *ptr_data = '\0';
}

void handle_c_specifier_scanf(Specifier_sscanf *specs, va_list *args) {
  char *out = va_arg(*args, char *);

  int width = (specs->width > 0) ? specs->width : 1;
  if (specs->size < width) width = specs->size;

  for (int i = 0; i < width; i++) {
    out[i] = specs->data[i];
  }
  specs->count_var = 1;
}

void handle_s_specifier_scanf(Specifier_sscanf *specs, va_list *args) {
  if (specs->size == 0) {
    specs->count_var = 0;
    return;
  }

  char *out = va_arg(*args, char *);
  int width = (specs->width > 0) ? specs->width : specs->size;
  if (width > specs->size) {
    width = specs->size;
  }

  for (int i = 0; i < width; i++) {
    out[i] = specs->data[i];
  }

  out[width] = '\0';
  specs->count_var = 1;
}

void handle_percent_specifier_scanf(Specifier_sscanf *specs, char **ptr_str) {
  while (**ptr_str && s21_isspace((unsigned char)**ptr_str)) {
    (*ptr_str)++;
  }

  if (**ptr_str == '%') {
    (*ptr_str)++;
  } else {
    specs->error = 1;
    s21_strcpy(specs->error_message, "Expected '%' in input");
  }
}

void handle_d_specifier_scanf(Specifier_sscanf *specs, va_list *args,
                              char **str_ptr) {
  const char *str = specs->data;
  int index = 0;
  int sign = 1;
  long long result = 0;
  int digits_found = 0;

  if (str[index] == '-') {
    sign = -1;
    index++;
  } else if (str[index] == '+') {
    index++;
  }

  int digit = parse_digit(str[index], 10);
  while (digit != -1) {
    result = result * 10 + digit;
    index++;
    digit = parse_digit(str[index], 10);
    digits_found++;
  }
  result *= sign;

  if (digits_found > 0) {
    specs->count_var = 1;

    if (specs->short_h) {
      short *ptr = va_arg(*args, short *);
      *ptr = (short)result;
    } else if (specs->long_l) {
      long *ptr = va_arg(*args, long *);
      *ptr = (long)result;
    } else {
      int *ptr = va_arg(*args, int *);
      *ptr = (int)result;
    }
  }

  if (*str_ptr) {
    *str_ptr -= (specs->size - index);
    specs->size = index;
  }
}

void handle_i_specifier_scanf(Specifier_sscanf *specs, va_list *args) {
  const char *str = specs->data;
  int index = 0;
  int sign = 1;
  int base = 10;
  long long result = 0;
  int digits_found = 0;
  if (str[index] == '-') {
    sign = -1;
    index++;
  } else if (str[index] == '+') {
    index++;
  }
  if (str[index] == '0') {
    base = 8;
    index++;
    if (str[index] == 'x' || str[index] == 'X') {
      base = 16;
      index++;
    }
  }
  int digit = parse_digit(str[index], base);
  while (digit != -1) {
    result = result * base + digit;
    index++;
    digit = parse_digit(str[index], base);
    digits_found++;
  }
  result *= sign;
  if (digits_found > 0) {
    if (specs->short_h) {
      short *ptr = va_arg(*args, short *);
      *ptr = (short)result;
    } else if (specs->long_l) {
      long *ptr = va_arg(*args, long *);
      *ptr = (long)result;
    } else {
      int *ptr = va_arg(*args, int *);
      *ptr = (int)result;
    }
    specs->count_var = 1;
  }
}

long double get_float(const char *str, Specifier_sscanf *specs) {
  long double num = 0.0;
  int i = 0;

  int num_sign = 1;
  if (str[0] == '-') {
    num_sign = -1;
    i++;
  } else if (str[0] == '+') {
    i++;
  }

  int digits_found = 0;
  while (str[i] != '\0' && str[i] != '.') {
    if (str[i] < '0' || str[i] > '9') break;
    num = num * 10 + (str[i] - '0');
    i++;
    digits_found++;
  }

  if (str[i] == '.') {
    i++;
    long double degree = -1;
    while (str[i] != '\0' && str[i] != 'e' && str[i] != 'E') {
      if (str[i] < '0' || str[i] > '9') break;
      num += (str[i] - '0') * powl(10.0L, degree);
      degree--;
      i++;
    }
  }
  if (digits_found > 0) {
    num *= num_sign;
    specs->count_var = 1;
  }

  return num;
}

long double get_e(const char *str, Specifier_sscanf *specs) {
  long double num = get_float(str, specs);
  long double exponent = 0.0;

  char *e_pos = s21_strchr(str, 'e');
  if (!e_pos) e_pos = s21_strchr(str, 'E');

  if (e_pos) {
    int e_sign = 1;
    e_pos++;
    if (*e_pos == '-') {
      e_sign = -1;
      e_pos++;
    } else if (*e_pos == '+') {
      e_pos++;
    }

    while (*e_pos >= '0' && *e_pos <= '9') {
      exponent = exponent * 10.0L + (*e_pos - '0');
      e_pos++;
    }
    exponent *= e_sign;
  }

  return num * powl(10.0L, exponent);
}

void handle_feg_specifier_scanf(Specifier_sscanf *specs, va_list *args) {
  int width = specs->width ? specs->width : specs->size;
  char str[1024] = {0};
  s21_strncpy(str, specs->data, width);
  str[width] = '\0';

  void *ptr = S21_NULL;

  if (specs->long_l) {
    ptr = va_arg(*args, double *);
    *(double *)ptr = (double)get_e(str, specs);
  } else if (specs->long_long_L) {
    ptr = va_arg(*args, long double *);
    *(long double *)ptr = (long double)get_e(str, specs);
  } else {
    ptr = va_arg(*args, float *);
    *(float *)ptr = (float)get_e(str, specs);
  }
}

void handle_uox_specifier_scanf(Specifier_sscanf *specs, va_list *args) {
  int width = specs->width ? specs->width : specs->size;
  char str[1024];
  s21_strncpy(str, specs->data, width);
  str[width] = '\0';
  char *current = str;
  if (current[0] == '0' &&
      (specs->numeral_system == 8 || specs->numeral_system == 16)) {
    if (s21_strlen(current) > 1) {
      current++;
      if (specs->numeral_system == 16 &&
          (current[0] == 'x' || current[0] == 'X')) {
        if (s21_strlen(current) > 1) {
          current++;
        } else {
          current--;
        }
      }
    }
  }

  long long int value = 0;
  int digit;
  int counter = 0;
  while ((digit = parse_digit(*current, specs->numeral_system)) != -1) {
    value = value * specs->numeral_system + digit;
    current++;
    counter++;
  }

  void *ptr = S21_NULL;

  if (specs->short_h) {
    ptr = va_arg(*args, int *);
    *(unsigned short int *)ptr = (unsigned short int)value;
  } else if (specs->long_l) {
    ptr = va_arg(*args, unsigned long int *);
    *(unsigned long int *)ptr = (unsigned long int)value;
  } else {
    ptr = va_arg(*args, unsigned int *);
    *(unsigned int *)ptr = (unsigned int)value;
  }

  if (counter != 0) {
    specs->count_var = 1;
  }
}

void handle_p_specifier_scanf(Specifier_sscanf *specs, va_list *args) {
  const char *str = specs->data;
  uintptr_t value = 0;
  int index = 0;
  int digit_parsed = 0;

  if (str[index] == '0' && (str[index + 1] == 'x' || str[index + 1] == 'X')) {
    index += 2;
  }

  int digit = parse_digit(str[index], 16);
  while (digit != -1) {
    value = value * 16 + (uintptr_t)digit;
    index++;
    digit_parsed++;
    digit = parse_digit(str[index], 16);
  }

  if (digit_parsed > 0) {
    void **ptr = va_arg(*args, void **);
    if (ptr) {
      *ptr = (void *)value;
      specs->count_var = 1;
    }
  }
}

void handle_n_specifier_scanf(const Specifier_sscanf *specs, va_list *args,
                              int read_chars) {
  if (specs->short_h) {
    short *val_s = va_arg(*args, short *);
    *val_s = (short)read_chars;
  } else if (specs->long_l) {
    long *val_l = va_arg(*args, long *);
    *val_l = (long)read_chars;
  } else {
    int *val_i = va_arg(*args, int *);
    *val_i = (int)read_chars;
  }
}

void parse_lenght_scanf(Specifier_sscanf *specs, char **ptr_format) {
  switch (**ptr_format) {
    case 'h':
      specs->short_h = 1;
      (*ptr_format)++;
      break;
    case 'l':
      specs->long_l = 1;
      (*ptr_format)++;
      break;
    case 'L':
      specs->long_long_L = 1;
      (*ptr_format)++;
      break;
  }
}

int get_num_scanf(char **ptr_format, Specifier_sscanf *specs) {
  int num = 0;

  if (**ptr_format == '*') {
    specs->skip = 1;
  } else {
    while (**ptr_format) {
      if (**ptr_format >= '0' && **ptr_format <= '9') {
        num *= 10;
        num += **ptr_format - '0';
      } else {
        break;
      }

      (*ptr_format)++;
    }
  }

  return num;
}

void parse_width_scanf(Specifier_sscanf *specs, char **ptr_format) {
  specs->width = get_num_scanf(ptr_format, specs);
}

void parser_scanf(Specifier_sscanf *specs, char **ptr_format) {
  parse_width_scanf(specs, ptr_format);
  parse_lenght_scanf(specs, ptr_format);
}

void retrieve_data_for_specifier(Specifier_sscanf *specs, char **ptr_format,
                                 char **ptr_str) {
  if (**ptr_format != 'n') {
    if (**ptr_format == 'c') {
      get_data_for_c(specs, ptr_str);
    } else if (**ptr_format == 's') {
      get_data_for_s(specs, ptr_str);
    } else {
      get_data(specs, ptr_str);
    }
  }
}

void process_specifier_scanf(Specifier_sscanf *specs, char **ptr_format,
                             char **ptr_str, va_list *args_ptr,
                             const char *input_start) {
  specs->data = (char *)calloc(BUFFER_SIZE, sizeof(char));
  specs->alloc_size = BUFFER_SIZE;

  if (!specs->data) {
    specs->error = 1;
    s21_strcpy(specs->error_message, s21_strerror(12));
    return;
  }
  retrieve_data_for_specifier(specs, ptr_format, ptr_str);
  if (specs->skip) {
    return;
  }
  switch (**ptr_format) {
    case 'c':  // 1
      handle_c_specifier_scanf(specs, args_ptr);
      break;
    case 'd':  // 2
      handle_d_specifier_scanf(specs, args_ptr, ptr_str);
      break;
    case 'i':  // 3
      handle_i_specifier_scanf(specs, args_ptr);
      break;
    case 'f':  // 6
    case 'e':  // 4
    case 'E':  // 5
    case 'g':  // 7
    case 'G':  // 8
      handle_feg_specifier_scanf(specs, args_ptr);
      break;
    case 'o':  // 9
      specs->numeral_system = 8;
      handle_uox_specifier_scanf(specs, args_ptr);
      break;
    case 's':  // 10
      handle_s_specifier_scanf(specs, args_ptr);
      break;
    case 'u':  // 11
      specs->numeral_system = 10;
      handle_uox_specifier_scanf(specs, args_ptr);
      break;
    case 'x':  // 12
      specs->numeral_system = 16;
      handle_uox_specifier_scanf(specs, args_ptr);
      break;
    case 'X':  // 13
      specs->numeral_system = 16;
      specs->upper_case = 1;
      handle_uox_specifier_scanf(specs, args_ptr);
      break;
    case 'p':  // 14
      handle_p_specifier_scanf(specs, args_ptr);
      break;
    case 'n':  // 15
      int read_chars = (int)(*ptr_str - input_start);
      handle_n_specifier_scanf(specs, args_ptr, read_chars);
      break;
    case '%':  // 16
      handle_percent_specifier_scanf(specs, ptr_str);
      break;
    default:
      specs->error = 1;
      s21_strcpy(specs->error_message, "Неизвестный спецификатор");
      break;
  }

  if (specs->error) {
    free(specs->data);
    specs->data = NULL;
  }
}

int s21_sscanf(const char *str, const char *format, ...) {
  char *ptr_str = (char *)str;
  char *ptr_format = (char *)format;
  int count_var = 0;

  va_list args;
  va_start(args, format);

  while (*ptr_format) {
    if (s21_isspace((unsigned char)*ptr_format)) {
      skip_format_whitespace(&ptr_format, &ptr_str);
      continue;
    }

    if (*ptr_format == '%') {
      ptr_format++;
      Specifier_sscanf specs = {0};
      specs.width = -1;
      parser_scanf(&specs, &ptr_format);

      process_specifier_scanf(&specs, &ptr_format, &ptr_str, &args, str);

      if (specs.error) {
        if (specs.data) {
          free(specs.data);
          // fprintf(stderr, "%s\n", specs.error_message);
        }
        break;
      }

      ptr_format++;
      free(specs.data);
      count_var += specs.count_var;
    } else {
      ptr_format++;
    }
  }

  va_end(args);
  return count_var;
}
