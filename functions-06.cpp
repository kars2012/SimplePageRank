//
//  functions-06.cpp
//  proj06
//
//  Created by Bryan J Kars on 10/14/14.
//  Copyright (c) 2014 Bryan J Kars. All rights reserved.
//

#include "functions-06.h"
#include <cstdlib>
using std::atol;
using std::stol;
#include <fstream>
using std::ifstream;
#include <sstream>
using std::istringstream;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <map>
using std::map;
using std::pair;
using std::make_pair;
#include <algorithm>
using std::transform;
using std::copy;
using std::begin;
using std::end;
using std::to_string;
#include<iostream>
using std::cout;
using std::endl;
#include <random>


bool read_index(map<long, string> &index_map, string file_name){
    // opens a .txt file and places the contents into a specified map
    
    string line;
    ifstream myfile(file_name);
    
    if (myfile.is_open()){
            
            long id = 0; //will hold the first item from line
            string name = ""; //will hold the second item of the line
            
            while(myfile >> id >> name){ //loops through the lines in specified .txt
                
                auto id_name = std::make_pair(id,name);
                index_map.insert(id_name);
            
        }
        
           /* for (auto it = index_map.begin(); it != index_map.end(); ++it){
                cout << it->first << ":" << it->second << endl;
            }*/
        myfile.close();
        return true;
        
    }
    else{
    return false;
    }
}

bool read_arc(map<long, vector<long>> &arc_map, string file_name){
    /* opens designated file, places contents into a map. goes line by line and converts strings into
     appropriate types. first value on a line will be used as first element in a pair. second value will be placed into a vector that is is second element in pair*/
    
    string line;
    ifstream myfile (file_name);
    
    if (myfile.is_open()){
        
        vector<long> endarcs;
        long begin_arc = 0; // will hold first item in line
        long end_arc = 0; // will hold second item in line
        
        while(myfile >> begin_arc >> end_arc){ //loops through lins in .txt and extracts strings
            
            arc_map[begin_arc].push_back(end_arc);

        }
        
        myfile.close();
        return true;
        
    }
    else{
        
    return false;
        
    }
    
}

void init_pr_map(map<long,double> &pr_map, size_t sz){
    // initiates the map by filling it in relation to the requested size
    
    for(long i = 0; i < sz; i++){ //loops and creates pairs to go into the map
    
        double node_val = 1.0/sz; //using idea 1/n
        pr_map[i] = node_val;
        
    }
    /*for (auto it = pr_map.begin(); it != pr_map.end(); ++it){
                cout << it->first << ":" << it->second << endl;
            }*/
    
}

long outgoing (map<long, vector<long>> &arc_map, long id){
    // searches map for designated id and provides the size of the vector associated with that id
    
    for (auto it = arc_map.begin(); it!=arc_map.end(); ++it){ //iterate through map looking for matching id
        
        if(it->first == id){ // when found
            
            long link_count = it->second.size();
            return link_count; //return the size of vector holding the link count
        }
    }
    return 0;
}
 
vector<long> incoming (map<long, vector<long>> &arc_map, long id){
    
    vector<long> inc_v;
 
    for (auto it = arc_map.begin(); it!=arc_map.end(); ++it){
            
            for (auto i = it->second.begin(); i != it->second.end(); i++){
                
                if(*i == id){
                    
                    inc_v.push_back(it->first);      
            }
        }
    }
    return inc_v;
}

void page_rank(map<long, vector<long>> &arc_map, map<long,double> & pr_map, long iters, double damping,
default_random_engine &dre){
   
    double pile_calc = 0.0;
    double calculation;
    double total_calculation;
    init_pr_map(pr_map, pr_map.size());
    long total_nodes = pr_map.size();
    
    for (int i = 0; i < iters; i++){
        
        std::uniform_int_distribution<long> distribution(0, total_nodes -1);
        long random_n = distribution(dre);
        
        vector<long> inc_link = incoming(arc_map, random_n);  
        long arcmap_size = outgoing(arc_map, random_n);
        
        if(inc_link.size() == 0 || arcmap_size == 0){}
        else if(inc_link.size() != 0 || arcmap_size != 0){
            
            for (int i =0; i < inc_link.size(); i++){
                
                long out_nodes = outgoing(arc_map, i);
                calculation = pr_map[inc_link[i]]/out_nodes;
                //cout << "the current calc: " << calculation << endl;
                pile_calc += calculation;
                //cout << "the calc pile: " << pile_calc << endl        
            }
    
        total_calculation = (1-damping)/total_nodes + damping * pile_calc;
        pr_map[random_n] = total_calculation;
        // cout << "the PR:" << total_calculation << endl;
            
        }
        pile_calc = 0;
        
    }
    
}

void print_page_ranks(map<long, double> &pr_map, map<long, string> &index_map, ostream &out){
    
    for ( int i = 0; i < pr_map.size(); i++){
        cout << "Site: " << index_map[i] << " " << "PR: " << pr_map[i] << endl;
    }
}