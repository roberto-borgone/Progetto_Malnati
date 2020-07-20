//
// Created by rober on 13/07/2020.
//

#ifndef DB_SERVER_TASKGENERIC_H
#define DB_SERVER_TASKGENERIC_H


#include <QRunnable>
#include <QObject>
#include <sstream>
#include <QJsonObject>
#include <QJsonDocument>
#include "Service.h"

class TaskGeneric: public QObject, public QRunnable  {

    Q_OBJECT

public:

    TaskGeneric(const Service& service, QJsonObject message);

signals:
    void returnResult(QByteArray result);
    void forwardMessage(QByteArray);
    void login(QString user);

protected:

    const Service& service;
    QJsonObject message;

    void run() override;
    int getOpCode();
};


#endif //DB_SERVER_TASKGENERIC_H
