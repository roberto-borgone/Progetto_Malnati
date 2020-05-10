//
// Created by Clemente Cetera on 08/04/2020.
//

#include "DB_server.h"

void DB_server::new_connection(){
    QSslSocket* client_socket;
    client_socket= dynamic_cast<QSslSocket *>(nextPendingConnection());
    connect(client_socket, &QTcpSocket::readyRead, this, &DB_server::reply);
    std::cout<<"new connection here!"<<std::endl;
}

void DB_server::incomingConnection(qintptr socketDescriptor) {

    std::cout<<"incoming"<<std::endl;
    QSslSocket *sslSocket = new QSslSocket(this);
    sslSocket->setSocketDescriptor(socketDescriptor);

    sslSocket->setPrivateKey("certificates\\server.key", QSsl::Rsa); //make sure certificates folder is in your working dir
    sslSocket->setLocalCertificate("certificates\\server.crt");

    sslSocket->startServerEncryption();
    this->addPendingConnection(sslSocket);
}

void DB_server::reply() {
    QSslSocket* clientSocket = qobject_cast<QSslSocket*>(sender());
    std::cout<<"new connection here!"<<std::endl;
    QElapsedTimer timer;

    //need to user timer... waitForReadyRead function fails in windows
    timer.start();
    //wait until some byte s available or timeout expires
    while(!clientSocket->bytesAvailable() && timer.elapsed()<10000);


    if(clientSocket->bytesAvailable()) {
        std::string received_message(clientSocket->readAll().data());
        std::string tmp;
        std::vector <std::string> strings;
        std::string user;
        std::string pwd;
        std::string mode;

        std::cout << received_message<<std::endl;

        //split received message to get information
        std::istringstream stream_message(received_message);
        while (std::getline(stream_message, tmp, '_')) {
            strings.push_back(tmp);
        }
        user = strings[0];
        pwd = strings[1];
        mode = strings[2];

        if (mode == "log") {
            //try to log in
            std::cout<<"here";
            int result = DB.log_in(user, pwd);
            QByteArray result_message;
            result_message.setNum(result);
            std::cout<<result<<std::endl;
            clientSocket->write(result_message);
            clientSocket->waitForBytesWritten();
        }

        if (mode == "sub") {
            //try to log in
            std::cout<<"here";
            int result = DB.subscribe(user, pwd);
            QByteArray result_message;
            result_message.setNum(result);
            std::cout<<result<<std::endl;
            clientSocket->write(result_message);
            clientSocket->waitForBytesWritten();
        }
    }else{
        qDebug() << "timeout expired!";
        qDebug() << clientSocket->bytesAvailable();
        QByteArray result_message;
        result_message.setNum(1);
        clientSocket->write(result_message);
    }

    //clientSocket->close();
}
