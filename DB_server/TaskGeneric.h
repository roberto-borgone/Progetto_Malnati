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
#import <memory>
#include <mutex>
#include "Service.h"
#include "Project.h"

class TaskGeneric: public QObject, public QRunnable  {

    Q_OBJECT

public:

    TaskGeneric(const Service& service, std::map<std::string, std::shared_ptr<Project>>& projects, std::mutex& projects_mux, std::shared_ptr<Project>& project, QJsonObject message);

signals:
    void returnResult(QByteArray result);
    void forwardMessage(QByteArray);
    void login(QString user);
    void openProject(std::shared_ptr<Project> project);
    void closeProject(std::string id);

protected:

    const Service& service;
    std::map<std::string, std::shared_ptr<Project>>& projects;
    std::mutex& projects_mux;
    std::shared_ptr<Project>& project;
    QJsonObject message;

    void run() override;
    int getOpCode();
};


#endif //DB_SERVER_TASKGENERIC_H
