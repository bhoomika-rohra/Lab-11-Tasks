#include <stdio.h>
#include <string.h>

#define MAX_EMPLOYEES 100

struct Employee {
    int id;
    char name[50];
    char department[20];
    char designation[20];
    float salary;
    char joinDate[11];
    char phone[15];
    char email[50];
};

struct Employee employees[MAX_EMPLOYEES];
int empCount = 0;
int currentYear = 2025;

int calculateExperience(struct Employee e) {
    int joinYear;
    sscanf(e.joinDate + 6, "%d", &joinYear);
    return currentYear - joinYear;
}

void addEmployee() {
    struct Employee e;
    printf("Enter Employee ID: ");
    scanf("%d", &e.id);
    getchar();
    printf("Enter Name: ");
    fgets(e.name, 50, stdin);
    e.name[strcspn(e.name, "\n")] = 0;
    printf("Enter Department (IT/HR/Finance/Marketing/Operations): ");
    scanf("%s", e.department);
    printf("Enter Designation (Intern/Junior/Senior/Manager/Director): ");
    scanf("%s", e.designation);
    printf("Enter Salary: ");
    scanf("%f", &e.salary);
    printf("Enter Date of Joining (DD-MM-YYYY): ");
    scanf("%s", e.joinDate);
    printf("Enter Phone Number: ");
    scanf("%s", e.phone);
    printf("Enter Email: ");
    scanf("%s", e.email);
    employees[empCount++] = e;
    printf("Employee added successfully!\n");
}

void displayEmployees() {
    printf("\nEmployee Records:\n");
    for (int i = 0; i < empCount; i++) {
        printf("ID: %d, Name: %s, Dept: %s, Desig: %s, Salary: %.2f, Experience: %d years, Phone: %s, Email: %s\n",
               employees[i].id, employees[i].name, employees[i].department, employees[i].designation,
               employees[i].salary, calculateExperience(employees[i]), employees[i].phone, employees[i].email);
    }
}

void departmentSalaryStats() {
    char dept[20];
    scanf("%s", dept);
    int count = 0;
    float total = 0, min = 1e9, max = 0;
    for (int i = 0; i < empCount; i++) {
        if (strcmp(employees[i].department, dept) == 0) {
            float s = employees[i].salary;
            total += s;
            if (s < min) min = s;
            if (s > max) max = s;
            count++;
        }
    }
    if (count == 0) {
        printf("No employees in this department.\n");
        return;
    }
    printf("Department: %s | Total Employees: %d | Min Salary: %.2f | Max Salary: %.2f | Average Salary: %.2f\n",
           dept, count, min, max, total / count);
}

void annualAppraisal() {
    for (int i = 0; i < empCount; i++) {
        int percent;
        scanf("%d", &percent);
        if (percent < 5) percent = 5;
        if (percent > 15) percent = 15;
        employees[i].salary += employees[i].salary * percent / 100.0;
    }
    printf("Salaries updated based on appraisal.\n");
}

void searchEmployees() {
    int choice;
    scanf("%d", &choice);
    if (choice == 1) {
        char dept[20];
        scanf("%s", dept);
        for (int i = 0; i < empCount; i++)
            if (strcmp(employees[i].department, dept) == 0)
                printf("%d: %s, %s\n", employees[i].id, employees[i].name, employees[i].designation);
    } 
    else if (choice == 2) {
        char desig[20];
        scanf("%s", desig);
        for (int i = 0; i < empCount; i++)
            if (strcmp(employees[i].designation, desig) == 0)
                printf("%d: %s, Dept: %s\n", employees[i].id, employees[i].name, employees[i].department);
    } 
    else if (choice == 3) {
        int exp;
        scanf("%d", &exp);
        for (int i = 0; i < empCount; i++)
            if (calculateExperience(employees[i]) >= exp)
                printf("%d: %s, Dept: %s, Designation: %s\n", employees[i].id, employees[i].name,
                       employees[i].department, employees[i].designation);
    } 
    else printf("Invalid choice.\n");
}

void eligibleForPromotion() {
    for (int i = 0; i < empCount; i++) {
        if (calculateExperience(employees[i]) > 3)
            printf("%d: %s, Dept: %s, Designation: %s, Experience: %d years\n",
                   employees[i].id, employees[i].name, employees[i].department,
                   employees[i].designation, calculateExperience(employees[i]));
    }
}

int main() {
    int choice;
    do {
        scanf("%d", &choice);
        switch (choice) {
            case 1: addEmployee(); 
            break;
            case 2: displayEmployees(); 
            break;
            case 3: departmentSalaryStats(); 
            break;
            case 4: annualAppraisal(); 
            break;
            case 5: searchEmployees(); 
            break;
            case 6: eligibleForPromotion(); 
            break;
            case 7: 
            break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 7);
    return 0;
}
