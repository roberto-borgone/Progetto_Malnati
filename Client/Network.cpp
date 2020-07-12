//
// Created by davide miro on 19/10/2019.
//

#include "Network.h"
using namespace std;
Network::Network(Project *project):QObject(nullptr) {
    QObject::connect(this,&Network::insert,project,&Project::externalInsert,Qt::BlockingQueuedConnection);
    QObject::connect(this,&Network::erase,project,&Project::externalDelete,Qt::BlockingQueuedConnection);
   // connect(project,&Project::internalInsert,[](Symbol s)-> void {s.print();},Qt::BlockingQueuedConnection);
    //connect(project,&Project::internalDelete,[](string s)-> void {cout << s << endl;},Qt::BlockingQueuedConnection);


}

void Network::receiveCommand() {

    this_thread::sleep_for(chrono::seconds(3));

    Symbol symbol('d',"Arial",true,true,true,true,"#000000",vector<int>({-10}),"p1","u1");
    emit insert(symbol);
    this_thread::sleep_for(chrono::seconds(3));
    emit erase(symbol.getId());



}

void Network::getSocket(QSslSocket& s) {
    std::cout<<"qui dovrei prendermi il socket\n"<< s.tr;
    socket_ptr=std::shared_ptr<QSslSocket>(&s);
}

void Network::send_symbol(Symbol s) {
    std::string std_message(s.getId() + "_" + s.getChar() + "_log");
    QString message = QString::fromStdString(s.getId() + "_" + s.getChar() + "_log");
    socket_ptr->write(message.toUtf8());
    if (socket_ptr->waitForBytesWritten()) {
        qDebug() << "sent!";
        qDebug() << "wait for response";
        if (socket_ptr->waitForReadyRead()) {
            int result = socket_ptr->readAll().toInt();
            std::cout << result;
        } else {
            qDebug() << "no response";
            socket_ptr->close();
            return;
        }
    } else {
        //qDebug() << sslClient.errorString();
        qDebug() << socket_ptr->state();
        return;
    }
}
