//
// Created by Clemente Cetera on 28/07/2020.
//

#ifndef EDITORCOLLABORATIVO_CLICKABLELABEL_H
#define EDITORCOLLABORATIVO_CLICKABLELABEL_H
#include <QLabel>
#include <QWidget>
#include <Qt>

class ClickableLabel : public QLabel {
Q_OBJECT

public:
    explicit ClickableLabel(QString name):QLabel(name){};
    ~ClickableLabel()= default;

signals:
    void clicked(std::string prj_name);

protected:
    void mousePressEvent(QMouseEvent* event){
        emit clicked(this->text().toStdString());
    };

};
#endif //EDITORCOLLABORATIVO_CLICKABLELABEL_H
