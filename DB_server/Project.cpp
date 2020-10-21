//
// Created by rober on 28/07/2020.
//

#include "Project.h"

Project::Project(std::string id, std::multiset<Symbol> text): id(id), text(text){}

std::string Project::getId(){
    return this->id;
}

void Project::insert(Symbol s) {
    text.insert(s);
}

void Project::remote_delete(Symbol s) {
    text.erase(s);
}

int Project::add_user(std::pair<QString, QString> user) {
    auto lock = std::lock_guard(this->user_mux);
    this->users.insert(user);
}

int Project::remove_user(std::pair<QString, QString> user){
    auto lock = std::lock_guard(this->user_mux);
    this->users.erase(user);
}