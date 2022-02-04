/* @Author 
Student Name: Zeynep Deniz Gündoğan
Student ID: 040190382
Date:26.10.2021*/

#include <iostream> 
#include <stdlib.h>
#include <fstream>
#include "linkedList.h"

using namespace std;

int main(int argc, char* argv[]) {

	system("clear");// make this line as comment if you are compiling on Linux or Mac
	//system("cls"); // make this line as comment if you are compiling on Windows

    LinkedList newLinkedList;

    newLinkedList.readChar();

    cout<<"Readed letters in linked list: ";
    newLinkedList.printList();

    newLinkedList.reorderList();
    cout<<"After reordering: ";
    newLinkedList.printList();

    newLinkedList.removeDublicates();
    cout<<"After removing dublicates: ";
    newLinkedList.printList();
    
    newLinkedList.reverseList();
    cout<<"Reversed list: ";
    newLinkedList.printList();

    return EXIT_SUCCESS;
}