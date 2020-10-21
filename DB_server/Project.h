//
// Created by rober on 28/07/2020.
//

#ifndef DB_SERVER_PROJECT_H
#define DB_SERVER_PROJECT_H


#include <mutex>
#include "Symbol.h"
#include <set>
#include <map>

class Project {

    std::string id;

public:

    std::multiset<Symbol> text;
    std::mutex text_mux;
    std::set<std::pair<QString,QString>> users;
    std::mutex user_mux;

    Project(std::string id, std::multiset<Symbol> text);
    std::string getId();
    void insert(Symbol s);
    void remote_delete(Symbol s);
    int add_user(std::pair<QString, QString> user);
    int remove_user(std::pair<QString, QString> user);

};


#endif //DB_SERVER_PROJECT_H
