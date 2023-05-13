#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *left;
    struct Node *right;
} Node;

Node* createNode(int value) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void insert(Node** root, int parentValue, int value, char child) {
    if (*root == NULL) {
        return;
    }
    if ((*root)->value == parentValue) {
        if (child == 'L') {
            (*root)->left = createNode(value);
        } else {
            (*root)->right = createNode(value);
        }
        return;
    }
    insert(&((*root)->left), parentValue, value, child);
    insert(&((*root)->right), parentValue, value, child);
}

int getMaxDepth(Node* root) {
    if (root == NULL) {
        return 0;
    }
    int leftDepth = getMaxDepth(root->left);
    int rightDepth = getMaxDepth(root->right);
    return 1 + ((leftDepth > rightDepth) ? leftDepth : rightDepth);
}

int findMaxValue(Node* root, int maxDepth) {
    if (root == NULL) {
        return -1; 
    }
    if (getMaxDepth(root) == maxDepth) {
        return root->value;
    }
    int leftValue = findMaxValue(root->left, maxDepth);
    int rightValue = findMaxValue(root->right, maxDepth);
    if (leftValue == -1 && rightValue == -1) {
        return -2; 
    } else if (leftValue == -1) {
        return rightValue;
    } else if (rightValue == -1) {
        return leftValue;
    } else {
        return (leftValue > rightValue) ? leftValue : rightValue; 
}

void printTree(Node* root, int level) {
    if (root == NULL) {
        return;
    }
    printTree(root->right, level + 1);
    for (int i = 0; i < level; i++) {
        printf("   ");
    }
    printf("%d\n", root->value);
    printTree(root->left, level + 1);
}

int main() {
    int n, rootValue, parentValue, value;
    char child;
    scanf("%d", &n);
    scanf("%d", &rootValue);
    Node* root = createNode(rootValue);
    for (int i = 0; i < n - 1; i++) {
        scanf("%d %d %c", &parentValue, &value, &child);
        insert(&root, parentValue, value, child);
    }
    int maxDepth = getMaxDepth(root);
    int maxValue = findMaxValue(root, maxDepth);
    if (maxValue == -1) {
        printf("Дерево пустое\n");
    } else if (maxValue == -2) {
        printf("Нет вершины с максимальной глубиной\n");
    } else {
        printf("Значение вершины с максимальной глубиной: %d\n", maxValue);
    }
    printf("Дерево:\n");
    printTree(root, 0);
    return 0;
}
