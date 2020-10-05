//
// Created by rober on 13/07/2020.
//

#include "Client.h"
#include "DB_server.h"

Client::Client(const Service& service, std::map<std::string, std::shared_ptr<Project>>& projects, std::mutex& projects_mux, qintptr socketDescriptor, QObject* parent): QObject(parent), service(service), projects(projects), projects_mux(projects_mux), userId(""), socketDescriptor(socketDescriptor) {

    // create the QSslSocket object
    this->socket = new QTcpSocket(this);

    // since i'm not in the QTcpServer class anymore i can't use the pending connections
    // mechanism of QTcpServer so i have to link the connected signal of the socket directly
    // to see the connection happening
    connect(this->socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(this->socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    this->socket->setSocketDescriptor(socketDescriptor);

    std::cout << "New Client connected at: " << this->socketDescriptor << std::endl;
}

void Client::disconnected() {

    if(this->project){
        //automatic saving of the project

        QJsonObject json_message;

        json_message = QJsonObject({
                                   qMakePair(QString("opcode"), QJsonValue(5)),
                                   qMakePair(QString("user"), QJsonValue(this->userId)),
                                   qMakePair(QString("prjID"), QJsonValue(QString::fromStdString(this->project->getId()))),
                           });

        auto task = new TaskGeneric(this->service, this->projects, this->projects_mux, this->project, this->userId, json_message);

        task->setAutoDelete(true);

        // i don't want to block the main thread while saving, i will
        // release the resources once the saving is finished by calling this same function
        connect(task, SIGNAL(finished()), this, SLOT(disconnected()));

        QThreadPool::globalInstance()->start(task);

    }else {
        // release resources
        std::cout << "Client disconnected from: " << this->socketDescriptor << std::endl;
        this->socket->deleteLater();
        this->deleteLater();
    }
}

void Client::killClient() {

    // i don't want to save the project if one of the clients causes an error
    if(this->project)
        this->project.reset();

    this->socket->disconnectFromHost();
}

void Client::readyRead() {

    std::cout << "Message received from " << this->socket->socketDescriptor() << std::endl;

    QByteArray message;
    QJsonDocument document_message;

    do{
        if(this->socket->bytesAvailable() == 0)
            this->socket->waitForReadyRead();
        message.append(this->socket->readAll());
        document_message = QJsonDocument::fromJson(message);
    }while(document_message.isNull());


    QJsonObject json_message = document_message.object();

    std::cout << "Message: \n" << document_message.toJson().toStdString() << std::endl;

    auto task = new TaskGeneric(this->service, this->projects, this->projects_mux, this->project, this->userId, json_message);

    task->setAutoDelete(true);

    connect(task, SIGNAL(login(QString)), this, SLOT(login(QString)));
    connect(task, SIGNAL(returnResult(QByteArray)), this, SLOT(taskCompleted(QByteArray)));
    connect(task, SIGNAL(forwardMessage(QByteArray)), this, SLOT(forwardMessage(QByteArray)));
    connect(task, SIGNAL(killClient()), this, SLOT(killClient()));
    QThreadPool::globalInstance()->start(task);

    std::cout << "New task created for client at " << this->socket->socketDescriptor() << std::endl;
}

void Client::taskCompleted(const QByteArray& result) {

    std::cout << "Task completed for client at " << this->socket->socketDescriptor() << std::endl;

    // send response to the client
    this->socket->write(result);
    this->socket->waitForBytesWritten();
}

void Client::forwardMessage(const QByteArray& message){

    auto childrens = this->parent()->findChildren<Client(*)>();
    foreach(auto obj, childrens){
        auto c = qobject_cast<Client*>(obj);
        if(c->userId.toStdString() != "" && this->userId.toStdString() != c->userId.toStdString() && c->project && this->project->getId() == c->project->getId()){
            c->sendMessage(message);
        }
    }
}

void Client::sendMessage(const QByteArray& message){
    this->socket->write(message);
}

void Client::login(QString user){
    this->userId = user;
    std::cout << "Client Logged, user: " << this->userId.toStdString() << std::endl;
}

Client::~Client() {
    std::cout << "Client destroyed at: " << this->socketDescriptor << std::endl;
}
