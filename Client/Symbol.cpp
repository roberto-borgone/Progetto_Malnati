//
// Created by davide miro on 2019-10-12.
//

#include "Symbol.h"

Symbol::Symbol(char s, string font, bool bold, bool italic, bool underline, bool strike, string color,
        const vector<int>& frac, const string &project, const string &user) {
    id = user + project + to_string(chrono::system_clock::now().time_since_epoch().count());
    this-> s = s;
    this->font = font;
    this->color = color;
    this->bold = bold;
    this->italic = italic;
    this->underline = underline;
    this->strike = strike;
    this->frac = frac;




}
Symbol::Symbol(const Symbol &symbol) {

    this->id = symbol.id;
    this->s = symbol.s;
    this->color = symbol.color;
    this->font = symbol.font;
    this->frac = symbol.frac;
    this->bold = symbol.bold;
    this->italic = symbol.italic;
    this->underline = symbol.underline;
    this->strike = symbol.strike;
}

Symbol::Symbol(Symbol &&symbol) {
    this->id = symbol.id;
    this->s = symbol.s;
    this->color = symbol.color;
    this->font = symbol.font;
    this->frac = symbol.frac;
    this->bold = symbol.bold;
    this->italic = symbol.italic;
    this->underline = symbol.underline;
    this->strike = symbol.strike;

}

Symbol& Symbol::operator=(const Symbol& symbol) {
    if(&symbol != this){
        this->id = symbol.id;
        this->s = symbol.s;
        this->color = symbol.color;
        this->font = symbol.font;
        this->frac = symbol.frac;
        this->bold = symbol.bold;
        this->italic = symbol.italic;
        this->underline = symbol.underline;
        this->strike = symbol.strike;
    }
    return *this;
}
bool Symbol::operator<(const Symbol &symbol) {
    return this->frac < symbol.frac;
}
bool Symbol::operator>(const Symbol &symbol) {
    return this->frac > symbol.frac;
}
bool Symbol::operator<=(const Symbol &symbol) {
    return this->frac <= symbol.frac;
}
bool Symbol::operator>=(const Symbol &symbol) {
    return this->frac >= symbol.frac;
}
bool Symbol::operator==(const Symbol& symbol) {
    return this->id == symbol.id;
}
const vector<int>& Symbol::getFrac() {
    return this->frac;
}
void Symbol::print() {
    cout << this->s <<" "<< this->bold << this->italic << this->underline << this->strike << this->color << "---";
    for(auto& n : frac)
        cout << n;
    cout << std::endl;
}
string Symbol::getId() {
    return id;
}
char Symbol::getChar() {
    return s;
}