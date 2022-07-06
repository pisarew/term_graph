#include "double_stack.h"
#include <stdlib.h>

d_node* d_init(double num) {
    d_node* head = malloc(sizeof(d_node));
    head->num = num;
    head->next = NULL;
    return head;
}
d_node* d_push(d_node* head, double num) {
    if (!head)
        return NULL;
    d_node* new_head = malloc(sizeof(d_node));
    new_head->num = num;
    new_head->next = head;
    return new_head;
}
d_node* d_pop(d_node* head) {
    if (!head)
        return NULL;
    d_node* buf = head;
    head = head->next;
    free(buf);
    return head;
}
void d_destroy(d_node* head) {
    if (!head)
        return;
    while (head->next) {
        struct d_node* buf = head;
        head = head->next;
        free(buf);
    }
    free(head);
}
