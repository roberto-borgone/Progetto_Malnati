//
// Created by davide miro on 19/10/2019.
//

#ifndef EDITORCOLLABORATIVO_NETWORK_H
#define EDITORCOLLABORATIVO_NETWORK_H

#include <QObject>
#include "Symbol.h"
#include "Project.h"
#include "Gui.h"
#include <functional>
#include <thread>
#include <vector>
#include <map>
#include <iostream>
#include <QSslSocket>
#include <QJsonObject>
#include <memory>
#include <QJsonParseError>
#include <set>
#include <QBuffer>

class Network : public QObject {
Q_OBJECT;
    std::shared_ptr<QTcpSocket> socket_ptr;
    std::shared_ptr<Project> project_ptr;
    std::shared_ptr<Gui> gui_ptr;
    std::set<string> users;
public:
    Network(Project *project, Gui *gui);
    void selfCall();

    void receiveCommand(); //riceve comando da esterno e lo manda a project

signals:

    void insert(Symbol s);

    void erase(string s);

    void logged_in(std::string user);

    void wrong_log_in();

    void wrong_sub();

    void list_available(std::vector<std::string> list);

    void change_cursor(std::string user, int position);

    void new_user(std::string user);


public slots:

    //void sendCommand(); //manda comando all' esterno
    void getSocket(QTcpSocket &s);

    //void sendCommand(); //manda comando all' esterno
    void disconnect();

    //creo slot che riceve il segnale send_symbol emesso in gui.cpp con il corrispondente simbolo e lo invia tramite socket_ptr
    void send_symbol(Symbol s, int pos, std::string prj, std::string usr);

    //slot per l'invio della cancellazione di un carattere
    void remove_symbol(Symbol s);

    //funzione generica per la ricezione di una risposta o di un comando da parte del server
    void message_received();

    //slot per invio richiesta progetti
    void ask_projects(std::string usr);

    //slot per l'invio chiusura progetto
    void close_project(std::string prj);

    void project_to_get(std::string prj_name);

    //slot per richiesta nuovo progetto
    void new_project(std::string prjID);

    //slot per l'invio cursore
    void send_cursor(int position);

    //to add the user that just logged in in "user" set
    void add_my_user(std::string user);

    //clear the users vector leaving only current user
    void clear_users(bool also_user);

    //slot per invio immagine
    void send_image(QImage img);

    //slot per invio nickname
    void send_nickname(std::string nick);

};


#endif //EDITORCOLLABORATIVO_NETWORK_H
