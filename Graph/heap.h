//
//  heap.h
//  DSA II 
//
//  Created by Nishat Ahmed on 10/17/21.
//

#ifndef _HEAP_H
#define _HEAP_H

#include <vector>
#include <string>
#include "hash.h"

class heap{
public:
    //constructor to initalize heap
    heap(int capacity =0);
    //insert key and string in heap
    int insert(const std::string &id, int key, void *pn);
    //Change key of existing entry
    int setKey(const std::string &id, int key);
    //Remove heap item
    int remove(std::string &id, int *key);
    //Remove top heap item
    int deleteMin(std::string *id, int *key, void **ppn);
    
private:
    class node{
    //inner class in heap
    public:
        //id of the node
        std::string id;
        //key of node
        int key;
        //pointer to data at the node
        void *pData;
        bool operator<(node n2)const{return key < n2.key;}
    };
    
    int filled = 0;
    int capacity = 0;
    //actural binary heap
    std::vector<node> data;
    //maps ids to node pointers
    hashTable mapping;
    //Move key higher to its correct position
    int percUp(int CurrentPos);
    //Move key lower to its correct position
    int percDown(int CurrentPos);
    //Retrieve position of node
    int getPos(node *pn);
};


#endif //_HEAP_H
