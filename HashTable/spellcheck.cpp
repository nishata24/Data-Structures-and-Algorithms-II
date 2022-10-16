//  Created by Nishat Ahmed on 2021-09-17
//  ECE-365 DSA II
//  Hash Table


#include "spellcheck.hpp"
#include "hash.h"
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
using namespace std;

//Load dictionary file into hash table
hashTable loadDictionary(string &dictionary){
    ifstream input(dictionary);
    string word;
    hashTable dict = hashTable(200000);
    input.clear();
    input.seekg(0);
    while(getline(input, word)){
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        dict.insert(word);
    }
    return dict;
}

//Check whether or not the word is valid
bool checkphrase(string &phrase, hashTable &dict){
    return phrase == "" ? true : dict.contains(phrase);
}

//Spellcheck a line in a file
void checkl(string &line, int nu, hashTable &dict, ofstream &output){
    transform(line.begin(), line.end(), line.begin(), ::tolower);
    line.append(" ");
    string phrase = "";
    bool number = false;
    for(int i=0; i<line.length(); i++){
        if((line[i] >= 97 && line[i] <= 122) || (line[i] == 45) || (line[i] == 39)){
            phrase += line[i];
        }
        else if(line[i] >= 48 && line[i] <= 57){
            number = true;
            phrase += line[i];
        }
        else{
            if(phrase.length() > 20){
                output << "Long word at line " << to_string(nu) << ", starts: " << phrase.substr(0, 20) << endl;
            }
            else if(number == false && checkphrase(phrase, dict) ==  false){
                output << "Unknown word at line " << to_string(nu) << ": " << phrase << endl;
            }
            phrase = "";
            number = false;
        }
    }
}
//Spellcheck input file and print outputs to output file
void SpellCheck(string &inputf, string &outputf, hashTable &dict){
    ifstream input(inputf);
    ofstream output(outputf);
    string line;
    string out;
    int nu = 1;
    while(getline(input, line)){
        checkl(line, nu, dict, output);
        nu++;
    }
}

//Ask user for dictionary, input/output files and spellcheck. Report time to load dictionary and spellcheck.
//Reference 1: www.techiedelight.com/measure-elapsed-time-program-chrono-library/
//Reference 2: en.cppreference.com/w/cpp/chrono/time_point
int main(){
    string dictionary;
    string inputf;
    string outputf;
    cout << "Dictionary file: " << endl;
    cin >> dictionary;
    cout << "Input file: " << endl;
    cin >> inputf;
    cout << "Output file: " << endl;
    cin >> outputf;
    chrono::steady_clock::time_point time = chrono::steady_clock::now();
    hashTable dict = loadDictionary(dictionary);
    chrono::steady_clock::time_point time1 = chrono::steady_clock::now();
    chrono::duration<double> timedifference = chrono::duration_cast<chrono::duration<double>>(time1-time);
    cout << "Time to load dictionary: " << timedifference.count() << endl;
    time = chrono::steady_clock::now();
    SpellCheck(inputf, outputf, dict);
    time1 = chrono::steady_clock::now();
    timedifference = chrono::duration_cast<chrono::duration<double>>(time1-time);
    cout << "Time to spellcheck document: " << timedifference.count() << endl;
}

