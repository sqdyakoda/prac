#include <stdio.h>
#include <stdlib.h>
#include <string.h>
enum {MAXLEN = 10};
typedef struct node {
    struct node *next, *prev;
    char *str;
} node;
//функция удаляет элемент из списка
void delete(node **List, node *element) {
    //1 элемент
    if (*List == (*List)->next) {
        *List = NULL;
        return;
    }
    if (*List == element) {
        element->prev->next = element->next;
        element->next->prev = element->prev;
        *List = element->next;
        return;
    }
    element->prev->next = element->next;
    element->next->prev = element->prev;    
}
void append(node **List, char *str) {
    node *element = (node*) malloc(sizeof(node));
    element->str = (char*) malloc(strlen(str));
    strcpy(element->str, str);
    if (*List == NULL) {
        *List = element;
        element->next = element;
        element->prev = element;
        return;
    }
    node *last = (*List)->prev;
    last->next = element;
    (*List)->prev = element;
    element->next = *List;
    element->prev = last;
}
void dublicate(node **List, node *element, int n) {
    if (*List == element) {
        append(&element, element->str);
        node *first = (*List)->prev;
        for (int i = 0; i < n - 1; ++i)
            append(&element, element->str);
        *List = first;
        return;
    }
    for (int i = 0; i < n; ++i)
        append(&element, element->str);
}
void print(node **List) {
    node *curel = *List;
    node *last = (*List)->prev;
    putchar('\n');
    while (curel != last) {
        printf("%s", curel->str);
        curel = curel->next;
    }
    printf("%s\n", curel->str);
}
void process(node **List, const char *s) {
    node *last = (*List)->prev;
    node *curel = *List;
    node *temp = NULL;
    while (curel != last) {

        if (strstr(curel->str, s)) {
            dublicate(List, curel, strlen(curel->str));
            curel = curel->next;
        } else {
            temp = curel->next;
            delete(List, curel);
            append(List, curel->str);
            curel = temp;
        }
    }
    if (strstr(curel->str, s)) {
        dublicate(List, curel, strlen(curel->str));
    } else {
        delete(List, curel);
        append(List, curel->str);
    }
}
int main(void) {
    node *List = NULL;
    char buf[MAXLEN + 2];
    
    while (fgets(buf, MAXLEN + 2, stdin)) {
        append(&List, buf);
    }
    
    process(&List, "1");
    // dublicate(&List, List, 3);
    print(&List);
}