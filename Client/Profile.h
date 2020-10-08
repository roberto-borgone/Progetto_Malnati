//
// Created by davide miro on 09/09/2020.
//

#ifndef EDITORCOLLABORATIVO_PROFILE_H
#define EDITORCOLLABORATIVO_PROFILE_H

#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QIcon>
#include <QPushButton>
#include <QTextEdit>
#include <QSizePolicy>
#include <QLineEdit>

class Profile :public QDialog{

Q_OBJECT;
public: Profile();

signals:
    void log_out();
    void new_image(QImage img);




};


#endif //EDITORCOLLABORATIVO_PROFILE_H
