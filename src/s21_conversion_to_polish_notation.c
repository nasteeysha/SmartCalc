#include "polish.h"

double parse_str(const char* str, int* error, double x) {
  int n = 0, sign = 1, pred = 0;
  stack* operators_stack = NULL;
  stack_final* final_stack = NULL;
  while (n <= 255 && str[n] != '\0' && !(*error)) {
    if (str[n] == 'c' || str[n] == 's' || str[n] == 't' || str[n] == 'a' ||
        str[n] == 'l' || str[n] == '^') {
      *error = prioritization_funcs(str, &n, &operators_stack, &final_stack);
      pred = 1;
    } else if (str[n] == '+' || str[n] == '-' || str[n] == '*' ||
               str[n] == '/' || str[n] == 'm') {
      *error = prioritization_operators(str, &n, &operators_stack, &final_stack,
                                        &sign, pred);
      pred = 1;
    } else if (str[n] == ')')
      *error = prioritization_close(&n, &operators_stack, &final_stack);
    else if (str[n] == '(') {
      *error = prioritization_open(&n, &operators_stack, &final_stack);
      pred = 1;
    } else if (str[n] == '.' || (str[n] >= 48 && str[n] <= 57)) {
      n = write_count(str, n, &final_stack, &sign);
      pred = 0;
    } else if (str[n] == ' ')
      n++;
    else if (str[n] == 'x') {
      if (final_stack != NULL)
        final_stack = push_f(final_stack, x, 0, -1);
      else
        final_stack = init_f(x, 0, -1);
      pred = 0;
      n++;
    } else
      *error = 1;
  }
  while (operators_stack != NULL) {
    record_in_final_stack(&operators_stack, &final_stack);
    if (operators_stack->lex.func == '(') *error = 1;
    operators_stack = pop(operators_stack);
  }
  double res = 0;
  if (!(*error) && final_stack != NULL)
    res = calculate_expression(&final_stack, error);
  else
    *error = 1;
  if (final_stack != NULL) destroy_f(final_stack);
  return res;
}

int prioritization_funcs(const char* str, int* n, stack** operators_stack,
                         stack_final** final_stack) {
  lexem lex = {0};
  int error = 0;
  char func = '\0';
  lex.prioritet = FUNCS;
  if (str[*n] == 'c' && str[*n + 1] == 'o' && str[*n + 2] == 's') {
    func = 'c';
    *n += 3;
  } else if (str[*n] == 't' && str[*n + 1] == 'a' && str[*n + 2] == 'n') {
    func = 't';
    *n += 3;
  } else if (str[*n] == 'a' && str[*n + 1] == 's' && str[*n + 2] == 'i' &&
             str[*n + 3] == 'n') {
    func = 'i';
    *n += 4;
  } else if (str[*n] == 'a' && str[*n + 1] == 'c' && str[*n + 2] == 'o' &&
             str[*n + 3] == 's') {
    func = 'o';
    *n += 4;
  } else if (str[*n] == 'a' && str[*n + 1] == 't' && str[*n + 2] == 'a' &&
             str[*n + 3] == 'n') {
    func = 'a';
    *n += 4;
  } else if (str[*n] == 's' && str[*n + 1] == 'q' && str[*n + 2] == 'r' &&
             str[*n + 3] == 't') {
    func = 'q';
    *n += 4;
  } else if (str[*n] == 's' && str[*n + 1] == 'i' && str[*n + 2] == 'n') {
    func = 's';
    *n += 3;
  } else if (str[*n] == 'l' && str[*n + 1] == 'o' && str[*n + 2] == 'g') {
    func = 'g';
    *n += 3;
  } else if (str[*n] == 'l' && str[*n + 1] == 'n') {
    func = 'n';
    *n += 2;
  } else if (str[*n] == '^') {
    func = '^';
    *n += 1;
  } else
    error = 1;
  if (func != '^' && str[*n] != '(')
    error = 1;
  else if (func != '^' && str[*n] == '(' && str[*n + 1] == ')')
    error = 1;
  lex.func = func;
  record_in_stack(lex, operators_stack, final_stack);
  return error;
}

int prioritization_operators(const char* str, int* n, stack** operators_stack,
                             stack_final** final_stack, int* sign, int pred) {
  lexem lex = {0};
  int error = 0;
  char func = '\0';
  *sign = 0;
  if (str[*n] == '+') {
    func = '+';
    lex.prioritet = OPERATORS_PLUS;
    if (pred) *sign = 1;
    if (*final_stack == NULL && *operators_stack == NULL) *sign = 1;
  } else if (str[*n] == '-') {
    func = '-';
    lex.prioritet = OPERATORS_PLUS;
    if (pred) *sign = 2;
    if (*final_stack == NULL && *operators_stack == NULL) *sign = 2;
  } else if (str[*n] == '/') {
    func = '/';
    lex.prioritet = OPERATORS_MULT;
  } else if (str[*n] == '*') {
    func = '*';
    lex.prioritet = OPERATORS_MULT;
  } else if (str[*n] == 'm') {
    func = 'm';
    *n += 2;
    lex.prioritet = OPERATORS_MULT;
  }
  lex.func = func;
  *n += 1;
  if (!(*sign)) error = record_in_stack(lex, operators_stack, final_stack);
  return error;
}

int prioritization_close(int* n, stack** operators_stack,
                         stack_final** final_stack) {
  lexem lex = {0};
  int error = 0;
  char func = ')';
  lex.prioritet = CLOSING_BRACKET;
  lex.func = func;
  *n += 1;
  error = record_in_stack(lex, operators_stack, final_stack);
  return error;
}

int prioritization_open(int* n, stack** operators_stack,
                        stack_final** final_stack) {
  lexem lex = {0};
  int error = 0;
  char func = '(';
  lex.prioritet = OPENING_BRACKET;
  lex.func = func;
  *n += 1;
  error = record_in_stack(lex, operators_stack, final_stack);
  return error;
}

int write_count(const char* str, int n, stack_final** final_stack, int* sign) {
  int count = 0;
  double number = 0.0;
  while (str[n] != '.' && (str[n] >= 48 && str[n] <= 57)) {
    count++;
    n++;
  }
  long long int mult = 1;
  for (int i = 0; i < count; i++) {
    number += mult * (str[n - i - 1] - 48);
    mult *= 10;
  }
  if (str[n] == '.') n++;
  double mult_part = 0.1;
  while (str[n] >= 48 && str[n] <= 57) {
    number += mult_part * (str[n] - 48);
    mult_part /= 10.0;
    n++;
  }
  if ((*sign) == 2) number *= -1;
  if (*final_stack != NULL)
    *final_stack = push_f(*final_stack, number, 0, -1);
  else
    *final_stack = init_f(number, 0, -1);
  return n;
}

int record_in_stack(lexem lex, stack** operators_stack,
                    stack_final** final_stack) {
  int error = 0;
  if (*operators_stack == NULL)
    *operators_stack = init(lex);
  else {
    if (lex.prioritet == 0)
      error = processing_closing_bracket(operators_stack, final_stack);
    else if (lex.prioritet >= (*operators_stack)->lex.prioritet &&
             lex.prioritet != 4) {
      if (!(lex.func == (*operators_stack)->lex.func && lex.func == '^'))
        processing_operators(operators_stack, final_stack, lex);
      record_in_operators_stack(operators_stack, lex);
    } else
      record_in_operators_stack(operators_stack, lex);
  }
  return error;
}

int processing_closing_bracket(stack** operators_stack,
                               stack_final** final_stack) {
  int flag = 1, error = 0;
  if ((*operators_stack)->lex.func == '(') flag = 0;
  while (flag) {
    record_in_final_stack(operators_stack, final_stack);
    *operators_stack = pop(*operators_stack);
    if (*operators_stack == NULL) flag = 0;
    if (flag)
      if ((*operators_stack)->lex.func == '(') flag = 0;
  }
  if (*operators_stack == NULL)
    error = 1;
  else
    *operators_stack = pop(*operators_stack);
  if (*operators_stack != NULL) {
    if ((*operators_stack)->lex.prioritet == 1) {
      record_in_final_stack(operators_stack, final_stack);
      *operators_stack = pop(*operators_stack);
    }
  }
  return error;
}

void processing_operators(stack** operators_stack, stack_final** final_stack,
                          lexem lex) {
  int flag = 1;
  while (flag) {
    *final_stack = push_f(*final_stack, -1, (*operators_stack)->lex.func,
                          (*operators_stack)->lex.prioritet);
    *operators_stack = pop(*operators_stack);
    if (*operators_stack == NULL) flag = 0;
    if (flag)
      if (lex.prioritet < (*operators_stack)->lex.prioritet) flag = 0;
  }
}

void record_in_final_stack(stack** operators_stack, stack_final** final_stack) {
  if (*final_stack != NULL)
    *final_stack = push_f(*final_stack, -1, (*operators_stack)->lex.func,
                          (*operators_stack)->lex.prioritet);
  else
    *final_stack = init_f(-1, (*operators_stack)->lex.func,
                          (*operators_stack)->lex.prioritet);
}

void record_in_operators_stack(stack** operators_stack, lexem lex) {
  if (*operators_stack != NULL)
    *operators_stack = push(*operators_stack, lex);
  else
    *operators_stack = init(lex);
}
