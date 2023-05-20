#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE 100 

typedef struct Coordinates {
    int row;
    int col;
    int value;
} coord;

int main() {
    int matrix[MAX_SIZE][MAX_SIZE]; 
    int n, m; 
    int target; 
    int minDistance = 99999; 
    printf("Введите размеры матрицы (n, m): ");
    scanf("%d %d", &n, &m);
    printf("Введите элементы матрицы:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    printf("Введите искомое значение: ");
    scanf("%d", &target);
    coord closestCoords[MAX_SIZE*MAX_SIZE]; 
    int closestCount = 0; 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int distance = abs(matrix[i][j] - target); 
            if (distance < minDistance) { 
                minDistance = distance; 
                closestCount = 1; 
                closestCoords[0] = (coord) {i, j, matrix[i][j]}; 
            } else if (distance == minDistance) {
                closestCoords[closestCount++] = (coord) {i, j, matrix[i][j]}; 
            }
        }
    }
    for (int i = 0; i < closestCount; i++) {
        int row = closestCoords[i].row;
        int col = closestCoords[i].col;
        int value = closestCoords[i].value;
        for (int k = 0; k < m; k++) {
            if (matrix[row][k] != 0) { 
                matrix[row][k] /= value; 
            }
        }
        for (int k = 0; k < n; k++) {
            if (matrix[k][col] != 0) { 
                matrix[k][col] /= value; 
            }
        }
    }
    printf("Результат:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    return 0;
}
