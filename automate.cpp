#include "automate.h"

void Automate::lecture() {
    Symbole* s;
    // debug helper: print state stack
    auto printStack = [&]() {
        cout << "[pile etats]";
        for (Etat* e : statestack) {
            cout << " " << e->getName();
        }
        cout << endl;
    };

    // read and process all symbols, including the final FIN
    Symbole *prevToken = nullptr;
    bool firstPrint = true;
    while (true) {
        s = lexer.Consulter();
        // avoid reprinting the same token when it remains on the input
        // after a reduction; the next loop iteration will see the same
        // symbol but we don't want to treat it as a fresh "lecture".
        if (s != prevToken || firstPrint) {
            cout << "-- lecture symbole " << Etiquettes[(int)*s];
            if ((int)*s == INT) {
                Entier* entier = (Entier*) s;
                cout << "(" << entier->getValeur() << ")";
            }
            cout << endl;
            // remember what we just printed
            prevToken = s;
            firstPrint = false;
        }

        // reset parsing flags for this symbol
        errorFlag = false;
        consumed = false;

        Etat* etat = statestack.back();
        bool accepté = etat->transition(*this, s);

        if (errorFlag) {
            // stop processing further symbols on syntax/lexical error
            printStack();
            break;
        }

        if (accepté && *(s) == FIN) {
            // final success
            break;
        }
        printStack();

        // if the symbol was consumed by a decalage(), the lexer has already advanced;
        // otherwise we leave it in place so that the next loop iteration will
        // re-process the same token (possibly after a reduction triggered above).
        if (consumed) {
            // lexer advanced, forget previous token so we reprint next one
            prevToken = nullptr;
            firstPrint = true;
        }
        // otherwise prevToken remains set and the duplicate print will be skipped
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
    // transitionsimple does not consume the input symbol
    consumed = false;
}

void Automate::reduction(int n,Symbole * s) {
    // reduction itself never consumes the current input symbol
    // (do **not** zero the flag here; a prior decalage may have set it and
    // subsequent reductions should preserve that information until the
    // next loop iteration.)
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
    // clean up state stack
    for (Etat* e : statestack) {
        delete e;
    }
    statestack.clear();
    
    // clean up symbol stack
    for (Symbole* s : symbolstack) {
        delete s;
    }
    symbolstack.clear();
}