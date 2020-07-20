//
// Created by Clemente Cetera on 29/03/2020.
//

#include "DB_functions.h"

DB_interface::DB_interface() {
    int result;
    char *statement;
    char *err_message = nullptr;

    //try to open (or create if not existing) database
    result = sqlite3_open("users_database.db", &db);
    if (result) {
        std::cout << "can't connect to DB" << std::endl;
        db = nullptr;
        return;
    } else {
        std::cout << "successfully connected to DB" << std::endl;
    }

    //create user table (if it doesn't exists)
    statement = "create table if not exists users("\
                "user text primary key not null,"\
                "pwd text not null);";
    result = sqlite3_exec(db, statement, nullptr, nullptr, &err_message);
    if (result != SQLITE_OK) {
        std::cout << "SQL error: " << err_message << std::endl;
        sqlite3_free(err_message);
    } else {
        std::cout << "table created successfully" << std::endl;
    }
}

DB_interface::~DB_interface() {
    if (db != nullptr) {
        sqlite3_close(db);
        std::cout << "DB closed!" << std::endl;
    }
}

int DB_interface::subscribe(const std::string &user, std::string pwd) const{
    int result;
    std::string statement;
    char *err_message = nullptr;

    //check if user is already in DB
    statement = std::string("SELECT user FROM users WHERE user = ?");

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, statement.c_str(), statement.size(), &stmt, nullptr) != SQLITE_OK) {
        std::cout << "some error occured in query the DB" << std::endl;
        return 2;
    }
    sqlite3_bind_text(stmt, 1, user.c_str(), user.size(), SQLITE_STATIC);
    int stat = sqlite3_step(stmt);
    if (stat != SQLITE_DONE) {
        std::cout << "already existing user" << std::endl;
        return 1;
    } else {
        std::ostringstream s_pwd;
        s_pwd << (int) std::hash<std::string>()(pwd);
        pwd = s_pwd.str();
        statement = "insert into users(user,pwd)"\
                "values('" + user + "'," + pwd + ")";
        result = sqlite3_exec(db, statement.c_str(), nullptr, nullptr, &err_message);
        if (result != SQLITE_OK) {
            std::cout << "SQL error: " << err_message << std::endl;
            sqlite3_free(err_message);
            return 2;
        } else {
            std::cout << "added user" << std::endl;
        }
    }
    return 0;
}

int DB_interface::log_in(const std::string &user, std::string pwd) const{
    int result;
    std::string statement;
    char *err_message = nullptr;

    //check if user is already in DB
    statement = std::string("SELECT pwd FROM users WHERE user = ?");

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, statement.c_str(), statement.size(), &stmt, nullptr) != SQLITE_OK) {
        std::cout << "some error occured in query the DB" << std::endl;
        return 2;
    }
    sqlite3_bind_text(stmt, 1, user.c_str(), user.size(), SQLITE_STATIC);
    int stat = sqlite3_step(stmt);
    if (stat == SQLITE_DONE) {
        std::cout << "wrong username or password" << std::endl;
        return 1;
    } else {
        std::ostringstream s_pwd;
        s_pwd << (int) std::hash<std::string>()(pwd);
        pwd = s_pwd.str();

        //get pwd from db
        std::string real_pwd((char *) sqlite3_column_text(stmt, 0));

        if (pwd == real_pwd) {
            std::cout << "log in success" << std::endl;
        } else{
            std::cout<<"wrong username or password"<<std::endl;
            return 1;
        }
    }
    return 0;
}
