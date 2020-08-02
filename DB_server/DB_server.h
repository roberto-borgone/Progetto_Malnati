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
#include <QThreadPool>
#include <QSslKey>
#include <QSslCertificate>
#include <QElapsedTimer>
#include "DB_functions.h"
#include "Client.h"
#include "Service.h"

class DB_server : public QTcpServer {
Q_OBJECT

    Service service;
    std::map<std::string, std::shared_ptr<Project>> projects;
    std::mutex projects_mux;

public:
    explicit DB_server(QObject *parent = nullptr) : QTcpServer(parent) {

        //put server on listening
        QHostAddress address = QHostAddress::Any;
        quint16 port = 1290;

        if (this->listen(address, port)) {
            std::cout << QSslSocket::supportsSsl() << std::endl;
            std::cout << (QSslSocket::sslLibraryBuildVersionString()).toStdString()<<std::endl;
            std::cout << "Now listen on address: " << qPrintable(address.toString()) << " on port: " << port
                      << std::endl;
        } else
            std::cout << "ERROR: could not bind to " << qPrintable(address.toString()) << ":" << port << std::endl;
    }

protected:
    void incomingConnection(qintptr socketDescriptor) override;

};

#endif //DB_SERVER_DB_SERVER_H
