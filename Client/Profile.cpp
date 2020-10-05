//
// Created by davide miro on 09/09/2020.
//

#include "Profile.h"
#include <iostream>
#include <QFileDialog>
#include <QBuffer>

Profile::Profile():QDialog(){
    setWindowTitle("Profile information");
    setWindowFlags(Qt::Dialog);

    QGridLayout *grid = new QGridLayout(this);

    QPixmap p("images/User_icon.png");
    QLabel *icon = new QLabel(this);
    icon->setPixmap(p);
    icon->resize(icon->pixmap()->size());
    if(icon->pixmap(Qt::ReturnByValue).isNull()){
        std::cout << "a";
    }
    grid->addWidget(icon,0,0);
    QWidget* w = new QWidget(this);

    QPushButton *changeIcon = new QPushButton("Change image",this);
    grid->addWidget(changeIcon,0,1);



    connect(changeIcon,&QPushButton::clicked,[&](){
        QString fileName = QFileDialog::getOpenFileName((QWidget *) 0, "Select the image", QString(), "*.png");

        QPixmap pixmap;
        pixmap.load(fileName,"PNG");
        pixmap.save(QString("images/User_profile.png"));
        

    });



    grid->addWidget(new QLabel("Username : "),1,0);

    QPushButton* changeUsername = new QPushButton(w);
    grid->addWidget(changeUsername,1,1);
    changeUsername->setText("Change Username");

    QLineEdit* editext = new QLineEdit(w);
    editext->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));
    grid->addWidget(editext,2,0);

    QPushButton* logout = new QPushButton(w);
    logout->setText("Logout");
    QObject::connect(logout, &QPushButton::clicked, [this]() {
        emit log_out();
        this->close();
    });
    grid->addWidget(logout,2,1);



    setLayout(grid);
}