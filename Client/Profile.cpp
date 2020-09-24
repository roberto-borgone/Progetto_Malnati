//
// Created by davide miro on 09/09/2020.
//

#include "Profile.h"
#include <iostream>

Profile::Profile():QDialog(){
    setWindowTitle("Profile information");
    setWindowFlags(Qt::Dialog);

    QHBoxLayout* layout = new QHBoxLayout();
    QPixmap p("/Users/davidemiro/Downloads/87244019_125707735545739_1155971369473671168_n.jpg");
    QPushButton *icon = new QPushButton(this);
    icon->setIcon(QIcon(p));
    icon->setIconSize(p.rect().size());
    layout->addWidget(icon,Qt::AlignCenter);
    QWidget* w = new QWidget(this);

    QGridLayout *grid = new QGridLayout(this);
    grid->addWidget(new QLabel("Username : "),0,0);

    QPushButton* changeUsername = new QPushButton(w);
    grid->addWidget(changeUsername,1,0);
    changeUsername->setText("Change Username");

    QTextEdit* editext = new QTextEdit(w);
    editext->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));
    grid->addWidget(editext,0,1);

    QPushButton* logout = new QPushButton(w);
    logout->setText("Logout");
    QObject::connect(logout, &QPushButton::clicked, [this]() {
        emit log_out();
        this->close();
    });
    grid->addWidget(logout,1,1);

    w->setLayout(layout);
    layout->addWidget(w);

    setLayout(layout);
}