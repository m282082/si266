#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

Student* create_student(char* first, char* last, int id, double gpa)
{
    Student* s = malloc(sizeof(Student));
    s->first_name = malloc(sizeof(char*));
    s->last_name = malloc(sizeof(char*));
    strncpy(s->first_name, first, sizeof(char*));
    strncpy(s->last_name, last, sizeof(char*));
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

int main()
{
    Student* s = create_student("Grace", "Hopper", 42, 5.00);
    print_student(s);
    free_student(s);
}