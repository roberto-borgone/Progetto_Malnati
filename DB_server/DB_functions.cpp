//
// Created by Clemente Cetera on 29/03/2020.
//

#include "DB_functions.h"

DB_interface::DB_interface() {
    int result;
    char *statement;
    char *err_message = nullptr;

    //try to open (or create if not existing) database
    result = sqlite3_open("database.db", &db);
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

    //create project table (if it doesn't exists)
    statement = "create table if not exists projects("\
                "id text primary key not null,"\
                "doc text not null);";
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

int DB_interface::create_project(const std::string& id, QByteArray& doc) const{

    int result;
    std::string statement;
    char *err_message = nullptr;

    //check if project is already in DB
    statement = std::string("SELECT id FROM projects WHERE id = ?");

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, statement.c_str(), statement.size(), &stmt, nullptr) != SQLITE_OK) {
        std::cout << "some error occured in query the DB" << std::endl;
        return 2;
    }
    sqlite3_bind_text(stmt, 1, id.c_str(), id.size(), SQLITE_STATIC);
    int stat = sqlite3_step(stmt);
    if (stat != SQLITE_DONE) {
        std::cout << "already existing project" << std::endl;
        return 1;
    } else {
        statement = std::string("INSERT into projects(id, doc) values(?,?)");

        sqlite3_stmt *stmt;
        if (sqlite3_prepare_v2(db, statement.c_str(), statement.size(), &stmt, nullptr) != SQLITE_OK) {
            std::cout << "some error occured in query the DB" << std::endl;
            return 2;
        }
        sqlite3_bind_text(stmt, 1, id.c_str(), id.size(), SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, doc.toStdString().c_str(), doc.toStdString().size(), SQLITE_STATIC);
        result = sqlite3_step(stmt);
        if (result != SQLITE_DONE) {
            std::cout << "SQL error creating project" << std::endl;
            sqlite3_free(err_message);
            return 2;
        } else {
            std::cout << "created project" << std::endl;
        }
    }

    return 0;
}

QStringList DB_interface::get_projects() const{

    std::string statement;
    QStringList project_list;

    statement = std::string("SELECT id FROM projects");

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, statement.c_str(), statement.size(), &stmt, nullptr) != SQLITE_OK) {
        std::cout << "some error occured in query the DB" << std::endl;
        return project_list;
    }

    while (sqlite3_step(stmt) != SQLITE_DONE) {
        project_list.push_back(QString((char*)sqlite3_column_text(stmt, 0)));
    }

    return project_list;
}

QByteArray DB_interface::get_project(std::string& id) const{

    std::string statement;

    statement = std::string("SELECT doc FROM projects WHERE id = ?");

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, statement.c_str(), statement.size(), &stmt, nullptr) != SQLITE_OK) {
        std::cout << "some error occured in query the DB" << std::endl;
        return QByteArray("");
    }
    sqlite3_bind_text(stmt, 1, id.c_str(), id.size(), SQLITE_STATIC);

    int stat = sqlite3_step(stmt);

    if (stat != SQLITE_DONE) {
        return QByteArray((char*)sqlite3_column_text(stmt, 0));
    }

    return QByteArray("");
}

int DB_interface::update_project(const std::string& id, QByteArray doc) const{

    std::string statement;

    //check if project is already in DB
    statement = std::string("UPDATE projects SET doc = ? WHERE id = ?");

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, statement.c_str(), statement.size(), &stmt, nullptr) != SQLITE_OK) {
        std::cout << "some error occured in query the DB" << std::endl;
        return 2;
    }
    sqlite3_bind_text(stmt, 1, doc.toStdString().c_str(), doc.toStdString().size(), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, id.c_str(), id.size(), SQLITE_STATIC);

    int stat = sqlite3_step(stmt);
    if (stat != SQLITE_DONE) {
        std::cout << "error in update project" << std::endl;
        return 1;
    }

    return 0;
}

