//
// Created by davide miro on 09/09/2020.
//

#include "Profile.h"
#include <iostream>
#include <QFileDialog>
#include <QBuffer>

Profile::Profile(QImage image):QDialog(){
    setWindowTitle("Profile information");
    setWindowFlags(Qt::Dialog);

    QGridLayout *grid = new QGridLayout(this);
    QLabel *icon = new QLabel(this);
    QPixmap p = QPixmap::fromImage(image,Qt::AutoColor);
    icon->setPixmap(p.scaled(100,100));

    grid->addWidget(icon,0,0);
    QWidget* w = new QWidget(this);

    QPushButton *changeIcon = new QPushButton("Change image",this);
    grid->addWidget(changeIcon,0,1);



    connect(changeIcon,&QPushButton::clicked,[=](){
        QString fileName = QFileDialog::getOpenFileName((QWidget *) 0, "Select the image", QString(), "*.png");
        QImage new_profile_image(fileName);
        QPixmap p = QPixmap::fromImage(new_profile_image,Qt::AutoColor);
        icon->setPixmap(p.scaled(100,100));

        emit new_image(new_profile_image);
    });



    grid->addWidget(new QLabel("Nickname : "),1,0);

    QPushButton* changeNickname = new QPushButton(w);
    grid->addWidget(changeNickname,1,1);
    changeNickname->setText("Change Nickname");

    QLineEdit* editext = new QLineEdit(w);
    editext->setObjectName(QString("my_nickname"));
    editext->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));
    grid->addWidget(editext,2,0);

    //change nickname
    QObject::connect(changeNickname, &QPushButton::clicked, [this]() {
        emit new_nickname(this->findChild<QLineEdit*>(QString("my_nickname"))->text());
        this->close();
    });

    QPushButton* logout = new QPushButton(w);
    logout->setText("Logout");
    QObject::connect(logout, &QPushButton::clicked, [this]() {
        emit log_out();
        this->close();
    });
    grid->addWidget(logout,2,1);



    setLayout(grid);
}