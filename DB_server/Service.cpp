    //
// Created by rober on 16/07/2020.
//

#include <QtCore/QJsonDocument>
#include "Service.h"

int Service::login(std::string user, std::string password) const{
    //try to log in
    return this->user_db.log_in(user, password);
}

QByteArray Service::subscribe(std::string user, std::string password) const{
    //try to subscribe
    int result = this->user_db.subscribe(user, password);
    QJsonObject json({
                             qMakePair(QString("opcode"), QJsonValue(1)),
                             qMakePair(QString("status"), QJsonValue(result)),
                     });
    return QJsonDocument(json).toJson();
}
