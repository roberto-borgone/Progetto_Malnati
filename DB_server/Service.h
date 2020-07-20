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

    int login(std::string user, std::string password) const;
    QByteArray subscribe(std::string user, std::string password) const;

private:

    DB_interface user_db;

};


#endif //DB_SERVER_SERVICE_H
