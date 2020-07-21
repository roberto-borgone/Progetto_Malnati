//
// Created by rober on 13/07/2020.
//

#include "Client.h"

Client::Client(const Service& service, qintptr socketDescriptor, QObject* parent): QObject(parent), service(service), userId("") {

    // create the QSslSocket object
    this->socket = new QSslSocket(this);

    // since i'm not in the QTcpServer class anymore i can't use the pending connections
    // mechanism of QTcpServer so i have to link the connected signal of the socket directly
    // to see the connection happening
    connect(this->socket, SIGNAL(encrypted()), this, SLOT(connected()));
    connect(this->socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(this->socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    this->socket->setSocketDescriptor(socketDescriptor);

    // start a secure connection
    this->socket->setPrivateKey("certificates\\server.key", QSsl::Rsa); //make sure certificates folder is in your working dir
    this->socket->setLocalCertificate("certificates\\server.crt");
    this->socket->setPeerVerifyMode(QSslSocket::VerifyNone);
    this->socket->startServerEncryption();
}

void Client::connected() {
    std::cout << "New Client connected at: " << this->socket->socketDescriptor() << std::endl;
}

void Client::disconnected() {
    std::cout << "Client disconnected from: " << this->socket->socketDescriptor() << std::endl;
    this->socket->deleteLater();
    this->deleteLater();
}

void Client::readyRead() {

    std::cout << "Message received from " << this->socket->socketDescriptor() << std::endl;
    QJsonDocument document_message = QJsonDocument::fromJson(this->socket->readAll());
    QJsonObject json_message = document_message.object();

    std::cout << "Message: \n" << document_message.toJson().toStdString() << std::endl;

    auto task = new TaskGeneric(this->service, json_message);

    task->setAutoDelete(true);

    connect(task, SIGNAL(login(QString)), this, SLOT(login(QString)));
    connect(task, SIGNAL(returnResult(QByteArray)), this, SLOT(taskCompleted(QByteArray)));
    connect(task, SIGNAL(forwardMessage(QByteArray)), this, SLOT(forwardMessage(QByteArray)));
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
        std::cout << c->userId.toStdString() << std::endl;
        if(c->userId.toStdString() != "" && this->userId.toStdString() != c->userId.toStdString()){
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