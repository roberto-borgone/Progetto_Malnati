    //
// Created by rober on 16/07/2020.
//

#include <QtCore/QJsonDocument>
#include "Service.h"

int Service::login(std::string user, std::string password) const{
    //try to log in
    return this->db.log_in(user, password);
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

QByteArray Service::getProject(std::string id) const{
    return this->db.get_project(id);
}

int Service::update_project(const std::string id, QByteArray doc) const{
    return this->db.update_project(id, doc);
}


