/* @Author
Student Name: Zeynep Deniz Gündoğan
Student ID : 040190382
Date: 13.12.2021 */

#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include <iomanip>
#include <cmath>
#include "huffman.h"

using namespace std;

int Huffman::findindex(Token *arr,string elem){

    for (int i = 0; i<token_count; i++){
        if (arr[i].symbol == elem){
            return i;
        }
    }
    return -1;
}

void Huffman::find_frequencies(){
    
    int index = -1;
    ifstream file_obj; //object to read file
    file_obj.open("../input.txt",ifstream::in);
    char symbol = 0;
    if (!file_obj.is_open()) {
        file_obj.open("input.txt",ifstream::in);
        if (!file_obj.is_open()) {
            cerr << "Could not open the file" << endl;
            exit(1);
        }
    }
    while (file_obj.get(symbol)) 
    {
        string s;
        s.push_back(symbol);

        string elem;
        elem.assign(1,symbol); // making char to string
        
        index = findindex(token_array,elem);

        if (index >= 0){
            token_array[index].count++;
        }
        else if(index == -1){
            token_array[token_count].count = 1;
            token_array[token_count].symbol = symbol;
            token_count++;
        }
    }
    file_obj.close();
}

PriorityQueue::PriorityQueue()
{
    head = NULL;
    token_count = 0;
}

void PriorityQueue::push(Node *newnode)
{
	if (head==NULL){ // if head is null then the node that will be pushed is head
        head = newnode;
    }
    else{// if it is not null then there are nodes in the queue
        Node* curr = head;
       if(newnode->token.count<curr->token.count){ 
           //if newnode token frequency less than current token freuency newnode will be added to head
           head = newnode;
           head->next = curr;
       }
       else{// otherwise it should be added in between or tail
           Node* prev=head;
           curr=curr->next;
           
           while(curr!=NULL && newnode->token.count>curr->token.count){ //this while loop finds the place where node should be adde
               curr=curr->next;
               prev=prev->next;
           }
            prev->next = newnode;
            newnode->next = curr;
       }
    }
    token_count++;
}

Node* PriorityQueue::pop()
{
    Node* firstNode=head;
    head=head->next;
    token_count--;
    return firstNode;
}

void Huffman::get_priority_queue()
{
    int i=0;
    while(i<token_count){
        Node* newnode = new Node();
        newnode->token = token_array[i];
        priority_queue.push(newnode); 
        i++;
    }
}

HuffmanBinaryTree::HuffmanBinaryTree()
{
    root = NULL;
}

Node * HuffmanBinaryTree::merge(Node *node1, Node *node2)
{
    Node* merged = new Node();
    merged->token.count = node1->token.count + node2->token.count;
    merged->token.symbol = node1->token.symbol + node2->token.symbol;

    return merged;
}

void HuffmanBinaryTree::delete_postorder_traversal(Node *traversal)
{
    if(traversal!=NULL) 
    {
        delete_postorder_traversal(traversal->left);
        delete_postorder_traversal(traversal->right);
        delete traversal;
    }
}

HuffmanBinaryTree::~HuffmanBinaryTree()
{
    delete_postorder_traversal(root);
    cout<<"Code with no memory leak ;)"<<endl;
    root = NULL;
}

void Huffman::get_huffman_tree()
{
    Node* first_child = new Node();
    Node* second_child = new Node();
    Node* parent = new Node;
    while (priority_queue.token_count>1){ //Controls if priority queue has more than one node
        first_child = priority_queue.pop();
        second_child = priority_queue.pop();
        parent = huffman_binary_tree.merge(first_child,second_child);
        parent->left = first_child;
        parent->right = second_child;
        priority_queue.push(parent);
        huffman_binary_tree.root = parent;
    }    
}

void Huffman::get_codes(Node *traversal,string codepart)
{   

    if(traversal->left==NULL && traversal->right==NULL){
        int traversal_index = findindex(token_array,traversal->token.symbol);
        token_array[traversal_index].code = codepart;
    }  

    if(traversal->right!=NULL){
        get_codes(traversal->right, codepart+"1");
    }

    if(traversal->left!=NULL){
        get_codes(traversal->left, codepart+"0");
    }
}
string Huffman::return_code(string target)
{
    int index = findindex(token_array,target);
    return token_array[index].code;
}

double Huffman::calculate_compression_ratio()
{
    double bit_required_before = 0;
    for(int i=0;i<token_count;i++)
        bit_required_before += token_array[i].count * 8;
    double bit_required_after = 0;
    for(int i=0;i<token_count;i++)
        bit_required_after += token_array[i].count * token_array[i].code.length();
    return bit_required_before / bit_required_after;
}
