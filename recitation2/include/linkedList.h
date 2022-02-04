/* @Author 
Student Name: Zeynep Deniz Gündoğan
Student ID: 040190382
Date:26.10.2021*/

#ifndef _H
#define _H

#include <iostream>
#include <stdio.h>

using namespace std;

class Node{
    public:
        char letter;
        Node* next;
        void set_letter(char);
        char get_letter();
        void set_next(Node*);
        Node* get_next();
};

class LinkedList{

    Node* head;

    public:

        void readChar();
        void reorderList();
        void removeDublicates();
        void reverseList();
        void printList();
};

#endif