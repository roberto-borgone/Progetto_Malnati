//
// Created by Clemente Cetera on 27/07/2020.
//

#ifndef EDITORCOLLABORATIVO_PROJECTSPOPUP_H
#define EDITORCOLLABORATIVO_PROJECTSPOPUP_H

#include <QDialog>
#include <QLabel>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <utility>
#include "ClickableLabel.h"

class ProjectsPopUp : public QDialog {
Q_OBJECT;

    QVBoxLayout *layout = new QVBoxLayout();
public:
    ProjectsPopUp() : QDialog() {
        setWindowTitle("projects available");
        setWindowFlags(Qt::Dialog);
    };

    ~ProjectsPopUp() = default;

public slots:

    void set_list(std::vector<std::string> projects_name) {
        //per ogni stringa nella lista creo unq Qlabel cliccabile e la aggiungo al layout e per ognuno faccio la connect per l'invio della scelta
        while ( auto w = findChild<QWidget*>() ) {
            delete w;
        }
        setLayout(layout);

        for (const auto &project_name : projects_name) {
            auto name = new ClickableLabel(QString(project_name.c_str()));
            connect(name, &ClickableLabel::clicked,
                    [this](std::string name) {
                emit send_prj_to_open(name);});
            connect(name, &ClickableLabel::clicked,
                    this, &QDialog::accept);
            layout->addWidget(name);
            layout->addSpacing(10);
        }

    };

signals:

    void send_prj_to_open(std::string name);

};

#endif //EDITORCOLLABORATIVO_PROJECTSPOPUP_H
