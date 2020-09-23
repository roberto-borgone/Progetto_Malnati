//
// Created by Clemente Cetera on 23/09/2020.
//

#ifndef EDITORCOLLABORATIVO_WRONGCREDENTIALSPOPUP_H
#define EDITORCOLLABORATIVO_WRONGCREDENTIALSPOPUP_H

#include <QDialog>
#include <QLabel>
#include <QDialogButtonBox>
#include <QBoxLayout>

class WrongCredentialsPopUp : public QDialog {
Q_OBJECT;
public:
    WrongCredentialsPopUp(bool sub) : QDialog() {
        setWindowTitle("wrong credentials");
        setWindowFlags(Qt::Dialog);

        QVBoxLayout *layout = new QVBoxLayout();
        setLayout(layout);
        if (sub)
            layout->addWidget(new QLabel("Already existing user"));
        else
            layout->addWidget(new QLabel("wrong username or password"));
        QDialogButtonBox *buttonBox =
                new QDialogButtonBox(QDialogButtonBox::Ok);
        connect(buttonBox, &QDialogButtonBox::accepted,
                this, &QDialog::accept);

        layout->addSpacing(10);
        layout->addWidget(buttonBox);
    };

    ~WrongCredentialsPopUp() = default;

};

#endif //EDITORCOLLABORATIVO_WRONGCREDENTIALSPOPUP_H
