//
// Created by davide miro on 2019-10-12.
//

#ifndef EDITORCOLLABORATIVO_SYMBOL_H
#define EDITORCOLLABORATIVO_SYMBOL_H

#include <vector>
#include <string>
#include <chrono>
#include <iostream>
#include <QJsonObject>
#include <QString>
#include <QJsonArray>
#include <QJsonValue>

using namespace std;
class Symbol {
    QChar s;
    string font;
    bool bold,italic,underline,strike;
    string color;
    string id;
    vector <int> frac;
public:
    Symbol(QChar s,string font,bool bold,bool italic,bool underline,bool strike,string color,const vector<int>& frac,const string& project,const string& user);
    Symbol(const Symbol& symbol);
    Symbol(Symbol&& symbol);
    Symbol(QJsonObject json_symbol);
    Symbol& operator=(const Symbol& symbol);
    bool operator<(const Symbol& symbol);
    bool operator>(const Symbol& symbol);
    bool operator<=(const Symbol& symbol);
    bool operator>=(const Symbol& symbol);
    bool operator==(const Symbol& symbol);
    string getId();
    QChar getChar();
    const vector<int>& getFrac();
    void print();
    QJsonObject toJson();

    const QString getFont() const;

    bool isBold() const;

    bool isItalic() const;

    bool isUnderline() const;

    bool isStrike() const;

    const QString getColor() const;


};


#endif //EDITORCOLLABORATIVO_SYMBOL_H
