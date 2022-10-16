//  Created by Nishat Ahmed on 2021-12-02
//  ECE-365 DSA II
//  ACM Programming Contest

#include "merge.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <bits/stdc++.h>
#include <chrono>

using namespace std;

//Remember all instances seen previously
unordered_map<string, string> memory;

string checkmerge(const string &x, const string &y, const string &z){
    //If all 3 strings are empty, return true
    if ((x=="") && (y=="") && (z=="")){
        return "";
    }
    //If 2 of the 3 strings are empty, return false
    else if ((x=="") + (y=="") + (z=="") == 2){
        return "*** NOT A MERGE ***";
    }
    //Check whether or not scenario was already seen and is in memory
    else if (memory.find(x+"\n"+y+"\n"+z) != memory.end()){
        return memory[x+"\n"+y+"\n"+z];
    }
    //Default return value
    string merge = "*** NOT A MERGE ***";
    
    //Check if 1st character of x is equal to the 1st character of z
    if ((x!="") && (x[0]==z[0])){
        merge = checkmerge(x.substr(1), y, z.substr(1));
        //If merge is confirmed and occurs, create output
        if (merge!="*** NOT A MERGE ***"){
            merge.insert(0, string(1, toupper(z[0])));
        }
    }
    
    //Repeat for y if merge was not confirmed
    if ((y!="") && (y[0]==z[0]) && (merge == "*** NOT A MERGE ***")){
        merge = checkmerge(x, y.substr(1), z.substr(1));
        //If merge is confirmed and occurs, create output
        if (merge!="*** NOT A MERGE ***"){
            merge.insert(0, string(1, z[0]));
        }
    }
    
    //Add scenario and output to memory
    memory.insert(make_pair(x+"\n"+y+"\n"+z, merge));
    return merge;
}
    
int main(){
    string inputfile, outputfile, x, y, z;
    
    //Obtain input file
    cout << "Enter name of input file: ";
    cin >> inputfile;
    ifstream input(inputfile);
    
    //Obtain output file
    cout << "Enter name of output file: ";
    cin >> outputfile;
    ofstream output(outputfile);
    
    //Initialize start/stop timer variables
    //chrono::steady_clock::time_point t1, t2;
    //chrono::duration<double> timediff;
    //int n = 0;
    
    //Read 3 lines at a time
    //Print checkmerge outputs to output file
    while (getline(input, x) && getline(input, y) && getline(input, z)){
        //t1 = chrono::steady_clock::now();
        output << checkmerge(x,y,z) << endl;
        //t2 = chrono::steady_clock::now();
        //timediff = chrono::duration_cast<chrono::duration<double>>(t2-t1);
        //cout << "__ " << ++n << " __" << endl;
        //cout << "Time (seconds): " << timediff.count() << endl;
        memory.clear();
    }
}

