//
// Created by davide miro on 30/09/2020.
//

#ifndef EDITORCOLLABORATIVO_SENDEMAILPOPUP_H
#define EDITORCOLLABORATIVO_SENDEMAILPOPUP_H

#include <QDialog>
#include <QLabel>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QLineEdit>
#include <iostream>

class SendEmailPopup : public QDialog {
Q_OBJECT;

    QLineEdit *lineEdit = new QLineEdit();
public:
    SendEmailPopup(bool isProject) : QDialog() {
        if(isProject){
            setWindowTitle("Send invite to collaborate");
            setWindowFlags(Qt::Dialog);

            QVBoxLayout *layout = new QVBoxLayout();
            setLayout(layout);
            layout->addWidget(new QLabel("Insert the email address"));
            layout->addWidget(lineEdit);

            QDialogButtonBox *buttonBox =
                    new QDialogButtonBox(QDialogButtonBox::Ok);
            connect(buttonBox, &QDialogButtonBox::accepted,
                    this, &QDialog::accept);

            connect(buttonBox, &QDialogButtonBox::accepted,
                    [this]() {
                        emit get_email(lineEdit->text().toStdString());
                    });
            layout->addSpacing(10);
            layout->addWidget(buttonBox);
        }
        else{
            setWindowTitle("Impossible to send an invite to collaborate, open a project");
            setWindowFlags(Qt::Dialog);

            QVBoxLayout *layout = new QVBoxLayout();
            setLayout(layout);
            layout->addWidget(new QLabel("Impossible to send an invite to collaborate, open a project"));


            QDialogButtonBox *buttonBox =
                    new QDialogButtonBox(QDialogButtonBox::Ok);
            connect(buttonBox, &QDialogButtonBox::accepted,
                    this, &QDialog::accept);
            layout->addWidget(buttonBox);

        }


    };

    ~SendEmailPopup() = default;

signals:

    void get_email(std::string address);
};
#endif //EDITORCOLLABORATIVO_SENDEMAILPOPUP_H
