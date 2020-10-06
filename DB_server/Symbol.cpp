//
// Created by davide miro on 2019-10-12.
//

#include "Symbol.h"

Symbol::Symbol(QChar s, std::string font, bool bold, bool italic, bool underline, bool strike, std::string color,
               const std::vector<int> &frac, const std::string &project, const std::string &user) {
    id = user + project + std::to_string(std::chrono::system_clock::now().time_since_epoch().count());
    this->s = s;
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

bool Symbol::operator==(const Symbol &symbol) {
    return this->id == symbol.id;
}

const std::vector<int> &Symbol::getFrac() {
    return this->frac;
}

void Symbol::print() {
    /*
    std::cout << this->s << " " << this->bold << this->italic << this->underline << this->strike << this->color << "---";
    for (auto &n : frac)
        std::cout << n;
    std::cout << std::endl;
     */
}

std::string Symbol::getId() {
    return id;
}

QChar Symbol::getChar() {
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
                                           qMakePair(QString("s"), QJsonValue(this->s)),
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

                                   });
    return Json_symbol;
}

Symbol::Symbol(QJsonObject json_symbol) {
    QJsonArray json_frac = json_symbol["frac"].toArray();
    for(int i=0; i<json_frac.size(); i++){
        frac.insert(frac.end(),json_frac[i].toInt());
    }
    id=std::string(json_symbol["id"].toString().toStdString());
    s=json_symbol["s"].toString()[0];
    font=std::string(json_symbol["font"].toString().toStdString());
    color=std::string(json_symbol["color"].toString().toStdString());
    bold=json_symbol["bold"].toBool();
    italic=json_symbol["italic"].toBool();
    underline=json_symbol["underline"].toBool();
    strike=json_symbol["strike"].toBool();
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
