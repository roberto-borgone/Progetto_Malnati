//
// Created by rober on 28/07/2020.
//

#include "Project.h"

Project::Project(std::string id, std::vector<Symbol> text): id(id), text(text){}

std::string Project::getId(){
    return this->id;
}

int Project::insert(int pos, Symbol s) {

    text.insert(text.begin() + pos, s);
}

Symbol Project::get_symbol_in_pos(int pos) {
    return text[pos];
}

int Project::remote_delete(Symbol s) {
    std::vector<int> tmp;
    auto bounds = make_pair(text.begin(), text.end());
    tmp=s.getFrac();
    int pos=-1;
    for(int i=0; i<tmp.size()-1; i++) {
        Symbol tmp_symbol(QChar('t'), std::string("no_font"), false, false, false, false, std::string("no_color"), tmp,
                          std::string("no_project"), std::string("no_user"),0, Qt::AlignLeft);
        bounds = std::equal_range(bounds.first, bounds.second, tmp_symbol, [i](const Symbol &s1, const Symbol &s2) {
            return const_cast<Symbol &>(s1).getFrac()[i] < const_cast<Symbol &>(s2).getFrac()[i];
        });

        while (bounds.first->getFrac().size() <= i+1 && bounds.first!=bounds.second ) {
            bounds.first++;
        }

        while ((bounds.second-1)->getFrac().size() <= i+1 && bounds.first!=bounds.second) {
            bounds.second--;
        }
    }
    auto begin = bounds.first;
    auto end = bounds.second;
    for (auto it = begin; it != end; it++) {
        if (it->getId() == s.getId()) {
            pos=it-text.begin();
            text.erase(it);
        }
    }

    return pos;
}

int Project::add_user(std::pair<QString, QString> user) {
    auto lock = std::lock_guard(this->user_mux);
    this->users.insert(user);
}

int Project::remove_user(std::pair<QString, QString> user){
    auto lock = std::lock_guard(this->user_mux);
    this->users.erase(user);
}