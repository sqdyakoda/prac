#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
    struct Node * next;
    int value;
} Node;
typedef struct List {
    Node * first;
    Node * last;
    size_t size;
} List;
// List *CreateList() {
//     List *lst = (List*) malloc(sizeof(List));
//     lst->first = NULL;
//     lst->last  = NULL;
//     lst->size = 0;
//     return lst;
// }
void append(struct List * pList, int value) {
    Node *NewItem = (Node*) malloc(sizeof(Node));
    NewItem->value = value;
    NewItem->next = NULL;
    if (pList->size == 0)
        pList->first = NewItem;
    else 
        pList->last->next = NewItem;
    pList->last = NewItem;
    pList->size++;
}
void print(const struct List * pList) {
    printf("length = %zu\n", pList->size);
    Node *temp = pList->first;
    while (temp != NULL) {
        printf("%d ", temp->value);
        temp = temp->next;
    }
    putchar('\n');
}
void delete(struct List * pList) {
    Node *el1 = pList->first;
    Node *el2;
    while (el1 != NULL) {
        el2 = el1->next;
        free(el1);
        el1 = el2;
    }
    pList->first = NULL;
    pList->last = NULL;
    pList->size = 0;
}
int main(void) {
    // List * NewList = (List *) CreateList();
    List NewList = { .first = NULL, .last = NULL, .size = 0 };
    int n;
    while (scanf("%d", &n) == 1)
        append(&NewList, n);
    if (NewList.size > 1) {
        int temp = NewList.first->value;
        NewList.first->value = NewList.last->value;
        NewList.last->value = temp;
    }
    print(&NewList);
    delete(&NewList);
}