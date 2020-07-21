//
// Created by davide miro on 2019-10-01.
//


#include <QTextEdit>
#include <QTextBlock>
#include "Project.h"


Project::Project(QTextDocument *document,QObject* parent):QObject(parent),document(document){}

int Project::insertOrder(int l,int r,Symbol s){ //inserisco in tempo logaritmico in modo ordinato elemento,serve
    int q;
    if(s <= text[l]){
        text.insert(text.begin(),s);
        symbols.insert({s.getId(),0});

        return 0;
    }
    if(s >= text[r-1]){
        text.insert(text.end(),s);
        symbols.insert({s.getId(),r});
        return r;
    }
    while(l <= r){
        q = (l+r)/2;
        if( text[q] >= s){
            if(text[q - 1] <= s){
                text.insert(text.begin()+q,s);
                symbols.insert({s.getId(),q});
                return q;
            }
            r = q - 1;
        }
        else{
            if(text[q + 1] >= s ){
                text.insert(text.begin() + q,s);
                symbols.insert({s.getId(),q});
                return q;
            }
            l = q + 1;
        }
    }
}
void Project::eraseElement(int pos) {
    symbols.erase(text[pos].getId());
    text.erase(text.begin()+pos);
}
void Project::eraseElement(string id) {
    int pos = symbols[id];
    symbols.erase(id);
    text.erase(text.begin()+pos);
}
int Project::insert(int pos,Symbol s) {
    text.insert(text.begin()+pos,s);
    symbols.insert({s.getId(),pos});
}
void Project::eraseElements(int pos, int r) {
    /*auto it = text.begin()+pos;
    auto end = it + r;
    while(it != end){
        symbols.erase(it->getId());
        Symbol s = *it;
        text.erase(it);
        emit remove_symbol(s);
        it ++;
    }*/
    for(int i=0;i<r;i++){
        auto it = text.begin()+pos;
        symbols.erase(it->getId());
        Symbol s = *it;
        text.erase(it);
        emit remove_symbol(s);
    }
}


void Project::externalInsert(Symbol s) {

    int pos = insertOrder(0,text.size(),s);
    QTextCursor cursor(document);
    cursor.setPosition(pos);
    cursor.insertText(QString(s.getChar()));

}

void Project::externalDelete(string id) {
    int pos = symbols[id];
    eraseElement(pos);
    QTextCursor cursor(document);
    cursor.setPosition(pos);
    cursor.deleteChar();

}

Symbol Project::get_symbol_in_pos(int pos) {
    return text[pos];
}
