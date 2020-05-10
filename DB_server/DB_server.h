//
// Created by Clemente Cetera on 08/04/2020.
//

#ifndef DB_SERVER_DB_SERVER_H
#define DB_SERVER_DB_SERVER_H

#include <iostream>
#include <sstream>
#include <vector>
#include <bits/stdc++.h>
#include <QMainWindow>
#include <QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QMainWindow>
#include <string>
#include <QApplication>
#include <QSslSocket>
#include <QHostAddress>
#include <QTcpServer>
#include <QSslKey>
#include <QSslCertificate>
#include <QElapsedTimer>
#include "DB_functions.h"

class DB_server : public QTcpServer {
Q_OBJECT

    QSslSocket *socket = new QSslSocket;
    DB_interface DB;

public:
    DB_server(QObject *parent) : QTcpServer(parent) {

        //put server on listening
        QHostAddress address = QHostAddress::Any;
        quint16 port = 1290;

        socket->setPeerVerifyMode(QSslSocket::VerifyPeer);

        if (this->listen(address, port)) {
            std::cout << QSslSocket::supportsSsl() << std::endl;
            std::cout << (socket->sslLibraryBuildVersionString()).toStdString()<<std::endl;
            std::cout << "Now listen on address: " << qPrintable(address.toString()) << " on port: " << port
                      << std::endl;
            QObject::connect(this, &DB_server::newConnection, this, &DB_server::new_connection);
        } else
            std::cout << "ERROR: could not bind to " << qPrintable(address.toString()) << ":" << port << std::endl;
    }

public slots:

    void new_connection();
    void reply();

protected:
    void incomingConnection(qintptr socketDescriptor);

};

#endif //DB_SERVER_DB_SERVER_H
