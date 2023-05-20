#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 1000 
#define MAX_GRADES 4 

int main() {
    int p; 
    printf("Введите номер группы: ");
    scanf("%d", &p);
    char filename[] = "students.csv"; 
    FILE* file = fopen(filename, "r"); 
    if (file == NULL) { 
        printf("Ошибка открытия файла\n");
        return 1;
    }
    char line[MAX_LINE_LEN]; 
    int numStudents = 0; 
    int numStudentsWith = 0; 

    while (fgets(line, MAX_LINE_LEN, file)) { 
        char* token = strtok(line, ","); 
        int studentGroup = atoi(token); 

        if (studentGroup == p) { 
            numStudents++;
            int numGrades = 0; 
            while (token != NULL) { 
                token = strtok(NULL, ","); 
                if (token != NULL) { 
                    int grade = atoi(token);
                    if (grade == 3) { 
                        numGrades++; 
                    }
                }
            }
            if (numGrades > 2) { 
                numStudentsWith++; 
            }
        }
    }
    printf("Количество студентов в группе P: %d\n", numStudents);
    printf("Количество студентов с больше чем двумя тройками: %d\n", numStudentsWith);
    fclose(file); 
    return 0;
}
