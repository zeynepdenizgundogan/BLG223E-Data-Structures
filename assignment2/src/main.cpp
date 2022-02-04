/* @Author
Student Name: Zeynep Deniz Gündoğan
Student ID: 040190382
E-mail: gundoganz19@itu.edu.tr
Date: 30.12.2021
*/

#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include <iomanip>
#include <cmath>
#include "map.h"

using namespace std;

int main(int argc, char* argv[]) {
    Map map;
    MapTree maptree;

    map.read_file(argv[1], map.map_arr_friend1);
    map.read_file(argv[2], map.map_arr_friend2);
    
    map.first_friend_tree.get_map_tree(map.map_arr_friend1);
    map.first_friend_tree.prunning(map.first_friend_tree.root);

    map.second_friend_tree.get_map_tree(map.map_arr_friend2);
    map.second_friend_tree.prunning(map.second_friend_tree.root);
    
    maptree.find_common_cities(map.first_friend_tree.root, map.second_friend_tree.root);
    maptree.get_duration(maptree.common_cities, map.first_friend_tree.root, map.second_friend_tree.root);
 
    cout<<"FRIEND-1:";
    map.print_preorder_traversal(map.first_friend_tree.root);
    cout<<endl;
    
    cout<<"FRIEND-2:";
    map.print_preorder_traversal(map.second_friend_tree.root);
    cout<<endl;

    int total_duration_index=maptree.get_total_duration_index(maptree.duration);
    string meeting_point= maptree.get_meeting_point(total_duration_index, maptree.common_cities);
    cout<<"MEETING POINT: "<< meeting_point<<endl;
    cout<<"TOTAL DURATION COST: "<<maptree.duration[total_duration_index]<<endl;
    
    return EXIT_SUCCESS;
}

