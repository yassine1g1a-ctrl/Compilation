#include "automate.h"

void Automate::lecture() {
    Symbole* s;
    // aide au débogage pour afficher la pile d'états
    auto printStack = [&]() {
        cout << "[pile etats]";
        for (Etat* e : statestack) {
            cout << " " << e->getName();
        }
        cout << endl;
    };

    Symbole *prevToken = nullptr;
    bool firstPrint = true;
    while (true) {
        s = lexer.Consulter();
        if (verbose && (s != prevToken || firstPrint)) {
            cout << "-- lecture symbole " << Etiquettes[(int)*s];
            if ((int)*s == INT) {
                Entier* entier = (Entier*) s;
                cout << "(" << entier->getValeur() << ")";
            }
            cout << endl;
            // se souvenir du symbole imprimé pour éviter de le réafficher après une réduction qui elle ne consomme pas de nouveau symbole
            prevToken = s;
            firstPrint = false;
        }

        // on réinitialise les indicateurs d'analyse pour ce symbole
        errorFlag = false;
        consumed = false;

        Etat* etat = statestack.back();
        bool accepté = etat->transition(*this, s);

        if (errorFlag) {
            // arrêter le traitement en cas d'erreur syntaxique/lexicale
            if (verbose) printStack();
            break;
        }

        if (accepté && *(s) == FIN) {
            break;
        }
        if (verbose) printStack();
        // si le symbole a été consommé par décalage() le lexer avance, sinon il reste pour l’itération suivante
        if (consumed) {
            prevToken = nullptr;
            firstPrint = true;
        }
    }
    Expr* final_expr = nullptr;
    if (!symbolstack.empty())
        final_expr = dynamic_cast<Expr*>(symbolstack.back());
    if (final_expr) {
        int result = final_expr->eval({});
        std::cout << "Résultat de l'expression : " << result << std::endl;
    } else {
        std::cout << "Erreur : expression invalide !" << std::endl;
    }
}

void Automate::decalage(Symbole * s, Etat * e) {
    symbolstack.push_back(s);
    statestack.push_back(e);
    lexer.Avancer();
    consumed = true;
}

void Automate::transitionsimple(Symbole * s, Etat * e) {
    symbolstack.push_back(s);
    statestack.push_back(e);
    consumed = false;
}

void Automate::reduction(int n,Symbole * s) {
    for (int i = 0; i < n; i++) {
        delete statestack.back();
        statestack.pop_back();
    }
    statestack.back()->transition(*this, s);
}

Symbole* Automate::popSymbol() {
    if (!symbolstack.empty()) {
        Symbole* s = symbolstack.back();
        symbolstack.pop_back();
        return s;
    }
    return nullptr;
}

void Automate::popAndDestroySymbol() {
    if (!symbolstack.empty()) {
        Symbole* s = symbolstack.back();
        symbolstack.pop_back();
        delete s;
    }
}

Automate::Automate(Lexer& lexer) : lexer(lexer) {
    statestack.push_back(new Etat0());
}

Automate::~Automate() {
    // nettoyage des piles d'états et de symboles
    for (Etat* e : statestack) {
        delete e;
    }
    statestack.clear();
    
    for (Symbole* s : symbolstack) {
        delete s;
    }
    symbolstack.clear();
}