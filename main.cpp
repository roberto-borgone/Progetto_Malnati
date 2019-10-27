#include <iostream>
#include <thread>
#include <QApplication>
#include <chrono>
#include <functional>
#include "Gui.h"
#include "Network.h"


int main(int argc, char *argv[]) {


    QApplication a(argc,argv);

    Gui g(nullptr);
    Project *project = g.getCurrentProject();
   /*
    thread network([project](){
        Network network(project);
        network.receiveCommand();

    });
    */

    g.show();
    a.exec();
   // network.join();
    return 0;
}