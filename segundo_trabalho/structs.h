//imports libs
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <ncurses.h>

using namespace std;


class Board {
    public:
        char title[100], summary[100], time[100], local[100], attendance[3];};


class Person {
    public:    
        char name[100], email[100];};


class Student: public Person {
    public:
        char registration[10], course[100];};


class Evaluators: public Person {
    public:
        char institution[10];};


class Node {
    public:
        Board board;
        Student student;
        Evaluators evaluators[3];
        Person advisor;

        bool active;};