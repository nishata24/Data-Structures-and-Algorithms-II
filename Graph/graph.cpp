//  Created by Nishat Ahmed on 2021-11-02
//  ECE-365 DSA II
//  Graph

#include "graph.hpp"
#include "graph.h"

using namespace std;

//Construct graph from input file
void graph::load(string input_file) {
    
    string line, v1, v2;
    int weight;
    vertex *pv;
    ifstream input(input_file);
    
    //Record each edge (one per line)
    while (getline(input, line)) {
        
        //Parse line and identify v1, v2, and weight of edge
        stringstream ss(line);
        ss >> v1 >> v2 >> weight;
        edge e = edge(v1, v2, weight);
        
        //If v1 is unknown, create a vertex and take note of pv
        //Else obtain pointer to v1
        if (!vertices.contains(v1)) {
            pv = (vertex *)(new vertex(v1));
            vertices.insert(v1, pv);
            known.push_back(v1);
            size++;
        }
        else {pv = ((vertex *)vertices.getPointer(v1));}
        
        //Add edge e to v1's adjacency list
        pv -> adj.push_back(e);
        
        //Create v2 and add it to known list if not there already
        if (!vertices.contains(v2)) {
            pv = (vertex *)(new vertex(v2));
            vertices.insert(v2, pv);
            known.push_back(v2);
            size++;
        }
    }
}

//Check validity of given vertex
bool graph::checkVertex(string v) {
    return vertices.contains(v);
}

//Dijkstra's algorithm to find shortest path to every vertex
void graph::dijkstra(string start) {
    
    vertex *pv, *pv1, *pv2;
    
    //Obtain pointer to starting vertex
    pv = (vertex *) vertices.getPointer(start);
    pv -> dist=0;
    pv -> d_known = true;
    pv -> path = start;
    
    //Add every edge leaving start vertex to frontier
    heap frontier = heap(size);
    list<edge>::iterator it;
    for (it = pv -> adj.begin(); it != pv -> adj.end(); it++) {
        
        //Insert vertex to frontier if not already there
        if (frontier.insert(it -> v2, it -> weight, pv2) == 0) {
            pv2 = (vertex *) vertices.getPointer(it -> v2);
            pv2 -> dist=it -> weight;
            pv2 -> path=(pv -> path) + ", " + it -> v2;
        }
        
        //If vertex is already there, compare and change distance and path
        else {
            pv2 = (vertex *) vertices.getPointer(it -> v2);
            if (it -> weight < pv2 -> dist) {
                pv2 -> dist=it -> weight;
                pv2 -> path=(pv -> path) + ", " + it -> v2;
            }
            frontier.setKey(it -> v2, pv2 -> dist);
        }
    }
    
    //ID of the greatest vertex returned by deleteMin
    string id;
    //shortest distance discovered to that vertex
    int dist;
    //Net distance to new frontier vertex
    int w;
    
    while (!frontier.deleteMin(&id, &dist, nullptr)) {
        pv = (vertex *) vertices.getPointer(id);
        pv -> d_known=true;
        
        //Increase frontier to include adjacent edges to current vertex
        for (it=pv -> adj.begin(); it != pv -> adj.end(); it++) {
            
            //Check whether or not new vertex is already known
            pv1 = (vertex *) vertices.getPointer(it -> v1);
            pv2 = (vertex *) vertices.getPointer(it -> v2);
            if (pv2 -> d_known==true) {
                continue;
            }
            
            //Distance of frontier vertex equals distance up to previous vertex plus weight of edge
            w=dist + it -> weight;
            
            //Insert into frontier if vertex isn't already there
            if (frontier.insert(it -> v2, w, pv2)==0) {
                pv2=(vertex *) vertices.getPointer(it -> v2);
                pv2 -> dist=w;
                pv2 -> path=(pv1 -> path) + ", " + it -> v2;
            }
            
            //If vertex is already in frontier, compare and change distance and path
            else {
                pv2=(vertex *)vertices.getPointer(it -> v2);
                if (w < pv2 -> dist) {
                    pv2 -> dist=w;
                    pv2 -> path=(pv1 -> path) + ", " + it -> v2;
                }
                frontier.setKey(it -> v2, pv2 -> dist);
            }
        }
    }
    
}

//Iterate through vertices in order and print shortest paths
void graph::show(string output_file) {
    
    vertex *pv;
    list<string>::iterator it;
    ofstream output(output_file);
    
    //Print each vertex and its shortest path to the output file
    for (it=known.begin(); it!=known.end(); it++) {
        pv=(vertex *) vertices.getPointer(*it);
        //If no path is found do the following
        if (pv -> dist==-1) {
            output << pv -> id << ": NO PATH" << endl;
        }
        //If a path is found do the following
        else {
            output << pv -> id << ": " << pv -> dist << " [" << pv -> path << "]" << endl;
        }
    }
}
