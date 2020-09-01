//
// Created by Clemente Cetera on 09/05/2020.
//

#ifndef EDITORCOLLABORATIVO_DB_CLIENT_H
#define EDITORCOLLABORATIVO_DB_CLIENT_H
#include <iostream>
#include <QMainWindow>
#include <QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QMainWindow>
#include <string>
#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QtWidgets/QBoxLayout>
#include <QLineEdit>
#include <Qvector>
#include <QSslSocket>
#include <QTextEdit>
#include <QElapsedTimer>
#include <QJsonObject>
#include <QJsonDocument>
#include <QTcpSocket>


class DB_Client : public QMainWindow {
Q_OBJECT
    QWidget *widg = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout();
    QVector<QWidget *> layout_items;
    QString host_name;
    quint16 port;
    QTcpSocket sslClient;
    bool logged, connected; //connected servirà a capire se si è già connessi (tentivo precedente di login o subscribe fallito) oppure no

public:
    DB_Client() {
        widg->setLayout(layout);
        main_menu();
        host_name = "127.0.0.1";
        port = 1290;
        logged=false;
        connected = false;
    }


public slots:

    void main_menu();

    void log_in_Window();

    void subscribe_Window();

    void send_log_in();

    void send_subscribe();

    void log_in_success(const std::string& user);

    void failed_log_in();

    void failed_subscribe();

signals:

    void log_in();

    void move_socket(QTcpSocket& s);

};
#endif //EDITORCOLLABORATIVO_DB_CLIENT_H
