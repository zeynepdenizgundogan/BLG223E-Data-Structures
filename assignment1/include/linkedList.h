/* @Author 
Student Name: Zeynep Deniz GÃ¼ndoÄŸan
Student ID : 040190382 
Date: 10.11.2021 */

#ifndef _H
#define _H

#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

class materialNode{
    public:
        char id;
        int weight;
        materialNode* next;
};

class wagonNode{
    
    public:
        int wagonId;
        materialNode* material;
        wagonNode* next;
        materialNode* findPrevMaterialNode(char addedId);
        materialNode* findMaterialNode(char);
        
};

class Train{  

    wagonNode* head;
    
    public:
        void create();
        void addMaterial(char,int);
        void deleteFromWagon(char, int); 
        void printWagon(); //Prints wagon info
        void sortMaterial(wagonNode*, materialNode*);
        wagonNode* findWagonForRemoving(char);
        wagonNode* findTailWagon();
        wagonNode* findPrevWagon(char, wagonNode*);
        int addWeight(int, materialNode*);
        
};

#endif