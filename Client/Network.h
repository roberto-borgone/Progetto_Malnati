//
// Created by davide miro on 19/10/2019.
//

#ifndef EDITORCOLLABORATIVO_NETWORK_H
#define EDITORCOLLABORATIVO_NETWORK_H

#include <QObject>
#include "Symbol.h"
#include "Project.h"
#include <thread>
#include <vector>
#include <map>
#include <iostream>
#include <QSslSocket>
#include <QJsonObject>
#include <memory>

class Network : public  QObject{
    Q_OBJECT;
    std::shared_ptr<QSslSocket> socket_ptr;
public:
    Network(Project *project);
    void receiveCommand(); //riceve comando da esterno e lo manda a project
    signals:
    void insert(Symbol s);
    void erase(string s);

public slots:
    //void sendCommand(); //manda comando all' esterno
    void getSocket(QSslSocket& s);
    void send_symbol(Symbol s);



};


#endif //EDITORCOLLABORATIVO_NETWORK_H
