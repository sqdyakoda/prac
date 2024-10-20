#include <stdio.h>
#include <stdlib.h>
typedef struct Node * List;
struct Node {
    struct Node *prev;
    struct Node *next;
    int value;
};
void append(List *list, List element) {
    if (*list == NULL) {
        element->prev = element;
        element->next = element;
        *list = element;
    } else {
        List temp = (*list)->next;
        while (temp->next != *list)
            temp = temp->next;
        temp->next = element;
        element->prev = temp;
        element->next = *list;
        (*list)->prev = element;
    }
}
void Remove(List *list, List element) {
    if (*list == (*list)->next)
        *list = NULL;
    else {
        if (element == *list)
            *list = element->next;
        element->prev->next = element->next;
        element->next->prev = element->prev;
        element->next = element->prev = NULL;
    }
}
void print(List *list) {
    if (*list == NULL) {
        printf("\n");
        return;
    }   
    List currelement = *list;
    while (currelement != (*list)->prev) {
        printf("%d ", currelement->value);
        currelement = currelement->next;
    }
    printf("%d\n", currelement->value);
}
void reverseprint(List *list) {
    if (*list == NULL)
        return;   
    List currelement = (*list)->prev;
    while (currelement != *list) {
        printf("%d ", currelement->value);
        currelement = currelement->prev;
    }
    printf("%d\n", currelement->value);
}
void action(List *list) {
    if (*list == NULL)
        return;
    List currelement = *list;
    List temp;
    List end = (*list)->prev;
    while (currelement != end) {
        if (currelement->value > 100) {
            temp = currelement;
            currelement = currelement->next;
            Remove(list, temp);
            append(list, temp);
        } else if (currelement->value < 100 && currelement->value % 2 == 1) {
            temp = currelement;
            currelement = currelement->next;
            Remove(list, temp);
            free(temp);
        } else
            currelement = currelement->next;
    }
    if (currelement->value > 100) {
        temp = currelement;
        currelement = currelement->next;
        Remove(list, temp);
        append(list, temp);
    } else if (currelement->value < 100 && currelement->value % 2 == 1) {
        temp = currelement;
        currelement = currelement->next;
        Remove(list, temp);
        free(temp);
    }
}
void delete(List *list) {
    if (*list == NULL)
        return;
    List currelement = (*list)->prev;
    List temp;
    while (currelement != *list) {
        temp = currelement;
        currelement = currelement->prev;
        free(temp);
    }
    free(currelement);
}
int main(void) {
    List NewList = NULL;
    int number;
    while (scanf("%d", &number) == 1) {
        struct Node *element = (struct Node *) malloc(sizeof(struct Node));
        element->value = number;
        append(&NewList, element);
    }
    action(&NewList);
    reverseprint(&NewList);
    delete(&NewList);
}