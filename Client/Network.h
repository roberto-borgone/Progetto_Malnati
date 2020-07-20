//
// Created by davide miro on 19/10/2019.
//

#ifndef EDITORCOLLABORATIVO_NETWORK_H
#define EDITORCOLLABORATIVO_NETWORK_H

#include <QObject>
#include "Symbol.h"
#include "Project.h"
#include <functional>
#include <thread>
#include <vector>
#include <map>
#include <iostream>
#include <QSslSocket>
#include <QJsonObject>
#include <memory>
#include <QJsonParseError>

class Network : public QObject {
Q_OBJECT;
    std::shared_ptr<QSslSocket> socket_ptr;
    std::shared_ptr<Project> project_ptr;
public:
    Network(Project *project);

    void receiveCommand(); //riceve comando da esterno e lo manda a project
signals:

    void insert(Symbol s);

    void erase(string s);

    void logged_in(std::string user);

    void wrong_log_in();

    void wrong_sub();

public slots:

    //void sendCommand(); //manda comando all' esterno
    void getSocket(QSslSocket &s);

    //creo slot che riceve il segnale send_symbol emesso in gui.cpp con il corrispondente simbolo e lo invia tramite socket_ptr
    void send_symbol(Symbol s, int pos, std::string prj, std::string usr);

    //funzione generica per la ricezione di una risposta o di un comando da parte del server
    void message_received();

};


#endif //EDITORCOLLABORATIVO_NETWORK_H
