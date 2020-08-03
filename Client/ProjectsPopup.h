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
    ProjectsPopUp(std::vector<std::string> projects_name) : QDialog() {
        setWindowTitle("projects available");
        setWindowFlags(Qt::Dialog);
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

    ~ProjectsPopUp() = default;

signals:

    void send_prj_to_open(std::string name);

};

#endif //EDITORCOLLABORATIVO_PROJECTSPOPUP_H
