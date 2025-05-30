#include <stdio.h>
#include <stdlib.h>
#include <string.h>
enum { MAXLEN = 80 };
struct list_node {
    struct list_node* next;
    struct list_node* prev;
    char* value;
};

void append(struct list_node **list, char *str) {
    struct list_node *element = malloc(sizeof(struct list_node));
    element->value = (char*) malloc(MAXLEN + 2);
    strcpy(element->value, str);
    if (*list == NULL) {
        *list = element;
        element->next = element;
        element->prev = element;
        return;
    }
    element->next = *list;
    element->prev = (*list)->prev;
    (*list)->prev->next = element;
    (*list)->prev = element;
    return;
}
void release(struct list_node **list) {
    if (*list == NULL)
        return;
    struct list_node *curel = (*list)->prev;
    struct list_node *temp;
    while (curel != *list) {
        temp = curel;
        curel = curel->prev;
        free(temp->value);
        free(temp);
    }
    free(curel->value);
    free(curel);
    *list = NULL;
}

void reverse_print(struct list_node *list) {
    struct list_node *curel = list->prev;
    while (curel != list) {
        printf("%s", curel->value);
        curel = curel->prev;
    }
    printf("%s", curel->value);
}


int main(void) {
    char buf[MAXLEN + 2];
    struct list_node *List = NULL;
    while (fgets(buf, MAXLEN + 2, stdin))
        append(&List, buf);
    reverse_print(List);
    release(&List);
}