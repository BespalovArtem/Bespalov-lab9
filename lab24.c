#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

struct expressionTree {
    char value;
    int v;
    struct expressionTree* l_s;
    struct expressionTree* r_s;
    int status;
};

int getPriority(char elem) {
    if (elem == '+' || elem == '-')
        return 1;
    else if (elem == '*' || elem == '/')
        return 2;
    else if (elem == '^')
        return 3;
    else
        return 0;
}

bool isOperator(char elem) {
    return (!isdigit(elem) && !isalpha(elem));
}

char* infixToPostfix(char* input) {
    char* result = (char*)malloc(strlen(input) * sizeof(char));
    int resultIndex = 0;
    int inputLength = strlen(input);
    struct Stack {
        int top;
        unsigned capacity;
        char* array;
    };

    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = inputLength;
    stack->top = -1;
    stack->array = (char*)malloc(stack->capacity * sizeof(char));

    if (input[0] == '\0') {
        printf("empty expression, please try again:");
        fgets(input, sizeof(input), stdin);
        printf("\n");
        result = infixToPostfix(input);
    }
    else {
        for (int i = 0; i < inputLength; i++) {
            if (isOperator(input[i]) == false) {
                result[resultIndex++] = input[i];
            }
            else {
                if (stack->top == -1 || stack->array[stack->top] == '(') {
                    stack->array[++stack->top] = input[i];
                }
                else if (input[i] == ')') {
                    while (stack->top != -1) {
                        if (stack->array[stack->top] == '(') {
                            stack->top--;
                            break;
                        }
                        result[resultIndex++] = stack->array[stack->top--];
                    }
                }
                else if (input[i] == '(') {
                    stack->array[++stack->top] = input[i];
                }
                else if (getPriority(input[i]) > getPriority(stack->array[stack->top])) {
                    stack->array[++stack->top] = input[i];
                }
                else if (getPriority(input[i]) <= getPriority(stack->array[stack->top])) {
                    while (stack->top != -1) {
                        if (getPriority(input[i]) > getPriority(stack->array[stack->top]) || stack->array[stack->top] == '(') {
                            break;
                        }
                        result[resultIndex++] = stack->array[stack->top--];
                    }
                    stack->array[++stack->top] = input[i];
                }
                else if (input[i] == '(') {
                    stack->array[++stack->top] = input[i];
                    printf("%d\n", stack->top);
                }
            }
        }
    }
    while (stack->top != -1) {
        result[resultIndex++] = stack->array[stack->top--];
    }
    result[resultIndex] = '\0';

    return result;
}

struct expressionTree* createExpressionTree(char* expression) {
    struct Stack {
        int top;
        unsigned capacity;
        struct expressionTree** array;
    };

    struct Stack* nodes = (struct Stack*)malloc(sizeof(struct Stack));
    nodes->capacity = strlen(expression);
    nodes->top = -1;
    nodes->array = (struct expressionTree**)malloc(nodes->capacity * sizeof(struct expressionTree*));

    struct expressionTree* node = NULL;
    for (int i = 0; i < strlen(expression); i++) {
        if (isOperator(expression[i]) == false) {
            node = (struct expressionTree*)malloc(sizeof(struct expressionTree));
            node->value = expression[i];
            node->l_s = NULL;
            node->r_s = NULL;
            nodes->array[++nodes->top] = node;
        }
        else {
            node = (struct expressionTree*)malloc(sizeof(struct expressionTree));
            node->value = expression[i];
            node->r_s = nodes->array[nodes->top--];
            node->l_s = nodes->array[nodes->top--];
            nodes->array[++nodes->top] = node;
        }
    }
    node = nodes->array[nodes->top];
    free(nodes);

    return node;
}

void TreeWalk(struct expressionTree* root) {
    struct expressionTree* current_node = root;
    if (current_node != NULL) {
        printf("%c", current_node->value);
        TreeWalk(current_node->l_s);
        TreeWalk(current_node->r_s);
    }
    else {
        return;
    }
}

void Obhod(struct expressionTree* root) {
    int mas = 0;
    int prois = 1;
    char* mass;
    struct expressionTree** ind;
    struct expressionTree* cn = root;
    struct Queue {
        int front, rear, size;
        unsigned capacity;
        struct expressionTree** array;
    };

    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->capacity = 100;
    q->front = q->size = 0;
    q->rear = q->capacity - 1;
    q->array = (struct expressionTree**)malloc(q->capacity * sizeof(struct expressionTree*));

    if (root == NULL) {
        return;
    }
    else {
        q->rear = (q->rear + 1) % q->capacity;
        q->array[q->rear] = root;
    }

    while (q->front != (q->rear + 1) % q->capacity) {
        cn = q->array[q->front];
        q->front = (q->front + 1) % q->capacity;

        printf("%c\n", cn->value);
        if (isalpha(cn->value)) {
            mas = mas + 1;
            char b = cn->value;
            char c = b;
            mass[mas] = c;
            ind[mas] = cn;
        }

        if (!isalpha(cn->value) && cn->value != '*') {
            char r = (cn->value);
            int res = atoi(&r);
            prois = res * prois;
        }

        if (cn->l_s != NULL) {
            q->rear = (q->rear + 1) % q->capacity;
            q->array[q->rear] = cn->l_s;
        }
        if (cn->r_s != NULL) {
            q->rear = (q->rear + 1) % q->capacity;
            q->array[q->rear] = cn->r_s;
        }
    }
    printf("\n\n");

    printf("\n\n");

    cn = root;

    for (int i = 0; i < mas; i++) {
        cn->r_s = ind[i];
        struct expressionTree* rn;
        rn = cn->l_s;
        cn = cn->r_s;

        cn->r_s = NULL;
        cn->l_s = NULL;
        cn = rn;
    }

    cn = cn->l_s;
    cn->v = prois;
    cn->l_s = NULL;
    cn->r_s = NULL;

    q->front = q->size = 0;
    q->rear = q->capacity - 1;
    q->rear = (q->rear + 1) % q->capacity;
    q->array[q->rear] = root;

    while (q->front != (q->rear + 1) % q->capacity) {
        cn = q->array[q->front];
        q->front = (q->front + 1) % q->capacity;

        printf("%c\n", cn->value);

        if (cn->l_s != NULL) {
            struct expressionTree* kn;
            kn = cn->l_s;
            if (kn->l_s == NULL) {
                cn = kn;
                cn->v = prois;
                printf("%d\n", cn->v);
            }
            q->rear = (q->rear + 1) % q->capacity;
            q->array[q->rear] = cn->l_s;
        }
        if (cn->r_s != NULL) {
            q->rear = (q->rear + 1) % q->capacity;
            q->array[q->rear] = cn->r_s;
        }
    }

    free(q->array);
    free(q);
}

int main(void) {
    char inf[] = "2*a*2*b*3*c";
    printf("%s\n", inf);
    printf("\n");
    char* post = infixToPostfix(inf);
    struct expressionTree* root = createExpressionTree(post);
    Obhod(root);
    printf("\n%s\n%c\n", post, root->value);
    return 0;
}
