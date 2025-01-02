#include <stdio.h>
#include <string.h>
#include "Functions.h"

void pressToExitOrReturn() { 
    char choice;
    printf("\nPress [0] to exit the program or [b] to return to the menu: ");
    scanf(" %c", &choice);

    if (choice == '0') {
        printf("Exiting the program...\n");
        exit(0);
    } else if (choice == 'b' || choice == 'B') {
        printf("Returning to the menu...\n");
        return; 
    } else {
        printf("Invalid input. Returning to the menu...\n");
        return; 
    }
}

void inputStudent(Student students[], int *n) {
    int num;
    printf("Enter the number of students to add: ");
    scanf("%d", &num);
    getchar();  // Clear newline left by scanf

    for (int i = 0; i < num; i++) {
        
        students[*n].id = *n + 1;
        printf("Enter student ID: ");
        scanf("%d", &students[*n].id);
        getchar();

        printf("Enter student name: ");
        fgets(students[*n].name, 50, stdin);
        students[*n].name[strcspn(students[*n].name, "\n")] = '\0';  

        printf("Enter classroom ID: ");
        scanf("%d", &students[*n].classroomId);
        getchar();  

        printf("Enter gender: ");
        fgets(students[*n].gender, 10, stdin);
        students[*n].gender[strcspn(students[*n].gender, "\n")] = '\0';  

        printf("Enter email: ");
        fgets(students[*n].email, 50, stdin);
        students[*n].email[strcspn(students[*n].email, "\n")] = '\0';  

        printf("Enter phone number: ");
        fgets(students[*n].phone, 20, stdin);
        students[*n].phone[strcspn(students[*n].phone, "\n")] = '\0';  

        (*n)++;
    }
    printf("%d students have been added to the list.\n", num);
}


void printStudent(Student students[], int n) {
    printf("\nStudent List:\n");
    printf("ID   | Name                | Classroom | Gender    | Email                   | Phone\n");
    printf("-----------------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-4d | %-20s | %-9d | %-9s | %-23s | %-15s\n",
               students[i].id, students[i].name, students[i].classroomId, students[i].gender,
               students[i].email, students[i].phone);
    }
    pressToExitOrReturn();
}

void updateStudent(Student students[], int n) {
    int id;
    printf("Enter the ID of the student to update: ");
    scanf("%d", &id);
    getchar(); 
    int i;
    for (i = 0; i < n; i++) {
        if (students[i].id == id) {
            break;
        }
    }
    if (i == n) {
        printf("Student with ID %d does not exist.\n", id);
    } else {
        printf("Enter new name: ");
        fgets(students[i].name, 50, stdin);
        students[i].name[strcspn(students[i].name, "\n")] = '\0';
        printf("Enter new classroom ID: ");
        scanf("%d", &students[i].classroomId);
        getchar();
        printf("Enter new gender: ");
        fgets(students[i].gender, 10, stdin);
        students[i].gender[strcspn(students[i].gender, "\n")] = '\0';
        printf("Enter new email: ");
        fgets(students[i].email, 50, stdin);
        students[i].email[strcspn(students[i].email, "\n")] = '\0';
        printf("Enter new phone number: ");
        fgets(students[i].phone, 20, stdin);
        students[i].phone[strcspn(students[i].phone, "\n")] = '\0';
        printf("Student information updated successfully.\n");
    }
    pressToExitOrReturn();
}

void deleteStudent(Student students[], int *n) {
    int id;
    printf("Enter the ID of the student to delete: ");
    scanf("%d", &id);
    int i;
    for (i = 0; i < *n; i++) {
        if (students[i].id == id) {
            break;
        }
    }
    if (i == *n) {
        printf("Student with ID %d does not exist.\n", id);
    } else {
        for (int j = i; j < *n - 1; j++) {
            students[j] = students[j + 1];
        }
        (*n)--;
        printf("Student with ID %d has been deleted.\n", id);
    }
    pressToExitOrReturn();
}

void saveStudentsToFile(Student students[], int n) {
    FILE *file = fopen("student.bin", "wb");
    if (file == NULL) {
        printf("Could not open file.\n");
        return;
    }
    fwrite(students, sizeof(Student), n, file);
    fclose(file);
    printf("Student information saved successfully.\n");
}

void loadStudentsFromFile(Student students[], int *n) {
    FILE *file = fopen("student.bin", "rb");
    if (file == NULL) {
        printf("Could not open file.\n");
        return;
    }
    *n = fread(students, sizeof(Student), 100, file);
    fclose(file);
    printf("Student data loaded successfully.\n");
}

void displayStudentsMenu() {
    Student students[100];
    int n = 0;
    int studentChoice;
    loadStudentsFromFile(students, &n);
    do {
        printf("\n*** Student Management System Using C ***\n");
		printf(" \n");
		printf("         =========MENU=========\n");
		printf("         [1] Input A New Student.\n");
		printf("         [2] Show All Students.\n");
		printf("         [3] Update A Student.\n");
		printf("         [4] Delete A Student.\n");
		printf("         [5] Search A Student.\n");
		printf("         [6] Arrange Students\n");
		printf("         [0] Exit Program.\n");
		printf("         ======================\n");
		printf("         Enter Your Choice: ");
        scanf("%d", &studentChoice);
        getchar();

        switch (studentChoice) {
            case 1:
                inputStudent(students, &n);
                saveStudentsToFile(students, n);
                break;
            case 2:
                printStudent(students, n);
                break;
            case 3:
                updateStudent(students, n);
                saveStudentsToFile(students, n);
                break;
            case 4:
                deleteStudent(students, &n);
                saveStudentsToFile(students, n);
                break;
            case 5:
                updateStudent(students, n);
                saveStudentsToFile(students, n);
                break;
            case 0:
                printf("Returning to Main Menu...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (studentChoice != 0);
}

void displayMainMenu() {
    printf("\n=========== MAIN MENU ===========\n");
    printf("1. Manage Students\n");
    printf("2. Manage Teacher\n");
    printf("3. Manage Classroom\n");
    printf("0. Exit\n");
    printf("=================================\n");
    printf("Your choice: ");
}
