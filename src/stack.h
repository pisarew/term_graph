#ifndef MATERIALS_LINTERS_STACK_H_
#define MATERIALS_LINTERS_STACK_H_
#include <stdlib.h>

typedef struct node {
    int num;
    struct node* next;
} node;

node* init(int num);
node* push(node* head, int num);
node* pop(node* head);
void destroy(node* head);



#endif  // MATERIALS_LINTERS_STACK_H_
