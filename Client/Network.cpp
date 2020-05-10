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