//
// Created by davide miro on 2019-10-01.
//


#include <QTextEdit>
#include <QTextBlock>
#include "Project.h"


Project::Project(QTextDocument *document, QObject *parent) : QObject(parent), document(document) {}
/*
int Project::new_insert(Symbol s) {
    int pos;
    if(text.size() > 0){
        if(s < text[0]) pos = 0;
        if(s >text[text.size() - 1]) pos = text.size() - 1;
        for(int i = 1 ; i < text.size(); i++){
            if(text[i - 1] <= s && text[i] >=s){
                pos = i;
            }
        }
    }
    else{
        pos = 0;
    }
    text.insert(text.begin() + pos, s);
    symbols.insert({s.getId(), pos});
    return pos;


}
*/
/*
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
*/

void Project::eraseElements(int pos, int removed) {

    std::vector<Symbol> removed_symbols;

    if(pos + removed > text.size()){
        return;
    }
    auto start = text.begin();
    auto end = text.begin();

    std::advance(start,pos);
    std::advance(end,pos +removed);

    for(auto it = start; it !=end;it++){
        symbols.erase(it->getId());
        removed_symbols.push_back(*it);
    }

    emit remove_symbol(removed_symbols);

    text.erase(start,end);




}
int Project::eraseElement(string id) {
    if(symbols.find(id) == symbols.end()){
        return -1;
    }
    Symbol s = symbols[id];
    auto it = text.find(s);
    int pos = std::distance(text.begin(),it);
    text.erase(s);
    return pos;
}
int Project::eraseElement(Symbol s) {
    auto it = text.find(s);
    if(it == text.end()){
        return -1;
    }
    symbols.erase(s.getId());


    int pos = std::distance(text.begin(),it);
    text.erase(s);
    return pos;
}

int Project::insert(Symbol s) {
    auto it = text.insert(s);
    int pos = std::distance(text.begin(),it);
    symbols.insert({s.getId(),s});
    return pos;

}



/*
int Project::remote_delete(Symbol s) {
    std::cout << "dentro la remote cancella" << std::endl;
    std::vector<int> tmp; //vettore temporane che mi servirà per la ricerca
    auto bounds = make_pair(text.begin(), text.end());
    //std::cout << "da cercare: " << s.getChar() << std::endl;
    tmp=s.getFrac();
    std::cout << "vettore tmp: ";
    for (auto el:tmp) std::cout << el << " ";
    std::cout << std::endl;
    int pos=-1;
    for(int i=0; i<tmp.size()-1; i++) {
        Symbol tmp_symbol(QChar('t'), std::string("no_font"), false, false, false, false, std::string("no_color"), tmp,
                          std::string("no_project"), std::string("no_user"),0,0);
        bounds = std::equal_range(bounds.first, bounds.second, tmp_symbol, [i](const Symbol &s1, const Symbol &s2) {
            return const_cast<Symbol &>(s1).getFrac()[i] < const_cast<Symbol &>(s2).getFrac()[i];
        });

        //fino a che begin è di una lunghezza minore di tmp vado avanti
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
            //std::cout << "element: " << t->getChar() << " " << t->getFrac()[0] << " ";
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
    auto element_to_delete = begin-1;
    for (auto it = begin; it != end; it++) {
        //std::cout << "trovato elemento" << it->getChar() << std::endl;
        if (it->getId() == s.getId()) {
            element_to_delete=it;
        }
    }

    if(element_to_delete!=begin-1){
        pos=element_to_delete-text.begin();
        text.erase(element_to_delete);
    }

    return pos;
}
*/

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
void Project::externalInsert(Symbol s) {

    int pos = insert(s);
    QTextCursor cursor(document);
    cursor.setPosition(pos);
    cursor.insertText(s.getChar());

}

void Project::externalDelete(string id) {

    int pos = eraseElement(id);
    QTextCursor cursor(document);
    cursor.setPosition(pos);
    cursor.deleteChar();

}


