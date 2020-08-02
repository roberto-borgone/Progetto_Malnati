//
// Created by Clemente Cetera on 02/08/2020.
//

#ifndef EDITORCOLLABORATIVO_NEWPROJECTPOPUP_H
#define EDITORCOLLABORATIVO_NEWPROJECTPOPUP_H
#include <QDialog>
#include <QLabel>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QLineEdit>

class NewProjectPopUp : public QDialog
{
Q_OBJECT;

    QLineEdit* lineEdit = new QLineEdit();
public:
    NewProjectPopUp(): QDialog(){
        setWindowTitle("No project open");
        setWindowFlags(Qt::Dialog);

        QVBoxLayout* layout = new QVBoxLayout();
        setLayout(layout);
        layout->addWidget(new QLabel("insert name of project"));
        layout->addWidget(lineEdit);

        QDialogButtonBox* buttonBox =
                new QDialogButtonBox(QDialogButtonBox::Ok);
        connect(buttonBox, &QDialogButtonBox::accepted,
                this, &QDialog::accept);

        connect(buttonBox, &QDialogButtonBox::accepted,
                [this](){
            std::cout<<lineEdit->text().toStdString();
            emit create_project(lineEdit->text().toStdString());});


        layout->addSpacing(10);
        layout->addWidget(buttonBox);
    };
    ~NewProjectPopUp()= default;

signals:
    void create_project(std::string prj_name);
};
#endif //EDITORCOLLABORATIVO_NEWPROJECTPOPUP_H
