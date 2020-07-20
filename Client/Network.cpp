//
// Created by davide miro on 19/10/2019.
//

#include "Network.h"

using namespace std;
enum opcode {
    log_in, subscribe, request_projects, open, create, close, remote_insert, remote_delete, cursor
};

Network::Network(Project *project) : QObject(nullptr) {
    project_ptr = shared_ptr<Project>(project);
    QObject::connect(this, &Network::insert, project, &Project::externalInsert, Qt::BlockingQueuedConnection);
    QObject::connect(this, &Network::erase, project, &Project::externalDelete, Qt::BlockingQueuedConnection);
    // connect(project,&Project::internalInsert,[](Symbol s)-> void {s.print();},Qt::BlockingQueuedConnection);
    //connect(project,&Project::internalDelete,[](string s)-> void {cout << s << endl;},Qt::BlockingQueuedConnection);

}

void Network::receiveCommand() {

    this_thread::sleep_for(chrono::seconds(3));

    Symbol symbol('d', "Arial", true, true, true, true, "#000000", vector<int>({-10}), "p1", "u1");
    emit insert(symbol);
    this_thread::sleep_for(chrono::seconds(3));
    emit erase(symbol.getId());


}

void Network::getSocket(QSslSocket &s) {
    std::cout << "qui dovrei prendermi il socket\n" << s.tr;
    socket_ptr = std::shared_ptr<QSslSocket>(&s);
    QObject::connect(socket_ptr.get(), &QSslSocket::readyRead, this, &Network::message_received);
}

void Network::send_symbol(Symbol s, int pos,  std::string prj, std::string usr) {
    //create JSON object of type log in
    auto json_message = QJsonObject({
                                            qMakePair(QString("opcode"), QJsonValue(6)),
                                            qMakePair(QString("symbol"), QJsonValue(s.toJson())),
                                            qMakePair(QString("position"), QJsonValue(pos)),
                                            qMakePair(QString("prjID"), QJsonValue(QString(prj.c_str()))),
                                            qMakePair(QString("user"), QJsonValue(QString(usr.c_str()))),

                                    });

    //print JSON object
    QJsonDocument Doc(json_message);
    QString message_to_send= QString::fromLatin1(Doc.toJson());
    std::cout << message_to_send.toStdString() << std::endl;

    //send JOSN obj
    socket_ptr->write(message_to_send.toLatin1());
}

void Network::message_received() {
    qDebug() << "nuovo messaggio ricevuto";
    //prendo tutto il qByteArray e lo trasformo in oggetto json
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(socket_ptr->readAll(), &parseError);

    if (parseError.error == QJsonParseError::NoError) {
        //possible error to handle
        return;
    }

    QJsonObject obj = doc.object();

    // accessing all object Keys
    for (const QString &key : obj.keys()) {
        qDebug() << obj[key];
    }

    int opcode = obj["opcode"].toInt();

    //gestione dei vari messaggi
    switch (opcode) {

        case log_in: {
            int result = obj["status"].toInt();
            if (result == 0) {
                std::string usr = obj["user"].toString().toStdString();
                emit logged_in(usr); //qui dovrò prendermi lo user dalla risposta del server
            } else if (result == 1) { emit wrong_log_in(); }

        }
            break;

        case subscribe: {
            int result = obj["status"].toInt();
            if (result == 0) {
                std::string usr = obj["user"].toString().toStdString();
                emit logged_in(usr); //qui dovrò prendermi lo user dalla risposta del server
            } else if (result == 1) { emit wrong_sub(); }
        }
            break;

        case request_projects: {
            //to do
        }
            break;

        case open: {
            //to do
        }
            break;

        case create: {
            //to do
        }
            break;

        case close: {
            //to do
        }
            break;

        case remote_insert: {
            //ricezione insrimento simbolo da remoto
            Symbol s(obj["symbol"].toObject());
            std::string user = obj["user"].toString().toStdString();
            int position = obj["position"].toInt();

            //passi per inserimento nel progetto
            //se i vettori del simbolo che mi arriva e quello che ho in poszione pos sono uguali vado a vedere id...
            //altrimenti vuol dire che il simbolo che mi arriva è stato generato dopo che era arrvato al client il mio simbolo
            //in quella posizione
            Symbol symbol_in_pos = project_ptr->get_symbol_in_pos(position);
            if(symbol_in_pos.getFrac()==s.getFrac()){
                //in questo caso bisogna controllare gli id
                std::hash<std::string> hash_funct;
                int local_id = hash_funct(symbol_in_pos.getId());
                int remote_id = hash_funct(symbol_in_pos.getId());
                if(remote_id<=local_id) {
                    //nel caso l'id del simbolo remoto sia minore di quello in progetto lo metto prima di quest'ultimo, altrimenti dopo
                    project_ptr->insert(position, s);
                }
                else{
                    project_ptr->insert(position+1,s);
                }
            }
            else{
                project_ptr->insert(position,s);
            }
        }
            break;

        case remote_delete: {
            //to do
        }
            break;

        case cursor: {
            //to do
        }
            break;


    }

}
