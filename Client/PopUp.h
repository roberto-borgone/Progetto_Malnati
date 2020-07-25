//
// Created by Clemente Cetera on 25/07/2020.
//
#include <QDialog>
#include <QLabel>
#include <QDialogButtonBox>
#ifndef EDITORCOLLABORATIVO_POPUP_H
#define EDITORCOLLABORATIVO_POPUP_H
class PopUp : public QDialog
{
    Q_OBJECT;
public:
    PopUp(): QDialog(){
        setWindowTitle("No project open");
        setWindowFlags(Qt::Dialog);

        QVBoxLayout* layout = new QVBoxLayout();
        setLayout(layout);
        layout->addWidget(new QLabel("you have to open or create a project first!"));
        QDialogButtonBox* buttonBox =
                new QDialogButtonBox(QDialogButtonBox::Ok);
        connect(buttonBox, &QDialogButtonBox::accepted,
                this, &QDialog::accept);

        connect(buttonBox, &QDialogButtonBox::accepted,
                [this](){emit popUp_delete(0);});


        layout->addSpacing(10);
        layout->addWidget(buttonBox);
    };
    ~PopUp()= default;

signals:
    void popUp_delete(int pos);
};
#endif //EDITORCOLLABORATIVO_POPUP_H
