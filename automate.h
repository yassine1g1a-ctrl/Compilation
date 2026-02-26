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

        // parsing helpers
        bool errorFlag = false;   // set by states when a syntax/lexical error occurs
        bool consumed = false;    // whether the last transition consumed the input symbol

    protected:
        vector<Etat*> statestack;
        vector<Symbole*> symbolstack;
        Lexer& lexer;
};

#endif