//
// Created by rober on 16/07/2020.
//

#ifndef DB_SERVER_SERVICE_H
#define DB_SERVER_SERVICE_H


#include <QByteArray>
#include <QJsonObject>
#include "DB_functions.h"

class Service {

public:

    std::string login(std::string user, std::string password, int* status) const;
    int subscribe(std::string user, std::string password) const;
    int createProject(const std::string id, QByteArray doc) const;
    QStringList getProjects() const;
    QByteArray getProject(std::string id, int* status) const;
    int update_project(const std::string id, QByteArray doc) const;
    int update_nick(std::string user, std::string nick) const;
    std::string get_nick(std::string user) const;

private:

    DB_interface db;

};


#endif //DB_SERVER_SERVICE_H
