#include "polish.h"

double calculate_expression(stack_final** final_stack, int* error) {
  int flag = 0;
  do {
    flag = 0;
    stack_final* p = *final_stack;
    while (p != NULL) {
      if (p->prioritet == 1 && p->func != '^')
        flag = processing_funcs(p, final_stack);
      else if (p->prioritet == 2 || p->prioritet == 3 || p->func == '^')
        flag = proc_operators(p, final_stack);
      p = p->next;
    }

  } while ((*final_stack)->next != NULL && flag);
  if ((*final_stack)->next != NULL) *error = 1;
  double res = 0;
  if ((*final_stack)->prioritet == -1)
    res = (*final_stack)->number;
  else
    *error = 1;
  return res;
}

int processing_funcs(stack_final* p, stack_final** final_stack) {
  stack_final* count = p->next;
  double res = 0;
  int flag = 0;
  if (count != NULL)
    if (count->prioritet == -1) {
      res = arithmetic_funcs(p->func, count->number);
      p->number = res;
      p->prioritet = -1;
      p->func = 0;
      pop_count(&count, &p);
      flag = 1;
    }
  return flag;
}

int proc_operators(stack_final* p, stack_final** final_stack) {
  stack_final* count_1 = p->next;
  stack_final* count_2;
  if (count_1 != NULL) count_2 = count_1->next;
  double res = 0;
  int flag = 0;
  if (count_1 != NULL && count_2 != NULL)
    if (count_1->prioritet == -1 && count_2->prioritet == -1) {
      res = operators(p->func, count_1->number, count_2->number);
      p->number = res;
      p->prioritet = -1;
      p->func = 0;
      pop_count(&count_1, &p);
      pop_count(&count_2, &p);
      flag = 1;
    }
  return flag;
}

double arithmetic_funcs(char func, double count) {
  double res = 0;
  if (func == 'c')
    res = cos(count);
  else if (func == 's')
    res = sin(count);
  else if (func == 'i')
    res = asin(count);
  else if (func == 'o')
    res = acos(count);
  else if (func == 'a')
    res = atan(count);
  else if (func == 't')
    res = tan(count);
  else if (func == 'q')
    res = sqrt(count);
  else if (func == 'n')
    res = log(count);
  else if (func == 'g')
    res = log10(count);
  return res;
}

double operators(char func, double count_1, double count_2) {
  double res = 0;
  if (func == '+')
    res = count_1 + count_2;
  else if (func == '-')
    res = count_2 - count_1;
  else if (func == '*')
    res = count_2 * count_1;
  else if (func == '/')
    res = count_2 / count_1;
  else if (func == 'm')
    res = fmod(count_2, count_1);
  else if (func == '^')
    res = pow(count_2, count_1);
  return res;
}