//
// Created by davide miro on 2019-10-12.
//

#ifndef EDITORCOLLABORATIVO_SYMBOL_H
#define EDITORCOLLABORATIVO_SYMBOL_H

#include <vector>
#include <string>
#include <chrono>
#include <iostream>

using namespace std;
class Symbol {
    char s;
    string font;
    bool bold,italic,underline,strike;
    string color;
    string id;
    vector <int> frac;
public:
    Symbol(char s,string font,bool bold,bool italic,bool underline,bool strike,string color,const vector<int>& frac,const string& project,const string& user);
    Symbol(const Symbol& symbol);
    Symbol(Symbol&& symbol);
    Symbol& operator=(const Symbol& symbol);
    bool operator<(const Symbol& symbol);
    bool operator>(const Symbol& symbol);
    bool operator<=(const Symbol& symbol);
    bool operator>=(const Symbol& symbol);
    bool operator==(const Symbol& symbol);
    string getId();
    char getChar();
    const vector<int>& getFrac();
    void print();



};


#endif //EDITORCOLLABORATIVO_SYMBOL_H
