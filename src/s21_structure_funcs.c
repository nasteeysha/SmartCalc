#include "polish.h"

stack* init(lexem lex) {
  stack* head;
  head = (stack*)malloc(sizeof(stack));
  head->lex = lex;
  head->next = NULL;
  return head;
}

stack* push(stack* head, lexem lex) {
  stack* tmp = malloc(sizeof(stack));
  tmp->next = head;
  tmp->lex = lex;
  head = tmp;
  return head;
}

stack* pop(stack* head) {
  stack* out;
  out = head;
  head = head->next;
  free(out);
  return head;
}

stack_final* init_f(double number, char func, int prioritet) {
  stack_final* head;
  head = (stack_final*)malloc(sizeof(stack_final));
  head->number = number;
  head->func = func;
  head->prioritet = prioritet;
  head->next = NULL;
  return head;
}

stack_final* push_f(stack_final* head, double number, char func,
                    int prioritet) {
  stack_final* tmp = malloc(sizeof(stack_final));
  tmp->next = head;
  tmp->number = number;
  tmp->func = func;
  tmp->prioritet = prioritet;
  head = tmp;
  return head;
}

void destroy_f(stack_final* head) {
  stack_final* copyroot = head;
  while (head) {
    head = head->next;
    free(copyroot);
    copyroot = head;
  }
}

void pop_count(stack_final** del, stack_final** pred) {
  stack_final* next = (*del)->next;
  (*pred)->next = next;
  free(*del);
}