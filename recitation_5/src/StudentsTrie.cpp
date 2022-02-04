#include <fstream>
#include <iostream>
#include "StudentsTrie.h"

/* @Author 
Student Name: Zeynep Deniz Gündoğan
Student ID : 040190382 
Date: 29.12.2021 */

using namespace std;

TrieNode::TrieNode (const char& digit){
   this->digit = digit;
   for(int i=0; i<MAX_CHILDREN; children[i++] = NULL); 
};

// Construct a StudentsTrie using the records in 'file_name' 
StudentsTrie::StudentsTrie ( const string& file_name  ) { 
    ifstream student_ids_file ( file_name );   // ifstream object for input file
    string current_student_id;

    root = new TrieNode('r');

    if( student_ids_file.is_open() ) {
        for(int i=1; student_ids_file >> current_student_id; i++ ) {
           insert_id(current_student_id); // YOU HAVE TO IMPLEMENT insert_id() METHOD
        }
        student_ids_file.close();
    }
    else {
        cout << "File: " << file_name << " could NOT be opened!!";
        exit(1);
    }

    student_ids_file.close();
};

// Insert a student ID into the StudentsTrie 
void StudentsTrie::insert_id ( const string& student_id ) {
   // IMPLEMENT THIS METHOD
   TrieNode* curr=root;
   TrieNode* temp=root;
   for(char c:student_id){
      if(curr->children[c-'0']==NULL){
         curr->children[c-'0']=new TrieNode(c);
      }
      curr=curr->children[c-'0'];
   } 
   //cout << "I have to implement insert_id() method" << endl;
}; 
void StudentsTrie::get_student_id_from_trie(TrieNode* traversal, string student_id, int* total_num){
   if(traversal!=NULL){
      for(int i=0;i<MAX_CHILDREN;i++){
         if(student_id.length()!=9){
            if(traversal->children[i]!= NULL){
               get_student_id_from_trie(traversal->children[i], student_id+traversal->children[i]->digit, total_num);
            }
         }
         else{
            get_student_id_from_trie(traversal->children[i], student_id, total_num);
            break;
         }         
      }
   }
   else{
      if(student_id.length()==9){
         cout<<student_id;
         (*total_num)++;

         if(*(total_num)%10==0){
         cout<<endl;
         }
         else{
            cout<<" ";
         }
      } 
   }
};
// Print Student IDs in Trie in ascending order 
void StudentsTrie::print_trie(){
   // IMPLEMENT THIS METHOD
   int printed_id=0;
   get_student_id_from_trie(root, "", &printed_id);
   if(printed_id%10!=0){
      cout<<endl;
   }
   //cout << "I have to implement print_trie() method" << endl;
};

// StudentsTrie Destructor
StudentsTrie::~StudentsTrie() {
   for (int i=0; i < MAX_CHILDREN; i++){
      if( root->children[i] ) delete root->children[i];
   };
};

