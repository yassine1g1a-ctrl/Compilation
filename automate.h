#ifndef AUTOMATE_H
#define AUTOMATE_H

#include "etats.h"
#include "lexer.h"
#include "symbole.h"

class Automate {
    public:
        Automate(Lexer& lexer);
        virtual ~Automate() {};
        void decalage(Symbole * s, Etat * e);
        void transitionsimple(Symbole * s, Etat * e);
        void reduction(int n,Symbole * s);
        void lecture();
        Symbole* popSymbol();
        void popAndDestroySymbol();

    protected:
        stack<Etat*> statestack;
        stack<Symbole*> symbolstack;
        Lexer& lexer;
};

#endif