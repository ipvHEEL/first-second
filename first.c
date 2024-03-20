#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100
#define MAX_STUDENTS 100
struct Student {
    char name[MAX_LINE_LENGTH];
    char group[MAX_LINE_LENGTH];
    float totalGrade;
    int count;
};
int main() {
    FILE *inputFile, *outputFile;
    char line[MAX_LINE_LENGTH];
    struct Student students[MAX_STUDENTS];
    int numStudents = 0;
    inputFile = fopen("in.txt", "r");
    

    // Считываем данные из файла и вычисляем средний балл для каждого студента
    while (fgets(line, sizeof(line), inputFile) != NULL) {
        char name[MAX_LINE_LENGTH], group[MAX_LINE_LENGTH], subject[MAX_LINE_LENGTH];
        float grade;
        sscanf(line, "%s %s %s %f", name, group, subject, &grade);

        // Поиск студента в массиве
        int found = 0;
        for (int i = 0; i < numStudents; i++) {
            if (strcmp(students[i].name, name) == 0 && strcmp(students[i].group, group) == 0) {
                students[i].totalGrade += grade;
                students[i].count++;
                found = 1;
                break;
            }
        }

        // Если студент не найден, добавляем его в массив
        if (!found) {
            strcpy(students[numStudents].name, name);
            strcpy(students[numStudents].group, group);
            students[numStudents].totalGrade = grade;
            students[numStudents].count = 1;
            numStudents++;
        }
    }
    fclose(inputFile);
    outputFile = fopen("out.txt", "w");
    // Записываем средний балл каждого студента
    for (int i = 0; i < numStudents; i++) {
        float averageGrade = students[i].totalGrade / students[i].count;
        fprintf(outputFile, "%s %s %.2f\n", students[i].name, students[i].group, averageGrade);
    }
    fclose(outputFile);
    printf("Успешно записано в out.txt\n");

    return 0;
}
