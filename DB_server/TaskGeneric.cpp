//
// Created by rober on 13/07/2020.
//

#include "TaskGeneric.h"

#include <utility>

#define LOGIN 0
#define SUBSCRIPTION 1
#define INSERT 6
#define DELETE 7
#define CURSOR 8
#define ERROR -1

TaskGeneric::TaskGeneric(const Service& service, QJsonObject message): service(service), message(std::move(message)){}

void TaskGeneric::run(){

    QJsonObject json;
    int result_login;

    int opCode = this->getOpCode();

    switch(opCode){

        case LOGIN:
            result_login = this->service.login(this->message["user"].toString().toStdString(), this->message["password"].toString().toStdString());
            json = QJsonObject({
                                     qMakePair(QString("opcode"), QJsonValue(0)),
                                     qMakePair(QString("status"), QJsonValue(result_login)),
                             });

            if(result_login == 0){
                json.insert("user", QJsonValue(this->message["user"].toString()));
                emit login(this->message["user"].toString());
            }else{
                json.insert("user", QJsonValue(""));
            }

            emit returnResult(QJsonDocument(json).toJson());
            break;

        case SUBSCRIPTION:

            emit returnResult(this->service.subscribe(this->message["user"].toString().toStdString(), this->message["password"].toString().toStdString()));
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
        switch(this->message["opcode"].toInt()){
            case 0:
                return LOGIN;
            case 1:
                return SUBSCRIPTION;
            case 6:
                return INSERT;
            case 7:
                return DELETE;
            case 8:
                return CURSOR;
            default:
                return ERROR;
        }
    }
}
