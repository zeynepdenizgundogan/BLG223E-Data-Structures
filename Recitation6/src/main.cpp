/* @Author 
Student Name: Zeynep Deniz Gündoğan
Student ID : 040190382 
Date: 10.01.2022 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include<string>
#include <map>
#include <unordered_map>
#include <fstream>
#include <iomanip>

using namespace std;

string file_path;

bool perform_operation(char);
void print_menu();
void listProducts();
void listDay();

int main(int argc, char* argv[])
{
    bool end = false;
    char choice;
    ifstream inFile;

    file_path = argv[1];

    inFile.open(file_path,ios::in);
    if (!inFile.is_open()) 
    {
        cerr << "File cannot be opened";
        return EXIT_FAILURE;
    }

    while (!end)
    {
        print_menu();
        cin >> choice;
        end = perform_operation(choice);
    }
    
    inFile.close();
    return EXIT_SUCCESS;

}

void print_menu()
{
    cout << "Choose an operation" << endl;
    cout << "L: List 5 products with the highest revenue for total" << endl;
    cout << "D: List 5 products with the highest revenue for each day" << endl;
    cout << "E: Exit" << endl;
    cout << "Enter a choice {L, D, E}: ";
}

bool perform_operation(char choice)
{
    bool terminate = false;
    string strday;

    switch (choice)
    {
    case 'L':
    case 'l':
        listProducts();
        break;
    case 'D':
    case 'd':
        listDay();
        break;
    case 'E':
    case 'e':
            terminate = true;
        break;
    default:
        cout << "Error: You have entered an invalid choice" << endl;
        cin >> choice;
        terminate = perform_operation(choice);
        break;
    }
    return terminate;
}

void listProducts()
{
// *********************Fill this method 
    map<string, double> productMap;

    int i=0;
    string line;
    string day;
    string product;
    double productPrice=0;
    int quantity=0;
    double revenue=0;
    ifstream fileInfo;
    fileInfo.open(file_path);
    
    while(getline(fileInfo, line)){
        istringstream ss(line);
        ss >> product >> productPrice >> quantity >> day; // set the variables  
        if(i==0){ //first line is the name of the columns so we dont want to add it to the map
            i++;
            getline(fileInfo, line); //go to next line
            istringstream ss(line); 
            ss >> product >> productPrice >> quantity >> day; // set the variables 
        }
        
        if(productMap[product]==0){ // if product's revenue is zero we are adding revenue for the first time
            revenue=productPrice*quantity;
            productMap[product]=revenue;
        }
        else{
            revenue=productPrice*quantity;
            productMap[product]=productMap[product]+revenue; // if it is not zero we add it to the previous one
        }
    } 
    //sortling values by using multimap
    multimap<double,string> highRev;
    map<string,double>::iterator it;

    for(it=productMap.begin();it!=productMap.end();it++){
        highRev.insert(make_pair(it->second,it->first));
	}
    multimap <double,string>::reverse_iterator myit;
    int count;
    cout<<"5 products with the highest revenue for total are:"<<endl;
    for (myit=highRev.rbegin(),count=0;count<5;myit++,count++){
        cout<<(*myit).second<<" "<<fixed<<setprecision(2)<<(*myit).first<<endl;
    }
}

void listDay()
{
// *********************Fill this method 
    //I used 2-dim map because I need to group revenues and products by days 
    map<string, map<string, double>> dayMap;
    
    int i=0;
    string line;
    string day;
    string product;
    float productPrice=0;
    int quantity=0;
    double revenue=0;
    ifstream fileInfo;
    fileInfo.open(file_path);
    
    while(getline(fileInfo, line)){
        istringstream ss(line);
        ss >> product >> productPrice >> quantity >> day; 
        if(i==0){
            i++;
            getline(fileInfo, line);
            istringstream ss(line); 
            ss >> product >> productPrice >> quantity >> day;
        }
        
        if(dayMap[day][product]==0){
            revenue=productPrice*quantity;
            dayMap[day][product]=revenue;
        }
        else{
            revenue=productPrice*quantity;
            dayMap[day][product]=dayMap[day][product]+revenue;
        }
    }
    //I sorted every days product-revenue map by making multimap for each day
    multimap<double,string> mondayRevenue;
    multimap<double,string> sundayRevenue;
    multimap<double,string> tuesdayRevenue;
    multimap<double,string> wednesdayRevenue;
    multimap<double,string> thursdayRevenue;
    multimap<double,string> fridayRevenue;
    multimap<double,string> saturdayRevenue;

    map<string,double>::iterator it;
    string days[7]={"Monday", "Sunday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
   for (int i = 0; i<7;i++){
        multimap<double,string> day_multimap;
        map<string,double>::iterator it;

        for(it=dayMap[days[i]].begin();it!=dayMap[days[i]].end();it++){
            day_multimap.insert(make_pair(it->second,it->first));
        }

        multimap <double,string>::reverse_iterator rit;
        int count;
        cout<<"5 products with the highest revenue for "<<days[i]<<" are:"<<endl;
        for (rit=day_multimap.rbegin(),count=0;count<5;rit++,count++){
            cout<<fixed<<setprecision(2)<<(*rit).second<<" "<<(*rit).first<<endl;
        }
    }
}