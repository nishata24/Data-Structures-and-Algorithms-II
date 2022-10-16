//  Created by Nishat Ahmed on 2021-10-16
//  ECE-365 DSA II
//  Heap

#include "heap.hpp"
#include "heap.h"
#include <string>
#include <iostream>

//Constructor for initializing hashTable with a specified capacity
heap::heap(int capacity) : mapping(capacity*2), capacity(capacity){
    data.resize(capacity+1);
}

//Given string and key inserted to heap
int heap::insert(const std::string &id, int key, void *pn){
    //Check whether or not heap if filled
    if(capacity == filled){
        return 1;
    }
    //Check if string is in heap already
    else if(mapping.contains(id)){
        return 2;
    }
    //Insert new node
    else{
        int CurrentPos = filled+1;
        data[CurrentPos].id = id;
        data[CurrentPos].key = key;
        data[CurrentPos].pData = pn;
        mapping.insert(data[CurrentPos].id, &data[CurrentPos]);
        CurrentPos = percUp(CurrentPos);
        filled++;
        return 0;
    }
}


//Change existing entry key
int heap::setKey(const std::string &id, int key){
    //Check if node already exists in heap
    if(!mapping.contains(id)){
        return 1;
    }
    //Use hashTable to locate correct node
    else{
        int CurrentPos = getPos((node*)mapping.getPointer(id));
        data[CurrentPos].key = key;
        CurrentPos = percUp(CurrentPos);
        percDown(CurrentPos);
        return 0;
    }
}

//Remove item in heap
int heap::remove(std::string &id, int *key){
    //Check is string is already in heap
    if(mapping.contains(id)){
        //Use hashTable to locate correct node
        int CurrentPos = getPos((node*)mapping.getPointer(id));
        if(key != nullptr){
            *key = data[CurrentPos].key;
        }
        //Remove located node and percolate down
        mapping.remove(data[CurrentPos].id);
        data[CurrentPos] = data[filled--];
        data[filled+1] = node();
        if (CurrentPos <= filled){
            CurrentPos = percDown(CurrentPos);
            percUp(CurrentPos);
        }
        return 0;
    }
    //For string not located in heap
    else{
        return 1;
    }
}

//Remove item at the top of heap
int heap::deleteMin(std::string *id, int *key, void **ppn){
    //Check if heap is empty
    if(filled == 0){
        return 1;
    }
    //Remove top item and percolate down
    else{
        node min = data[1];
        if(id != nullptr){
            *id = min.id;
        }
        if(key != nullptr){
            *key = min.key;
        }
        if (ppn != nullptr){
            *ppn = &min.key;
        }
        mapping.remove(min.id);
        data[1] = data[filled--];
        data[filled+1] = node();
        percDown(1);
        return 0;
    }
}

//Move key up to its correct location in tree
int heap::percUp(int new_node_pos){
    //New node is temporarily stored in data[0]
    data[0] = data[new_node_pos];
    //Percolate up
    while(data[0] < data[new_node_pos/2]){
        data[new_node_pos] = data[new_node_pos/2];
        mapping.setPointer(data[new_node_pos].id, &data[new_node_pos]);
        new_node_pos /= 2;
    }
    //Clear placeholder and insert new node in proper location
    data[new_node_pos] = data[0];
    mapping.setPointer(data[new_node_pos].id, &data[new_node_pos]);
    data[0] = node();
    //return new node position
    return new_node_pos;
}

//Move key down to its correct location in tree
int heap::percDown(int new_node_pos){
    //New node is temporarily stored in data[0]
    data[0] = data[new_node_pos];
    //Percolate down
    int child;
    for(;new_node_pos*2 <= filled; new_node_pos = child){
        //Consider left child
        child = new_node_pos*2;
        //Compare left and right child and choose the smaller one
        if(child != filled && data[child+1] < data[child]){
            child++;
        }
        //Compare child and parent to check is child is smaller
        if(data[child] < data[0]){
            data[new_node_pos] = data[child];
            mapping.setPointer(data[new_node_pos].id, &data[new_node_pos]);
        }
        //If nodes are placed correctly, break
        else{
            break;
        }
    }
    data[new_node_pos] = data[0];
    mapping.setPointer(data[new_node_pos].id, &data[new_node_pos]);
    data[0] = node();
    return new_node_pos;
}

//Retrieve position of node
int heap::getPos(node *pn){
    return(pn - &data[0]);
}

