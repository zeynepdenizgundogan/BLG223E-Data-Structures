/* @Author 
Student Name: Zeynep Deniz Gündoğan
Student ID : 040190382 
Date: 10.11.2021 */

#include <iostream>
#include <stdio.h>
#include <string.h>

#include "linkedList.h"

using namespace std;

void Train::create(){
    head=NULL;
};

wagonNode* Train::findWagonForRemoving(char removedId){ //the function that finds suitable wagon for the removal 
    wagonNode* suitableWagon=new wagonNode; 
    suitableWagon=findTailWagon(); //I found last wagon and put it in suitablewagon variable 
    int length=suitableWagon->wagonId; //The wagonid of last wagon is equal to length of linkedlist 

    while(suitableWagon->findMaterialNode(removedId)==NULL){  //while loop controls if suitable wagon has material with input id. If it does not have the material loop continues.
        wagonNode* tempWagon=new wagonNode;
        tempWagon=head;
        
        if(tempWagon->next->findMaterialNode(removedId)==NULL){ // if tempwagon's next does not have a material with input id return head 
                return head;
        }
        for(int i=1;i<=length-1;i++){ //continue in loop form 1 to length-1 (the reason for -1 is that we control the tail wagon in while loop so its not necesery to go for the length.

            tempWagon=tempWagon->next; //go to tempwagon's next and update the tempwagon
            suitableWagon=tempWagon; //make tempwagon the suitablewagon

        }
        length-=1; //decrease the length with -1 so that loop can stop at the previous wagon
    }
    return suitableWagon; 
};

wagonNode* Train::findPrevWagon(char removedId, wagonNode* suitableWagon){
    
    wagonNode* prevWagon=new wagonNode;
    prevWagon=head;

    int length=suitableWagon->wagonId; 
    
    for(int i=1; i<=length-2;i++){ // this time loop continue to length-2 because we are trying to find previous
        prevWagon=prevWagon->next; //go to prevwagon's next and update the prevwagon
    }
    return prevWagon;
};

materialNode* wagonNode::findMaterialNode(char addedId){ //function to find suiatable material node with input material id
    materialNode* curr=material;
    while(curr!=NULL){
        if(curr->id==addedId){
            return curr;
        }
        else{
            curr=curr->next;
        }
    }
    return curr;
};

materialNode* wagonNode::findPrevMaterialNode(char removedId){
    materialNode* removedMaterialNode=new materialNode; //the node that we want to remove from the wagon
    materialNode* prevMaterialNode=new materialNode; //the previous node of the wagon that we want to remove
    removedMaterialNode=material; 
    prevMaterialNode=material;

    while(removedMaterialNode!=NULL){ //continue to loop while removed material node is not null
        if(removedMaterialNode->id==removedId){ //if material id is the id that we want to remove
            return prevMaterialNode; 
        }
        prevMaterialNode=removedMaterialNode; // if material id is not id that we want to remove make prev equal to removed material
        removedMaterialNode=removedMaterialNode->next; //go to removedmaterialnode's next and update the removedmaterialnode
    }
    return prevMaterialNode; 
};

void Train::sortMaterial(wagonNode* currWagon, materialNode* lastMaterial){
    materialNode* currMaterial=currWagon->material; 

    while(currMaterial!=NULL){
        if(currMaterial->id > lastMaterial->id){// compare the material nodes ids. If part means that if current material node's id is greater that the material id of the last material that we added 
            // this part changes the id and weight datas of the material nodes 
            char c=currMaterial->id; 
            int w=currMaterial->weight;

            currMaterial->id=lastMaterial->id;
            currMaterial->weight=lastMaterial->weight;

            lastMaterial->id=c;
            lastMaterial->weight=w;
            }
        currMaterial=currMaterial->next; //I go to the next current material so that it can compare with every material node in the wagon 
    } 
};

wagonNode* Train::findTailWagon(){ //function to find the last wagon
    if(head==NULL){
        return head;
    }
    else{
        wagonNode* tailNode=head;
        while(tailNode->next!=NULL){
            tailNode=tailNode->next;
        }
        return tailNode;
    }
};
int Train::addWeight(int weight, materialNode* MaterialNode){
//this function is for adding and updating the weight
int capacity=MaterialNode->weight;
int availableCap=2000-capacity;

    if (weight<availableCap){
        MaterialNode->weight=MaterialNode->weight+weight;
        weight=0;  
        return weight;  
    }
    else{
    MaterialNode->weight=2000;
    weight=weight-availableCap;
    return weight;
    }
};

void Train::addMaterial(char material, int weight){
    //FILL THIS FUNCTION ACCORDINGLY
    wagonNode* currWagon=new wagonNode; 
    currWagon=head;

    while(weight>0){
        if(head==NULL){ // if there is no wagon add the first wagon
            wagonNode* newWagon=new wagonNode;
            currWagon=newWagon;
            currWagon->wagonId=1;
            head=currWagon;
        }
        else{ // if there is wagon
            while (currWagon!=NULL){ //contiune inside of the loop while currwagon is not null (this is because we go to the next wagon after every adding. If it is null it will go out of the while loop and add new wagon)
                if(weight==0){ // when I was adding more that 2kg, in one of the scenerios it was contiunuing in the loop after finishing the adding so I put break
                    break;
                }
                if(currWagon->material==NULL){ //if there is no material node add the first material node for the current wagon
                    materialNode* addedMaterialNode=new materialNode;
                    addedMaterialNode->id=material;
                    weight=addWeight(weight,addedMaterialNode);
                    currWagon->material=addedMaterialNode;
                    currWagon=currWagon->next;
                }
                else{// if there is material node add the material node as tail then sort it
                    if(currWagon->findMaterialNode(material)==NULL){ //if there is material node but its id is not the same as input id
                    materialNode* addedMaterialNode=new materialNode;
                    addedMaterialNode->id=material;
                    weight=addWeight(weight,addedMaterialNode);

                        materialNode* tailMaterial=new materialNode; 
                        tailMaterial=currWagon->material;

                        while(tailMaterial->next!=NULL){
                            tailMaterial=tailMaterial->next;
                        }
                        
                        tailMaterial->next=addedMaterialNode;
                        sortMaterial(currWagon, addedMaterialNode); //After adding the material node sort the nodes
                    
                    currWagon=currWagon->next;
                }

                else { //If there is suitable material node with the desired id
                    materialNode* availableMaterial=new materialNode;
                    availableMaterial=currWagon->findMaterialNode(material);
                    weight=addWeight(weight, availableMaterial);

                    currWagon=currWagon->next;
                }
            }
        }       
            if(weight==0){ //Code was continuing and adding new wagon even though the weight is zero
                break;
            }
            //adding new wagon and updating currwagon if necesery
            wagonNode* endWagon=findTailWagon();
            int endWagonId=endWagon->wagonId;
            endWagon->next = new wagonNode;
            endWagon=endWagon->next;
            endWagon->wagonId=endWagonId+1;
            currWagon=endWagon; 
        }
    }
};

void Train::deleteFromWagon(char material, int weight){
    //FILL THIS FUNCTION ACCORDINGLY
    while(weight!=0){
        wagonNode* suitableWagon=new wagonNode;
        suitableWagon=findWagonForRemoving(material); //find suitable wagon for removing 
        materialNode* removedMaterialNode=new materialNode;
        materialNode* prevMaterialNode=new materialNode;
        removedMaterialNode=suitableWagon->findMaterialNode(material); //find suitable material with the input id for removing 
        prevMaterialNode=suitableWagon->findPrevMaterialNode(material); //find suitable materials prev
        
        if(weight<=removedMaterialNode->weight){ //if the weight is less than the material weight inside of the material node 
            removedMaterialNode->weight-=weight;//remove as much as the input weight 
            weight-=weight; //remove weight as much as the input weight and updat weight
        }
        else{//if the input weight is more than the weight inside of the material node 
            int currWeight=removedMaterialNode->weight; 
            removedMaterialNode->weight-=removedMaterialNode->weight;//remove as much as the weight inside of the material node
            weight=weight-currWeight;//Subtract the amount removed from the weight
        }

        if(removedMaterialNode->weight==0){ //if material node weigth is zero 
            if(suitableWagon->material==removedMaterialNode){ //if the removed material node is the first material node of the wagon
                if(removedMaterialNode->next!=NULL){ //if the removed material node is not the only material node in the wagon 
                    suitableWagon->material=removedMaterialNode->next;
                    delete removedMaterialNode;
                }
                else{//if it is the only material node
                    suitableWagon->material=NULL;
                    delete removedMaterialNode;
                }
            }
            else{// if the material node is not the first material node of the wagon
                prevMaterialNode->next=removedMaterialNode->next;
                removedMaterialNode->next=NULL;
                delete removedMaterialNode;
            }
        }

        if(suitableWagon->material==NULL){//if wagon has no material nodes than wagon should be deleted
            wagonNode* prevWagon=new wagonNode;
            prevWagon=findPrevWagon(material, suitableWagon);
            
            if(suitableWagon==head){//if suitable wagon is the only wagon remaning
                head=NULL;
                delete suitableWagon;
            }
            else{//if there are more wagons
                prevWagon->next=NULL;
                delete suitableWagon;
            }
        }
    }
};

void Train::printWagon(){
    wagonNode* tempWagon = head;

    if(tempWagon == NULL){
            cout<<"Train is empty!!!"<<endl;
            return;
    }

    while(tempWagon != NULL){
        materialNode* tempMat = tempWagon->material;
        cout<<tempWagon->wagonId<<". Wagon:"<<endl; 
        while (tempMat != NULL){
            cout<<tempMat->id<<": "<<tempMat->weight<<"KG, "; 
            tempMat = tempMat->next;  
        }
        cout<<endl; 
        tempWagon = tempWagon->next;
    }
    cout<<endl;
}; 