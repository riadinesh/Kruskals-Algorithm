#include <iostream>
#include "spanning.cpp"
#include <stdexcept>
#include <fstream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <cstring>
using namespace std;
#define edge pair<int, int>
#define lw pair<double, int>


int main(int argc, char** argv)
{
    if (argc < 3) //if 2 arguments are not provided, error
    {
        throw std::invalid_argument("Usage: ./MWST <INPUT FILE> <OUTPUT FILE>"); // throw error
    }

    ifstream input; 
    ofstream output; 
    input.open(argv[1]); 
    output.open(argv[2]); 

    string command;
    char *com, *op;
    int line_count = 1;

    //create full graph in the form of vector
    vector<pair<lw, edge>> full_graph; 
    //create resulting mwst graph in the form of vector
    vector<pair<lw, edge>> mwst_graph;
    //create vector for each vertex as its own tree
    vector<int> singles;


    int num_vertices, num_edges;
    while(getline(input,command)) //get next line of input
    {
        if (line_count == 1) {
	    num_vertices = stoi(command);
	}
	else if (line_count == 2) {
            num_edges = stoi(command);
        }
        else {
            //separated each edge and the weight
  	    com = strdup(command.c_str()); //copy string into a "C-style" string
            op = strtok(com, " \t"); //tokenize command on whitespace
            int v1;
	    v1 = stoi(op);
            op = strtok(NULL, " \t");
	    int v2;
            v2 = stoi(op);
	    op = strtok(NULL, " \t");
	    double weight;
            weight = stod(op);

            //push pair into vector
	    full_graph.push_back(make_pair(lw(weight,line_count-2), edge(v1, v2))); 
 	} 
	line_count++;
    }
   
    //sort vector in ascending order based on weight
    sort_vector(full_graph);
   
    //create array for each vertices to be it's own tree 
    for (int i=0; i <= num_vertices; i++) {
        singles.push_back(i);
    }
   
    //Kruskal's Algorithm Implementation 
    int x,y;
    while (mwst_graph.size() != num_vertices - 1) {
        for (int i=0; i < num_edges; i++) {
            //find the root for each edge, if it's the same, they belong to the same tree 
            x = FindRoot(singles, full_graph[i].second.first);
            y = FindRoot(singles, full_graph[i].second.second); 
            
            //if the root is not the same, it can be added to the graph
            if (x!=y) {
                mwst_graph.push_back(make_pair(lw(full_graph[i].first.first,full_graph[i].first.second), 
		edge(full_graph[i].second.first, full_graph[i].second.second)));
                //Get the union of the roots, combine their origin
                Combine(singles, x, y);                
            }
        }
    }

    //Print Output
    output.precision(1);
    for (int j=0; j< mwst_graph.size(); j++) {
        output.width(4);
        output << mwst_graph[j].first.second << ": (" << mwst_graph[j].second.first << ", " 
	<< mwst_graph[j].second.second << ") " << fixed << mwst_graph[j].first.first << "\n";
    }

 
    //Print Total Weight
    double total_weight = 0;
    for (int j=0; j< mwst_graph.size(); j++) {
        total_weight += mwst_graph[j].first.first;
    }
    output.width(10);
    output.precision(2);
    output <<"Total Weight = " << fixed << total_weight << "\n";

    
    input.close();
    output.close();
    return 0;
}
