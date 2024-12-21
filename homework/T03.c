#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *next;
    struct node *prev;
} node;

void delete(node **List, node *element) {
    //0 элементов
    if (*List == NULL)
        return;
    //1 элемент
    if (*List == (*List)->next) {
        *List = NULL;
        return;
    }
    //2 и более элемента
    element->prev->next = element->next;
    element->next->prev = element->prev;
}
void append(node **List, node *element) {
    //0 элементов
    if (*List == NULL) {
        *List = element;
        element->next = element;
        element->prev = element;
        return;
    }
        
    //1 элеменt
    if (*List == (*List)->next) {
        (*List)->next = element;
        (*List)->prev = element;
        element->next = *List;
        element->prev = *List;
        return;
    }
    //2 и более эелементов
    node *last = (*List)->prev;
    last->next = element;
    (*List)->prev = element;
    element->next = *List;
    element->prev = last;
}
void print(node **List) {
    //0 элементов
    if (*List == NULL)
        return;
    //1 элеменt
    if (*List == (*List)->next) {
        printf("%d\n", (*List)->value);
        return;
    }
    //2 и более эелементов
    node *cur_elem = (*List)->prev;
    while (cur_elem != *List) {
        printf("%d ", cur_elem->value);
        cur_elem = cur_elem->prev;
    }
    printf("%d\n", cur_elem->value);
}
void action(node **List) {
    //0 элементов
    if (*List == NULL)
        return;
    //1 элеменt
    if (*List == (*List)->next) {
        if (((*List)->value < 100) && ((*List)->value & 1))
            delete(List, *List);
    }
   
    node *cur_elem = (*List);
    node *last = (*List)->prev;
    node *temp = NULL;
    while (cur_elem != last) {
        if (cur_elem->value > 100) {
            temp = cur_elem->next;
            delete(List, cur_elem);
            append(List, cur_elem);
            cur_elem = temp;
        } else if ((cur_elem->value & 1) && (cur_elem->value < 100)) {
            temp = cur_elem->next;
            delete(List, cur_elem);
            cur_elem = temp;
        } else {
            cur_elem = cur_elem->next;
        }
    }
    if (cur_elem->value > 100) {
        delete(List, cur_elem);
        append(List, cur_elem);
    }
    if ((cur_elem->value & 1) && (cur_elem->value < 100))
        delete(List, cur_elem);
}
int main(void) {
    node *list = NULL;
    int number;
    while (scanf("%d", &number) == 1) {
        node *element = (node*) malloc(sizeof(node));
        element->value = number;
        append(&list, element);
    }
    action(&list);
    print(&list);
}
