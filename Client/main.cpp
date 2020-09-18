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
#include "NewProjectPopUp.h"


int main(int argc, char *argv[]) {


    QApplication a(argc,argv);

    //create Pop up
    auto no_prj_pop_up = new PopUp();
    //create Pop up for list of projects
    //auto projects_pop_up = new ProjectsPopUp();
    //create Pop up for creating new project
    auto newPrj_pop_up = new NewProjectPopUp();

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
    QObject::connect(network,&Network::change_cursor,g,&Gui::change_cursor);
    QObject::connect(network,&Network::new_user,g,&Gui::add_user);

    //for C/S communication (projects)
    QObject::connect(no_prj_pop_up, &PopUp::popUp_delete, g, &Gui::delete_in_Gui);
    QObject::connect(g, &Gui::no_project, [&no_prj_pop_up](){no_prj_pop_up->exec();}); //pop up when no project is open

    //PopUp fow a new project
    QObject::connect(g, &Gui::new_project, [&network](){
        auto newPrj_pop_up = new NewProjectPopUp();
        QObject::connect(newPrj_pop_up, &NewProjectPopUp::create_project, network, &Network::new_project);
        newPrj_pop_up->exec();});

    QObject::connect(g, &Gui::request_for_projects, network, &Network::ask_projects);
    QObject::connect(g, &Gui::close_project, network, &Network::close_project);

    QObject::connect(network, &Network::list_available, [=](std::vector<std::string> list){
        auto projects_pop_up = new ProjectsPopUp(list);
        QObject::connect(projects_pop_up, &ProjectsPopUp::send_prj_to_open, network, &Network::project_to_get);
        projects_pop_up->exec();
    });

    //for C/S communication (cursor)
    QObject::connect(g, &Gui::time_out, network, &Network::send_cursor);

    g->show();
    g->setVisible(false);
    db_client->show();
    a.exec();
   // network.join();
    return 0;
}