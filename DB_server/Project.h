//
// Created by rober on 28/07/2020.
//

#ifndef DB_SERVER_PROJECT_H
#define DB_SERVER_PROJECT_H


#include <mutex>
#include "Symbol.h"
#include <set>

class Project {

    std::string id;

public:

    std::vector<Symbol> text;
    std::mutex text_mux;
    std::set<QString> users;

    Project(std::string id, std::vector<Symbol> text);
    std::string getId();
    Symbol get_symbol_in_pos(int pos);
    int insert(int pos,Symbol s);
    int remote_delete(Symbol s);

};


#endif //DB_SERVER_PROJECT_H
