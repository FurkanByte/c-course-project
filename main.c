//
// Created by Furkan on 26.12.2024.
// This file created for EENG212 Course Project
// Binary Search Tree
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
course *insertFromFile(course *);
void searchCourse(course *, int);
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
            root = insertFromFile(root);
        }
        else if (choice == 3) {
            int courseCodeToSearch;
            printf("Enter course code to search: ");
            scanf("%d", &courseCodeToSearch);

            searchCourse(root, courseCodeToSearch);
        }
        else if (choice == 4) {
            listLetterGrades(root);
        }
        else if (choice == 5) {
            listCourses(root);
        }
        else if (choice == 0) {
            break;
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
           "2. Add new course from a file.\n"
           "3. Search a course.\n"
           "4. List letter grades.\n"
           "5. List all courses (descending order).\n"
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

course *insertFromFile(course *root) {
    FILE *file;
    char line[100];
    course *temp;

    file = fopen("course_data.txt", "r");
    if (file == NULL) {
        printf("File cannot open.\n");
        return root;
    }

    while (fgets(line, sizeof(line), file)) {
        temp = (course *)malloc(sizeof(course));

        if (sscanf(line, "%49[^,],%49[^,],%49[^,],%d,%d,%d,%f,%f,%f,%f",
            temp->lecturerName, temp->lecturerSurname, temp->courseName,
            &temp->courseCode, &temp->academicSemester, &temp->attendance,
            &temp->midtermScore, &temp->finalScore, &temp->labScore, &temp->quizScore) == 10) {

            temp->courseGrade = (temp->midtermScore * 0.25) +
                                (temp->finalScore * 0.45) +
                                (temp->labScore * 0.2) +
                                (temp->quizScore * 0.15);

            temp->left = temp->right = NULL;

            root = insertNewNode(root, temp);

            } else {
                printf("Invalid format for course: %s\n", line);
                free(temp);
            }
    }

    fclose(file);
    printf("Your courses has been added\n");
    return root;
}

//This function list all courses in descending order.
void listCourses(course *root) {
    //if node is not NULL printing course information.
    if(root != NULL) {
        listCourses(root->right);
        printf("**********************************\n"
               "Course Name: %s\n"
               "Course Code: %d\n"
               "Lecturer Name: %s\n"
               "Lecturer Surname: %s\n"
               "Academic Semester: %d\n"
               "Attendance: %d\n"
               "Midterm Score: %f\n"
               "Final Score: %f\n"
               "Lab Score: %f\n"
               "Quiz Score: %f\n"
               "Course Grade: %f\n"
               "**********************************\n" ,root->courseName, root->courseCode, root->lecturerName, root->lecturerSurname, root->academicSemester, root->attendance, root->midtermScore, root->finalScore, root->labScore, root->quizScore, root->courseGrade);
        if(root->left != NULL) printf("\tleft->courseCode: %d", root->left->courseCode);
        if(root->right != NULL) printf("\tright->courseCode: %d", root->right->courseCode);
        listCourses(root->left);
    }
}

void listLetterGrades(course *root) {
    if(root != NULL) {
        listLetterGrades(root->right);
        printf("**********************************\n"
               "Course Name: %s\n"
               "Course Code: %d\n"
               "Course Grade: %f\n", root->courseName, root->courseCode, root->courseGrade);
        if(root->courseGrade > 85) printf("Letter grade: A\n");
        else if(root->courseGrade > 80) printf("Letter grade: A-\n");
        else if(root->courseGrade > 75) printf("Letter grade: B+\n");
        else if(root->courseGrade > 70) printf("Letter grade: B\n");
        else if(root->courseGrade > 67) printf("Letter grade: B-\n");
        else if(root->courseGrade > 63) printf("Letter grade: C+\n");
        else if(root->courseGrade > 60) printf("Letter grade: C\n");
        else if(root->courseGrade > 57) printf("Letter grade: C-\n");
        else if(root->courseGrade > 55) printf("Letter grade: D+\n");
        else if(root->courseGrade > 50) printf("Letter grade: D\n");
        else if(root->courseGrade > 45) printf("Letter grade: D-\n");
        else printf("Letter grade: F\n");
        printf("*********************************\n");
        listLetterGrades(root->left);
    }
}

void searchCourse(course *root, int courseCode) {
    if(root != NULL) {
        searchCourse(root->right, courseCode);
        if (root->courseCode == courseCode) {
            printf("**********************************\n"
               "Course Name: %s\n"
               "Course Code: %d\n"
               "Lecturer Name: %s\n"
               "Lecturer Surname: %s\n"
               "Academic Semester: %d\n"
               "Attendance: %d\n"
               "Midterm Score: %f\n"
               "Final Score: %f\n"
               "Lab Score: %f\n"
               "Quiz Score: %f\n"
               "Course Grade: %f\n"
               "**********************************\n" ,root->courseName, root->courseCode, root->lecturerName, root->lecturerSurname, root->academicSemester, root->attendance, root->midtermScore, root->finalScore, root->labScore, root->quizScore, root->courseGrade);
            return;
        }
        searchCourse(root->left, courseCode);
    }
}