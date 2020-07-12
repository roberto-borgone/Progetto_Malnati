//
// Created by davide miro on 2019-09-27.
//

#ifndef EDITORCOLLABORATIVO_GUI_H
#define EDITORCOLLABORATIVO_GUI_H

#include <vector>
#include <string>
#include <iostream>
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QComboBox>
#include <QStringList>
#include <QPushButton>
#include <QSpinBox>
#include <QColorDialog>
#include <QColor>
#include <QTextEdit>
#include <QFileDialog>
#include <QFontDatabase>
#include <QFont>
#include <QTextDocument>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QToolButton>
#include <QStyle>
#include <QStringList>
#include <QPushButton>
#include <QSpinBox>
#include <QColorDialog>
#include <QColor>
#include <QTextEdit>
#include <QFileDialog>
#include <QFontDatabase>
#include <QFont>
#include <QTextDocument>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QToolButton>
#include <QStyle>

#include "Project.h"

using namespace std;
class Gui : public QMainWindow{
    Q_OBJECT
    QMenuBar* initMenuBar();
    QToolBar* initToolBar();
    QTextEdit *textEdit;




public:
    Gui(QWidget *parent);
    Project* getCurrentProject();
    void setFont(QString text);
    void bold();
    void italic();
    void underline();
    void overline();
    void setTextSize(int size);
    void undo();
    void redo();
    void cut();
    void paste();
    void selectAll();
    void deleteT();
    void setTextColor(const QColor& c);

public slots:
    void logged_in(const std::string& user);

signals:
    void send_symbol(Symbol s);

};



#endif //EDITORCOLLABORATIVO_GUI_H
