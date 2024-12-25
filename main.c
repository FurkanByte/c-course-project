//
// Created by Furkan on 26.12.2024.
// This file created for EENG212 Course Project
// Binary Search Tree
//
#include <stdio.h>
#include <stdlib.h>

struct Course {
    char lecturerName[50];
    char lecturerSurname[50];
    char courseName[50];
    int courseCode;
    int academicSemester;
    int attendance;
    float midtermScore;
    float finalScore;
    float labScore;
    float quizScore;
    float courseGrade;
};



int menu();
void insertNewNode(struct Course *);

int main() {
    printf("Hello World\n");
}