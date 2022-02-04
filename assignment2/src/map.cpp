#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include <iomanip>
#include <cmath>
#include "map.h"

using namespace std;

/* @Author
Student Name: Zeynep Deniz Gündoğan
Student ID: 040190382
E-mail: gundoganz19@itu.edu.tr
Date: 30.12.2021
*/

MapTree::MapTree(){
    root=NULL;
};

Node* MapTree::find_required_city(Node* traversal, string city_name){
    //This function finds the node with the required city name
    if(traversal!=NULL){
        if(traversal->name==city_name){
            return traversal;
        } 
        else{
        Node* left=find_required_city(traversal->left, city_name);
        Node* right=find_required_city(traversal->right,city_name);
        if(left==NULL && right==NULL){
            return NULL;
        }
        else{
            if(left!=NULL){
                return left;
            }
            else if(right!=NULL){
                return right;
            }
        }      
    }
}
    return NULL;
};

int MapTree::find_length(City_routes_from_file* map_arr_friend){
    /* mapp_arr_friend is th array that keeps all the data from the file
    this function finds the length of that array
    in other words it finds how many rows are in the text file*/
    int i=0;
    int length=0;
    while(!map_arr_friend[i].source.empty()){
        i++;
        length++;
    }
    return length;
};

int MapTree::find_route_info_length(route_information* route_info){
    /* route_info is th array in every node that keeps all the routes of cities with its duration
    this function finds the length of that array
    in other words it finds how many routes each cith has*/
    int i=0;
    int length=0;
    while(!route_info[i].source.empty()){
        i++;
        length++;
    }
    return length;
};

void MapTree::prunning(Node* traversal){
    if(traversal!=NULL){
        /*First I get the length of route array if it is more than one this means that traversal node has more than one poteintial
        routes. But one of them is the route that should be prunned. In order to find which route should be prunned I made a function
        that finds the index of the route with maximum duration. I give that index to find city function to find the node of the source
        and destination city in that index. If destination city is in the left of the source then make source left NULL.
        But we also need to delete the data in route information array in the given index. So that it wont check the same routes 
        over and over again.*/
        int length=find_route_info_length(traversal->Route_information);
        while(length>1){
            int index=find_max_dur_index(traversal->Route_information,length);
            Node* source=find_required_city(root, traversal->Route_information[index].source);
            Node* destination=find_required_city(root, traversal->Route_information[index].destination);

            if(source->left==destination){
                source->left=NULL;
                traversal->Route_information[index].duration=0;
                traversal->Route_information[index].source="";
                traversal->Route_information[index].destination="";
                length--;
            }

            else if(source->right==destination){
                source->right=NULL;
                traversal->Route_information[index].duration=0;
                traversal->Route_information[index].source="";
                traversal->Route_information[index].destination="";
                length--;
            }

        }
        prunning(traversal->left);
        prunning(traversal->right);

    }

};
int MapTree::find_index_with_data(route_information* route_info){
    /*After prunning the tree we delete some of the data in the route_info array. 
    But we don't know the only remaining routes' index in the route_info array
    this function finds the index of only remaining routes' index */
    int index=0;
    if(!route_info[index].source.empty()){
        return index;
    }
    while(route_info[index].source.empty()){
        index++;
    }
    return index;
};

int MapTree::find_min_dur_index(route_information* info, int length_route_info){
    /*this function finds the index of minimum duration in route_info array */
    int index = 0;

    for(int i = 1; i < length_route_info; i++)
    {
        if(info[i].duration < info[index].duration)
            index = i;              
    }
    return index;
};

int MapTree::find_max_dur_index(route_information* info, int length_route_info){
    /*this function finds the index of maximum duration in route_info array */
    int index = 0;

    for(int i = 0; i < length_route_info; i++){
        if(info[i].duration > info[index].duration)
            index = i;              
    }
    return index;
};

void Map::print_preorder_traversal(Node* traversal){
    if (traversal == NULL)
        return;

        cout <<" "<<traversal->name;

    print_preorder_traversal(traversal->left);
    print_preorder_traversal(traversal->right);

};

void MapTree::get_duration(string* common_cities, Node* root1, Node* root2 ){
    /*First while loop finds how many common cities are there in the common_cities array
    then in the for loop it searches every element in the common_cities array in both of the trees. 
    Then it finds the index of its only route in route_info array (prunedan sonra arraydeki bazı yollar silindi
    bu yüzden kaln yolun indexini bulmamız gerekir) Sonra aynı şehrin iki farklı ağacındakidurationları duration_datada topluyorum
    ve duration arrayine atıyorum. Duration arrayinde atacağım yer j olmalı çünkü işlem yaptığım ortak şehrin indexiyle 
    aynı indexte olmasını istiyorum.*/
    int i=0;
    int length=0;
    while(!common_cities[i].empty()){
        i++;
        length++;
    }
    for(int j=0;j<length;j++){
        Node* common_city_tree1=find_required_city(root1, common_cities[j]);
        Node* common_city_tree2=find_required_city(root2, common_cities[j]);

        int index1_with_data=find_index_with_data(common_city_tree1->Route_information);
        int index2_with_data=find_index_with_data(common_city_tree2->Route_information);
        
        int duration_data=common_city_tree1->Route_information[index1_with_data].duration+common_city_tree2->Route_information[index2_with_data].duration;
        duration[j]=duration_data;
    }
};

int MapTree::get_total_duration_index(int* duration){
    //This function finds the minimum total duration index from teh duration array
    int length=common_city_index; 
    /*common_city_index is the number of how many common cities we have in the txt file
    in order to not to loop unnecessarily, I assigned length to common_city_index*/
    int index=0;
    for (int i=0; i<length;i++){
        if(duration[i]<duration[index]){
            index=i;
        }
    }
    return index;
};

string MapTree::get_meeting_point(int total_duration_index, string* common_cities){
    /*If I give the index of minimum total duration to common_cities array as an index
    It would give us the meeting city  */
    return common_cities[total_duration_index];
};

void MapTree::find_common_cities(Node* traversal_city1, Node* traversal_city2){
    /*In this function I am trying to find the cities that both friend1 and friend2 can go. 
    In other words I am trying to find common cities*/
    if(traversal_city1!=NULL){
        /*In order to find the common cities I give traversal node from the second tree to the find_city function
        but I give the city names from the first tree so that it can check if a city is in both of the trees */
        Node* common_city=find_required_city(traversal_city2, traversal_city1->name);
        if(common_city==NULL){ 
            /*if a city in the first tree does not exist in the second
            it continues to search if there is common city by recursive function*/
            find_common_cities(traversal_city1->left,traversal_city2);
            find_common_cities(traversal_city1->right,traversal_city2);
        }

        else{//if there is a common city
            int i=0;
            int length=0;
            bool checker=false; //this checker control if we have found a common city
            while(!common_cities[i].empty()){ //this part finds the length of common city array
                i++;
                length++;
            }
            for(int j=0;j<length;j++){
                if(common_city->name==common_cities[j]){ 
                    /*this if checkes if if the city we are looking for is already in the common_cities array*/
                    checker=true;
                }
            }
            if(checker==false){ // if checker is false this means the common city we have found is not in the common_cities array
                common_cities[common_city_index]=common_city->name; //I added the coomon cit in the common cities array
                common_city_index++; //increment the common city index because new common city is added
            }
        }
        find_common_cities(traversal_city1->left,traversal_city2);
        find_common_cities(traversal_city1->right,traversal_city2);
    }
    
};

int MapTree::find_required_route_from_map_array(City_routes_from_file* map_arr_friend, int length,string dest_name, string source_name){
    /*This function finds the index of the mapp_arr_friend(the array that keeps all the data from the file)
    if the required destination_name and source_name matches in the indexes data then it returns that index*/
    int index=0;
    for (int i=0;i<length;i++){
        if(map_arr_friend[i].destination==dest_name && map_arr_friend[i].source==source_name){
            index=i;
        }
    }
    return index;
};

int MapTree::find_max_dur_index_with_required_source_city(string source_name, route_information *info, int length_route_info, int possible_duration){
    /*Bu fonksiyonda verilen nodeun route information arrayindeki source ismi verilen source ismine eşitse ve
    verilen nodeun route information arrayindeki durationı şehrin possible durationından büyük ise o indexi döndür.
    Bu fonksiyonu destinationın sourcedan kaynaklı birkaç farklı yolu olma ihtimali için yazdım. Eğer böyle bir durum varsa 
    maximum durationlı olan indexi bluyorum ki onun yerine possible durationı koyabileyim. Çünkü maximum duration zaten prunelanacak*/
    int index = 0;
    for(int i = 0; i < length_route_info; i++){
        if( info[i].source==source_name && info[i].duration>possible_duration)
            index = i;              
    }
    return index;
};

void MapTree::get_map_tree(City_routes_from_file* map_arr_friend){
    int i=0;
    int length=find_length(map_arr_friend);//finds the length of array which is the rows in the file or the number of links in tree

    while(i<length){ // while i is less than length continue making the tree
        if(root==NULL){ //if root is NULL create root of the tree
        Node* source=new Node();
        source->name=map_arr_friend[i].source;
        source->Route_information[i].source=source->name;
        root=source;
    }
    else{
        /*first I keep the destination and source city in the ith index of the map_arr_friend array */
            Node* destination=find_required_city(root, map_arr_friend[i].destination);
            Node* source=find_required_city(root,map_arr_friend[i].source);
            /* if destination city is NULL this means it is not in the tree. So we create that node
            and update the node's route_information array*/
            if(destination==NULL){
                destination= new Node();
                destination->name=map_arr_friend[i].destination;
                destination->Route_information[0].source=source->name;
                destination->Route_information[0].destination=destination->name;
                /*while updating the duration I added source city's duration as well. Because I need that 
                to find minimum total duration cost later on.*/
                if(source->route_num>0){
                /*Eğer source şehrinin birden fazla yolu varsa sourcedan kaynaklı olarak destination şehrininde birden fazla yolu 
                oluyor demektir. İşte bu yüzden source şehrinin minimum durationlı yolu ile destination ve source arasındaki durationu toplayark
                yeni bir yol olarak ekliyorm. Çünkü source şehrinin maximum durationlu yolu zaten prunelanacağı için destination route_info 
                arrayinde bu olasılığı tutmak gereksiz olacak. Bu yüzden sadecce minimumlu yol ile olan olasılığı ekliyorum.
                (again zero is the base condition if route_num is zero that it has only one route)*/
                    int length=find_route_info_length(source->Route_information);
                    int index=find_min_dur_index(source->Route_information,length);
                    destination->Route_information[destination->route_num].duration=map_arr_friend[i].duration+source->Route_information[index].duration;
                }
                else{
                    destination->Route_information[destination->route_num].duration=map_arr_friend[i].duration+source->Route_information[0].duration;
                }
            }

            else{
                //if destination city is in the tree increase the route number variable by one.
                destination->route_num++;
            } 
             if(destination->route_num!=0){
                /*if destination city's route number is not 1 this 
                this means destination city has different routes or it has more than one paretns
                then update destination node's route information array in the route_numth index
                (zero is the base condition if route_num is zero that it has only one route)*/
                destination->Route_information[destination->route_num].source=source->name;
                destination->Route_information[destination->route_num].destination=destination->name;

                if(source->route_num>0){
                /*Eğer source şehrinin birden fazla yolu varsa sourcedan kaynaklı olarak destination şehrininde birden fazla yolu 
                oluyor demektir. İşte bu yüzden source şehrinin minimum durationlı yolu ile destination ve source arasındaki durationu toplayark
                yeni bir yol olarak ekliyorm. Çünkü source şehrinin maximum durationlu yolu zaten prunelanacağı için destination route_info 
                arrayinde bu olasılığı tutmak gereksiz olacak. Bu yüzden sadecce minimumlu yol ile olan olasılığı ekliyorum.
                (again zero is the base condition if route_num is zero that it has only one route)*/
                    int length=find_route_info_length(source->Route_information);
                    int index=find_min_dur_index(source->Route_information,length);
                    destination->Route_information[destination->route_num].duration=map_arr_friend[i].duration+source->Route_information[index].duration;
                }
                else{
                    destination->Route_information[destination->route_num].duration=map_arr_friend[i].duration+source->Route_information[0].duration;
                }
            }

            if(destination->left!=NULL){
                Node* previously_added_city= new Node();
                previously_added_city=find_required_city(root,destination->left->name);
                int length_route_info=find_route_info_length(previously_added_city->Route_information);
                int index=find_required_route_from_map_array(map_arr_friend,length,previously_added_city->name,destination->name);
                int possible_duration= map_arr_friend[index].duration+destination->Route_information[destination->route_num].duration;
                int max_dur_index=find_max_dur_index_with_required_source_city(destination->name ,previously_added_city->Route_information,length_route_info,possible_duration);
                if(possible_duration<previously_added_city->Route_information[max_dur_index].duration){
                    previously_added_city->Route_information[max_dur_index].destination=previously_added_city->name;
                    previously_added_city->Route_information[max_dur_index].source=destination->name;
                    previously_added_city->Route_information[max_dur_index].duration=possible_duration;
                }
            }  

            if(destination->right!=NULL){
                Node* previously_added_city= new Node();
                previously_added_city=find_required_city(root,destination->right->name);
                int length_route_info=find_route_info_length(previously_added_city->Route_information);
                int index=find_required_route_from_map_array(map_arr_friend,length,previously_added_city->name,destination->name);
                int possible_duration=map_arr_friend[index].duration+destination->Route_information[destination->route_num].duration;
                int max_dur_index=find_max_dur_index_with_required_source_city(destination->name ,previously_added_city->Route_information,length_route_info,possible_duration);
                if(possible_duration<previously_added_city->Route_information[max_dur_index].duration){
                    previously_added_city->Route_information[max_dur_index].destination=previously_added_city->name;
                    previously_added_city->Route_information[max_dur_index].source=destination->name;
                    previously_added_city->Route_information[max_dur_index].duration=possible_duration;
                }
            }  

            if(source->left==NULL){ //if source's left link is null add the destination node to its left
                source->left=destination; 
                i++;
            }
            else{//if source's right link is null add the destination node to its right
                source->right=destination;
                i++;
            }
        }
    }  
};

void Map::read_file(string filename, City_routes_from_file* map_arr_friend){
    ifstream inFile;
    inFile.open(filename,ifstream::in);
    char file_char;
    int index=0;
    int place=0;
    while (inFile.get(file_char)){
        string s;

        while((file_char>=65 && file_char<=90)||(file_char>=47 && file_char<=57)){
            /*This while loops helps us to read only characters from A to Z and 0 to 9 */
            s.push_back(file_char);
            if(inFile.peek()==EOF){
                break;
            }
            inFile.get(file_char);
            
        }
        if(!s.empty()){
            /*After reading the file I am putting the data in an array 
            but in the file program reads first source city, second destination city then third duration
            I am using place variable to finds out what the program reads and puts the data where it belongs  
            Basically map_arr_friend hold all the data from the file*/
            if(place%3==0){
                map_arr_friend[index].source=s;
                place++;

            }
            else if(place%3==1){
                map_arr_friend[index].destination=s;
                place++;
            }

            else if(place%3==2){
                int i= stoi(s);
                map_arr_friend[index].duration=i;
                place++;
                index++;

            }
        }
            
     }
    inFile.close();
};

void MapTree::delete_preorder_traversal(Node *traversal){
    if(traversal!=NULL) 
    {
        delete traversal;
        delete_preorder_traversal(traversal->left);
        delete_preorder_traversal(traversal->right);
        
    }
};

MapTree::~MapTree(){
    delete_preorder_traversal(root);
    root = NULL;
};

