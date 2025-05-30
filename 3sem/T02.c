#include <stdio.h>
#include <stdlib.h>

struct Node {
    struct Node * next;
    int value;
};

struct List {
    struct Node * first;
    struct Node * last;
};

void append(struct List * list, int value) {
    struct Node * node = malloc(sizeof(struct Node));
    *node = (struct Node) { .value = value };
    if (list->last) {
        list->last->next = node;
        list->last = node;
    } else {
        list->first = list->last = node; 
    }
}

void print(const struct List * list)  {
    struct Node * node = list->first;
    while (node) {
        printf("%d ", node->value);
        node = node->next;
    }
    putchar('\n');
}

void release(struct List * list) {
    struct Node * node;
    while ((node = list->first)) {
        list->first = list->first->next;
        free(node);
    }
    list->first = list->last = NULL;
}

struct List merge(struct List * list1, struct List * list2) {
    struct List result = { };
    struct Node *element1 = list1->first;
    struct Node *element2 = list2->first;
    while (1) {
        if (element1 == NULL) {
            while (element2 != NULL) {
                append(&result, element2->value);
                element2 = element2->next;
            }
            break;
        }
        if (element2 == NULL) {
            while (element1 != NULL) {
                append(&result, element1->value);
                element1 = element1->next;
            }
            break;
        }
        if (element1->value < element2->value) {
            append(&result, element1->value);
            element1 = element1->next;
        }
        else {
            append(&result, element2->value);
            element2 = element2->next;
        }
    }
    return result;
}

int main(void)
{
    struct List list1 = { };
    struct List list2 = { };
    int n;
    while (scanf("%d", &n) == 1 && n != 0) {
        append(&list1, n);
    }
    while (scanf("%d", &n) == 1 && n != 0) {
        append(&list2, n);
    }

    struct List merged = merge(&list1, &list2);

    print(&merged);
    release(&merged);
    release(&list1);
    release(&list2);
}
