#include <iostream>
#include <thread>
#include <QApplication>
#include <chrono>
#include <functional>
#include <QMessageBox>
#include "Gui.h"
#include "Network.h"
#include "DB_Client.h"


int main(int argc, char *argv[]) {


    QApplication a(argc,argv);

    auto g = new Gui(nullptr);
    Project *project = g->getCurrentProject();
    auto network = new Network(g->getCurrentProject());
    auto db_client = new DB_Client();
   /*
    thread network([project](){
        Network network(project);
        network.receiveCommand();

    });
    */

    QObject::connect(db_client, &DB_Client::logged_in, g, &Gui::logged_in);
    QObject::connect(db_client, &DB_Client::move_socket, network, &Network::getSocket);
    QObject::connect(g, &Gui::send_symbol, network, &Network::send_symbol);
    g->show();
    g->setVisible(false);
    db_client->show();
    a.exec();
   // network.join();
    return 0;
}