#include <cstdlib>
#include <iostream>
#include <vector> 
#include <algorithm>
#include <string>
#include <stack>
#include <bits/stdc++.h>

using namespace std;

#define edge pair<int, int>
#define lw pair<double,int>


//Function to sort vector by weight
void sort_vector(vector<pair<lw, edge>> &full_graph) {
    sort(full_graph.begin(), full_graph.end());

}

//Function to find the root for each edge (recursive)
int FindRoot(vector<int> &singles, int e) {

    if (singles[e] == e) {
        return e;
    }

    return FindRoot(singles, singles[e]);
}

//Function to combine the roots after it has been added to MWST
void Combine(vector<int> &singles, int x, int y) {
    int a, b;
    a = FindRoot(singles, x);
    b = FindRoot(singles, y);
    singles[a] = b;
}
