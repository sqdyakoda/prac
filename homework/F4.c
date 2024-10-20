#include <stdio.h>
#include <stdlib.h>
typedef struct TNode * Tree;
struct TNode {
    int key;
    struct TNode * left;
    struct TNode * right;
};
Tree createnode(int value) {
    Tree element = (Tree) malloc(sizeof(struct TNode));
    element->key = value;
    element->right = NULL;
    element->left  = NULL;
    return element;
}
Tree add(Tree pTree, int n) {
    if (pTree == NULL)
        return createnode(n);
    if (n > pTree->key)
        pTree->right = add(pTree->right, n);
    else if (n < pTree->key)
        pTree->left = add(pTree->left, n);
    return pTree;
}
void print(Tree tree) {
    if (tree == NULL)
        return;
    print(tree->left);
    printf("%d ", tree->key);
    print(tree->right);
}
void release(Tree tree) {
    if (tree == NULL)
        return;
    release(tree->left);
    release(tree->right);
    free(tree);
}
int main(int argc, char *argv[]) {
    if (argv[1] == NULL)
        return 0;
    Tree BT = NULL;
    char *curptr = argv[1];
    while (1) {
        if (*argv[1] == ',') {
            *argv[1] = '\0';
            BT = add(BT, atoi(curptr));
            curptr = argv[1] + 1;
        } else if (*argv[1] == '\0') {
            BT = add(BT, atoi(curptr));
            break;
        }
        argv[1]++;
    }
    print(BT);
    putchar('\n');
    release(BT);
}