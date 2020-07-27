//
// Created by rober on 13/07/2020.
//

#include "TaskGeneric.h"

#include <utility>

#define LOGIN 0
#define SUBSCRIPTION 1
#define REQUEST_PROJECTS 2
#define OPEN 3
#define CREATE 4
#define CLOSE 5
#define INSERT 6
#define DELETE 7
#define CURSOR 8
#define ERROR -1

TaskGeneric::TaskGeneric(const Service& service, QJsonObject message): service(service), message(std::move(message)){}

void TaskGeneric::run(){

    QJsonObject json;
    int result;

    int opCode = this->getOpCode();

    switch(opCode){

        case LOGIN:
            result = this->service.login(this->message["user"].toString().toStdString(), this->message["password"].toString().toStdString());
            json = QJsonObject({
                                     qMakePair(QString("opcode"), QJsonValue(0)),
                                     qMakePair(QString("status"), QJsonValue(result)),
                             });

            if(result == 0){
                json.insert("user", QJsonValue(this->message["user"].toString()));
                emit login(this->message["user"].toString());
            }else{
                json.insert("user", QJsonValue(""));
            }

            emit returnResult(QJsonDocument(json).toJson());
            break;

        case SUBSCRIPTION:

            result = this->service.subscribe(this->message["user"].toString().toStdString(), this->message["password"].toString().toStdString());
            json = QJsonObject({
                                       qMakePair(QString("opcode"), QJsonValue(1)),
                                       qMakePair(QString("status"), QJsonValue(result)),
                               });

            if(result == 0){
                json.insert("user", QJsonValue(this->message["user"].toString()));
                emit login(this->message["user"].toString());
            }else{
                json.insert("user", QJsonValue(""));
            }

            emit returnResult(QJsonDocument(json).toJson());
            break;

        case REQUEST_PROJECTS:
            break;

        case OPEN:
            break;

        case CREATE:

            break;

        case CLOSE:
            break;

        case INSERT:

            emit forwardMessage(QJsonDocument(this->message).toJson());
            break;

        case DELETE:

            emit forwardMessage(QJsonDocument(this->message).toJson());
            break;

        case CURSOR:

            emit forwardMessage(QJsonDocument(this->message).toJson());
            break;

        default:
            break;
    }


}

int TaskGeneric::getOpCode(){

    if(this->message.contains("opcode") && this->message["opcode"].isDouble()){
        return this->message["opcode"].toInt();
    }
}
