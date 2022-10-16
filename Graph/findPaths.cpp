//  Created by Nishat Ahmed on 2021-11-02
//  ECE-365 DSA II
//  Paths

#include "findPaths.hpp"
#include <iostream>
#include <chrono>
#include "graph.h"

using namespace std;

int main() {
    string input_file, start, output_file;
    
    //Initialize empty graph
    graph g;
    //Obtain input file
    cout << "Enter name of graph file: ";
    cin >> input_file;
    
    //Create graph based on input file
    g.load(input_file);
    
    //Retrieve start vertex
    do {
        cout << "Enter name of starting vertex: ";
        cin >> start;
    } while (g.checkVertex(start) == false);
    
    //Start timer
    chrono:: steady_clock::time_point time1 = chrono::steady_clock::now();
    
    //Determine shortest path from start vertex to every other vertex
    g.dijkstra(start);
    
    //Stop timer
    chrono::steady_clock::time_point time2 = chrono::steady_clock::now();
    chrono::duration<double> time_difference = chrono::duration_cast<chrono::duration<double>>(time2-time1);
    cout << "Total time (in seconds) to apply Dijkstra's algorithm: " << time_difference.count() << endl;
    
    //Retrieve output file
    cout << "Enter name of output file: ";
    cin >> output_file;
    
    g.show(output_file);
    
    return 1;
}
