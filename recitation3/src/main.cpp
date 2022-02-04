
/* @Author
Student Name: Zeynep Deniz Gündoğan
Student ID : 040190382
Date: 8.11.2021 */

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <stack>
#include <string>
#include <iomanip>

using namespace std;

void infix_to_postfix(string,string&);
bool higher_priority(char,char);
double eval_postfix(string);
double evaluate(double,double,char);

int main(){
    string infix;
    string postfix;
    bool is_exit = false;

    while(!is_exit)
    {
        cout<<"Input the expression in infix: ";
        cin>>infix;

        if (infix == "E" || infix == "e") 
            is_exit = true;

        else
        {
            infix_to_postfix(infix, postfix);
            cout<<postfix<<endl;
            cout<<setprecision(2)<<fixed<<eval_postfix(postfix)<<endl;
        }
        
        cin.clear();
        cin.ignore();
        infix.clear();
        postfix.clear();

    }
    return EXIT_SUCCESS;
}

void infix_to_postfix(string infix,string& postfix)
{
    stack<char> s;
    // *********************Fill this method 

    for (char c:infix){ // continue to loop for every char in infix 

        if(c>=48 && c<=57){ // if scanned char's ascii number i between 48 to 57 (ascii representation of number from 0 to 9)
            postfix+=c; // add c to postfix string
        }

        else if(c=='+' || c=='-' || c=='*' || c=='/'){ // if scanned char is operator 
            
            if(s.empty()){ // if stack is empty
                s.push(c); // push scanned char into the stack
            } 

            else{ // if stack is not empty 
                
                if(!higher_priority(s.top(),c)){ // if higher priority relationship with c and s.top() is c>s.top()
                    
                    s.push(c);
                }

                else if(higher_priority(s.top(),c )){//if higher priority relationship with c and s.top() is c<=s.top()
                    
                    while(!s.empty() && higher_priority(s.top(),c)){ //while stack is not empty and higher priority relationship with c and s.top() is c<=s.top()

                        char temp=s.top(); //put top of the stack into temprory char variable
                        postfix+=temp; // add temp to postfix 
                        s.pop(); //pop the top value in the stack

                    }
                    s.push(c); //add scanned char into the stack when stack is empty
                }

            }
        }
    }

    while(!s.empty()){// this while loop is for putting remaining elements in the stack to postfix string after the reaching the end of the infix string
        postfix+=s.top();
        s.pop();
    }
}

bool higher_priority(char first,char second){
    if(first=='*' || first=='/')
        return true;
    else if(second=='+' || second=='-')
        return true;
    else return false;
}

double eval_postfix(string expr){
    stack<double> s;
    double first, second;
    // *********************Fill this method
    for (char c:expr){ // move through each char in the expr string
        if(c>=48 && c<=57){ // if scanned char's ascii number i between 48 to 57 (ascii representation of number from 0 to 9)
            char num= c- '0'; // ascii number of 0 is 48. So I subtracted the ascii value of '0' from each char value so that I can turn the values into decimal form
            s.push(num);
        }
        else {
            second=s.top(); //added stack's top to second 
            //top elementi önce seconda atıyoruz çünkü operatordan sonraki ilk iki elementi sırayla alıyoruz yani tersten ilerliyoruz 
            //örn: 342/ 4/2 istiyoruz bu yüzden 2 second 4 first
            s.pop(); //deleted stack's top
            first=s.top(); //added stack's new top to first
            s.pop();//deleted stack's top
            s.push(evaluate(first, second, c)); //making calculations
        }
    }

    return s.top();
}

double evaluate(double first,double second,char c){
    switch(c){
        case '*':
            return first*second;
        case '+':
            return first+second;
        case '-':
            return first-second;
        case '/':
            return first/second;
        default:
            return 0;
    }
}
