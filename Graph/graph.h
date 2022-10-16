//
//  Header.h
//  DSA II 
//
//  Created by Nishat Ahmed on 11/02/21.
//

#ifndef graph_h
#define graph_h
#include <fstream>
#include <sstream>
#include <list>
#include <iterator>
#include "heap.h"

using namespace std;

class graph {
    
private:
    
    //Search vertex from ID
    hashTable vertices;
    
    //List known vertices in original order
    list<string> known;
    int size = 0;
    
    //Each edge stores destination and weight
    struct edge {
        string v1;
        string v2;
        int weight;
        edge(string a, string b, int w):v1(a), v2(b), weight(w) {}
    };
    
    //Each vertex
    struct vertex {
        string id; //may not be necessary
        list<edge> adj;
        bool d_known = false;
        int dist = -1;
        //previous vertex on shortest path
        string path = "";
        vertex(string a):id(a) {}
    };
    
public:
    
    //Construct graph from input file
    void load(string input_file);
    
    //Check validity of given vertex
    bool checkVertex(string v);
    
    //Run Dijkstra's algorithm for shortest path to each vertex
    void dijkstra(string start)
    ;
    
    //Iterate through vertices in order and print shortest paths
    void show(string output_file);
};

#endif /* graph_h */
