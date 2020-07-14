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

#include "Symbol.h"

using namespace std;


class Project: public QObject{//Questa classe permette di comunicare con thread esteri
Q_OBJECT


    QTextDocument *document;
public:

    Project(QTextDocument *document,QObject *parent);
    vector<Symbol> text;
    map<string,int> symbols; //id->position

    int insert(int pos,Symbol s);
    int insertOrder(int l,int r,Symbol s);
    void eraseElement(int pos);
    void eraseElement(string id);
    void eraseElements(int pos,int r);

    signals:
    void internalInsert(Symbol s);
    void internalDelete(string id);

public slots:
   // void updateText(int pos,int removed,int added);
    void externalInsert(Symbol s);
    void externalDelete(string id);








};


#endif //EDITORCOLLABORATIVO_PROJECT_H