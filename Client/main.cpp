#include <iostream>
#include <thread>
#include <QApplication>
#include <chrono>
#include <functional>
#include <QMessageBox>
#include "Gui.h"
#include "Network.h"
#include "DB_Client.h"
#include "PopUp.h"
#include "ProjectsPopup.h"


int main(int argc, char *argv[]) {


    QApplication a(argc,argv);

    //create Pop up
    auto no_prj_pop_up = new PopUp();
    //create Pop up for list of projects
    auto projects_pop_up = new ProjectsPopUp();

    auto g = new Gui(nullptr);
    Project *project = g->getCurrentProject();
    auto network = new Network(g->getCurrentProject(), g);
    auto db_client = new DB_Client();
   /*
    thread network([project](){
        Network network(project);
        network.receiveCommand();

    });
    */

   //for log in and socket
    QObject::connect(network, &Network::logged_in, g, &Gui::logged_in);
    QObject::connect(db_client, &DB_Client::move_socket, network, &Network::getSocket);
    QObject::connect(network, &Network::logged_in, db_client, &DB_Client::log_in_success);
    QObject::connect(network, &Network::wrong_log_in, db_client, &DB_Client::failed_log_in);
    QObject::connect(network, &Network::wrong_sub, db_client, &DB_Client::failed_subscribe);

    //for C/S communication (symbols)
    QObject::connect(g, &Gui::send_symbol, network, &Network::send_symbol);
    QObject::connect(project, &Project::remove_symbol, network, &Network::remove_symbol);
    QObject::connect(no_prj_pop_up, &PopUp::popUp_delete, g, &Gui::delete_in_Gui);

    //for C/S communication (projects)
    QObject::connect(g, &Gui::no_project, [&no_prj_pop_up](){no_prj_pop_up->exec();}); //pop up when no project is open
    QObject::connect(g, &Gui::request_for_projects, network, &Network::ask_projects);
    QObject::connect(g, &Gui::close_project, network, &Network::close_project);
    QObject::connect(network, &Network::list_available, projects_pop_up, &ProjectsPopUp::set_list);
    QObject::connect(network, &Network::project_to_choose, [&projects_pop_up](){projects_pop_up->exec();});
    QObject::connect(projects_pop_up, &ProjectsPopUp::send_prj_to_open, network, &Network::project_to_get);

    g->show();
    g->setVisible(false);
    db_client->show();
    a.exec();
   // network.join();
    return 0;
}