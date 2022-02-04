/* @Author
Student Name: Zeynep Deniz Gündoğan
Student ID: 040190382
E-mail: gundoganz19@itu.edu.tr
Date: 30.12.2021
*/

#ifndef _H
#define _H

using namespace std;

class route_information{
    public:
        string source;
        string destination;
        int duration=0;
};

class City_routes_from_file{
    public:
        string source;
        string destination;
        int duration=0;
};

class Node{
    public:
        string name;
        Node* left=NULL;   
        Node* right=NULL;
        int route_num=0;
        route_information Route_information[200];
};

class MapTree{
    public:
        Node* root=NULL;
        MapTree();
        ~MapTree();
        Node* find_required_city(Node*, string);
        void prunning(Node*);
        void delete_preorder_traversal(Node*);
        void get_map_tree(City_routes_from_file*);
        int find_length(City_routes_from_file*);
        int find_route_info_length(route_information*);
        int find_min_dur_index(route_information*,int);
        int find_max_dur_index(route_information*,int);
        int find_index_with_data(route_information*);
        string get_meeting_point(int, string*);
        void get_duration(string*, Node*, Node*);
        int get_total_duration(string*, Node*, Node*);
        void find_common_cities(Node*, Node*);
        int get_total_duration_index(int* );
        int find_required_route_from_map_array(City_routes_from_file*,int, string, string);
        int find_max_dur_index_with_required_source_city(string, route_information*, int, int);
        int common_city_index=0;
        int duration[250];
        string common_cities[250];
};

class Map{
    public:
        void print_preorder_traversal(Node*);
        void read_file(string, City_routes_from_file*);
        City_routes_from_file map_arr_friend1[250];
        City_routes_from_file map_arr_friend2[250];
        MapTree  first_friend_tree;
        MapTree  second_friend_tree;
        
};

#endif
