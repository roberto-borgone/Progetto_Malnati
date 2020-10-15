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
    void selfCall();
    ~Client() override;

signals:

public slots:
    void disconnected();
    void readyRead();

    void taskCompleted(QByteArray result);
    void forwardMessage(const QByteArray& message, const QString& projectID);
    void sendMessage(QByteArray message);
    void login(QString user, QString nick);
    void killClient();

private:

    QTcpSocket* socket;
    const Service& service;
    QString userId;
    QString nick;
    std::shared_ptr<Project> project;
    std::map<std::string, std::shared_ptr<Project>>& projects;
    std::mutex& projects_mux;
    qintptr socketDescriptor;

};


#endif //DB_SERVER_CLIENT_H
