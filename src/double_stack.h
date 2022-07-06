#ifndef MATERIALS_LINTERS_DOUBLE_STACK_H_
#define MATERIALS_LINTERS_DOUBLE_STACK_H_
#include <stdlib.h>

typedef struct d_node { // Структура для подсчета (отличается от stack.h только типом переменной num)
    double num;
    struct d_node* next;
} d_node;

d_node* d_init(double num);
d_node* d_push(d_node* head, double num);
d_node* d_pop(d_node* head);
void d_destroy(d_node* head);



#endif  // MATERIALS_LINTERS_DOUBLE_STACK_H_
