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

class Symbol {
    char s;
    std::string font;
    bool bold,italic,underline,strike;
    std::string color;
    std::string id;
    std::vector <int> frac;
public:
    Symbol(char s, std::string font, bool bold, bool italic, bool underline, bool strike, std::string color, const std::vector<int>& frac, const std::string& project, const std::string& user);
    Symbol(const Symbol& symbol);
    Symbol(Symbol&& symbol);
    Symbol(QJsonObject json_symbol);
    Symbol& operator=(const Symbol& symbol);
    bool operator<(const Symbol& symbol);
    bool operator>(const Symbol& symbol);
    bool operator<=(const Symbol& symbol);
    bool operator>=(const Symbol& symbol);
    bool operator==(const Symbol& symbol);
    std::string getId();
    char getChar();
    const std::vector<int>& getFrac();
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
