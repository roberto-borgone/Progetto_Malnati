//
// Created by Clemente Cetera on 09/05/2020.
//

#include "DB_Client.h"
#include <QSslConfiguration>
#include <QStandardPaths>
#include <QSslCipher>
#include <QSslKey>

void DB_Client::log_in_Window() {

    //change layout
    QWidget *new_widget = new QWidget;

    //create text field for username
    QLineEdit *user = new QLineEdit();
    user->setPlaceholderText("username");
    user->setObjectName("username");

    //create text field for password
    QLineEdit *pwd = new QLineEdit();
    pwd->setPlaceholderText("password");
    pwd->setObjectName("password");
    pwd->setEchoMode(QLineEdit::Password);


    QPushButton *submit = new QPushButton("log in");
    QPushButton *back = new QPushButton("come back");

    delete widg;
    //create new widget and layout
    widg = new QWidget;
    layout = new QVBoxLayout;

    layout_items.clear();

    layout_items.append(user);
    layout_items.append(pwd);
    layout_items.append(submit);
    layout_items.append(back);

    for (auto t : layout_items) {
        layout->addWidget(t);
    }

    widg->setLayout(layout);
    this->setCentralWidget(widg);

    //pass to function send when submitted
    QObject::connect(submit, &QPushButton::clicked, this, &DB_Client::send_log_in);
    //pass to function main_menu when coming back
    QObject::connect(back, &QPushButton::clicked, this, &DB_Client::main_menu);
}

void DB_Client::subscribe_Window() {

    QWidget *new_widget = new QWidget;

    //create text field for username
    QLineEdit *user = new QLineEdit();
    user->setPlaceholderText("username");
    user->setObjectName("username");

    //create text field for password
    QLineEdit *pwd = new QLineEdit();
    pwd->setPlaceholderText("password");
    pwd->setObjectName("password");
    pwd->setEchoMode(QLineEdit::Password);

    QPushButton *submit = new QPushButton("subscribe");
    QPushButton *back = new QPushButton("come back");

    delete widg;
    //create new widget and layout
    widg = new QWidget;
    layout = new QVBoxLayout;

    layout_items.clear();

    layout_items.append(user);
    layout_items.append(pwd);
    layout_items.append(submit);
    layout_items.append(back);

    for (auto t : layout_items) {
        layout->addWidget(t);
    }

    widg->setLayout(layout);
    this->setCentralWidget(widg);

    //pass to function send when submitted
    QObject::connect(submit, &QPushButton::clicked, this, &DB_Client::send_subscribe);
    //pass to function main_menu when coming back
    QObject::connect(back, &QPushButton::clicked, this, &DB_Client::main_menu);
}

void DB_Client::send_log_in() {
    QString user = widg->findChild<QLineEdit *>("username")->text();
    QString pwd = widg->findChild<QLineEdit *>("password")->text();

    std::cout << "username: " << user.toStdString() << std::endl;
    std::cout << "password: " << pwd.toStdString() << std::endl;
    if (!connected) {
        std::cout << QSslSocket::supportsSsl() << std::endl;
        //ignore errors deriving from autosigned certficate
        QList<QSslCertificate> cert = QSslCertificate::fromPath(
                QLatin1String("certificates/server.crt")); //make sure certificates folder is in your working dir
        QSslError error(QSslError::SelfSignedCertificate, cert.at(0));
        QSslError name_error(QSslError::HostNameMismatch, cert.at(0));
        QList<QSslError> expectedSslErrors;
        expectedSslErrors.append(error);
        expectedSslErrors.append(name_error);
        //sslClient.ignoreSslErrors(expectedSslErrors);
        sslClient.connectToHost(host_name, port);
        //sslClient.connectToHostEncrypted("gmail.com", 443);

    // send data and wait for response
    if (sslClient.waitForConnected(3000)) {
        std::cout << "connession established!!" << std::endl;
        emit move_socket(sslClient); //metto socket creato in network
        std::string std_message(user.toStdString() + "_" + pwd.toStdString() + "_log");
        QString message = QString::fromStdString(user.toStdString() + "_" + pwd.toStdString() + "_log");

        //create JSON object of type log in
        auto json_message = QJsonObject({
                                                qMakePair(QString("opcode"), QJsonValue(0)),
                                                qMakePair(QString("user"), QJsonValue(user)),
                                                qMakePair(QString("password"), QJsonValue(pwd)),

                                        });

        //print JSON object
        QJsonDocument Doc(json_message);
        QString message_to_send= QString::fromLatin1(Doc.toJson());
        std::cout << message_to_send.toStdString() << std::endl;

        //send JOSN obj
        sslClient.write(message_to_send.toLatin1());
        //sslClient.write(message.toStdString().c_str());

        if (sslClient.waitForBytesWritten()) {
            qDebug() << "sent!";
            qDebug() << "wait for response";
            /*
            if (sslClient.waitForReadyRead()) {
                int result = sslClient.readAll().toInt();
                std::cout << result;
                if (result == 0) {
                    //sslClient.close();
                    logged = true;
                    emit logged_in(user.toStdString());
                } else {
                    if (widg->findChild<QTextEdit *>("wrong_credentials") == nullptr) {
                        QTextEdit *text = new QTextEdit();
                        text->viewport()->setAutoFillBackground(false);
                        text->setText("wrong username or password");
                        text->setObjectName("wrong_credentials");
                        layout->addWidget(text);
                        widg->setLayout(layout);
                        this->setCentralWidget(widg);
                    }
                    sslClient.close();
                    return;
                }
            } else {
                qDebug() << "no response";
                sslClient.close();
                return;
            }*/
        } else {
            //qDebug() << sslClient.errorString();
            qDebug() << sslClient.state();
            return;
        }
    } else {
        std::cout << "failed to establish connection!!!" << std::endl;
        qDebug() << sslClient.errorString();
        return;
    }
    }else{
        std::string std_message(user.toStdString() + "_" + pwd.toStdString() + "_log");
        QString message = QString::fromStdString(user.toStdString() + "_" + pwd.toStdString() + "_log");

        //create JSON object of type log in
        auto json_message = QJsonObject({
                                                qMakePair(QString("opcode"), QJsonValue(0)),
                                                qMakePair(QString("user"), QJsonValue(user)),
                                                qMakePair(QString("password"), QJsonValue(pwd)),

                                        });

        //print JSON object
        QJsonDocument Doc(json_message);
        QString message_to_send= QString::fromLatin1(Doc.toJson());
        std::cout << message_to_send.toStdString() << std::endl;

        //send JOSN obj
        sslClient.write(message_to_send.toLatin1());
        //sslClient.write(message.toStdString().c_str());

        if (sslClient.waitForBytesWritten()) {
            qDebug() << "sent!";
            qDebug() << "wait for response";

        } else {
            //qDebug() << sslClient.errorString();
            qDebug() << sslClient.state();
            return;
        }
    }
}

void DB_Client::send_subscribe() {
    QString user = widg->findChild<QLineEdit *>("username")->text();
    QString pwd = widg->findChild<QLineEdit *>("password")->text();

    std::cout << "username: " << user.toStdString() << std::endl;
    std::cout << "password: " << pwd.toStdString() << std::endl;
    if (!connected) {
         //std::cout << QSslSocket::supportsSsl() << std::endl;
        //ignore errors deriving from autosigned certficate
        /*
        QList<QSslCertificate> cert = QSslCertificate::fromPath(
                QLatin1String("/Users/davidemiro/Desktop/Progetto_Malnati-master/Client/certificates/project.pem")); //make sure certificates folder is in your working dir

        QSslError error(QSslError::SelfSignedCertificate, cert.at(0));
        QSslError name_error(QSslError::HostNameMismatch, cert.at(0));
        QList<QSslError> expectedSslErrors;
        expectedSslErrors.append(error);
        expectedSslErrors.append(name_error);
        sslClient.ignoreSslErrors(expectedSslErrors);
        */
        /*
        QList<QSslCertificate> cert = QSslCertificate::fromPath(
                QLatin1String("/Users/davidemiro/Desktop/Progetto_Malnati-master/Client/certificates/myCA.pem"));
        sslClient.addCaCertificates(cert);
        */

        sslClient.connectToHost(host_name, port);
        //sslClient.connectToHostEncrypted("gmail.com", 443);

        // send data and wait for response
        if (sslClient.waitForConnected(3000)) {
            std::cout << "connession established!!" << std::endl;
            emit move_socket(sslClient); //metto socket creato in network
            std::string std_message(user.toStdString() + "_" + pwd.toStdString() + "_sub");
            QString message = QString::fromStdString(user.toStdString() + "_" + pwd.toStdString() + "_sub");

            //create JSON object of type log in
            auto json_message = QJsonObject({
                                                    qMakePair(QString("opcode"), QJsonValue(1)),
                                                    qMakePair(QString("user"), QJsonValue(user)),
                                                    qMakePair(QString("password"), QJsonValue(pwd)),

                                            });

            //print JSON object
            QJsonDocument Doc(json_message);
            QString message_to_send= QString::fromLatin1(Doc.toJson());
            std::cout << message_to_send.toStdString() << std::endl;

            //send JOSN obj
            sslClient.write(message_to_send.toLatin1());
            //sslClient.write(message.toStdString().c_str());

            if (sslClient.waitForBytesWritten()) {
                qDebug() << "sent!";
                qDebug() << "wait for response";
                /*
                if (sslClient.waitForReadyRead()) {
                    int result = sslClient.readAll().toInt();
                    std::cout << result;
                    if (result == 0) {
                        //sslClient.close();
                        logged = true;
                        emit logged_in(user.toStdString());
                    } else {
                        if (widg->findChild<QTextEdit *>("wrong_credentials") == nullptr) {
                            QTextEdit *text = new QTextEdit();
                            text->viewport()->setAutoFillBackground(false);
                            text->setText("wrong username or password");
                            text->setObjectName("wrong_credentials");
                            layout->addWidget(text);
                            widg->setLayout(layout);
                            this->setCentralWidget(widg);
                        }
                        sslClient.close();
                        return;
                    }
                } else {
                    qDebug() << "no response";
                    sslClient.close();
                    return;
                }*/
            } else {
                //qDebug() << sslClient.errorString();
                qDebug() << sslClient.state();
                return;
            }
        } else {
            std::cout << "failed to establish connection!!!" << std::endl;
            qDebug() << sslClient.errorString();
            return;
        }
    }else{
        std::string std_message(user.toStdString() + "_" + pwd.toStdString() + "_sub");
        QString message = QString::fromStdString(user.toStdString() + "_" + pwd.toStdString() + "_sub");

        //create JSON object of type log in
        auto json_message = QJsonObject({
                                                qMakePair(QString("opcode"), QJsonValue(1)),
                                                qMakePair(QString("user"), QJsonValue(user)),
                                                qMakePair(QString("password"), QJsonValue(pwd)),

                                        });

        //print JSON object
        QJsonDocument Doc(json_message);
        QString message_to_send= QString::fromLatin1(Doc.toJson());
        std::cout << message_to_send.toStdString() << std::endl;

        //send JOSN obj
        sslClient.write(message_to_send.toLatin1());
        //sslClient.write(message.toStdString().c_str());

        if (sslClient.waitForBytesWritten()) {
            qDebug() << "sent!";
            qDebug() << "wait for response";

        } else {
            //qDebug() << sslClient.errorString();
            qDebug() << sslClient.state();
            return;
        }
    }
}

void DB_Client::log_in_success(const std::string &user) {
    logged = true;
//change layout
    QWidget *new_widget = new QWidget;

    QTextEdit *text = new QTextEdit();
    text->setText(QString::fromStdString("logged in as:" + user));
    text->viewport()->setAutoFillBackground(false);
    text->setReadOnly(true);
    text->fontItalic();
    text->frameWidth();

    delete widg;
    //create new widget and layout
    widg = new QWidget;
    layout = new QVBoxLayout;

    layout_items.clear();

    layout_items.append(text);

    for (auto t : layout_items) {
        layout->addWidget(t);
    }

    widg->setLayout(layout);
    this->setCentralWidget(widg);

    this->setVisible(false);
}

void DB_Client::main_menu() {
    //layout set up
    QPushButton *log_in = new QPushButton("Log in");
    QPushButton *subscribe = new QPushButton("subscribe");

    delete widg;
    //create new widget and layout
    widg = new QWidget;
    layout = new QVBoxLayout;
    layout_items.clear();
    layout_items.append(log_in);
    layout_items.append(subscribe);

    //add elements to layout
    for (auto t : layout_items) {
        layout->addWidget(t);
    }

    widg->setLayout(layout);
    this->setCentralWidget(widg);

    QObject::connect(log_in, &QPushButton::clicked, this, &DB_Client::log_in_Window);
    QObject::connect(subscribe, &QPushButton::clicked, this, &DB_Client::subscribe_Window);
}

void DB_Client::failed_log_in() {
    connected = true;
    if (widg->findChild<QTextEdit *>("wrong_credentials") == nullptr) {
        QTextEdit *text = new QTextEdit();
        text->viewport()->setAutoFillBackground(false);
        text->setText("wrong username or password");
        text->setObjectName("wrong_credentials");
        layout->addWidget(text);
        widg->setLayout(layout);
        this->setCentralWidget(widg);
    }
}

void DB_Client::failed_subscribe() {
    connected = true;
    if (widg->findChild<QTextEdit *>("existing_user") == nullptr) {
        QTextEdit *text = new QTextEdit();
        text->viewport()->setAutoFillBackground(false);
        text->setText("Already existing user");
        text->setObjectName("existing_user");
        layout->addWidget(text);
        widg->setLayout(layout);
        this->setCentralWidget(widg);
    }

}

