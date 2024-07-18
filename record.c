#include <stdio.h>
#include <string.h>

struct gradeStructure
{
    char student_name[20];
    int student_row_number;
    int student_grade;
    char student_remark[5];
};

struct gradeStructure students[100];
int table_length = 0;
int passing_threshold = 40;

void add_student()
{
    struct gradeStructure student;

    printf("Enter student name: ");
    scanf("%s", student.student_name);

    student.student_row_number = table_length + 1;
    printf("Enter student grade: ");
    scanf("%d", &student.student_grade);
    if (student.student_grade >= passing_threshold)
    {
        strcpy(student.student_remark, "Pass");
    }
    else
    {
        strcpy(student.student_remark, "Fail");
    }
    students[table_length] = student;
    table_length++;
}

void list_students()
{
    if (table_length == 0)
    {
        printf("No students listed.\n");
    }
    else
    {
        printf("Listing students:\n");
        for (int i = 0; i < table_length; i++)
        {
            printf("Row: %d, Name: %s, Grade: %d, Remark: %s\n",
                   students[i].student_row_number,
                   students[i].student_name,
                   students[i].student_grade,
                   students[i].student_remark);
        }
    }
}

void save_students_to_file(const char *filename)
{
    FILE *fptr = fopen(filename, "w");
    if (fptr == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < table_length; i++)
    {
        fprintf(fptr, "%s %d %d %s\n",
                students[i].student_name,
                students[i].student_row_number,
                students[i].student_grade,
                students[i].student_remark);
    }

    fclose(fptr);
    printf("File saved.\n");
}

void load_students_from_file(const char *filename)
{
    FILE *fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        printf("Error opening file for reading.\n");
        return;
    }

    table_length = 0;
    while (fscanf(fptr, "%s %d %d %s",
                  students[table_length].student_name,
                  &students[table_length].student_row_number,
                  &students[table_length].student_grade,
                  students[table_length].student_remark) != EOF)
    {
        table_length++;
    }

    fclose(fptr);
    printf("Loaded %d students from file.\n", table_length);
}

int main()
{
    char firstname[100];
    int choice;
    char save_choice;

    printf("Hello, kindly enter your firstname\n");
    scanf("%s", firstname);
    printf("Hello %s\n", firstname);

    printf("Enter passing threshold: ");
    scanf("%d", &passing_threshold);

    do
    {
        printf("Menu\n 1. Add Student\n 2. Remove Student\n 3. List Students\n 4. Load From File\n 5. Save and Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            printf("Add Student\n");
            add_student();
            printf("\nStudent added: ROW %d\n", table_length);
        }
        else if (choice == 2)
        {
            printf("Remove Student\n");
            int row_number;
            printf("Enter row number of student to remove: ");
            scanf("%d", &row_number);
            if (row_number > table_length || row_number < 1)
            {
                printf("Student not found\n");
            }
            else
            {
                for (int i = row_number - 1; i < table_length - 1; i++)
                {
                    students[i] = students[i + 1];
                }
                table_length--;
                printf("Student removed\n");
            }
        }
        else if (choice == 3)
        {
            list_students();
        }
        else if (choice == 4)
        {
            printf("Loading students from file.\n");
            load_students_from_file("student_record.txt");
        }

    } while (choice != 5);

    printf("Do you want to save the students to file? (y/n)\n");
    scanf(" %c", &save_choice);
    if (save_choice == 'y')
    {
        save_students_to_file("student_record.txt");
    }
    else
    {
        printf("Changes not saved.\n");
    }

    printf("Thank you %s\n", firstname);
    return 0;
}
