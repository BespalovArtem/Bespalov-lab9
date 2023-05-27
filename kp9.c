#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct Table {
    int key;
    int value;
} Table;

void Swap(Table *x, Table *y) {
    Table temporary = *x;
    *x = *y;
    *y = temporary;
}

int f;
void Bracketize(Table a[], int i) {
    int winner = i;
    int right = 2*i + 2;
    int left = 2*i + 1;
    if (left < f && a[left].key > a[i].key) {
        winner = left;
    }
    if (right < f && a[right].key > a[winner].key) {
        winner = right;
    }
    if (winner != i) {
        Swap(&a[i], &a[winner]);
        Bracketize(a, winner);
    }
}

void Heap(Table a[]) {
    int i = (f - 2) / 2;
    while (i >= 0) {
        Bracketize(a, i--);
    }
}

void Tournament(Table a[], int n) {
    f = n;
    Heap(a);
    while (f != 1) {
        Swap(&a[0], &a[f - 1]);
        --f;
        Bracketize(a, 0);
    }
}

int Search(Table a[], int n, int value) {
    int low = 0, high = n - 1, middle;
    while (low <= high) {
        middle = (low + high) / 2;
        if (a[middle].key == value) return a[middle].value;
        if (a[middle].key > value) high = middle - 1;
        else low = middle + 1;
    }
    return -1;
}

void TableValues(Table *a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i].value);
    }
    printf("\n");
}

void TableKeys(Table *a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i].key);
    }
    printf("\n");
}

int main(void) {
    Table a[10] = {};
    int n;
    int key, value;
    printf("Введи количество элементов: ");
    scanf("%d", &n);
    int scanKey, element = -1;
    printf("Введи эелементы: ключ и значение\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &key, &value);
        a[i].key = key;
        a[i].value = value;
    }
    printf("\n");
    printf("Отсортированная таблица\n");
    Tournament(a, n);
    TableKeys(a, n);
    TableValues(a, n);
    printf("\n");
    printf("Введите ключ: ");
    scanf("%d", &scanKey);
    element = Search(a, n, scanKey);
    if (element != -1) printf("%d\n", element);
    else printf("По заданному ключу элемент не найден\n");
    return 0;
}
