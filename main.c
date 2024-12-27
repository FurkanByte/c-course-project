//
// Created by Furkan on 26.12.2024.
// This file created for EENG212 Course Project
// Binary Search Tree
//
#include <stdio.h>
#include <stdlib.h>

typedef struct course{
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
    struct course *left;
    struct course *right;
} course;


int menu();
course *insertNewNode(course*, course*);
void insertFromFile(course *);
void deleteCourse(course *, int);
void searchCourse(course *);
void listLetterGrades(course *);
void listCourses(course *);
void calculateCGPA(course *);

int main() {
    course *root = NULL;
    int choice;
    while(1) {
        choice = menu();
        if (choice == 1) {
            course *temp = (course*)malloc(sizeof(course));
            printf("Enter lecturer name: ");
            scanf("%s", temp->lecturerName);
            printf("Enter lecturer surname: ");
            scanf("%s", temp->lecturerSurname);
            printf("Enter course name: ");
            scanf("%s", temp->courseName);
            printf("Enter course code: ");
            scanf("%d", &temp->courseCode);
            printf("Enter academic semester: ");
            scanf("%d", &temp->academicSemester);
            printf("Enter attendance: ");
            scanf("%d", &temp->attendance);
            printf("Enter midterm score: ");
            scanf("%f", &temp->midtermScore);
            printf("Enter final score: ");
            scanf("%f", &temp->finalScore);
            printf("Enter lab score: ");
            scanf("%f", &temp->labScore);
            printf("Enter quiz score: ");
            scanf("%f", &temp->quizScore);
            temp->courseGrade = ((temp->midtermScore * 0.25) + (temp->finalScore*0.45) + (temp->labScore*0.2) + (temp->quizScore*0.15));
            temp->left = NULL;
            temp->right = NULL;

            root = insertNewNode(root, temp);
            printf("Your course has been added\n");
        }
        else if (choice == 2) {
            int courseCodeToDelete;
            printf("Enter course code to delete: ");
            scanf("%d", &courseCodeToDelete);

            deleteCourse(root, courseCodeToDelete);
        }
        else if (choice == 3) {
            insertFromFile(root);
        }
        else if (choice == 6) {
            listCourses(root);
        }
    }
}

//This function printing the menu for UI and returns user's choice.
int menu() {
    int option;
    printf("----------------------------\n"
           "  Course Tree System\n"
           "----------------------------\n"
           "1. Add new course.\n"
           "2. Delete a course.\n"
           "3. Add new course from a file.\n"
           "4. Search a course.\n"
           "5. List letter grades.\n"
           "6. List all courses (descending order).\n"
           "0. Exit\n"
           "----------------------------\n\n"
           "Enter your choice : ");
    scanf("%d", &option);
    return option;
}

//This function creates new node for a course.
course *insertNewNode(course *p, course *temp) {
    if(p == NULL) {
        p = temp;
        return p;
    }
    else {
        if(temp->courseGrade < p->courseGrade) p->left = insertNewNode(p->left, temp);
        else p->right = insertNewNode(p->right, temp);
        return p;
    }
}

//This function list all courses in descending order.
void listCourses(course *root) {
    //if node is not NULL printing course information.
    if(root != NULL) {
        listCourses(root->right);
        printf("**********************************\n");
        printf("%s\n", root->courseName);
        printf("%d\n", root->courseCode);
        printf("%s\n", root->lecturerName);
        printf("%f\n", root->courseGrade);
        printf("**********************************\n");
        listCourses(root->left);
    }
}

void insertFromFile(course *root) {
    printf("Inserting from file...");
    FILE *file = fopen("course_data.txt", "r");
    if (file == NULL) {
        printf("File cannot open. Please check the file.\n");
        return;
    }

    course *head = NULL, *current = NULL;

    while (!feof(file)) {
        course *temp = (course *)malloc(sizeof(course));
        if (!temp) {
            printf("Error.\n");
            break;
        }

        if (fscanf(file, "%s %s %s %d %d %d %f %f %f %f",
                   temp->lecturerName, temp->lecturerSurname, temp->courseName,
                   &temp->courseCode, &temp->academicSemester, &temp->attendance,
                   &temp->midtermScore, &temp->finalScore, &temp->labScore,
                   &temp->quizScore) != 10) {
            free(temp);
            break;
                   }

        char separator[10];
        fscanf(file, "%s", separator);

        insertNewNode(root, temp);
        current = temp;
    }
    printf("Your courses has been added\n");
}

void deleteCourse(course *root, int courseCode) {
    if(root != NULL) {
        listCourses(root->right);
        if (root->courseCode == courseCode) {
            
        }
        listCourses(root->left);
    }
}