//
// Created by davide miro on 2019-09-27.
//

#ifndef EDITORCOLLABORATIVO_GUI_H
#define EDITORCOLLABORATIVO_GUI_H

#include <vector>
#include <string>
#include <iostream>
#include <random>
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QComboBox>
#include <QStringList>
#include <QPushButton>
#include <QSpinBox>
#include <QColorDialog>
#include <QColor>
#include <QTextEdit>
#include <QFileDialog>
#include <QFontDatabase>
#include <QFont>
#include <QTextDocument>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QToolButton>
#include <QStyle>
#include <QStringList>
#include <QPushButton>
#include <QSpinBox>
#include <QColorDialog>
#include <QColor>
#include <QTextEdit>
#include <QFileDialog>
#include <QFontDatabase>
#include <QFont>
#include <QTextDocument>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QToolButton>
#include <QStyle>
#include <QTimer>
#include <QPdfWriter>
#include <QListWidgetItem>
#include "Profile.h"
#include "SendEmailPopup.h"
#include "Project.h"

class Gui : public QMainWindow{
    Q_OBJECT
    QMenuBar* initMenuBar();
    QToolBar* initToolBar();
    QTextEdit *textEdit;
    QTimer* cursor_timer;
    QListWidget* list;
    QHBoxLayout* lh;
    QWidget *centralWidget;
    map<string,vector<int>> user_color;
    map<string,bool> connected_users;
    map<string,QListWidgetItem*> user_items;
    string user;
    bool show_collaborators;
    QImage profile_image;
    SendEmailPopup *mailpopup;




public:
    Gui(QWidget *parent);
    Project* getCurrentProject();
    void setFont(QString text);
    void bold();
    void italic();
    void underline();
    void overline();
    void setTextSize(int size);
    void undo();
    void redo();
    void cut();
    void paste();
    void selectAll();
    void deleteT();
    void setTextColor(const QColor& c);
    void insert_in_Gui(int pos, Symbol s);
    void delete_in_Gui(int pos);
    void delete_all_Gui();
    void start_timer();
    void stop_timer();
    void markTextUser(map<string,vector<int>> colors);
    std::string getUser();
    void clear_users_list(bool also_user);
    void set_profile_image(const QImage& img);
    void closeProject();
    void add_connected_user(string usr);
    void user_disconnected(string usr);

public slots:
    void logged_in(const std::string& user);
    void add_user(std::string user);
    void change_cursor(std::string user, int pos);


signals:
    void send_symbol(Symbol s, int pos, std::string prj, std::string usr);
    void no_project();
    void request_for_projects(std::string usr);
    void close_project(std::string prj);
    void new_project();
    void time_out(int position);
    void add_my_user(std::string user);
    void disconnect_socket();
    void disconnected();
    void clear_users(bool also_user);
    void sendMail(std::string prjID,std::string sender);
    void useInvite();
    void change_image(QImage img);
};



#endif //EDITORCOLLABORATIVO_GUI_H
