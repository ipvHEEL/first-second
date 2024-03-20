#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100
#define MAX_STUDENTS 100

struct Student {
    char name[MAX_LINE_LENGTH];
    char group[MAX_LINE_LENGTH];
    float totalGrade;
};

int main() {
    FILE *inputFile, *outputFile;
    char line[MAX_LINE_LENGTH];
    struct Student students[MAX_STUDENTS] = {0};
    int numStudents = 0;
    inputFile = fopen("in.txt", "r");
    // Считываем данные из файла и вычисляем суммарный балл для каждого студента
    while (fgets(line, sizeof(line), inputFile) != NULL) {
        char name[MAX_LINE_LENGTH], group[MAX_LINE_LENGTH];
        float grade;
        sscanf(line, "%s %s %*s %f", name, group, &grade);

        // Поиск студента в массиве
        int found = 0;
        for (int i = 0; i < numStudents; i++) {
            if (strcmp(students[i].name, name) == 0) {
                if (grade > students[i].totalGrade) {
                    strcpy(students[i].group, group);
                    students[i].totalGrade = grade;
                }
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(students[numStudents].name, name);
            strcpy(students[numStudents].group, group);
            students[numStudents].totalGrade = grade;
            numStudents++;
        }
    }
    fclose(inputFile);
    outputFile = fopen("out.txt", "w");
    if (outputFile == NULL) {
        perror("Ошибка открытия файла");
        return EXIT_FAILURE;
    }
    // Записываем студента с наилучшей успеваемостью в каждой группе
    for (int i = 0; i < numStudents; i++) {
        fprintf(outputFile, "%s %s %.2f\n", students[i].group, students[i].name, students[i].totalGrade);
    }
    fclose(outputFile);
    printf("Успешно записано в out.txt\n");
    return 0;
}
