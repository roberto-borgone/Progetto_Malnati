//
// Created by davide miro on 19/10/2019.
//

#include "Network.h"

using namespace std;
enum opcode {
    log_in,
    subscribe,
    request_projects,
    open,
    create,
    close,
    remote_insert,
    remote_delete,
    cursor,
    user_connecting,
    user_disconnecting,
    get_nickname
};

Network::Network(Project *project, Gui *gui) : QObject(nullptr) {
    project_ptr = shared_ptr<Project>(project);
    gui_ptr = std::shared_ptr<Gui>(gui);
    QObject::connect(this, &Network::insert, project, &Project::externalInsert, Qt::BlockingQueuedConnection);
    QObject::connect(this, &Network::erase, project, &Project::externalDelete, Qt::BlockingQueuedConnection);
    // connect(project,&Project::internalInsert,[](Symbol s)-> void {s.print();},Qt::BlockingQueuedConnection);
    //connect(project,&Project::internalDelete,[](string s)-> void {cout << s << endl;},Qt::BlockingQueuedConnection);

}

void Network::receiveCommand() {

    this_thread::sleep_for(chrono::seconds(3));

    Symbol symbol(QChar('d'), "Arial", true, true, true, true, "#000000", vector<int>({-10}), "p1", "u1",0,0);
    emit insert(symbol);
    this_thread::sleep_for(chrono::seconds(3));
    emit erase(symbol.getId());


}

void Network::getSocket(QTcpSocket &s) {

    //socket_ptr.reset();
    socket_ptr = std::shared_ptr<QTcpSocket>(&s);

    QObject::connect(socket_ptr.get(), &QSslSocket::readyRead, this, &Network::message_received);
}

void Network::send_symbol(std::vector<Symbol> symbols, std::string prj, std::string usr) {
    //create JSON object of type insert
    QJsonArray text;

    for (Symbol s : symbols) {
        text.push_back(s.toJson());
    }

    auto json_message = QJsonObject({
                                            qMakePair(QString("opcode"), QJsonValue(6)),
                                            qMakePair(QString("prjID"), QJsonValue(QString(prj.c_str()))),
                                            qMakePair(QString("user"), QJsonValue(QString(usr.c_str()))),
                                            qMakePair(QString("symbols"), text)
                                    });

    //print JSON object
    QJsonDocument Doc(json_message);
    QString message_to_send = QString::fromLatin1(Doc.toJson());
    std::cout << message_to_send.toStdString() << std::endl;

    //send JOSN obj
    int size = message_to_send.toLatin1().size();

    // send response to the client
    QByteArray message_to_send2 = message_to_send.toLatin1();
    message_to_send2.prepend((const char*) &size, sizeof(int));

    //send JOSN obj
    socket_ptr->write(message_to_send2);
    socket_ptr->flush();

    /**PROVA DI ARRIVO DI PROGETTI DA SCEGLIERE*
    std::vector<std::string> list;
    list.insert(list.end(), std::string("progetto1"));
    list.insert(list.end(), std::string("progetto2"));
    list.insert(list.end(), std::string("progetto3"));
    list.insert(list.end(), std::string("progetto4"));
    emit list_available(list);
    emit project_to_choose();*/
}

void Network::remove_symbol(std::vector<Symbol> s) {


    std::string prj = std::string(project_ptr->prjID);
    std::string usr = gui_ptr->getUser(); //qui si dovrà prendere lo user (quello ritornato dal server dopo il login e salvato)

    QJsonArray removed_symbols;

    for(Symbol sym : s){
        removed_symbols.push_back(sym.toJson());
    }

    //create JSON object of type remove
    auto json_message = QJsonObject({
                                            qMakePair(QString("opcode"), QJsonValue(7)),
                                            qMakePair(QString("symbols"), QJsonValue(removed_symbols)),
                                            qMakePair(QString("prjID"), QJsonValue(QString(prj.c_str()))),
                                            qMakePair(QString("user"), QJsonValue(QString(usr.c_str()))),

                                    });

    //print JSON object
    QJsonDocument Doc(json_message);
    QString message_to_send = QString::fromLatin1(Doc.toJson());
    std::cout << message_to_send.toStdString() << std::endl;

    //send JOSN obj
    int size = message_to_send.toLatin1().size();

    // send response to the client
    QByteArray message_to_send2 = message_to_send.toLatin1();
    message_to_send2.prepend((const char*) &size, sizeof(int));

    //send JOSN obj
    socket_ptr->write(message_to_send2);
    socket_ptr->flush();
}

void Network::message_received() {

    if(socket_ptr->bytesAvailable() == 0)
        return;


    //prendo tutto il qByteArray e lo trasformo in oggetto json
    //QJsonParseError parseError;
    //QJsonDocument doc = QJsonDocument::fromJson(socket_ptr->readAll(), &parseError);

    QJsonParseError parseError;
    QByteArray message;
    QJsonDocument doc;

    int maxsize;
    int size = 0;
    QByteArray read;

    socket_ptr->read((char*) &maxsize, sizeof(int));



    do{
        if(socket_ptr->bytesAvailable() == 0)
            socket_ptr->waitForReadyRead();
        read = socket_ptr->read(maxsize - size);
        size += read.size();
        message.append(read);
    }while(size < maxsize);

    doc = QJsonDocument::fromJson(message);

    /*
    if (parseError.error == QJsonParseError::NoError) {
        //possible error to handle
        return;
    }
     */

    QJsonObject obj = doc.object();

    // accessing all object Keys
    for (const QString &key : obj.keys()) {
        //qDebug() << obj[key];
    }

    int opcode = obj["opcode"].toInt();

    //gestione dei vari messaggi
    switch (opcode) {

        case log_in: {



            int result = obj["status"].toInt();

            if (result == 0) {
                std::string usr = obj["user"].toString().toStdString();

                //get profile image
                auto const encoded = obj["user_img"].toString().toLatin1();
                QImage img;
                img.loadFromData(QByteArray::fromBase64(encoded),
                                 "PNG"); //da capire perchè l'immagine non viene presa correttamente
                //per ora metto io l'immagine di default
                //img.load("../images/User_icon.png");
                if (img.isNull())
                    std::cout << "IMMAGINE NULLA!!!" << std::endl;
                gui_ptr->set_profile_image(img);

                //get nickname and change window title
                std::string nick = obj["nickname"].toString().toStdString();
                gui_ptr->set_nickname(nick);

                emit logged_in(usr); //qui dovrò prendermi lo user dalla risposta del server
            } else if (result == 1) { emit wrong_log_in(); }

        }
            break;

        case subscribe: {
            int result = obj["status"].toInt();

            if (result == 0) {
                std::string usr = obj["user"].toString().toStdString();

                //get profile image
                auto const encoded = obj["user_img"].toString().toLatin1();
                QImage img;
                img.loadFromData(QByteArray::fromBase64(encoded),
                                 "PNG"); //da capire perchè l'immagine non viene presa correttamente
                //per ora metto io l'immagine di default
                //img.load("../images/User_icon.png");
                if (img.isNull())
                    std::cout << "IMMAGINE NULLA!!!" << std::endl;
                gui_ptr->set_profile_image(img);

                //get nickname and change window title
                std::string nick = obj["nickname"].toString().toStdString();
                gui_ptr->set_nickname(nick);

                emit logged_in(usr); //qui dovrò prendermi lo user dalla risposta del server
            } else if (result == 1) { emit wrong_sub(); }
        }
            break;

        case request_projects: {
            std::vector<std::string> list;
            QJsonArray projects_list = obj["prjIDs"].toArray();
            for (auto el : projects_list) {
                list.insert(list.end(), el.toString().toStdString());
            }
            emit list_available(list);
        }
            break;

        case open: {
            int result = obj["status"].toInt();
            if(result==0) {
                project_ptr->delete_all();
                gui_ptr->delete_all_Gui();
                gui_ptr->initializeCounter();
                project_ptr->prjID_set = true;
                project_ptr->prjID = obj["prjID"].toString().toStdString();
                QJsonArray symbols = obj["text"].toArray();
                QJsonArray online_users = obj["user_names"].toArray();
                QJsonArray online_nicknames = obj["nicknames"].toArray();
                std::string delimiter = "/";
                int i = 0;

                for (auto el : symbols) {
                    Symbol s(el.toObject());
                    i = project_ptr->insert(s);
                    gui_ptr->insert_in_Gui(i, s);

                    //aggiungo user alla lista di user del progetto se non esistente
                    std::string id = s.getId();
                    std::string user = id.substr(0, id.find(delimiter));
                    if (users.find(user) == users.end()) {
                        users.insert(user);
                        //qui si potrebbe inviare un segnale in cui si manda l'utente e viene ritornato sia utente che nickname
                        if(!online_users.contains(QJsonValue(QString::fromStdString(user))))
                            get_nick(user);
                    }
                }

                //setta gli utenti come connessi nella GUI (e aggiungi nuovi utenti connessi ma che non hanno mai scritto sul progetto)
                for (i=0; i<online_users.size(); i++) {
                    std::string online_user = online_users[i].toString().toStdString();
                    std::string online_nick = online_nicknames[i].toString().toStdString();
                    if (users.find(online_user) == users.end()) {
                        users.insert(online_user);
                    }
                    gui_ptr->add_connected_user(online_user,online_nick);
                }

                //set new window title
                QString new_title(gui_ptr->get_nickname().c_str());
                new_title.append("//");
                new_title.append(project_ptr->prjID.c_str());
                gui_ptr->setWindowTitle(new_title);

                gui_ptr->start_timer();
            }else{
                emit wrong_open();
            }
        }
            break;

        case create: {
            int result = obj["status"].toInt();
            if(result==0) {
                project_ptr->delete_all();
                gui_ptr->delete_all_Gui();
                gui_ptr->initializeCounter();

                project_ptr->prjID_set = true;
                project_ptr->prjID = obj["prjID"].toString().toStdString();

                //set new window title
                QString new_title(gui_ptr->get_nickname().c_str());
                new_title.append("//");
                new_title.append(project_ptr->prjID.c_str());
                gui_ptr->setWindowTitle(new_title);

                gui_ptr->start_timer();
            }else{
                emit wrong_create();
            }
        }
            break;

        case close: {
            //NOTHING TO DO
        }
            break;

        case remote_insert: {
            //ricezione insrimento simbolo da remoto
            std::string user = obj["user"].toString().toStdString();
            QJsonArray symbols = obj["symbols"].toArray();

            if (users.find(user) == users.end()) {
                users.insert(user);
                get_nick(user);
            }

            //int position = obj["position"].toInt();

            //passi per inserimento nel progetto
            //se i vettori del simbolo che mi arriva e quello che ho in poszione pos sono uguali vado a vedere id...
            //altrimenti vuol dire che il simbolo che mi arriva è stato generato dopo che era arrvato al client il mio simbolo
            //in quella posizione
            /*
            if (position < project_ptr->text.size()) {
                Symbol symbol_in_pos = project_ptr->get_symbol_in_pos(position);
                //in questo caso bisogna controllare gli id di tutti i simboli successivi (nel caso di pi utenti che inseriscano contemporaneamente in stessa pos)
                std::hash<std::string> hash_funct;
                //ciclo fino a che ho vettori uguali e l'id remoto è minore di quelli locali con uguali vettori, quando esc metto nella posizione trovata

                //da provare altro while!!!!!!!!!!!!!!!!!


                while (symbol_in_pos.getFrac() == s.getFrac() &&
                       hash_funct(symbol_in_pos.getId()) > hash_funct(symbol_in_pos.getId())) {
                    position++;
                    symbol_in_pos = project_ptr->get_symbol_in_pos(position);
                }
            }
            */
            int i = 0;
            for (auto el : symbols) {
                Symbol s(el.toObject());
                i = project_ptr->insert(s);
                gui_ptr->insert_in_Gui(i, s);
            }


        }
            break;

        case remote_delete: {


            //ricezione cancellazione simbolo da remoto
            QJsonArray symbols =obj["symbols"].toArray();

            std::string user = obj["user"].toString().toStdString();
            if (users.find(user) == users.end()) {
                users.insert(user);
                get_nick(user);
            }

            for(auto s : symbols){
                int pos = project_ptr->eraseElement(Symbol(s.toObject())); //funzione che si occuperà di cancellare il simbolo nel progetto
                if (pos >= 0) { //cioè se il simbolo da eliminare non era già stato eliminato in precedenza
                    gui_ptr->delete_in_Gui(pos);
                }
            }

        }
            break;

        case cursor: {

            std::string user = obj["user"].toString().toStdString();
            if (users.find(user) == users.end()) {
                users.insert(user);
                get_nick(user);
            }
            int position = obj["position"].toInt(); /*PER DAVIDE: QUI SI HA DOVE SI TROVA IL CURSORE DI UN UTENTE DA MOSTRARE*/

            emit change_cursor(user, position);
        }
            break;

        case user_connecting: {
            std::string user = obj["user"].toString().toStdString();
            std::string nick_name = obj["nickname"].toString().toStdString();
            //setto l'utente indicato come online e lo aggiugo alla lista se non ancora presente
            if (users.find(user) == users.end()) {
                users.insert(user);
            }
            gui_ptr->add_connected_user(user, nick_name);
        }
            break;

        case user_disconnecting: {
            std::string user = obj["user"].toString().toStdString();
            //setto l'utente indicato come offline
            gui_ptr->user_disconnected(user);
        }
            break;

        case get_nickname: {
            std::string user = obj["user"].toString().toStdString();
            std::string nick_name = obj["nickname"].toString().toStdString();

            //questo segnale new_user va modificato aggiungendo il nickname ed emesso nello switch
            // case quando si riceve user e nickname
            emit new_user(user,nick_name);
        }
            break;

    }

    this->selfCall();
}

void Network::ask_projects(std::string usr) {
    //create JSON object of type request_projects
    auto json_message = QJsonObject({
                                            qMakePair(QString("opcode"), QJsonValue(2)),
                                            qMakePair(QString("user"),
                                                      QJsonValue(QJsonValue(QString(gui_ptr->getUser().c_str())))),

                                    });

    //print JSON object
    QJsonDocument Doc(json_message);
    QString message_to_send = QString::fromLatin1(Doc.toJson());
    std::cout << message_to_send.toStdString() << std::endl;

    //send JOSN obj
    int size = message_to_send.toLatin1().size();

    // send response to the client
    QByteArray message_to_send2 = message_to_send.toLatin1();
    message_to_send2.prepend((const char*) &size, sizeof(int));

    //send JOSN obj
    socket_ptr->write(message_to_send2);
    socket_ptr->flush();
}

void Network::close_project(std::string prj) {
//create JSON object of type close_project
    auto json_message = QJsonObject({
                                            qMakePair(QString("opcode"), QJsonValue(5)),
                                            qMakePair(QString("prjID"), QJsonValue(QString(prj.c_str()))),
                                            qMakePair(QString("user"), QJsonValue(QString(gui_ptr->getUser().c_str())))

                                    });

    //print JSON object
    QJsonDocument Doc(json_message);
    QString message_to_send = QString::fromLatin1(Doc.toJson());
    std::cout << message_to_send.toStdString() << std::endl;

    //send JOSN obj
    int size = message_to_send.toLatin1().size();

    // send response to the client
    QByteArray message_to_send2 = message_to_send.toLatin1();
    message_to_send2.prepend((const char*) &size, sizeof(int));

    //send JOSN obj
    socket_ptr->write(message_to_send2);
    socket_ptr->flush();

    //delete project and stop timer for cursor
    project_ptr->prjID_set = false;
    project_ptr->delete_all();
    gui_ptr->delete_all_Gui();
    gui_ptr->stop_timer();

    //delete project from window title
    gui_ptr->setWindowTitle(QString(gui_ptr->get_nickname().c_str()));

    //delete list of users
    users.clear();
    users.insert(users.end(), gui_ptr->getUser());

}

void Network::project_to_get(std::string prj_name) {
    //create JSON object of type project_to_get
    auto json_message = QJsonObject({
                                            qMakePair(QString("opcode"), QJsonValue(3)),
                                            qMakePair(QString("prjID"), QJsonValue(QString(prj_name.c_str()))),
                                            qMakePair(QString("user"), QJsonValue(QString(gui_ptr->getUser().c_str()))),
                                    });

    //print JSON object
    QJsonDocument Doc(json_message);
    QString message_to_send = QString::fromLatin1(Doc.toJson());
    std::cout << message_to_send.toStdString() << std::endl;

    //send JOSN obj
    int size = message_to_send.toLatin1().size();

    // send response to the client
    QByteArray message_to_send2 = message_to_send.toLatin1();
    message_to_send2.prepend((const char*) &size, sizeof(int));

    //send JOSN obj
    socket_ptr->write(message_to_send2);
    socket_ptr->flush();
}

void Network::new_project(std::string prjID) {
    //create JSON object of type new_project
    auto json_message = QJsonObject({
                                            qMakePair(QString("opcode"), QJsonValue(4)),
                                            qMakePair(QString("prjID"), QJsonValue(QString(prjID.c_str()))),
                                            qMakePair(QString("user"), QJsonValue(QString(gui_ptr->getUser().c_str())))
                                    });

    //print JSON object
    QJsonDocument Doc(json_message);
    QString message_to_send = QString::fromLatin1(Doc.toJson());
    std::cout << message_to_send.toStdString() << std::endl;

    //send JOSN obj
    int size = message_to_send.toLatin1().size();

    // send response to the client
    QByteArray message_to_send2 = message_to_send.toLatin1();
    message_to_send2.prepend((const char*) &size, sizeof(int));

    //send JOSN obj
    socket_ptr->write(message_to_send2);
    socket_ptr->flush();
}

void Network::send_cursor(int position) {
    //create JSON object of type project_to_get
    auto json_message = QJsonObject({
                                            qMakePair(QString("opcode"), QJsonValue(8)),
                                            qMakePair(QString("prjID"),
                                                      QJsonValue(QString(project_ptr->prjID.c_str()))),
                                            qMakePair(QString("user"), QJsonValue(QString(gui_ptr->getUser().c_str()))),
                                            qMakePair(QString("position"), QJsonValue(position))
                                    });

    //print JSON object
    QJsonDocument Doc(json_message);
    QString message_to_send = QString::fromLatin1(Doc.toJson());
    std::cout << message_to_send.toStdString() << std::endl;

    //send JOSN obj
    int size = message_to_send.toLatin1().size();

    // send response to the client
    QByteArray message_to_send2 = message_to_send.toLatin1();
    message_to_send2.prepend((const char*) &size, sizeof(int));

    //send JOSN obj
    socket_ptr->write(message_to_send2);
    socket_ptr->flush();
}

void Network::add_my_user(std::string user) {
    users.insert(user);
}

void Network::disconnect() {
    socket_ptr->disconnectFromHost(); //da controllare
    socket_ptr->reset();
}

void Network::clear_users(bool also_user) {
    users.clear();
    if (!also_user) {
        users.insert(users.end(), gui_ptr->getUser());
    }
}

void Network::selfCall(){
    socket_ptr->readyRead();
}

void Network::send_image(QImage img) {

    //create JSON object of type project_to_get
    auto json_message = QJsonObject({
                                            qMakePair(QString("opcode"), QJsonValue(12)),
                                            qMakePair(QString("user"), QJsonValue(QString(gui_ptr->getUser().c_str()))),
                                    });

    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);
    img.save(&buffer, "PNG");
    auto const encoded = buffer.data().toBase64();
    json_message.insert("user_img", {QLatin1String(encoded)});

    //print JSON object
    QJsonDocument Doc(json_message);
    QString message_to_send = QString::fromLatin1(Doc.toJson());
    std::cout << message_to_send.toStdString() << std::endl;

    //send JOSN obj
    int size = message_to_send.toLatin1().size();

    // send response to the client
    QByteArray message_to_send2 = message_to_send.toLatin1();
    message_to_send2.prepend((const char*) &size, sizeof(int));

    //send JOSN obj
    socket_ptr->write(message_to_send2);
    socket_ptr->flush();


}

void Network::send_nickname(std::string nick) {
    //create JSON object of type project_to_get
    auto json_message = QJsonObject({
                                            qMakePair(QString("opcode"), QJsonValue(13)),
                                            qMakePair(QString("user"), QJsonValue(QString(gui_ptr->getUser().c_str()))),
                                            qMakePair(QString("nickname"), QJsonValue(QString(nick.c_str())))
                                    });

    //print JSON object
    QJsonDocument Doc(json_message);
    QString message_to_send = QString::fromLatin1(Doc.toJson());
    std::cout << message_to_send.toStdString() << std::endl;

    //send JOSN obj
    int size = message_to_send.toLatin1().size();

    // send response to the client
    QByteArray message_to_send2 = message_to_send.toLatin1();
    message_to_send2.prepend((const char*) &size, sizeof(int));

    //send JOSN obj
    socket_ptr->write(message_to_send2);
    socket_ptr->flush();
}

void Network::get_nick(std::string user) {
    //create JSON object of type project_to_get
    auto json_message = QJsonObject({
                                            qMakePair(QString("opcode"), QJsonValue(11)),
                                            qMakePair(QString("user"), QJsonValue(QString(gui_ptr->getUser().c_str()))),
                                            qMakePair(QString("user_nick"), QJsonValue(QString(user.c_str()))),
                                            qMakePair(QString("prjID"), QString(project_ptr->prjID.c_str()))
                                    });

    //print JSON object
    QJsonDocument Doc(json_message);
    QString message_to_send = QString::fromLatin1(Doc.toJson());
    std::cout << message_to_send.toStdString() << std::endl;

    //send JOSN obj
    int size = message_to_send.toLatin1().size();

    // send response to the client
    QByteArray message_to_send2 = message_to_send.toLatin1();
    message_to_send2.prepend((const char*) &size, sizeof(int));

    //send JOSN obj
    socket_ptr->write(message_to_send2);
    socket_ptr->flush();
}

