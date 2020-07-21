    //
// Created by rober on 16/07/2020.
//

#include <QtCore/QJsonDocument>
#include "Service.h"

int Service::login(std::string user, std::string password) const{
    //try to log in
    return this->user_db.log_in(user, password);
}

int Service::subscribe(std::string user, std::string password) const{
    //try to subscribe
    return this->user_db.subscribe(user, password);
}
