#include "automate.h"

void Automate::lecture() {
    Symbole* s;
    while(*(s=lexer.Consulter())!=FIN) {
        Etat* etat = statestack.top();
        etat->transition(*this, s);
        l.Avancer();
   }
    Expr* final_expr = dynamic_cast<Expr*>(symbolstack.top());
    if (final_expr) {
        int result = final_expr->eval();
        std::cout << "Résultat de l'expression : " << result << std::endl;
    } else {
        std::cout << "Erreur : expression invalide !" << std::endl;
    }
}

void Automate::decalage(Symbole * s, Etat * e) {
    symbolstack.push_back(s);
    statestack.push_back(e);
    lexer->Avancer();
}

void Automate::transitionsimple(Symbole * s, Etat * e) {
    symbolstack.push_back(s);
    statestack.push_back(e);
}

void Automate::reduction(int n,Symbole * s) {
    for (int i=0;i<n;i++){
        delete(statestack.back());
        statestack.pop_back();
    }
    statestack.back()->transition(*this,s);
}

Symbole* Automate::popSymbol() {
    if (!symbolstack.empty()) {
        Symbole* s = symbolstack.top();
        symbolstack.pop_back();
        return s;
    }
    return nullptr;
}

void Automate::popAndDestroySymbol() {
    if (!symbolstack.empty()) {
        Symbole* s = symbolstack.top();
        symbolstack.pop_back();
        delete s;
    }
}

Automate(Lexer& lexer) : lexer(lexer) {
    statestack.push(new Etat0());
};