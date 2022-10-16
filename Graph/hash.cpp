//  Created by Nishat Ahmed on 2021-09-17
//  ECE-365 DSA II
//  Hash Table

#include "hash.hpp"
#include "hash.h"
#include <iostream>
#include <cmath>
#include <typeinfo>
#include <string>
using namespace std;

//Constructor to initialize hash table with specified size
hashTable::hashTable(int size){
    capacity = getPrime(size);
    data.resize(capacity);
    filled = 0;
}

//Insert specified key into hash table (return 0=success, 1=already there, 2=rehash fail)
int hashTable::insert(const std::string &key, void *pv){
//Rehash when more than half of hashTable is filled
    if(capacity/(capacity-filled+1) >= 2){
        //Try to rehash, if not possible return 2
        if(rehash() == false){
            return 2;
        }
    }
    
    //Create position value
    int CurrentPos = hash(key);
    
    //Search location of key if already inserted, otherwise search for first available location
    while(data[CurrentPos].isOccupied && (data[CurrentPos].key != key)){
        ++CurrentPos %= capacity;
    }
    
    //If key is already in hashTable return 1
    if((data[CurrentPos].key == key) && (data[CurrentPos].isDeleted == false)){
        return 1;
    }
    
    //Insert new key in data[CurrentPos] location
    data[CurrentPos].key = key;
    data[CurrentPos].pv = pv;
    data[CurrentPos].isOccupied = true;
    data[CurrentPos].isDeleted = false;
    filled++;
    return 0;
}

//Returns true if specified key is in hash table, otherwise returns false
bool hashTable::contains(const std::string &key){
    return(findPos(key) == -1) ? false : true;
}

//Delete item with specified key and return true if success, otherwise return false
bool hashTable::remove(const std::string &key){
    int CurrentPos = findPos(key);
    if(CurrentPos == -1){
        return false;
    }
    else{
        data[CurrentPos].isOccupied = false;
        data[CurrentPos].isDeleted = true;
        return true;
    }
    
}

//Obtain pointer stored with given key
void *hashTable::getPointer(const std::string &key, bool *b){
    int CurrentPos = findPos(key);
    
    //True if item is found, otherwise false
    if(b != NULL){
        *b = (CurrentPos != -1);
    }
    
    //Return nullptr if key isn't found
    if(CurrentPos == -1){
        return nullptr;
    }
    //Return pointer associated with key if key is found
    else{
        return data[CurrentPos].pv;
    }
}

//Store given pointer with associated key
int hashTable::setPointer(const std::string &key, void *pv){
    int CurrentPos = findPos(key);
    //Determine whether or not key is in the table
    if(CurrentPos == -1){
        return 1;
    }
    data[CurrentPos].pv = pv;
    return 0;
}

//hash function that returns a number given a string
int hashTable::hash(const std::string &key){
    long s = 0, m = 1;
    for(int i =0; i < key.length(); i++){
        m = (i % 8 == 0) ? 1 : m * 256;
        s += tolower(key[i]) * m;
    }
    return(int)(abs(s) % capacity);
}

//Return position of specified key, if unfound return -1
int hashTable::findPos(const std::string &key){
    int CurrentPos = hash(key);
    while(data[CurrentPos].isOccupied || data[CurrentPos].isDeleted){
        if(data[CurrentPos].key == key){
            return (data[CurrentPos].isDeleted ? -1 : CurrentPos);
        }
        ++CurrentPos %= capacity;
    }
    //If key isn't found return 1
    return -1;
}

//Increase hash table capacity and rehash
bool hashTable::rehash(){
    int NewCapacity = getPrime(capacity);
    vector<hashItem> backup;
    data.swap(backup);
    try{data.resize(NewCapacity);}
    catch(std::bad_alloc){
        cout << "REHASH FAILED" << endl;
        return false;
    }
    capacity = NewCapacity;
    filled = 0;
    for(auto i : backup){
        if((i.isOccupied == true) && (i.isDeleted == false)){
            insert(i.key, i.pv);
        }
    }
    return true;
}

//Obtain prime number at least as large as the size from precalculated list
unsigned int hashTable::getPrime(int size){
    static int PrimeNumbers[] = {1009, 2003, 4001, 16001, 32003, 64007, 128021, 256019, 512009, 1024021, 2048003, 4096013};
    for(int i : PrimeNumbers){
        if(i>size){
            return i;
        }
    }
    //Return last value is list is maxed
    return PrimeNumbers[11];
}

