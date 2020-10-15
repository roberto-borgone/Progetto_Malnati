//
// Created by Clemente Cetera on 15/10/2020.
//

#ifndef EDITORCOLLABORATIVO_WRONGPROJECTPOPUP_H
#define EDITORCOLLABORATIVO_WRONGPROJECTPOPUP_H

#include <QDialog>
#include <QLabel>
#include <QDialogButtonBox>
#include <QBoxLayout>

class WrongProjectPopUp : public QDialog {
    Q_OBJECT;
public:
    WrongProjectPopUp(bool open) : QDialog() {
        setWindowTitle("wrong credentials");
        setWindowFlags(Qt::Dialog);

        QVBoxLayout *layout = new QVBoxLayout();
        setLayout(layout);
        if (open)
            layout->addWidget(new QLabel("Error in opening project: make sure project exists!"));
        else
            layout->addWidget(new QLabel("Error in creating project: make sure its name is unique!"));
        QDialogButtonBox *buttonBox =
                new QDialogButtonBox(QDialogButtonBox::Ok);
        connect(buttonBox, &QDialogButtonBox::accepted,
                this, &QDialog::accept);

        layout->addSpacing(10);
        layout->addWidget(buttonBox);
    };

    ~WrongProjectPopUp() = default;

};

#endif //EDITORCOLLABORATIVO_WRONGPROJECTPOPUP_H
