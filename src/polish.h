#ifndef POLISH_H
#define POLISH_H
#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

enum Prioritet {
  CLOSING_BRACKET,  // 0
  FUNCS,            // 1
  OPERATORS_MULT,   // 2
  OPERATORS_PLUS,   // 3
  OPENING_BRACKET   // 4
};

typedef struct lexem {
  char func;
  int prioritet;
} lexem;

typedef struct stack_final {
  double number;
  char func;
  int prioritet;
  struct stack_final* next;
} stack_final;

typedef struct stack {
  lexem lex;
  struct stack* next;
} stack;

double parse_str(const char* str, int* error, double x);
int prioritization_funcs(const char* str, int* n, stack** operators_stack,
                         stack_final** final_stack);
int prioritization_operators(const char* str, int* n, stack** operators_stack,
                             stack_final** final_stack, int* sign, int);
int prioritization_close(int* n, stack** operators_stack,
                         stack_final** final_stack);
int prioritization_open(int* n, stack** operators_stack,
                        stack_final** final_stack);
int write_count(const char* str, int n, stack_final** final_stack, int* sign);
int record_in_stack(lexem lex, stack** operators_stack,
                    stack_final** final_stack);
int processing_closing_bracket(stack** operators_stack,
                               stack_final** final_stack);
void processing_operators(stack** operators_stack, stack_final** final_stack,
                          lexem lex);
void record_in_final_stack(stack** operators_stack, stack_final** final_stack);
void record_in_operators_stack(stack** operators_stack, lexem lex);

double calculate_expression(stack_final** final_stack, int* error);
double arithmetic_funcs(char func, double count);
int processing_funcs(stack_final* p, stack_final** final_stack);
double operators(char func, double count_1, double count_2);
int proc_operators(stack_final* p, stack_final** final_stack);

stack* init(lexem lex);
stack* push(stack* head, lexem lex);
stack* pop(stack* head);

stack_final* init_f(double, char, int);
stack_final* push_f(stack_final* head, double, char, int);
void destroy_f(stack_final* head);
void pop_count(stack_final** del, stack_final** pred);

#ifdef __cplusplus
}
#endif
#endif
