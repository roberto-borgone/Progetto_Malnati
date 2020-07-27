//
// Created by Clemente Cetera on 29/03/2020.
//

#include <iostream>
//in order to use sqlite3 library in Clion the string
//"target_link_libraries(Prova_DataBase LINK_PUBLIC sqlite3)" had to be added
//at the end of the CMakeLists
#include "sqlite3.h"
#include <functional>
#include <string>
#include <sstream>
#include <QtCore/QByteArray>

#ifndef PROVA_DATABASE_DB_INTERFACE_H
#define PROVA_DATABASE_DB_INTERFACE_H
class DB_interface{
private:
    sqlite3* db;
public:
    DB_interface();
    virtual ~DB_interface();
    int subscribe(const std::string& user, std::string pwd) const;
    int log_in(const std::string& user, std::string pwd) const;
    int create_project(const std::string& id, QByteArray& doc) const;
    std::vector<std::string> get_projects() const;
    QByteArray get_project(std::string& id) const;
    int update_project(const std::string& id, QByteArray doc) const;
};
#endif //PROVA_DATABASE_DB_INTERFACE_H
