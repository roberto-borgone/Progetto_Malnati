//
// Created by rober on 13/07/2020.
//

#ifndef DB_SERVER_TASKGENERIC_H
#define DB_SERVER_TASKGENERIC_H


#include <QRunnable>
#include <QObject>
#include <QImage>
#include <sstream>
#include <QJsonObject>
#include <QJsonDocument>
#import <memory>
#include <mutex>
#include "Service.h"
#include "Project.h"

class TaskGeneric: public QObject, public QRunnable  {

    Q_OBJECT

public:

    TaskGeneric(const Service& service, std::map<std::string, std::shared_ptr<Project>>& projects, std::mutex& projects_mux, std::shared_ptr<Project>& project, QString userId, QJsonObject message);
    ~TaskGeneric() override;

signals:
    void returnResult(QByteArray result);
    void forwardMessage(QByteArray, QString);
    void login(QString user);
    void killClient();
    void finished();

protected:

    const Service& service;
    std::map<std::string, std::shared_ptr<Project>>& projects;
    std::mutex& projects_mux;
    std::shared_ptr<Project>& project;
    QJsonObject message;
    QString userId;

    void run() override;
    int getOpCode();
};


#endif //DB_SERVER_TASKGENERIC_H
