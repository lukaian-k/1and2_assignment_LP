//imports libs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>


typedef struct person {
    char name[100], email[100];
} Person;


typedef struct board {
    char title[100], summary[100], time[100], local[100], attendance[3];
} Board;


typedef struct student {
    Person person;
    char registration[10], course[100];
} Student;


typedef struct evaluators {
    Person person;
    char institution[100];
} Evaluators;


typedef struct node{
    Board board;
    Student student;
    Evaluators evaluators[3];
    Person advisor;

    int active;
} Node;