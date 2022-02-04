/* @Author 
Student Name: Zeynep Deniz Gündoğan
Student ID: 040190382
Date:26.10.2021*/

#include <iostream>
#include <stdio.h>
#include <fstream>
#include "linkedList.h"

using namespace std;

void Node::set_letter(char letter){
    this->letter=letter;
}

char Node::get_letter(){
    return this->letter;
}

void Node::set_next(Node* next){
    this->next=next;
}

Node* Node::get_next(){
    return this->next;
}

void LinkedList::readChar(){

    FILE* inFile = fopen("input.txt", "r");

    if(inFile==NULL){
        return;
    }

    char c;
    c=fgetc(inFile);
    Node* newNode= new Node;
    newNode = head;
    newNode->set_letter(c);


    while (!feof(inFile)){
        c=fgetc(inFile);
    
      if(c!='\n'&& !feof(inFile)){

          Node* tailNode = new Node;
          newNode->set_next(tailNode); 
          newNode=tailNode;
          newNode->set_letter(c); 
        
      }
    }
    fclose(inFile);
};

void LinkedList::reorderList(){
    //FILL THIS FUNCTION ACCORDINGLY

    Node* curr;
    Node* nextNode;
    char c;

    for(curr=head;curr->get_next()!=NULL;curr=curr->get_next()){

        for(nextNode=curr->get_next();nextNode!=NULL;nextNode=nextNode->get_next()){
            
            if(curr->get_letter() > nextNode->get_letter()){
                c=curr->get_letter();
                curr->set_letter(nextNode->get_letter());
                nextNode->set_letter(c);
            }
        }
    }
};

void LinkedList::removeDublicates(){
    //FILL THIS FUNCTION ACCORDINGLY
    Node* curr=head;
    Node* nextNode=curr->get_next();

    while(curr->get_next()!=NULL){
        if(curr->get_letter()==nextNode->get_letter()){

            nextNode=curr->get_next()->get_next();
            delete curr->get_next();
            curr->set_next(nextNode);

        }
        else{
            nextNode=nextNode->get_next();
            curr=curr->get_next();
        } 
    }
};

void LinkedList::reverseList(){
    //FILL THIS FUNCTION ACCORDINGLY 
    Node* prevNode=NULL;
    Node* nextNode=NULL;
    Node* currNode=head;
    
    if(head==NULL){
        return;
    }

    while(currNode!=NULL){
            
            nextNode=currNode->get_next();
            currNode->set_next(prevNode);
            prevNode=currNode;
            currNode=nextNode;
            head=prevNode; 
    } 
};

void LinkedList::printList(){
    Node* temp = head;
    while(temp != NULL){
        cout<<temp->letter<<" ";
        temp = temp->next;
    }
    cout<<endl; 
};