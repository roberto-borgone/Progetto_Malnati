//
// Created by davide miro on 2019-10-01.
//


#include <QTextEdit>
#include <QTextBlock>
#include "Project.h"


Project::Project(QTextDocument *document, QObject *parent) : QObject(parent), document(document) {}

int Project::insertOrder(int l, int r, Symbol s) { //inserisco in tempo logaritmico in modo ordinato elemento,serve
    int q;
    if (s <= text[l]) {
        text.insert(text.begin(), s);
        symbols.insert({s.getId(), 0});

        return 0;
    }
    if (s >= text[r - 1]) {
        text.insert(text.end(), s);
        symbols.insert({s.getId(), r});
        return r;
    }
    while (l <= r) {
        q = (l + r) / 2;
        if (text[q] >= s) {
            if (text[q - 1] <= s) {
                text.insert(text.begin() + q, s);
                symbols.insert({s.getId(), q});
                return q;
            }
            r = q - 1;
        } else {
            if (text[q + 1] >= s) {
                text.insert(text.begin() + q, s);
                symbols.insert({s.getId(), q});
                return q;
            }
            l = q + 1;
        }
    }
}

void Project::eraseElement(int pos) {
    symbols.erase(text[pos].getId());
    text.erase(text.begin() + pos);
}

void Project::eraseElement(string id) {
    int pos = symbols[id];
    symbols.erase(id);
    text.erase(text.begin() + pos);
}

int Project::insert(int pos, Symbol s) {
    text.insert(text.begin() + pos, s);
    symbols.insert({s.getId(), pos});
}

void Project::eraseElements(int pos, int r) {
    /*auto it = text.begin()+pos;
    auto end = it + r;
    while(it != end){
        symbols.erase(it->getId());
        Symbol s = *it;
        text.erase(it);
        emit remove_symbol(s);
        it ++;
    }*/

    for (int i = 0; i < r; i++) {
        auto it = text.begin() + pos;
        symbols.erase(it->getId());
        Symbol s = *it;
        text.erase(it);
        emit remove_symbol(s);
    }
}


void Project::externalInsert(Symbol s) {

    int pos = insertOrder(0, text.size(), s);
    QTextCursor cursor(document);
    cursor.setPosition(pos);
    cursor.insertText(QString(s.getChar()));

}

void Project::externalDelete(string id) {
    int pos = symbols[id];
    eraseElement(pos);
    QTextCursor cursor(document);
    cursor.setPosition(pos);
    cursor.deleteChar();

}

Symbol Project::get_symbol_in_pos(int pos) {
    return text[pos];
}

int Project::remote_delete(Symbol s) {
    std::cout << "dentro la remote cancella" << std::endl;
    std::vector<int> tmp; //vettore temporane che mi servirà per la ricerca
    auto bounds = make_pair(text.begin(), text.end());
    std::cout << "da cercare: " << s.getChar() << std::endl;
    tmp=s.getFrac();
    std::cout << "vettore tmp: ";
    for (auto el:tmp) std::cout << el << " ";
    std::cout << std::endl;
    int pos=-1;
    for(int i=0; i<tmp.size()-1; i++) {
        Symbol tmp_symbol('t', std::string("no_font"), false, false, false, false, std::string("no_color"), tmp,
                          std::string("no_project"), std::string("no_user"));
        bounds = std::equal_range(bounds.first, bounds.second, tmp_symbol, [i](const Symbol &s1, const Symbol &s2) {
            return const_cast<Symbol &>(s1).getFrac()[i] < const_cast<Symbol &>(s2).getFrac()[i];
        });

        //fino a che begin è di una lunghezza di begin è minore di tmp vado avanti
        while (bounds.first->getFrac().size() <= i+1 && bounds.first!=bounds.second ) { //i+2 cioè se non esiste l'elemento successivo
            std::cout << "avanti\n";
            bounds.first++;
        }

        while ((bounds.second-1)->getFrac().size() <= i+1 && bounds.first!=bounds.second) {
            std::cout << "indietro\n";
            bounds.second--;
        }

        std::cout << "i: "<<i;
        for (auto t = bounds.first; t != bounds.second; t++) {
            std::cout << "element: " << t->getChar() << " " << t->getFrac()[0] << " ";
        }
        cout << std::endl;
    }
    //qui in bounds dovrei avere il range di elementi che hanno lo stesso vettore posizione di quello da eliminare
    //a questo punto vado a vedere gli id e se combaciano, cancello
    auto begin = bounds.first;
    auto end = bounds.second;
    if (begin == end) {
        std::cout << "nessun elemento trovato";
    }
    for (auto it = begin; it != end; it++) {
        std::cout << "trovato elemento" << it->getChar() << std::endl;
        if (it->getId() == s.getId()) {
            pos=it-text.begin();
            text.erase(it);
        }
    }

    return pos;
}

void Project::delete_all() {
    text.clear();
    symbols.clear();
}

void Project::markUsersText(map<string,vector<int>> colors) {
    //Qui deve gestire il sottolineamento del testo,per farlo bisogna cambiare l' html.
    //Ho modificato l' id = utente/progetto/tempo in modo tale da poter facilmente estrapolare l'utente che lo ha scritto
    //Bisogna iterare su ogni simbolo
    std::cout << document->toHtml().toStdString();
    QString previousHTML = document->toHtml();
    string html = document->toHtml().toStdString();
    int start = html.find("<p");
    int end = html.find("p>") + 2;
    string paragraph = html.substr(start,end);


    auto it = symbols.begin();
    for (;it != symbols.end();it++){
        string id = it->first;
        string user  = id.substr(0, id.find("/"));

    }
    std::cout << document->toHtml().toStdString();

}
