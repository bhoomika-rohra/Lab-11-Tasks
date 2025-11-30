#include <stdio.h>
#include <string.h>

#define MAX 100

struct student{
    char name[50];
    int roll;
    float marks[3];
    char grade[3];
    float percentage;
};

float GetValidMarks(int subject){
    float m;
    while(1){
        printf("Enter marks for subject %d (0-100): ", subject+1);
        scanf("%f",&m);
        if(m>=0 && m<=100) return m;
        else printf("Invalid marks! Try again.\n");
    }
}

void CalculateGrade(struct student s[], int n){
    for(int i=0;i<n;i++){
        float sum = s[i].marks[0] + s[i].marks[1] + s[i].marks[2];
        s[i].percentage = (sum / 300) * 100;

        if(s[i].percentage >= 90) strcpy(s[i].grade,"A+");
        else if(s[i].percentage >= 80) strcpy(s[i].grade,"A");
        else if(s[i].percentage >= 70) strcpy(s[i].grade,"B+");
        else if(s[i].percentage >= 60) strcpy(s[i].grade,"B");
        else if(s[i].percentage >= 50) strcpy(s[i].grade,"C");
        else strcpy(s[i].grade,"F");
    }
}

void SearchStudent(struct student s[], int n){
    int choice;
    printf("\nSearch Student by:\n1) Roll Number\n2) Name\nEnter choice: ");
    scanf("%d",&choice);
    if(choice==1){
        int roll;
        printf("Enter roll number: ");
        scanf("%d",&roll);
        for(int i=0;i<n;i++){
            if(s[i].roll==roll){
                printf("Name: %s\nRoll: %d\nPercentage: %.2f%%\nGrade: %s\n",
                    s[i].name, s[i].roll, s[i].percentage, s[i].grade);
                return;
            }
        }
        printf("Student not found.\n");
    } else if(choice==2){
        char name[50];
        printf("Enter name: ");
        scanf(" %[^\n]", name);
        for(int i=0;i<n;i++){
            if(strcmp(s[i].name,name)==0){
                printf("Name: %s\nRoll: %d\nPercentage: %.2f%%\nGrade: %s\n",
                    s[i].name, s[i].roll, s[i].percentage, s[i].grade);
                return;
            }
        }
        printf("Student not found.\n");
    } else {
        printf("Invalid choice.\n");
    }
}

void Average(struct student s[], int n){
    float total=0;
    for(int i=0;i<n;i++) total += s[i].percentage;
    float classAvg = total / n;
    printf("\nClass Average: %.2f%%\n", classAvg);

    printf("\nStudents above average:\n");
    for(int i=0;i<n;i++)
        if(s[i].percentage>classAvg) printf("%s\n", s[i].name);

    printf("\nStudents below average:\n");
    for(int i=0;i<n;i++)
        if(s[i].percentage<classAvg) printf("%s\n", s[i].name);
}

void DisplayByGrade(struct student s[], int n){
    char grade[3];
    printf("\nEnter grade to search (A+, A, B+, B, C, F): ");
    scanf("%s",grade);
    printf("\nStudents with grade %s:\n", grade);
    for(int i=0;i<n;i++)
        if(strcmp(s[i].grade,grade)==0)
            printf("%s (Roll: %d, %.2f%%)\n", s[i].name,s[i].roll,s[i].percentage);
}

void DisplayRank(struct student s[], int n){
    struct student temp;
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(s[j].percentage<s[j+1].percentage){
                temp = s[j];
                s[j] = s[j+1];
                s[j+1] = temp;
            }
        }
    }
    printf("\nStudent Ranking:\n");
    for(int i=0;i<n;i++)
        printf("%d. %s - %.2f%% - %s\n", i+1, s[i].name, s[i].percentage, s[i].grade);
}

int main(){
    struct student s[MAX];
    int n;

    printf("Enter number of students: ");
    scanf("%d",&n);

    for(int i=0;i<n;i++){
        printf("\nEnter data for Student %d\n", i+1);
        printf("Name: ");
        scanf(" %[^\n]", s[i].name);
        printf("Roll Number: ");
        scanf("%d",&s[i].roll);
        for(int j=0;j<3;j++)
            s[i].marks[j] = GetValidMarks(j);
    }

    CalculateGrade(s,n);

    int choice;
    do{
        printf("\n========== MENU ==========\n");
        printf("1. Search Student\n");
        printf("2. Display Class Stats\n");
        printf("3. Display by Grade\n");
        printf("4. Display Rank\n");
        printf("5. Exit\n");
        printf("==========================\n");
        printf("Enter choice: ");
        scanf("%d",&choice);

        switch(choice){
            case 1: {
                SearchStudent(s,n);
                break;
            }
            case 2: {
                Average(s,n);
                break;
            }
            case 3: {
                DisplayByGrade(s,n);
                break;
            }
            case 4: {
                DisplayRank(s,n);
                break;
            }
            case 5: {
                printf("Exiting...\n");
                break;
            }
            default: {
                printf("Invalid choice!\n");
                break;
            }
        }
    }while(choice!=5);

    return 0;
}
