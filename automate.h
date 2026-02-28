#ifndef AUTOMATE_H
#define AUTOMATE_H

#include "etats.h"
#include "lexer.h"
#include "symbole.h"
#include <vector>

using namespace std;

class Automate {
    public:
        Automate(Lexer& lexer);
        virtual ~Automate();
        void decalage(Symbole * s, Etat * e);
        void transitionsimple(Symbole * s, Etat * e);
        void reduction(int n,Symbole * s);
        void lecture();
        Symbole* popSymbol();
        void popAndDestroySymbol();

        // aides pour analyser
        bool errorFlag = false;   // défini par les états lorsqu'une erreur syntaxique/lexicale survient
        bool consumed = false;    // si la dernière transition a consommé le symbole d'entrée
        bool verbose = false;     // affiche les détails de la pile si true

    protected:
        vector<Etat*> statestack;
        vector<Symbole*> symbolstack;
        Lexer& lexer;
};

#endif