//
// Created by rober on 13/07/2020.
//

#ifndef DB_SERVER_CLIENT_H
#define DB_SERVER_CLIENT_H


#include <QObject>
#include <QSslSocket>
#include <QTcpServer>
#include <QRunnable>
#include <iostream>
#include <sstream>
#include <QThreadPool>
#include <QJsonDocument>
#include <QJsonObject>
#include "TaskGeneric.h"
#include "Service.h"

class Client: public QObject {

    Q_OBJECT

public:
    Client(const Service& service, std::map<std::string, std::shared_ptr<Project>>& projects, std::mutex& projects_mux, qintptr socketDescriptor, QObject* parent = nullptr);

signals:

public slots:
    void connected();
    void disconnected();
    void readyRead();

    void taskCompleted(const QByteArray& result);
    void forwardMessage(const QByteArray& message);
    void sendMessage(const QByteArray& message);
    void login(QString user);

private:

    QSslSocket* socket;
    const Service& service;
    QString userId;
    std::shared_ptr<Project> project;
    std::map<std::string, std::shared_ptr<Project>>& projects;
    std::mutex& projects_mux;

};


#endif //DB_SERVER_CLIENT_H
