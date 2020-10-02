//
// Created by davide miro on 02/10/2020.
//

#ifndef EDITORCOLLABORATIVO_USEINVITE_H
#define EDITORCOLLABORATIVO_USEINVITE_H


#include <QDialog>
#include <QLabel>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QLineEdit>
#include <iostream>

class UseInvite : public QDialog {
Q_OBJECT;

    QLineEdit *lineEdit = new QLineEdit();
public: UseInvite() : QDialog() {
        setWindowTitle("Access to the project with the invite");
        setWindowFlags(Qt::Dialog);

        QVBoxLayout *layout = new QVBoxLayout();
        setLayout(layout);
        layout->addWidget(new QLabel("Insert the uri of the project"));
        layout->addWidget(lineEdit);

        QDialogButtonBox *buttonBox =
                new QDialogButtonBox(QDialogButtonBox::Ok);
        connect(buttonBox, &QDialogButtonBox::accepted,
                this, &QDialog::accept);

        connect(buttonBox, &QDialogButtonBox::accepted,
                [this]() {
                    emit request_for_project(lineEdit->text().toStdString());
                });
        layout->addSpacing(10);
        layout->addWidget(buttonBox);
    }

    ~UseInvite() = default;

signals:

    void request_for_project(std::string project);
};


#endif //EDITORCOLLABORATIVO_USEINVITE_H
