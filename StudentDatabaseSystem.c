
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50
#define MAX_BRANCH 30
#define MAX_EMAIL 50
#define PAGE_SIZE 5

struct Student {
    int id;
    char name[MAX_NAME];
    int age;
    char branch[MAX_BRANCH];
    float cgpa;
    char email[MAX_EMAIL];
};

int login() {
    char username[20], password[20];
    printf("Admin Login\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
        printf("Login successful.\n");
        return 1;
    } else {
        printf("Invalid credentials.\n");
        return 0;
    }
}

void pause() {
    printf("Press Enter to continue...");
    getchar();
    getchar();
}

void addStudent(FILE *fp) {
    struct Student s;
    printf("Enter ID: ");
    scanf("%d", &s.id);
    getchar();
    printf("Enter Name: ");
    fgets(s.name, MAX_NAME, stdin);
    s.name[strcspn(s.name, "\n")] = 0;

    printf("Enter Age: ");
    scanf("%d", &s.age);
    getchar();
    printf("Enter Branch: ");
    fgets(s.branch, MAX_BRANCH, stdin);
    s.branch[strcspn(s.branch, "\n")] = 0;

    printf("Enter CGPA: ");
    scanf("%f", &s.cgpa);
    getchar();
    printf("Enter Email: ");
    fgets(s.email, MAX_EMAIL, stdin);
    s.email[strcspn(s.email, "\n")] = 0;

    fseek(fp, 0, SEEK_END);
    fwrite(&s, sizeof(s), 1, fp);
    printf("Student added successfully.\n");
}

void listStudents(FILE *fp) {
    struct Student s;
    rewind(fp);
    int count = 0, page = 1;
    printf("\n%-5s %-20s %-4s %-10s %-5s %-30s\n", "ID", "Name", "Age", "Branch", "CGPA", "Email");
    printf("-------------------------------------------------------------------------------\n");
    while (fread(&s, sizeof(s), 1, fp)) {
        printf("%-5d %-20s %-4d %-10s %-5.2f %-30s\n", s.id, s.name, s.age, s.branch, s.cgpa, s.email);
        count++;
        if (count % PAGE_SIZE == 0) {
            printf("---- Page %d ----\n", page++);
            pause();
        }
    }
}

void updateStudent(FILE *fp) {
    struct Student s;
    int id, found = 0;
    printf("Enter ID to update: ");
    scanf("%d", &id);
    rewind(fp);
    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.id == id) {
            found = 1;
            int choice;
            do {
                printf("\nWhat do you want to update?\n");
                printf("1. Name\n2. Age\n3. Branch\n4. CGPA\n5. Email\n0. Done\nEnter choice: ");
                scanf("%d", &choice);
                getchar();
                switch (choice) {
                    case 1:
                        printf("Enter new Name: ");
                        fgets(s.name, MAX_NAME, stdin);
                        s.name[strcspn(s.name, "\n")] = 0;
                        break;
                    case 2:
                        printf("Enter new Age: ");
                        scanf("%d", &s.age);
                        break;
                    case 3:
                        printf("Enter new Branch: ");
                        fgets(s.branch, MAX_BRANCH, stdin);
                        s.branch[strcspn(s.branch, "\n")] = 0;
                        break;
                    case 4:
                        printf("Enter new CGPA: ");
                        scanf("%f", &s.cgpa);
                        break;
                    case 5:
                        printf("Enter new Email: ");
                        fgets(s.email, MAX_EMAIL, stdin);
                        s.email[strcspn(s.email, "\n")] = 0;
                        break;
                }
            } while (choice != 0);

            fseek(fp, -sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, fp);
            printf("Student record updated.\n");
            break;
        }
    }
    if (!found) printf("Student ID not found.\n");
}

void deleteStudent(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    FILE *temp = fopen("temp.txt", "wb");
    struct Student s;
    int id, found = 0;
    printf("Enter ID to delete: ");
    scanf("%d", &id);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.id != id) {
            fwrite(&s, sizeof(s), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);
    remove(filename);
    rename("temp.txt", filename);

    if (found) printf("Student deleted.\n");
    else printf("Student ID not found.\n");
}

void displayStats(FILE *fp) {
    struct Student s;
    rewind(fp);
    int total = 0;
    float totalCgpa = 0, maxCgpa = 0;

    while (fread(&s, sizeof(s), 1, fp)) {
        total++;
        totalCgpa += s.cgpa;
        if (s.cgpa > maxCgpa) maxCgpa = s.cgpa;
    }

    if (total == 0) {
        printf("No student records found.\n");
        return;
    }

    printf("\nTotal Students: %d\n", total);
    printf("Average CGPA: %.2f\n", totalCgpa / total);
    printf("Highest CGPA: %.2f\n", maxCgpa);
}

void searchStudent(FILE *fp) {
    struct Student s;
    char keyword[MAX_NAME];
    int found = 0;

    getchar();
    printf("Enter name or branch to search: ");
    fgets(keyword, MAX_NAME, stdin);
    keyword[strcspn(keyword, "\n")] = 0;

    rewind(fp);
    while (fread(&s, sizeof(s), 1, fp)) {
        if (strstr(s.name, keyword) || strstr(s.branch, keyword)) {
            printf("%-5d %-20s %-4d %-10s %-5.2f %-30s\n", s.id, s.name, s.age, s.branch, s.cgpa, s.email);
            found = 1;
        }
    }

    if (!found) printf("No matching records found.\n");
}

int main() {
    const char *filename = "students.txt";
    FILE *fp;

    if (!login()) return 0;

    fp = fopen(filename, "rb+");
    if (fp == NULL) {
        fp = fopen(filename, "wb+");
        if (fp == NULL) {
            perror("File error");
            return 1;
        }
    }

    int choice;
    do {
        printf("\nStudent Database System\n");
        printf("1. Add Student\n");
        printf("2. List Students\n");
        printf("3. Update Student\n");
        printf("4. Delete Student\n");
        printf("5. Search Student\n");
        printf("6. Display Statistics\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: addStudent(fp); break;
            case 2: listStudents(fp); break;
            case 3: updateStudent(fp); break;
            case 4: fclose(fp); deleteStudent(filename); fp = fopen(filename, "rb+"); break;
            case 5: searchStudent(fp); break;
            case 6: displayStats(fp); break;
            case 0: printf("Exiting...\n"); break;
            default: printf("Invalid choice.\n"); break;
        }
    } while (choice != 0);

    fclose(fp);
    return 0;
}
