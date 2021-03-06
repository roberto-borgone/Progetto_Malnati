//
// Created by davide miro on 2019-10-12.
//

#include "Symbol.h"
#include <sstream>

Symbol::Symbol(QChar s, string font, bool bold, bool italic, bool underline, bool strike, string color,
               const vector<int> &frac, const string &project, const string &user,int size, int align) {

    id = user +"/"+ project +"/" + to_string(chrono::system_clock::now().time_since_epoch().count());
    this->s = s;
    this->font = font;
    this->color = color;
    this->bold = bold;
    this->italic = italic;
    this->underline = underline;
    this->strike = strike;
    this->frac = frac;
    this->size = size;
    this->align=align;


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
    this->size = symbol.size;
    this->align=symbol.align;
}
Symbol::Symbol() {}

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
    this->size = symbol.size;
    this->align=symbol.align;

}

Symbol &Symbol::operator=(const Symbol &symbol) {
    if (&symbol != this) {
        this->id = symbol.id;
        this->s = symbol.s;
        this->color = symbol.color;
        this->font = symbol.font;
        this->frac = symbol.frac;
        this->bold = symbol.bold;
        this->italic = symbol.italic;
        this->underline = symbol.underline;
        this->strike = symbol.strike;
        this->size = symbol.size;
        this->align=symbol.align;

    }
    return *this;
}

vector<string> Symbol::splitId(string id) const{
    string intermediate;
    stringstream stream(id);
    vector<string> split;
    while(getline(stream,intermediate,'/')){
        split.push_back(intermediate);
    }
    return split;

}

bool Symbol::operator>(const Symbol &symbol) {
    if(this->frac == symbol.frac){
        vector<string> split1 = splitId(this->getId());
        vector<string> split2 = splitId(symbol.getId());

        string check1 = split1[2] + split1[0];
        string check2 = split2[2] + split2[0];

        return check1 > check2;
    }
    else{
        return this->frac > symbol.frac;

    }

}
bool Symbol::operator<(const Symbol &symbol) const {
    if(this->frac == symbol.frac){
        vector<string> split1 = splitId(this->getId());
        vector<string> split2 = splitId(symbol.getId());

        string check1 = split1[2] + split1[0];
        string check2 = split2[2] + split2[0];

        return check1 < check2;
    }
    else{
        return this->frac < symbol.frac;

    }

}

bool Symbol::operator>=(const Symbol &symbol) {
    if(this->frac == symbol.frac){
        vector<string> split1 = splitId(this->getId());
        vector<string> split2 = splitId(symbol.getId());

        string check1 = split1[2] + split1[0];
        string check2 = split2[2] + split2[0];

        return check1 >= check2;
    }
    else{
        return this->frac >= symbol.frac;

    }

}
bool Symbol::operator<=(const Symbol &symbol)  {
    if(this->frac == symbol.frac){
        vector<string> split1 = splitId(this->getId());
        vector<string> split2 = splitId(symbol.getId());

        string check1 = split1[2] + split1[0];
        string check2 = split2[2] + split2[0];

        return check1 <= check2;
    }
    else{
        return this->frac <= symbol.frac;

    }

}

bool Symbol::operator==(const Symbol &symbol) {
    return this->id == symbol.id;
}

const vector<int> &Symbol::getFrac() const {
    return this->frac;
}

void Symbol::print() {
    /*
    cout << this->s << " " << this->bold << this->italic << this->underline << this->strike << this->color << "---";
    for (auto &n : frac)
        cout << n;
    cout << std::endl;
    */
}

string Symbol::getId() const{
    return id;
}

QChar Symbol::getChar() const{
    return s;
}

QJsonObject Symbol::toJson() {
    //creo QJsonArray per inviare vettore posizione
    QJsonArray json_frac;
    for (auto el : frac) {
        json_frac.append(QJsonValue(el));
    }
    auto Json_symbol = QJsonObject({
                                           qMakePair(QString("id"), QJsonValue(QString(this->id.c_str()))),
                                           qMakePair(QString("s"), QJsonValue(QChar(this->s))),
                                           qMakePair(QString("font"), QJsonValue(QString(this->font.c_str()))),
                                           qMakePair(QString("color"),
                                                     QJsonValue(QString(this->color.c_str()))),
                                           qMakePair(QString("bold"),
                                                     QJsonValue(this->bold)),
                                           qMakePair(QString("italic"),
                                                     QJsonValue(this->italic)),
                                           qMakePair(QString("underline"),
                                                     QJsonValue(this->underline)),
                                           qMakePair(QString("strike"),
                                                     QJsonValue(this->strike)),
                                           qMakePair(QString("frac"),
                                                     QJsonValue(json_frac)),
                                           qMakePair(QString("size"),QJsonValue(this->size)),
                                           qMakePair(QString("align"),QJsonValue(this->align)),

                                   });
    return Json_symbol;
}

Symbol::Symbol(QJsonObject json_symbol) {
    QJsonArray json_frac = json_symbol["frac"].toArray();
    for(int i=0; i<json_frac.size(); i++){
        frac.insert(frac.end(),json_frac[i].toInt());
    }
    id=string(json_symbol["id"].toString().toStdString());
    s=json_symbol["s"].toString()[0];
    font=string(json_symbol["font"].toString().toStdString());
    color=string(json_symbol["color"].toString().toStdString());
    bold=json_symbol["bold"].toBool();
    italic=json_symbol["italic"].toBool();
    underline=json_symbol["underline"].toBool();
    strike=json_symbol["strike"].toBool();
    size=json_symbol["size"].toInt();
    align=json_symbol["align"].toInt();
}

const QString Symbol::getFont() const {
    return QString(font.c_str());
}

bool Symbol::isBold() const {
    return bold;
}

bool Symbol::isItalic() const {
    return italic;
}

bool Symbol::isUnderline() const {
    return underline;
}

bool Symbol::isStrike() const {
    return strike;
}

const QString Symbol::getColor() const {
    return QString(color.c_str());
}

int Symbol::getSize() {
    return size;
}

int Symbol::getAlign() {
    return align;
}