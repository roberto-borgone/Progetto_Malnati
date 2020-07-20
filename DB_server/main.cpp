#include <iostream>
#include "DB_functions.h"
#include "DB_server.h"

int main(int argc, char**argv) {
    //std::cout << "Hello, World!" << std::endl;
    QApplication app(argc, argv);  // inizializzazione // del framework
    //DB_interface db;
    DB_server server;
    //db.subscribe("Antonella5","ciao");
    //db.log_in("Antonella5", "ciao");
    app.exec();
    return 0;
}
