#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

Student* create_student(char* first, char* last, int id, double gpa)
{
    Student* s = malloc(sizeof(Student));
    s->first_name = malloc(strlen(first) + 1);
    s->last_name = malloc(strlen(last) + 1);
    strncpy(s->first_name, first, strlen(first) + 1);
    strncpy(s->last_name, last, strlen(last) + 1);
    s->id = id;
    s->gpa = gpa;

    return s;
}

void free_student(Student* s)
{
    free((*s).first_name);
    free((*s).last_name);
    free(s);
}

void print_student(Student* s)
{
    //[ID] Last, First (GPA: X.XX)
    printf("[%d] %s, %s (GPA: %.2f)\n", (*s).id, (*s).last_name, (*s).first_name, (*s).gpa);
}

Student* create_student_from_string(char* full_name, int id, double gpa)
{
    char* scan = full_name;
    char* space = scan;
    char* first_name;
    char* last_name;
    while(*scan != '\0')
    {
        if(*scan == ' ')
        {
            first_name = malloc(scan - full_name + 1);
            strncpy(first_name, full_name, scan - full_name);
            first_name[scan - full_name] = '\0';
            space = scan + 1;
        }
        scan = scan + 1;
    }

    if(space != full_name){
        last_name = malloc(scan - space + 1);
        strncpy(last_name, space, scan - space + 1);

        Student* s = create_student(first_name, last_name, id, gpa);
        free(first_name);
        free(last_name);
        return s;
    }
    //Error state
    else
    {
        return NULL;
    }
}

int main()
{
    Student* s = create_student_from_string("Grace Hopper", 42, 5.00);
    print_student(s);
    free_student(s);
}