//
// Created by davide miro on 2019-09-27.
//

#include "Gui.h"
#include <QDebug>
#include <QTextCodec>


Project *project = nullptr;
const QString rsrcPath = "../images";


Gui::Gui(QWidget *parent) : QMainWindow(parent) {

    centralWidget = new QWidget(this);
    lh = new QHBoxLayout();
    list = new QListWidget(centralWidget);
    textEdit = new QTextEdit(centralWidget);

    lh->addWidget(list);
    lh->addWidget(textEdit);
    centralWidget->setLayout(lh);
    this->setCentralWidget(centralWidget);
    project = new Project(textEdit->document(), this);
    cursor_timer = new QTimer();


    cursor_timer->callOnTimeout([this]() { emit time_out(textEdit->textCursor().position()); });
    QObject::connect(textEdit->document(), &QTextDocument::contentsChange, [=](int pos, int removed, int added) {

        if (added > 0) {

            QTextCursor c(textEdit->textCursor());
            cout << c.position();
            c.setPosition(pos);
            c.setPosition(pos + added, QTextCursor::KeepAnchor);
            //       cout << c.position() <<c.selectedText().toStdString() << endl;


            string add = c.selectedText().toStdString();

            if (add == "\U00002029"){
                add =="\n";
            }


            if (add == "") return;

            //CONTROLLATE QUESTA PARTE QUI CREO SIMBOLO RELATIVO A CARATTERE DIGITATO DA UTENTE E GENERO FRAZIONARIO
            /*BUG: se si copiano e incollano più caratteri questo non viene gestito bene*/

            for (auto sp = add.end() - 1; sp >= add.begin(); sp--) {
                std::cout << sp.base() << std::endl;
                QTextCharFormat f = c.charFormat();
                vector<int> frac;

                if (project->text.size() == 0)
                    frac = vector<int>{0};
                else if (pos == project->text.size()) {
                    frac = project->text[pos - 1].getFrac();
                    frac.back()++;
                } else if (pos == 0) {
                    frac = project->text[0].getFrac();
                    frac.back()--;
                } else {  //inserimento in mezzo

                    auto before = project->text[pos - 1].getFrac();
                    vector<int> next = project->text[pos].getFrac();

                    //caso in cui il secondo sia più piccolo del primo
                    if (next.size() < before.size()) {
                        //generate random number to put in the last position, summed next element of first vector by this number
                        std::default_random_engine generator;
                        std::uniform_int_distribution<int> distribution(5, 20);
                        int random_number = distribution(generator);
                        frac = before;
                        frac[frac.size() - 1] = frac[frac.size() - 1] + random_number;
                    } else {
                        //ciclo fino a che i due vettori sono uguali oppure uno dei due finisce
                        int i = 0;
                        while (before[i] == next[i] && i < before.size() && i < next.size()) {
                            frac.insert(frac.end(), before[i]);
                            i++;
                        }

                        //caso in cui entrambi i vettori siano finiti (caso particolare in cui due client siano riusciti a mettere due caratteri nella stessa posizione allo stesso momento)
                        if (i > before.size() - 1 && i > next.size() - 1) {
                            //generate random number to put in the last position
                            std::default_random_engine generator;
                            std::uniform_int_distribution<int> distribution(5, 20);
                            int random_number = distribution(generator);
                            frac.insert(frac.end(), random_number);

                        }

                            //caso in cui il primo sia finito e il secondo no
                        else if (i > before.size() - 1) {
                            //generate random number to put in the last position, subtract next element of second vector by this number
                            std::default_random_engine generator;
                            std::uniform_int_distribution<int> distribution(5, 20);
                            int random_number = distribution(generator);
                            frac.insert(frac.end(), next[i] - random_number);
                        }


                            //caso in cui sono arrivato ad elemento diverso tra i due vettori e differenza tra gli elementi > 1
                        else if (next[i] - before[i] > 1) {
                            int new_el = (next[i] + before[i]) / 2; //prendo la media dei valori e la metto nel vettore
                            frac.insert(frac.end(), new_el);
                        }

                            //caso in cui sono arrivato ad elemento diverso tra i due vettori e differenza tra gli elementi = 1
                        else if (next[i] - before[i] == 1) {
                            frac.insert(frac.end(), before[i]); //metto elemento del primo vettore
                            //generate random number to put in the last position
                            std::default_random_engine generator;
                            std::uniform_int_distribution<int> distribution(5, 20);
                            int random_number = distribution(generator);
                            frac.insert(frac.end(), random_number);
                        }
                    }

                    /*
                    //vecchio
                    if (frac.back() == next[frac.size() - 1]) {
                        //se alla fine si hanno gli stessi numeri allora va ricopiato il vettore e aggiunto/incrementato elemento
                        for (int i = frac.size(); i < next.size() - 1; i++)
                            frac.insert(frac.end(), next[i]);
                        if (next.back() == 1) {
                            frac.insert(frac.end(), 1);
                            frac.insert(frac.end(), 1);
                        } else {
                            frac.insert(frac.end(), next.back() - 1);
                        }
                    } else if (frac.back() + 1 == next.back()) frac.push_back(1);
                    else frac.back()++;
                     */
                }

                /*QUI SI POTREBBE CREARE SIMBOLO, INVIARE PER CONTROLLARE SE CI SONO COLLSISIONI E SE NO METTERLO NEL VETTORE**/
                std::cout << "invio carattere per controllo centrale su server..." << std::endl;
                //creo il simbolo ed emetto segnale per inviarlo alla classe network che lo invierà al server
                std::string proj = std::string(project->prjID); //qui si dovrà predere il progetto aperto dallo user
                //qui si dovrà prendere lo user (quello ritornato dal server dopo il login e salvato)

                Symbol s = Symbol(*sp, f.font().family().toStdString(),
                                  f.fontWeight() == QFont::Weight::Bold,
                                  f.fontItalic(),
                                  f.fontUnderline(),
                                  f.fontStrikeOut(),
                                  f.foreground().color().name().toStdString(),
                                  frac, proj, user);
                std::cout<<s.getId();

                if (project->prjID_set) {
                    emit send_symbol(s, pos, proj, user);
                    //inserisco simbolo in gui
                    project->insert(pos, s);
                    *sp = '\0';
                } else {
                    emit no_project();
                }


            }
        }
        if (removed > 0) {

            if (project->prjID_set) {
                textEdit->undo();
                QTextCursor c(textEdit->textCursor());
                c.setPosition(pos);
                c.setPosition(pos + removed, QTextCursor::KeepAnchor);
                std::cout << "invio eliminazione per controllo centrale su server..." << std::endl;
                project->eraseElements(pos, removed);
                textEdit->redo();
            }

        }

        cout << endl;
        for_each(project->text.begin(), project->text.end(),
                 [](Symbol s) -> void { s.print(); }); //per controllo informazioni,i due controlli sono andati a buon fine

    });
    //this->setCentralWidget(textEdit);
    this->setMenuBar(initMenuBar());
    this->addToolBar(initToolBar());
}

QMenuBar *Gui::initMenuBar() {


    QMenuBar *menuBar = new QMenuBar(this); // |File |Edit |View |

    //Definizione QMenu |File |New | Open | Close |Save | Export to PDF |
    //Uso addAction(nome,function,QKeySequence)
    QMenu *file = new QMenu("File", menuBar);
    file->addAction("New", [this]() {
        if(project->prjID_set){
            emit close_project(std::string(project->prjID));
            project->prjID_set = false; //client can't now write on editor
        }
        emit new_project();
    }, QKeySequence::New); //da implementare funzionalità
    file->addAction("Open", [this]() {
        if(project->prjID_set){
            emit close_project(std::string(project->prjID));
            project->prjID_set = false; //client can't now write on editor
        }
        emit request_for_projects(std::string("user1")); }, QKeySequence::Open);
    file->addAction("Close", [this]() {
        emit close_project(std::string(project->prjID));
        project->prjID_set = false; //client can't now write on editor
    }, QKeySequence::Close);
    file->addAction("Save", []() { cout << "Save"; }, QKeySequence::Save);
    file->addAction("Save as", []() { cout << "Save as"; }, QKeySequence::SaveAs);
    file->addAction("Export to PDF", [this]() {
        QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
        if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }
        QPdfWriter* writer = new QPdfWriter(QString(fileName));
        QTextDocument *doc = this->textEdit->document();
        doc->print(writer);
    });
    menuBar->addMenu(file);


    //Definizione QMenu Edit |Undo|Redo|Cut|Paste|Delete|Select All|
    //Uso addAction(nome,function,QKeySequence)
    QMenu *edit = new QMenu("Edit", menuBar);
    edit->addAction("Undo", [this]() { undo(); },
                    QKeySequence::Undo); //da implementare funzionalità e da mettere shortcut
    edit->addAction("Redo", [this]() { redo(); }, QKeySequence::Redo);
    edit->addAction("Cut", [this]() { cut(); }, QKeySequence::Cut);
    edit->addAction("Paste", [this]() { paste(); }, QKeySequence::Paste);
    edit->addAction("Delete", [this]() { deleteT(); }, QKeySequence::Delete);
    edit->addAction("Select All", [this]() { selectAll(); }, QKeySequence::SelectAll);


    menuBar->addMenu(edit);

    //Definizione QMenu View ...
    QMenu *view = new QMenu("View", menuBar);
    menuBar->addMenu(view);


    return menuBar;

}

QToolBar *Gui::initToolBar() {
    QToolBar *toolBar = new QToolBar(this);

    //ToolBar -> |stile(default,barrato,corsivo,grassetto,sottolineato)|Font|dimensione|Colore|

    toolBar->addAction(QIcon::fromTheme("Profile", QIcon("/Users/davidemiro/Downloads/87244019_125707735545739_1155971369473671168_n.jpg")), "Profile", [=]() {
        Profile f;
        f.exec();


    });
    toolBar->addAction(QIcon::fromTheme("Collaborators", QIcon(rsrcPath + "/link.svg")), "Collaborators", [=]() {

        //project->markUsersText(this->user_color);
    });
    toolBar->addAction(QIcon::fromTheme("New", QIcon(rsrcPath + "/file.svg")), "New", [=]() {
        if(project->prjID_set){
            emit close_project(std::string(project->prjID));
            project->prjID_set = false; //client can't now write on editor
        }
        emit new_project();
    });
    toolBar->addAction(QIcon::fromTheme("Open", QIcon(rsrcPath + "/file-1.svg")), "Open", [=]() {
        if(project->prjID_set){
            emit close_project(std::string(project->prjID));
            project->prjID_set = false; //client can't now write on editor
        }
        emit request_for_projects(std::string("user1"));
    });
    toolBar->addAction(QIcon::fromTheme("Close", QIcon(rsrcPath + "/close.svg")), "Close", [=]() {
        emit close_project(std::string(project->prjID));
        project->prjID_set = false; //client can't now write on editor
    });
    toolBar->addAction(QIcon::fromTheme("Save", QIcon(rsrcPath + "/save.svg")), "Save",
                       [this]() { //valutare cambio icona a save-1 a prima modifica

                       });
    toolBar->addAction(QIcon::fromTheme("Import", QIcon(rsrcPath + "/import.svg")), "Import", [this]() {

    });
    toolBar->addAction(QIcon::fromTheme("Export", QIcon(rsrcPath + "/export.svg")), "Export", [this]() {

    });
    toolBar->addAction(QIcon::fromTheme("Undo", QIcon(rsrcPath + "/undo.svg")), "Undo", [this]() {
        undo();

    });
    toolBar->addAction(QIcon::fromTheme("Redo", QIcon(rsrcPath + "/redo.svg")), "Redo", [this]() {
        redo();
    });
    toolBar->addAction(QIcon::fromTheme("Cut", QIcon(rsrcPath + "/scissors.svg")), "Cut", [this]() {
        cut();
    });
    toolBar->addAction(QIcon::fromTheme("Paste", QIcon(rsrcPath + "/paste.svg")), "Paste", [this]() {
        paste();
    });
    toolBar->addAction(QIcon::fromTheme("Delete", QIcon(rsrcPath + "/eraser.svg")), "Delete", [this]() {
        deleteT();
    });

    QComboBox *font = new QComboBox(toolBar);

    //Metto come opzioni tutti i font presenti nel sistema
    QFontDatabase db;
    QStringList families = db.families();
    QStringListIterator fonts(families);

    while (fonts.hasNext()) {
        QString f = fonts.next();
        font->addItem(f);
        if (f.toStdString() == "Arial")
            font->setCurrentText(f);


    }
    QObject::connect(font, &QComboBox::currentTextChanged, [this](const QString &tex) -> void {
        setFont(tex);
    });

    toolBar->addWidget(font);


    toolBar->addAction(QIcon::fromTheme("Bold", QIcon(rsrcPath + "/bold.svg")), "Bold", [this]() {
        bold();
    });
    toolBar->addAction(QIcon::fromTheme("Italic", QIcon(rsrcPath + "/italic.svg")), "Italic", [this]() {
        italic();
    });
    toolBar->addAction(QIcon::fromTheme("Underline", QIcon(rsrcPath + "/underline.svg")), "Underline", [this]() {
        underline();
    });
    toolBar->addAction(QIcon::fromTheme("Overline", QIcon(rsrcPath + "/strikethrough.svg")), "Overline", [this]() {
        overline();
    });

    QSpinBox *size = new QSpinBox(toolBar);
    size->setRange(8, 288);
    QObject::connect(size, QOverload<int>::of(&QSpinBox::valueChanged), [this](int i) -> void {
        setTextSize(i);
    });
    toolBar->addWidget(size);

    QPushButton *color = new QPushButton(toolBar);
    color->setStyleSheet("background-color: black");

    connect(color, &QPushButton::pressed, [=]() {

        QColorDialog palette(QColor("black"), this);
        connect(&palette, &QColorDialog::colorSelected, [color, this](const QColor &c) -> void {

            string s = "background-color: " + c.name().toStdString();

            color->setStyleSheet(QString::fromStdString(s));
            setTextColor(c);


        });
        palette.exec();
    });

    toolBar->addWidget(color);

    toolBar->addAction(QIcon::fromTheme("Left-align", QIcon(rsrcPath + "/left-align.svg")), "Left-align", [=]() {
        QTextCursor cursor = textEdit->textCursor();
        QTextBlockFormat textBlockFormat = cursor.blockFormat();
        textBlockFormat.setAlignment(Qt::AlignLeft);//or another alignment
        cursor.mergeBlockFormat(textBlockFormat);
        this->textEdit->setTextCursor(cursor);
    });
    toolBar->addAction(QIcon::fromTheme("Justify", QIcon(rsrcPath + "/justify.svg")), "Justify", [=]() {
        QTextCursor cursor = textEdit->textCursor();
        QTextBlockFormat textBlockFormat = cursor.blockFormat();
        textBlockFormat.setAlignment(Qt::AlignJustify);//or another alignment
        cursor.mergeBlockFormat(textBlockFormat);
        this->textEdit->setTextCursor(cursor);
    });
    toolBar->addAction(QIcon::fromTheme("Right-align", QIcon(rsrcPath + "/right-align.svg")), "Right-align", [=]() {
        QTextCursor cursor = textEdit->textCursor();
        QTextBlockFormat textBlockFormat = cursor.blockFormat();
        textBlockFormat.setAlignment(Qt::AlignRight);//or another alignment
        cursor.mergeBlockFormat(textBlockFormat);
        this->textEdit->setTextCursor(cursor);
    });

    return toolBar;


}

void Gui::setFont(QString text) {
    QTextCharFormat format = textEdit->currentCharFormat();
    format.setFont(QFont(text));
    textEdit->setCurrentCharFormat(format);


}

void Gui::bold() {
    QTextCharFormat format = textEdit->currentCharFormat();
    if (format.fontWeight() != QFont::Weight::Bold) format.setFontWeight(QFont::Weight::Bold);
    else format.setFontWeight(QFont::Weight::Normal);
    textEdit->setCurrentCharFormat(format);
}

void Gui::italic() {
    QTextCharFormat format = textEdit->currentCharFormat();
    format.setFontItalic(!format.fontItalic());
    textEdit->setCurrentCharFormat(format);
}

void Gui::underline() {
    QTextCharFormat format = textEdit->currentCharFormat();
    format.setFontUnderline(!format.fontUnderline());
    textEdit->setCurrentCharFormat(format);
}

void Gui::overline() {
    QTextCharFormat format = textEdit->currentCharFormat();
    format.setFontStrikeOut(!format.fontStrikeOut());
    textEdit->setCurrentCharFormat(format);
}


void Gui::setTextSize(int size) {
    QTextCharFormat format = textEdit->currentCharFormat();
    format.setFontPointSize(size);
    textEdit->setCurrentCharFormat(format);
}

void Gui::undo() {
    textEdit->undo();
}

void Gui::redo() {
    textEdit->redo();
}

void Gui::cut() {
    textEdit->cut();
}

void Gui::paste() {
    textEdit->paste();
}

void Gui::selectAll() {
    textEdit->selectAll();
}

void Gui::deleteT() {
    QTextCursor cursor = textEdit->textCursor();
    cursor.removeSelectedText();
}

void Gui::setTextColor(const QColor &color) {
    textEdit->setTextColor(color);
}

Project *Gui::getCurrentProject() {
    return project;
}

void Gui::logged_in(const std::string &user) {
    this->setVisible(true);
    this->setWindowTitle(QString::fromStdString(user));
    this->user = user;

    //Qui prende l' immagine a caso,ma dovrebbe chiedere al DB per un utente dove è salvata l' immagine
    std::string iconpath = "/Users/davidemiro/Downloads/87244019_125707735545739_1155971369473671168_n.jpg";
    QPixmap p(QString::fromStdString(iconpath));
    QIcon ico(p);
    QListWidgetItem* item = new QListWidgetItem(ico,QString::fromStdString(user));
    int r = rand() %255;
    int g = rand() %255;
    int b = rand() %255;
    item->setBackgroundColor(QColor::fromRgb(r,g,b));
    list->addItem(item);
    user_color[user] = {r,g,b};
}

void Gui::insert_in_Gui(int pos, Symbol s) {
    /*INSERIMENTO DI CARATTERE IN GUI*/
    auto old_cursor = textEdit->textCursor(); //save old cursor
    auto new_cursor = QTextCursor(textEdit->document());//create new cursor
    new_cursor.setPosition(pos); //set position of new cursor
    textEdit->setTextCursor(new_cursor); //update editor cursor
    QTextCharFormat format;//create in Gui same format of symbol (font, bold, italic, underline, strike, color)
    QFont q;
    q.setFamily(s.getFont());
    q.setBold(s.isBold());
    q.setItalic(s.isItalic());
    q.setUnderline(s.isUnderline());
    q.setStrikeOut(s.isStrike());
    format.setFont(q);
    QBrush brush;
    brush.setColor(QColor(s.getColor()));
    format.setForeground(brush);

    std::cout << "inserimento remoto" << s.getChar() << std::endl;
    bool resume_signals = textEdit->document()->blockSignals(
            true); //block signal "contentsChange" to avoid infinite loop
    new_cursor.insertText(
            QChar(s.getChar()), format); //insert text in position (better use overloaded function with format)
    textEdit->document()->blockSignals(resume_signals);

    if (pos <= old_cursor.position()) {
        old_cursor.setPosition(old_cursor.position() + 1);
    } else {
        old_cursor.setPosition(old_cursor.position());
    }
    textEdit->setTextCursor(old_cursor); //update editor cursor
}

void Gui::delete_in_Gui(int pos = 0) {
    /*CANCELLAZIONE DI CARATTERE IN GUI*/
    auto old_cursor = textEdit->textCursor(); //save old cursor
    auto new_cursor = QTextCursor(textEdit->document());//create new cursor
    new_cursor.setPosition(pos); //set position of new cursor
    textEdit->setTextCursor(new_cursor); //update editor cursor

    bool resume_signals = textEdit->document()->blockSignals(
            true); //block signal "contentsChange" to avoid infinite loop
    new_cursor.deleteChar();//delete text in position
    textEdit->document()->blockSignals(resume_signals);

    if (pos <= old_cursor.position()) {
        old_cursor.setPosition(old_cursor.position());
    } else {
        old_cursor.setPosition(old_cursor.position());
    }
    textEdit->setTextCursor(old_cursor); //update editor cursor
}

void Gui::delete_all_Gui() {
    if (!textEdit->document()->isEmpty()) {
        textEdit->clear();
    }
}
void Gui::add_user(std::string user, int pos) {

    QPixmap p(QString::fromStdString("..path"));
    QIcon ico(p);
    QListWidgetItem* item = new QListWidgetItem(ico,QString::fromStdString(user));
    int r = rand() %255;
    int g = rand() %255;
    int b = rand() %255;
    user_color[user] = {r,g,b};
    item->setBackgroundColor(QColor::fromRgb(r,g,b));
    list->addItem(item);

}
void Gui::start_timer() {
   //
    cursor_timer->start(1000);
}

void Gui::stop_timer() {
    cursor_timer->stop();
}

