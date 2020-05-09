//
// Created by davide miro on 2019-09-27.
//

#include "Gui.h"





Project *project = nullptr;
const QString rsrcPath = "../images";


Gui::Gui(QWidget *parent) :QMainWindow(parent){
    textEdit = new QTextEdit(this);
    project = new Project(textEdit->document(),this);
    QObject::connect(textEdit->document(),&QTextDocument::contentsChange,[=](int pos,int removed,int added){
        if(removed > 0){
            textEdit->undo();
            QTextCursor c(textEdit->textCursor());
            c.setPosition(pos);
            c.setPosition(pos + removed, QTextCursor::KeepAnchor);
            project->eraseElements(pos,removed);
            textEdit->redo();
        }
        if(added > 0){

            QTextCursor c(textEdit->textCursor());
            c.setPosition(pos);
            c.setPosition(pos + added, QTextCursor::KeepAnchor);
            //       cout << c.position() <<c.selectedText().toStdString() << endl;
            string add;
            if((add = c.selectedText().toStdString()) == "") return;

            //CONTROLLATE QUESTA PARTE QUI CREO SIMBOLO RELATIVO A CARATTERE DIGITATO DA UTENTE E GENERO FRAZIONARIO
            for(auto sp = add.end() - 1 ; sp >= add.begin() ; sp--){
                QTextCharFormat f = c.charFormat();
                vector<int> frac;

                if(project->text.size() == 0)
                    frac = vector<int>{0};
                else if(pos == project->text.size()){
                    frac = project->text[pos - 1].getFrac();
                    frac.back() ++;
                }
                else if (pos == 0){
                    frac = project->text[0].getFrac();
                    frac.back() --;
                }
                else{

                    frac = project->text[pos -1].getFrac();
                    vector<int> next = project->text[pos].getFrac();
                    if(frac.back() +1 == next.back()) frac.push_back(1);
                    else frac.back()++;
                }

                project->insert(pos,Symbol(*sp,f.font().family().toStdString(),
                                                    f.fontWeight() == QFont::Weight::Bold,
                                                    f.fontItalic(),
                                                    f.fontUnderline(),
                                                    f.fontStrikeOut(),
                                                    f.foreground().color().name().toStdString(),
                                                    frac,"p1","u1"));
            }
        }
        cout << endl;
        for_each(project->text.begin(),project->text.end(),[](Symbol s)->void{s.print();}); //per controllo informazioni,i due controlli sono andati a buon fine

    });
    this->setCentralWidget(textEdit);
    this->setMenuBar(initMenuBar());
    this->addToolBar(initToolBar());
}

QMenuBar* Gui::initMenuBar() {


    QMenuBar* menuBar = new QMenuBar(this); // |File |Edit |View |

    //Definizione QMenu File |New | Open | Close |Save | Export to PDF |
    //Uso addAction(nome,function,QKeySequence)
    QMenu *file = new QMenu("File",menuBar);
    file->addAction("New",[this](){
        QFileDialog dialog(this);
        dialog.setViewMode(QFileDialog::Detail);
        if(dialog.exec() == QDialog::Accepted){
            QString s;
            dialog.selectFile(s);
            cout << s.toStdString() << endl;
        }
        },QKeySequence::New); //da implementare funzionalità
    file->addAction("Open",[](){cout << "Open";},QKeySequence::Open);
    file->addAction("Close",[](){cout<<"Close";},QKeySequence::Close);
    file->addAction("Save",[](){cout <<"Save";},QKeySequence::Save);
    file->addAction("Save as",[](){cout << "Save as";},QKeySequence::SaveAs);
    file->addAction("Export to PDF",[](){cout <<"er";});
    menuBar->addMenu(file);


    //Definizione QMenu Edit |Undo|Redo|Cut|Paste|Delete|Select All|
    //Uso addAction(nome,function,QKeySequence)
    QMenu *edit = new QMenu("Edit",menuBar);
    edit->addAction("Undo",[this](){undo();},QKeySequence::Undo); //da implementare funzionalità e da mettere shortcut
    edit->addAction("Redo",[this](){redo();},QKeySequence::Redo);
    edit->addAction("Cut",[this](){cut();},QKeySequence::Cut);
    edit->addAction("Paste",[this](){paste();},QKeySequence::Paste);
    edit->addAction("Delete",[this](){deleteT();},QKeySequence::Delete);
    edit->addAction("Select All",[this](){selectAll();},QKeySequence::SelectAll);


    menuBar->addMenu(edit);

    //Definizione QMenu View ...
    QMenu *view = new QMenu("View",menuBar);
    menuBar->addMenu(view);




    return menuBar;

}
QToolBar* Gui::initToolBar() {
    QToolBar* toolBar = new QToolBar(this);

    //ToolBar -> |stile(default,barrato,corsivo,grassetto,sottolineato)|Font|dimensione|Colore|
    toolBar->addAction(QIcon::fromTheme("New", QIcon(rsrcPath + "/file.svg")),"New",[=](){

    });
    toolBar->addAction(QIcon::fromTheme("Open", QIcon(rsrcPath + "/file-1.svg")),"Open",[=](){

    });
    toolBar->addAction(QIcon::fromTheme("Close", QIcon(rsrcPath + "/close.svg")),"Close",[=](){

    });
    toolBar->addAction(QIcon::fromTheme("Save", QIcon(rsrcPath + "/save.svg")),"Save",[this](){ //valutare cambio icona a save-1 a prima modifica

    });
    toolBar->addAction(QIcon::fromTheme("Import", QIcon(rsrcPath + "/import.svg")),"Import",[this](){

    });
    toolBar->addAction(QIcon::fromTheme("Export", QIcon(rsrcPath + "/export.svg")),"Export",[this](){

    });
    toolBar->addAction(QIcon::fromTheme("Undo", QIcon(rsrcPath + "/undo.svg")),"Undo",[this](){
        undo();

    });
    toolBar->addAction(QIcon::fromTheme("Redo", QIcon(rsrcPath + "/redo.svg")),"Redo",[this](){
        redo();
    });
    toolBar->addAction(QIcon::fromTheme("Cut", QIcon(rsrcPath + "/scissors.svg")),"Cut",[this](){
        cut();
    });
    toolBar->addAction(QIcon::fromTheme("Paste", QIcon(rsrcPath + "/paste.svg")),"Paste",[this](){
        paste();
    });
    toolBar->addAction(QIcon::fromTheme("Delete", QIcon(rsrcPath + "/eraser.svg")),"Delete",[this](){
        deleteT();
    });

    QComboBox *font = new QComboBox(toolBar);

    //Metto come opzioni tutti i font presenti nel sistema
    QFontDatabase db;
    QStringList families = db.families();
    QStringListIterator fonts(families);

    while(fonts.hasNext()) {
        QString f = fonts.next();
        font->addItem(f);
        if(f.toStdString() == "Arial")
            font->setCurrentText(f);


    }
    QObject::connect(font,&QComboBox::currentTextChanged,[this](const QString &tex)->void {
        setFont(tex);
    });

    toolBar->addWidget(font);




    toolBar->addAction(QIcon::fromTheme("Bold", QIcon(rsrcPath + "/bold.svg")),"Bold",[this](){
        bold();
    });
    toolBar->addAction(QIcon::fromTheme("Italic", QIcon(rsrcPath + "/italic.svg")),"Italic",[this](){
        italic();
    });
    toolBar->addAction(QIcon::fromTheme("Underline", QIcon(rsrcPath + "/underline.svg")),"Underline",[this](){
        underline();
    });
    toolBar->addAction(QIcon::fromTheme("Overline", QIcon(rsrcPath + "/strikethrough.svg")),"Overline",[this](){
        overline();
    });

    QSpinBox *size = new QSpinBox(toolBar);
    size->setRange(8,288);
    QObject::connect(size,QOverload<int>::of(&QSpinBox::valueChanged),[this](int i)->void {
        setTextSize(i);
    });
    toolBar->addWidget(size);

    QPushButton *color = new QPushButton(toolBar);
    color->setStyleSheet("background-color: black");

    connect(color,&QPushButton::pressed,[=](){

        QColorDialog palette(QColor("black"),this);
        connect(&palette,&QColorDialog::colorSelected,[color,this](const QColor &c)->void{

            string s = "background-color: "+c.name().toStdString();

            color->setStyleSheet(QString::fromStdString(s));
            setTextColor(c);


        });
        palette.exec();
    });

    toolBar->addWidget(color);

    toolBar->addAction(QIcon::fromTheme("Left-align", QIcon(rsrcPath + "/left-align.svg")),"Left-align",[=](){
        overline();
    });
    toolBar->addAction(QIcon::fromTheme("Justify", QIcon(rsrcPath + "/justify.svg")),"Justify",[=](){
        overline();
    });
    toolBar->addAction(QIcon::fromTheme("Right-align", QIcon(rsrcPath + "/right-align.svg")),"Right-align",[=](){
        overline();
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
    if(format.fontWeight()!= QFont::Weight::Bold) format.setFontWeight(QFont::Weight::Bold);
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
void Gui::overline(){
    QTextCharFormat format = textEdit->currentCharFormat();
    format.setFontStrikeOut(!format.fontStrikeOut());
    textEdit->setCurrentCharFormat(format);
}

void Gui::setTextSize( int size){
    QTextCharFormat format = textEdit->currentCharFormat();
    format.setFontPointSize(size);
    textEdit->setCurrentCharFormat(format);
}

void Gui::undo(){
    textEdit->undo();
}

void Gui::redo(){
    textEdit->redo();
}

void Gui::cut(){
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

void Gui::setTextColor(const QColor& color) {
    textEdit->setTextColor(color);
}

Project* Gui::getCurrentProject() {
    return project;
}

void Gui::logged_in(const std::string &user) {
    this->setVisible(true);
}

