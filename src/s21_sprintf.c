#include "s21_string.h"

void parse_flags(Specifier *specs, char **ptr_format) {
  while (**ptr_format) {
    if (**ptr_format == '-')
      specs->left_justification = 1;
    else if (**ptr_format == '+')
      specs->sign = 1;
    else if (**ptr_format == '#')
      specs->hash = 1;
    else if (**ptr_format == '0')
      specs->leading_zeros = 1;
    else if (**ptr_format == ' ')
      specs->space = 1;
    else
      break;
    (*ptr_format)++;
  }

  if (specs->sign && specs->space) specs->space = 0;
  if (specs->leading_zeros && specs->left_justification)
    specs->leading_zeros = 0;
}

int get_num(char **ptr_format, va_list args) {
  int num = 0;

  if (**ptr_format == '*') {
    num = va_arg(args, int);
    (*ptr_format)++;
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

void parse_width(Specifier *specs, char **ptr_format, va_list args) {
  specs->width = get_num(ptr_format, args);
  if (specs->width < 0) {
    specs->left_justification = 1;
    specs->width *= -1;
  }
}

void parse_precision(Specifier *specs, char **ptr_format, va_list args) {
  if (**ptr_format == '.') {
    specs->dot = 1;
    (*ptr_format)++;
    specs->precision = get_num(ptr_format, args);
    if (specs->precision < 0) specs->precision = 6;
  }
}

void parse_lenght(Specifier *specs, char **ptr_format) {
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

void parser(Specifier *specs, char **ptr_format, va_list args) {
  parse_flags(specs, ptr_format);
  parse_width(specs, ptr_format, args);
  parse_precision(specs, ptr_format, args);
  parse_lenght(specs, ptr_format);
}

void cat_result(Specifier *specs, char *str) {
  const char *ptr_str = (char *)str;
  char *ptr_result = (char *)specs->result;

  while (*ptr_str) {
    if (specs->size + 1 >= specs->alloc_size) {
      specs->alloc_size *= 2;
      specs->result = realloc(specs->result, specs->alloc_size);

      if (!specs->result) {
        specs->error = 1;
        s21_strcpy(specs->error_message, s21_strerror(12));
        return;
      }

      ptr_result = specs->result + specs->size;
    }

    *ptr_result++ = *ptr_str++;
    specs->size++;
  }
  *ptr_result = '\0';
}

void handle_c_specifier(Specifier *specs, va_list args) {
  int width = (specs->width > 0) ? specs->width : 1;
  char ch = (char)va_arg(args, int);
  if (!ch) {
    specs->error = 1;
    s21_strcpy(specs->error_message,
               "Отсутствует аргумент для спецификатора с");
    return;
  }

  char *str = (char *)calloc(width + 1, sizeof(char));
  if (!str) {
    specs->error = 1;
    s21_strcpy(specs->error_message, s21_strerror(12));
    return;
  }

  if (specs->left_justification) {
    str[0] = ch;
    for (int i = 1; i < width; i++) {
      str[i] = ' ';
    }
  } else {
    for (int i = 0; i < width - 1; i++) {
      str[i] = ' ';
    }
    str[width - 1] = ch;
  }

  str[width] = '\0';

  cat_result(specs, str);
  free(str);
}

long long get_signed_argument(va_list args, const Specifier *specs) {
  long long num = 0;
  if (specs->long_long_L) {
    num = va_arg(args, long long);
  } else if (specs->long_l) {
    num = va_arg(args, long);
  } else if (specs->short_h) {
    num = (short)va_arg(args, int);
  } else {
    num = va_arg(args, int);
  }
  return num;
}

void convert_abs_to_string(unsigned long long abs_num, char *num_str,
                           int *num_len) {
  *num_len = 0;
  if (abs_num == 0) {
    num_str[(*num_len)++] = '0';
  } else {
    while (abs_num > 0 && *num_len < BUFFER_SIZE - 1) {
      num_str[(*num_len)++] = '0' + (abs_num % 10);
      abs_num /= 10;
    }
    for (int i = 0; i < *num_len / 2; i++) {
      char temp = num_str[i];
      num_str[i] = num_str[*num_len - i - 1];
      num_str[*num_len - i - 1] = temp;
    }
  }
  num_str[*num_len] = '\0';
}

void apply_precision(const Specifier *specs, char *num_str, int *num_len) {
  if (specs->precision > *num_len) {
    int zeros = specs->precision - *num_len;
    char temp[BUFFER_SIZE] = {0};
    for (int i = 0; i < zeros; i++) {
      temp[i] = '0';
    }
    s21_strcpy(temp + zeros, num_str);
    s21_strcpy(num_str, temp);
    *num_len += zeros;
  }
}

int get_sign_char(const Specifier *specs, int is_negative) {
  int sign_char = 0;
  if (is_negative) {
    sign_char = '-';
  } else if (specs->sign) {
    sign_char = '+';
  } else if (specs->space) {
    sign_char = ' ';
  }
  return sign_char;
}

void create_d_result_string_buf(const Specifier *specs, const char *num_str,
                                int num_len, int sign_char, char *result) {
  int number_total = num_len + (sign_char ? 1 : 0);
  int padding = (specs->width > number_total) ? specs->width - number_total : 0;
  int pos = 0;
  if (!specs->left_justification) {
    if (specs->leading_zeros && specs->dot == 0) {
      if (sign_char) {
        result[pos++] = sign_char;
      }
      for (int i = 0; i < padding; i++) {
        result[pos++] = '0';
      }
    } else {
      for (int i = 0; i < padding; i++) {
        result[pos++] = ' ';
      }
      if (sign_char) {
        result[pos++] = sign_char;
      }
    }
  } else {
    if (sign_char) {
      result[pos++] = sign_char;
    }
  }
  for (int i = 0; i < num_len; i++) {
    result[pos++] = num_str[i];
  }
  if (specs->left_justification) {
    for (int i = 0; i < padding; i++) {
      result[pos++] = ' ';
    }
  }
  result[pos] = '\0';
}

void handle_d_specifier(Specifier *specs, va_list args) {
  long long num = get_signed_argument(args, specs);
  int is_negative = (num < 0);
  unsigned long long abs_num =
      is_negative ? -((unsigned long long)num) : (unsigned long long)num;
  char num_str[BUFFER_SIZE] = {0};
  int num_len = 0;
  convert_abs_to_string(abs_num, num_str, &num_len);
  apply_precision(specs, num_str, &num_len);
  int sign_char = get_sign_char(specs, is_negative);
  int number_total = num_len + (sign_char ? 1 : 0);
  int padding = (specs->width > number_total) ? specs->width - number_total : 0;
  int result_size = number_total + padding + 1;
  char *result = malloc(result_size * sizeof(char));
  if (!result) {
    specs->error = 1;
    s21_strcpy(specs->error_message, s21_strerror(12));
    return;
  }
  create_d_result_string_buf(specs, num_str, num_len, sign_char, result);
  cat_result(specs, result);
  free(result);
}

long double get_double(va_list args, const Specifier *specs) {
  long double num = 0;
  if (specs->long_long_L)
    num = va_arg(args, long double);
  else
    num = va_arg(args, double);
  return num;
}

double rounding_float(int precision) { return 0.5 * pow(10, -precision); }

void split_number(long double num, long long *integer_part,
                  long double *fractional_part) {
  *integer_part = (long long)num;
  *fractional_part = num - *integer_part;
}

int convert_int_to_str(long long integer_part, char *int_str) {
  int integer_len = 0;
  if (integer_part == 0) {
    int_str[integer_len++] = '0';
  } else {
    while (integer_part > 0) {
      int_str[integer_len++] = (int)(integer_part % 10) + '0';
      integer_part /= 10;
    }
    for (int i = 0; i < integer_len / 2; i++) {
      char temp = int_str[i];
      int_str[i] = int_str[integer_len - i - 1];
      int_str[integer_len - i - 1] = temp;
    }
  }
  int_str[integer_len] = '\0';
  return integer_len;
}

int convert_fract_to_str(double fractional_part, int precision, char *fract_str,
                         const Specifier *specs) {
  int fractional_len = 0;
  for (int i = 0; i < precision; i++) {
    fractional_part *= 10;
    int digit = (int)fractional_part;
    fract_str[fractional_len++] = '0' + digit;
    fractional_part -= digit;
  }
  if (specs->general && !specs->hash) {
    while (fractional_len > 0 && fract_str[fractional_len - 1] == '0')
      fractional_len--;
  }
  fract_str[fractional_len] = '\0';
  return fractional_len;
}

void add_sign(char **str, int sign, const Specifier *specs) {
  if (sign < 0) {
    **str = '-';
    (*str)++;
  } else if (specs->sign) {
    **str = '+';
    (*str)++;
  } else if (specs->space) {
    **str = ' ';
    (*str)++;
  }
}

char *combine_number(char *str, const char *int_str, int integer_len,
                     const char *fract_str, int fractional_len, int precision) {
  s21_memcpy(str, int_str, integer_len);
  str += integer_len;
  if (precision > 0) {
    s21_memcpy(str, fract_str, fractional_len);
    str += fractional_len;
  }
  *str = '\0';
  return str;
}

int is_inf_or_nan(long double num, int width, Specifier *specs) {
  int flag = 0;
  char err[256] = {0};
  char *ptr_err = err;
  if (isnan(num)) {
    if (width < 3) width = 3;
    s21_memset(ptr_err, ' ', width - 3);
    ptr_err[width - 3] = '\0';
    s21_strncat(err, (specs->upper_case ? "NAN" : "nan"), 3);
    cat_result(specs, err);
    flag = 1;
  }
  if (isinf(num)) {
    if (num > 0) {
      if (width < 3) width = 3;
      s21_memset(ptr_err, ' ', width - 3);
      ptr_err[width - 3] = '\0';
      s21_strncat(err, (specs->upper_case ? "INF" : "inf"), 3);
    } else {
      if (width < 4) width = 4;
      s21_memset(ptr_err, ' ', width - 4);
      ptr_err[width - 4] = '\0';
      s21_strncat(err, (specs->upper_case ? "-INF" : "-inf"), 4);
    }
    cat_result(specs, err);
    flag = 1;
  }
  return flag;
}

void normalize_num(int *exp_degree, long double *num) {
  if (*num == 0.0) return;
  if (*num == 0.000001) {
    *num = 1.0;
    *exp_degree = -6;
  } else {
    while (fabsl(*num) >= 10.0) {
      *num /= 10.0;
      (*exp_degree)++;
    }
    while (fabsl(*num) > 0.0 && fabsl(*num) < 1.0) {
      *num *= 10.0;
      (*exp_degree)--;
    }
  }
}

void exponent_sign(char *exp_str, int exp_degree, char e) {
  *exp_str++ = e;
  if (exp_degree < 0) {
    *exp_str++ = '-';
    exp_degree = -exp_degree;
  } else {
    *exp_str++ = '+';
  }
  int digits[3] = {0};
  int ind = 0;
  do {
    digits[ind++] = exp_degree % 10;
    exp_degree /= 10;
  } while (exp_degree > 0);
  while (ind < 2) {
    digits[ind++] = 0;
  }
  while (ind > 0) {
    *exp_str++ = '0' + digits[--ind];
  }
  *exp_str = '\0';
}

void prepare_floating_point(Specifier *specs, va_list args, long double *num,
                            int *precision, int *sign) {
  *precision = (specs->precision == -1 ? 6 : specs->precision);
  *num = (specs->general ? specs->general_num : get_double(args, specs));
  *sign = (*num > 0 ? 1 : -1);
  double round_val = rounding_float(*precision);
  *num = fabsl(*num + *sign * round_val);
}

void convert_number_parts(long double num, int precision, char *int_str,
                          char *fract_str, int *integer_len,
                          int *fractional_len, const Specifier *specs) {
  long long integer_part = 0;
  long double fractional_part = 0;
  split_number(num, &integer_part, &fractional_part);
  *integer_len = convert_int_to_str(integer_part, int_str);
  if ((precision == 0 && specs->hash) || precision > 0) {
    s21_strncat(int_str, ".", 1);
    (*integer_len)++;
  }
  *fractional_len =
      convert_fract_to_str(fractional_part, precision, fract_str, specs);
}

void format_number_string(const Specifier *specs, int sign, int integer_len,
                          int fractional_len, const char *int_str,
                          const char *fract_str, char *result_str) {
  int precision = (specs->precision == -1 ? 6 : specs->precision);
  int width = specs->width;
  int total_len = integer_len + (precision > 0 ? fractional_len : 0);
  if (sign < 0 || specs->sign || specs->space) {
    total_len++;
  }
  char fill_symbol = (specs->leading_zeros ? '0' : ' ');
  char *ptr = result_str;
  if (!specs->left_justification) {
    if (specs->leading_zeros) add_sign(&ptr, sign, specs);
    if (width > total_len) {
      s21_memset(ptr, fill_symbol, width - total_len);
      ptr += width - total_len;
    }
  }
  if (!specs->leading_zeros) add_sign(&ptr, sign, specs);
  ptr = combine_number(ptr, int_str, integer_len, fract_str, fractional_len,
                       precision);
  if (specs->left_justification) {
    for (int i = 0; i < width - total_len; i++) *ptr++ = fill_symbol;
  }
  *ptr = '\0';
}

void handle_f_specifier(Specifier *specs, va_list args) {
  char result_str[256] = {0};
  char int_str[256] = {0};
  char fract_str[256] = {0};
  long double num;
  int precision, sign;
  prepare_floating_point(specs, args, &num, &precision, &sign);
  if (is_inf_or_nan(num, specs->width, specs) == 1) return;
  int integer_len, fractional_len;
  convert_number_parts(num, precision, int_str, fract_str, &integer_len,
                       &fractional_len, specs);
  format_number_string(specs, sign, integer_len, fractional_len, int_str,
                       fract_str, result_str);
  cat_result(specs, result_str);
}

int prepare_scientific_number(Specifier *specs, va_list args, long double *num,
                              int *precision, int *sign, int *exp_degree) {
  *precision = (specs->precision == -1 ? 6 : specs->precision);
  *num = (specs->general ? specs->general_num : get_double(args, specs));
  if (is_inf_or_nan(*num, specs->width, specs) == 1) return 1;
  *sign = (*num > 0 ? 1 : -1);
  double round_val = rounding_float(*precision);
  *exp_degree = 0;
  normalize_num(exp_degree, num);
  *num = fabsl(*num + *sign * round_val);
  return 0;
}

void convert_scientific_parts(long double num, int precision, char *int_str,
                              char *fract_str, int *integer_len,
                              int *fractional_len, const Specifier *specs) {
  long long integer_part = 0;
  long double fractional_part = 0;
  split_number(num, &integer_part, &fractional_part);
  *integer_len = 1;
  int_str[0] = '0' + (int)(integer_part % 10);
  *fractional_len =
      convert_fract_to_str(fractional_part, precision, fract_str, specs);
  if (((precision == 0 && specs->hash) || precision > 0) &&
      !(!specs->hash && specs->general && *fractional_len == 0)) {
    s21_strncat(int_str, ".", 1);
    (*integer_len)++;
  }
}

void build_exponent_string(const Specifier *specs, int exp_degree,
                           char *exp_str, int *exp_len) {
  *exp_len = (exp_degree < 100 ? 4 : 5);
  char e = (specs->upper_case == 1 ? 'E' : 'e');
  exponent_sign(exp_str, exp_degree, e);
}

void format_scientific_string(Specifier *specs, int sign, int integer_len,
                              int fractional_len, int exp_len,
                              const char *int_str, const char *fract_str,
                              const char *exp_str, char *result_str) {
  int precision = (specs->precision == -1 ? 6 : specs->precision);
  int width = specs->width;
  int total_len = integer_len + (precision > 0 ? fractional_len : 0) + exp_len;
  if (sign < 0 || specs->sign || specs->space) total_len++;
  char fill_symbol = (specs->leading_zeros ? '0' : ' ');
  char *ptr = result_str;
  if (!specs->left_justification) {
    if (specs->leading_zeros) add_sign(&ptr, sign, specs);
    if (width > total_len) {
      s21_memset(ptr, fill_symbol, width - total_len);
      ptr += width - total_len;
    }
  }
  if (!specs->leading_zeros) add_sign(&ptr, sign, specs);
  ptr = combine_number(ptr, int_str, integer_len, fract_str, fractional_len,
                       precision);
  *ptr = '\0';
  s21_strncat(ptr, exp_str, exp_len);
  ptr += total_len;
  if (specs->left_justification) {
    for (int i = 0; i < width - total_len; i++) *ptr++ = ' ';
  }
  *ptr = '\0';
}

void handle_e_specifier(Specifier *specs, va_list args) {
  char result_str[256] = {0};
  char int_str[256] = {0};
  char fract_str[256] = {0};
  char exp_str[6] = {0};
  long double num;
  int precision, sign, exp_degree;
  if (prepare_scientific_number(specs, args, &num, &precision, &sign,
                                &exp_degree)) {
    return;
  }

  int integer_len = 0, fractional_len = 0;
  convert_scientific_parts(num, precision, int_str, fract_str, &integer_len,
                           &fractional_len, specs);
  int exp_len = 0;
  build_exponent_string(specs, exp_degree, exp_str, &exp_len);
  format_scientific_string(specs, sign, integer_len, fractional_len, exp_len,
                           int_str, fract_str, exp_str, result_str);
  cat_result(specs, result_str);
}

void handle_g_specifier(Specifier *specs, va_list args) {
  specs->general = 1;
  long double num = get_double(args, specs);
  specs->general_num = num;
  int width = specs->width;
  if (is_inf_or_nan(num, width, specs) == 1) return;
  int precision;
  switch (specs->precision) {
    case -1:
      precision = 6;
      break;
    case 0:
      precision = 0;
      break;
    default:
      precision = specs->precision;
      break;
  }
  int exp_degree = 0;
  normalize_num(&exp_degree, &num);
  if ((precision > exp_degree) && (exp_degree >= -4)) {
    specs->precision = precision - (exp_degree + 1);
    handle_f_specifier(specs, args);
  } else {
    specs->precision = specs->hash ? 0 : precision - 1;
    handle_e_specifier(specs, args);
  }
}

void handle_s_specifier(Specifier *specs, va_list args) {
  const char *str = va_arg(args, char *);
  if (!str) {
    specs->error = 1;
    s21_strcpy(specs->error_message,
               "Отсутствует аргумент для спецификатора с");
    return;
  }
  s21_size_t size = s21_strlen(str);
  if (specs->precision >= 0 && (s21_size_t)specs->precision < size)
    size = specs->precision;
  int width = (specs->width > (int)size) ? specs->width : (int)size;
  char *res = (char *)calloc(width + 1, sizeof(char));
  if (!res) {
    specs->error = 1;
    s21_strcpy(specs->error_message, s21_strerror(12));
    return;
  }
  int printed = 0;

  if (specs->left_justification) {
    for (s21_size_t i = 0; i < size; i++) {
      res[printed++] = str[i];
    }
    for (s21_size_t i = size; i < (s21_size_t)width; i++) {
      res[printed++] = ' ';
    }
  } else {
    for (s21_size_t i = size; i < (s21_size_t)width; i++) {
      res[printed++] = ' ';
    }
    for (s21_size_t i = 0; i < size; i++) {
      res[printed++] = str[i];
    }
  }

  res[printed] = '\0';

  cat_result(specs, res);
  free(res);
}

void reverse_the_string(char *result, const char *temp, int *index,
                        Specifier *specs) {
  int i = 0;
  while (*index > 0) {
    result[i++] = temp[--(*index)];
  }

  *index = i;

  specs->is_reversed = 1;

  result[i] = '\0';
}

s21_size_t get_size_of_unsigned_long_int(Specifier *specs,
                                         unsigned long int num) {
  s21_size_t result = 0;
  unsigned long int copy_num = num;

  if (copy_num == 0) {
    result = 1;
  } else {
    while (copy_num > 0) {
      copy_num /= specs->numeral_system;
      result++;
    }
  }

  if ((s21_size_t)specs->width > result) {
    result = specs->width;
  }
  if ((s21_size_t)specs->precision > result) {
    result = specs->precision;
  }

  return result;
}

char get_num_char(int num, int upper_case) {
  char flag = '0';
  switch (num) {
    case 10:
      flag = (char)('a' - upper_case * 32);
      break;
    case 11:
      flag = (char)('b' - upper_case * 32);
      break;
    case 12:
      flag = (char)('c' - upper_case * 32);
      break;
    case 13:
      flag = (char)('d' - upper_case * 32);
      break;
    case 14:
      flag = (char)('e' - upper_case * 32);
      break;
    case 15:
      flag = (char)('f' - upper_case * 32);
      break;
  }

  if (0 <= num && num <= 9) flag = (char)(num + 48);
  return flag;
}

void fill_array_with(char *temp, int *index, char filling, int fill_parameter) {
  while (*index < fill_parameter) {
    temp[(*index)++] = filling;
  }
}

void uox_flags(char *temp, char *result, int *index, Specifier *specs) {
  if (specs->dot) {
    specs->leading_zeros = 0;
    if (*index < specs->precision) {
      fill_array_with(temp, index, '0', specs->precision);
    }
  }

  if (specs->hash && (specs->numeral_system != 10)) {
    if (specs->numeral_system == 8) {
      temp[(*index)++] = '0';
    } else if (specs->numeral_system == 16) {
      temp[(*index)++] = (char)('x' - specs->upper_case * 32);
      temp[(*index)++] = '0';
    }
  }

  if (specs->width) {
    if (*index < specs->width) {
      if (specs->leading_zeros && (!specs->left_justification)) {
        fill_array_with(temp, index, '0', specs->width);
      } else if (specs->left_justification) {
        reverse_the_string(result, temp, index, specs);
        fill_array_with(result, index, ' ', specs->width);
        result[*index] = '\0';
      } else {
        fill_array_with(temp, index, ' ', specs->width);
      }
    }
  }
}

int uox_convert_to_string(unsigned long int num, char *result, s21_size_t size,
                          Specifier *specs) {
  char *temp = malloc((size + 1) * sizeof(char));
  if (!temp) {
    specs->error = 1;
    s21_strcpy(specs->error_message, s21_strerror(12));
    return 0;
  }
  int index = 0;

  do {
    int digit = num % specs->numeral_system;
    temp[index++] = get_num_char(digit, specs->upper_case);
    num /= specs->numeral_system;
  } while (num > 0);

  uox_flags(temp, result, &index, specs);

  if (!specs->is_reversed) {
    reverse_the_string(result, temp, &index, specs);
  }

  free(temp);

  return 1;
}

void handle_uox_specifier(va_list arguments, Specifier *specs) {
  int flag = 1;
  if (specs->precision == -1) {
    specs->precision = 0;
  }
  unsigned long int num = 0;
  char *result = S21_NULL;
  if (specs->long_l) {
    num = (unsigned long int)va_arg(arguments, unsigned long int);
  } else if (specs->short_h) {
    num = (unsigned short int)va_arg(arguments, int);
  } else {
    num = (unsigned int)va_arg(arguments, unsigned int);
  }
  if (num == 0) {
    specs->hash = 0;
  }
  s21_size_t size_of_result =
      get_size_of_unsigned_long_int(specs, num) + specs->added_size;
  result = malloc((size_of_result + 1) * sizeof(char));
  if (!result) {
    specs->error = 1;
    s21_strcpy(specs->error_message, s21_strerror(12));
    flag = 0;
  }
  if (!uox_convert_to_string(num, result, size_of_result, specs)) {
    flag = 0;
  }
  if (flag) {
    cat_result(specs, result);
  }

  if (result) {
    free(result);
  }
}

void convert_pointer_to_str(void *ptr, char *buffer, int *len) {
  int index = 0;
  if (ptr == S21_NULL) {
    const char nil_str[] = "(nil)";
    for (int i = 0; nil_str[i] != '\0'; i++) {
      buffer[index++] = nil_str[i];
    }
  } else {
    uintptr_t address = (uintptr_t)ptr;
    buffer[index++] = '0';
    buffer[index++] = 'x';

    char temp[sizeof(uintptr_t) * 2] = {0};
    int temp_index = 0;
    while (address > 0) {
      int digit = address % 16;
      if (digit < 10) {
        temp[temp_index++] = '0' + digit;
      } else {
        temp[temp_index++] = 'a' + (digit - 10);
      }
      address /= 16;
    }
    for (int i = temp_index - 1; i >= 0; i--) {
      buffer[index++] = temp[i];
    }
  }
  buffer[index] = '\0';
  *len = index;
}

void fill_padding(const Specifier *specs, const char *src, int len,
                  char *dest) {
  int width = (specs->width > len) ? specs->width : len;
  int padding = width - len;
  int pos = 0;
  if (specs->left_justification) {
    for (int i = 0; i < len; i++) dest[pos++] = src[i];
    for (int i = 0; i < padding; i++) dest[pos++] = ' ';
  } else {
    for (int i = 0; i < padding; i++) dest[pos++] = ' ';
    for (int i = 0; i < len; i++) dest[pos++] = src[i];
  }
  dest[pos] = '\0';
}

void handle_p_specifier(Specifier *specs, va_list args) {
  void *ptr = va_arg(args, void *);
  char buffer[2 + sizeof(uintptr_t) * 2 + 1] = {0};
  int len = 0;
  convert_pointer_to_str(ptr, buffer, &len);
  int width = (specs->width > len) ? specs->width : len;
  char *result = malloc((width + 1) * sizeof(char));
  if (result) {
    fill_padding(specs, buffer, len, result);
    cat_result(specs, result);
    free(result);
  } else {
    specs->error = 1;
    s21_strcpy(specs->error_message, s21_strerror(12));
  }
}

void handle_n_specifier(Specifier *specs, va_list args) {
  if (specs->short_h) {
    short *ptr = va_arg(args, short *);
    *ptr = (short)specs->count_symb;
  } else if (specs->long_l) {
    long *ptr = va_arg(args, long *);
    *ptr = (long)specs->count_symb;
  } else {
    int *ptr = va_arg(args, int *);
    *ptr = specs->count_symb;
  }
}

void handle_percent_specifier(Specifier *specs) { cat_result(specs, "%"); }

void process_specifier(Specifier *specs, char **ptr_format, va_list args) {
  specs->result = (char *)calloc(BUFFER_SIZE, sizeof(char));
  specs->alloc_size = BUFFER_SIZE;

  if (!specs->result) {
    specs->error = 1;
    s21_strcpy(specs->error_message, s21_strerror(12));
    return;
  }

  switch (**ptr_format) {
    case 'c':  // 1
      handle_c_specifier(specs, args);
      break;
    case 'd':  // 2
      handle_d_specifier(specs, args);
      break;
    case 'i':  // 3
      handle_d_specifier(specs, args);
      break;
    case 'e':  // 4
      handle_e_specifier(specs, args);
      break;
    case 'E':  // 5
      specs->upper_case = 1;
      handle_e_specifier(specs, args);
      break;
    case 'f':  // 6
      handle_f_specifier(specs, args);
      break;
    case 'g':  // 7
      handle_g_specifier(specs, args);
      break;
    case 'G':  // 8
      specs->upper_case = 1;
      handle_g_specifier(specs, args);
      break;
    case 'o':  // 9
      specs->numeral_system = 8;
      specs->added_size = 1;
      handle_uox_specifier(args, specs);
      break;
    case 's':  // 10
      handle_s_specifier(specs, args);
      break;
    case 'u':  // 11
      specs->numeral_system = 10;
      handle_uox_specifier(args, specs);
      break;
    case 'x':  // 12
      specs->numeral_system = 16;
      specs->added_size = 2;
      handle_uox_specifier(args, specs);
      break;
    case 'X':  // 13
      specs->numeral_system = 16;
      specs->added_size = 2;
      specs->upper_case = 1;
      handle_uox_specifier(args, specs);
      break;
    case 'p':  // 14
      handle_p_specifier(specs, args);
      break;
    case 'n':  // 15
      handle_n_specifier(specs, args);
      break;
    case '%':  // 16
      handle_percent_specifier(specs);
      break;
    default:
      specs->error = 1;
      s21_strcpy(specs->error_message, "Неизвестный спецификатор");
      break;
  }
}

int s21_sprintf(char *str, const char *format, ...) {
  char *ptr_str = str;
  char *ptr_format = (char *)format;

  int count_symb = 0;

  va_list args;
  va_start(args, format);

  while (*ptr_format) {
    if (*ptr_format == '%') {
      ptr_format++;
      Specifier specs = {0};
      specs.precision = -1;

      parser(&specs, &ptr_format, args);

      specs.count_symb = count_symb;
      process_specifier(&specs, &ptr_format, args);

      if (specs.error) {
        // fprintf(stderr, "%s\n", specs->error_message);
        if (specs.result) {
          free(specs.result);
        }
        break;
      }

      ptr_format++;
      const char *ptr_result = specs.result;

      while (*ptr_result) {
        *ptr_str++ = *ptr_result++;
        count_symb++;
      }

      free(specs.result);
    } else {
      *ptr_str++ = *ptr_format++;
      count_symb++;
    }
  }

  *ptr_str = '\0';
  va_end(args);

  return ptr_str - str;
}