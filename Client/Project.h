//
// Created by davide miro on 2019-10-01.
//

#ifndef EDITORCOLLABORATIVO_PROJECT_H
#define EDITORCOLLABORATIVO_PROJECT_H

#include <QTextDocument>
#include <QFont>
#include <iostream>
#include <QTextCharFormat>
#include <QTextCursor>
#include <algorithm>
#include <set>
#include <mutex>

#include "Symbol.h"

using namespace std;


class Project: public QObject{//Questa classe permette di comunicare con thread esteri
Q_OBJECT


    QTextDocument *document;
public:


    Project(QTextDocument *document,QObject *parent);

    multiset<Symbol> text;

    map<string,Symbol> symbols; //id->position
    /*******PROVA DI POP UP PER NESSUN PROGETTO APERTO***/
    bool prjID_set = false; //set true to use editor
    std::string prjID;


    int insert(Symbol s);
    int eraseElement(Symbol s);
    void eraseElements(int pos,int removed);
    int remote_delete(Symbol s);
    int eraseElement(string id);
    void delete_all();
    void markUsersText(map<string,vector<int>> colors);

    signals:
    void internalInsert(Symbol s);
    void internalDelete(string id);
    void remove_symbol(std::vector<Symbol> s);

public slots:
   // void updateText(int pos,int removed,int added);
    void externalInsert(Symbol s);
    void externalDelete(string id);








};


#endif //EDITORCOLLABORATIVO_PROJECT_H
