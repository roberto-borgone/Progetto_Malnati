//
// Created by Clemente Cetera on 08/04/2020.
//

#include "DB_server.h"

void DB_server::incomingConnection(qintptr socketDescriptor) {

    auto client = new Client(this->service, this->projects, this->projects_mux, socketDescriptor, this);
}
