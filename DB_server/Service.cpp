    //
// Created by rober on 16/07/2020.
//

#include <QtCore/QJsonDocument>
#include "Service.h"

std::string Service::login(std::string user, std::string password, int* status) const{
    //try to log in
    return this->db.log_in(user, password, status);
}

int Service::subscribe(std::string user, std::string password) const{
    //try to subscribe
    return this->db.subscribe(user, password);
}

int Service::createProject(const std::string id, QByteArray doc) const{
    return this->db.create_project(id, doc);
}

QStringList Service::getProjects() const{
    return this->db.get_projects();
}

QByteArray Service::getProject(std::string id, int* status) const{
    return this->db.get_project(id, status);
}

int Service::update_project(const std::string id, QByteArray doc) const{
    return this->db.update_project(id, doc);
}

int Service::update_nick(std::string user, std::string nick) const{
    return this->db.update_nick(user, nick);
}

std::string Service::get_nick(std::string user) const{
    return this->db.get_nick(user);
}


