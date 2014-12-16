#include<map>
using std::map;
#include<iostream>
using std::cout; using std::endl; using std::cin;
#include<fstream>
using std::ifstream;
#include<vector>
using std::vector;
#include<algorithm>
using std::find; using std::copy;
#include<iterator>
using std::ostream_iterator;
#include "functions-06.h"


int main(){
    map<long, string> index_map;
    map<long, vector<long>> to_arc;
    map <long, double> node_pr;
    string index_file, arc_file;
    double damping;
    long iters;

    cout << "index file:";
    cin >> index_file;
    cout << "arc file:";
    cin >> arc_file;
    cout << "damping:";
    cin >> damping;
    cout << "iterations:";
    cin >> iters;

    if (! read_index(index_map, index_file)){
	cout << "Bad index file"<<endl;
	return false;
    }

    if (! read_arc(to_arc, arc_file)) {
	cout<< "Bad arc file"<<endl;
	return false;
    }

    init_pr_map(node_pr, index_map.size());

    default_random_engine dre(1);

    page_rank(to_arc, node_pr, iters, damping, dre);
    print_page_ranks(node_pr, index_map, cout);

}
