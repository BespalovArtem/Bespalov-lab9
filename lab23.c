#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *left;
    struct Node *right;
} Node;

Node* СreateNode(int value) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void Insert(Node** root, int parentValue, int value, char child) {
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
    Insert(&((*root)->left), parentValue, value, child);
    Insert(&((*root)->right), parentValue, value, child);
}

int GetMaxDepth(Node* root) {
    if (root == NULL) {
        return 0;
    }
    int leftDepth = GetMaxDepth(root->left);
    int rightDepth = GetMaxDepth(root->right);
    return 1 + ((leftDepth > rightDepth) ? leftDepth : rightDepth);
}

int FindMaxValue(Node* root, int maxDepth) {
    if (root == NULL) {
        return -1; 
    }
    if (GetMaxDepth(root) == maxDepth) {
        return root->value;
    }
    int leftValue = FindMaxValue(root->left, maxDepth);
    int rightValue = FindMaxValue(root->right, maxDepth);
    if (leftValue == -1 && rightValue == -1) {
        return -2; 
    } else if (leftValue == -1) {
        return rightValue;
    } else if (rightValue == -1) {
        return leftValue;
    } else {
        return (leftValue > rightValue) ? leftValue : rightValue; 
}

void PrintTree(Node* root, int level) {
    if (root == NULL) {
        return;
    }
    PrintTree(root->right, level + 1);
    for (int i = 0; i < level; i++) {
        printf("   ");
    }
    printf("%d\n", root->value);
    PrintTree(root->left, level + 1);
}

int main() {
    int n, rootValue, parentValue, value;
    char child;
    scanf("%d", &n);
    scanf("%d", &rootValue);
    Node* root = CreateNode(rootValue);
    for (int i = 0; i < n - 1; i++) {
        scanf("%d %d %c", &parentValue, &value, &child);
        Insert(&root, parentValue, value, child);
    }
    int maxDepth = GetMaxDepth(root);
    int maxValue = FindMaxValue(root, maxDepth);
    if (maxValue == -1) {
        printf("Дерево пустое\n");
    } else if (maxValue == -2) {
        printf("Нет вершины с максимальной глубиной\n");
    } else {
        printf("Значение вершины с максимальной глубиной: %d\n", maxValue);
    }
    printf("Дерево:\n");
    PrintTree(root, 0);
    return 0;
}
