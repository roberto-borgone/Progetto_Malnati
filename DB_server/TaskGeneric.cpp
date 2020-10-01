//
// Created by rober on 13/07/2020.
//

#include "TaskGeneric.h"
#include "Project.h"

#include <QtCore/QJsonArray>
#include <QtCore/QBuffer>

#define LOGIN 0
#define SUBSCRIPTION 1
#define REQUEST_PROJECTS 2
#define OPEN 3
#define CREATE 4
#define CLOSE 5
#define INSERT 6
#define DELETE 7
#define CURSOR 8
#define AUTHORIZATION_ERROR -2
#define PROJECT_ERROR -3

TaskGeneric::TaskGeneric(const Service& service, std::map<std::string, std::shared_ptr<Project>>& projects, std::mutex& projects_mux, std::shared_ptr<Project>& project, QString userId, QJsonObject message): service(service), projects(projects), projects_mux(projects_mux), project(project), userId(userId), message(std::move(message)){}

void TaskGeneric::run(){

    int opCode = this->getOpCode();

    switch(opCode){

        case LOGIN: {

            int result;
            QJsonObject json;
            QImage img;

            result = this->service.login(this->message["user"].toString().toStdString(),
                                         this->message["password"].toString().toStdString());
            json = QJsonObject({
                                       qMakePair(QString("opcode"), QJsonValue(0)),
                                       qMakePair(QString("status"), QJsonValue(result)),
                               });

            if (result == 0) {
                json.insert("user", QJsonValue(this->message["user"].toString()));
                img.load("../images/" + this->message["user"].toString() + ".png");
                QBuffer buffer;
                buffer.open(QIODevice::WriteOnly);
                img.save(&buffer, "PNG");
                auto const encoded = buffer.data().toBase64();
                json.insert("user_img", {QLatin1String(encoded)});
                emit login(this->message["user"].toString());
            } else {
                json.insert("user", QJsonValue(""));
            }

            emit returnResult(QJsonDocument(json).toJson());
            break;

        }

        case SUBSCRIPTION: {

            int result;
            QJsonObject json;
            QImage img = QImage("../images/User_icon.png");

            result = this->service.subscribe(this->message["user"].toString().toStdString(),
                                             this->message["password"].toString().toStdString());
            json = QJsonObject({
                                       qMakePair(QString("opcode"), QJsonValue(1)),
                                       qMakePair(QString("status"), QJsonValue(result)),
                               });

            if (result == 0) {
                json.insert("user", QJsonValue(this->message["user"].toString()));
                img.save("../images/" + this->message["user"].toString() + ".png");
                QBuffer buffer;
                buffer.open(QIODevice::WriteOnly);
                img.save(&buffer, "PNG");
                auto const encoded = buffer.data().toBase64();
                json.insert("user_img", {QLatin1String(encoded)});
                emit login(this->message["user"].toString());
            } else {
                json.insert("user", QJsonValue(""));
            }

            emit returnResult(QJsonDocument(json).toJson());
            break;

        }

        case REQUEST_PROJECTS: {

            QStringList result;
            QJsonObject json;

            result = this->service.getProjects();

            json = QJsonObject({
                qMakePair(QString("opcode"), QJsonValue(2)),
                qMakePair(QString("prjIDs"), QJsonArray::fromStringList(result))
            });

            emit returnResult(QJsonDocument(json).toJson());
            break;

        }

        case OPEN: {

            QByteArray result;
            QJsonObject json;
            std::vector<Symbol> text;
            QJsonArray text_json;
            std::shared_ptr<Project> new_project;

            {
                auto lock = std::lock_guard(this->projects_mux);
                if(this->projects.find(this->message["prjID"].toString().toStdString()) == this->projects.end()){

                    result = this->service.getProject(this->message["prjID"].toString().toStdString());

                    std::cout << "Opening:\n" << result.toStdString() << std::endl;

                    QJsonDocument json_document = QJsonDocument::fromJson(result);

                    json = json_document.object();

                    text_json = json["text"].toArray();
                    for (auto value : text_json) {
                        QJsonObject obj = value.toObject();
                        text.emplace_back(Symbol(obj));
                    }

                    new_project = std::make_shared<Project>(json["id"].toString().toStdString(), text);

                    this->projects.insert(std::pair(new_project->getId(), new_project));
                }else{
                    new_project = this->projects[this->message["prjID"].toString().toStdString()];
                }
            }

            QJsonArray response_text;

            for (Symbol s : new_project->text) {
                response_text.push_back(s.toJson());
            }

            json = QJsonObject({
                                       qMakePair(QString("opcode"), QJsonValue(3)),
                                       qMakePair(QString("prjID"), this->message["prjID"]),
                                       qMakePair(QString("text"), response_text)
                               });

            this->project = new_project;
            emit returnResult(QJsonDocument(json).toJson());
            break;

        }

        case CREATE: {

            int result;
            QJsonObject json;
            std::vector<Symbol> text;
            std::shared_ptr<Project> new_project;

            json = QJsonObject({
                                       qMakePair(QString("id"), this->message["prjID"]),
                                       qMakePair(QString("text"), QJsonArray())
                               });

            result = this->service.createProject(this->message["prjID"].toString().toStdString(), QJsonDocument(json).toJson());

            json = QJsonObject({
                                       qMakePair(QString("opcode"), QJsonValue(4)),
                                       qMakePair(QString("status"), QJsonValue(result)),
                                       qMakePair(QString("prjID"), this->message["prjID"]),
                               });

            if(result == 0) {

                new_project = std::make_shared<Project>(this->message["prjID"].toString().toStdString(), std::vector<Symbol>());

                {
                    auto lock = std::lock_guard(this->projects_mux);
                    this->projects.insert(std::pair(new_project->getId(), new_project));
                }

                this->project = new_project;
            }

            emit returnResult(QJsonDocument(json).toJson());

            break;

        }

        case CLOSE: {

            this->project.reset();

            {
                auto lock = std::lock_guard(this->projects_mux);
                if (this->projects[this->message["prjID"].toString().toStdString()].use_count() == 1) {

                    QJsonArray text;

                    for (Symbol s : this->projects[this->message["prjID"].toString().toStdString()]->text) {
                        text.push_back(s.toJson());
                    }

                    QJsonObject json = QJsonObject({
                                                           qMakePair(QString("id"), this->message["prjID"]),
                                                           qMakePair(QString("text"), text)
                                                   });

                    this->service.update_project(this->message["prjID"].toString().toStdString(), QJsonDocument(json).toJson());
                    this->projects.erase(this->message["prjID"].toString().toStdString());
                }
            }

            break;

        }

        case INSERT: {

            Symbol s(this->message["symbol"].toObject());
            int position = this->message["position"].toInt();

            {
                auto lock = std::lock_guard(this->project->text_mux);
                if (position < this->project->text.size()) {
                    Symbol symbol_in_pos = this->project->get_symbol_in_pos(position);
                    std::hash<std::string> hash_funct;
                    while (symbol_in_pos.getFrac() == s.getFrac() &&
                           hash_funct(symbol_in_pos.getId()) > hash_funct(symbol_in_pos.getId())) {
                        position++;
                        symbol_in_pos = this->project->get_symbol_in_pos(position);
                    }
                }
                this->project->insert(position, s);
            }

            emit forwardMessage(QJsonDocument(this->message).toJson());
            break;

        }

        case DELETE: {

            Symbol s(this->message["symbol"].toObject());

            {
                auto lock = std::lock_guard(this->project->text_mux);
                int pos = this->project->remote_delete(s);
            }

            emit forwardMessage(QJsonDocument(this->message).toJson());

            break;

        }

        case CURSOR:

            emit forwardMessage(QJsonDocument(this->message).toJson());
            break;

        case AUTHORIZATION_ERROR:

            std::cout << "AUTHORIZATION ERROR!" << std::endl;
            std::cout<<QJsonDocument(this->message).toJson().toStdString()<<std::endl;
            emit killClient();
            break;

        case PROJECT_ERROR:

            std::cout << "PROJECT ERROR!" << std::endl;
            std::cout<<QJsonDocument(this->message).toJson().toStdString()<<std::endl;
            emit killClient();
            break;

        default:
            std::cout << "OPCODE NOT RECOGNIZED!" << std::endl;
            std::cout<<QJsonDocument(this->message).toJson().toStdString()<<std::endl;
            emit killClient();
            break;
    }


}

int TaskGeneric::getOpCode(){

    if(this->message.contains("opcode") && this->message["opcode"].isDouble()){

        // shallow security checks

        //cannot login or subscribe after logged
        if(0 <= message["opcode"].toInt() && message["opcode"].toInt() <= 1){
            if(this->userId != "")
                return -2;
        }

        //cannot do any protected operation without authentication
        if(2 <= message["opcode"].toInt() && message["opcode"].toInt() <= 8){
            if(!this->message.contains("user"))
                return -2;
            if(this->userId == "" || this->message["user"].toString() != this->userId)
                return -2;

            // cannot work on a project without opening it
            if(5 <= message["opcode"].toInt() && message["opcode"].toInt() <= 8){
                if(!this->message.contains("prjID"))
                    return -3;
                if(!this->project || this->message["prjID"].toString().toStdString() != this->project->getId())
                    return -3;
            }
        }

        return message["opcode"].toInt();
    }

    return -1;
}

TaskGeneric::~TaskGeneric() {
    emit finished();
}
