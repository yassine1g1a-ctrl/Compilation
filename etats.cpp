#include "etats.h"

bool Etat0::transition(Automate & automate, Symbole * s) {
    switch ((int)*s){
        case INT:
            automate.decalage(s, new Etat3);
            break;
        case OPENPAR:
            automate.decalage(s, new Etat2);
            break;
        case EXPR:
            automate.transition(s, new Etat1);
            break;
        case ERREUR:
            cout << "Erreur lexicale" << endl;
            return false;
        case default:
            cout<<"Erreur de syntaxe"<<endl;
            break;
    }
    return false;
}
bool Etat1::transition(Automate & automate, Symbole * s) {
    switch((int)*s) {
        case PLUS:
            automate.decalage(s, new Etat4);
            break;
        case MULT:
            automate.decalage(s, new Etat5);
            break;
        case FIN:
            return true; // accepter
        case ERREUR:
            cout << "Erreur lexicale" << endl;
            return false;
        default:
            cout << "Erreur de syntaxe" << endl;
            break;
    }
    return false;
}

bool Etat2::transition(Automate & automate, Symbole * s) {
    switch((int)*s) {
        case INT:
            automate.decalage(s, new Etat3);
            break;
        case OPENPAR:
            automate.decalage(s, new Etat2);
            break;
        case EXPR:
            automate.transition(s, new Etat6);
            break;
        case ERREUR:
            cout << "Erreur lexicale" << endl;
            return false;
        default:
            cout << "Erreur de syntaxe" << endl;
            break;
    }
    return false;
}

bool Etat3::transition(Automate & automate, Symbole * s) {
    switch((int)*s) {
        case PLUS:
        case MULT:
        case CLOSEPAR:
        case FIN:
            Nombre * s1 = (Nombre*) automate.popSymbol();
            automate.reduction(1, s1);
            break;
        case ERREUR:
            cout << "Erreur lexicale" << endl;
            return false;
        default:
            cout << "Erreur de syntaxe" << endl;
            break;
    }
    return false;
}

bool Etat4::transition(Automate & automate, Symbole * s) {
    switch((int)*s) {
        case INT:
            automate.decalage(s, new Etat3);
            break;
        case OPENPAR:
            automate.decalage(s, new Etat2);
            break;
        case EXPR:
            automate.transition(s, new Etat7);
            break;
        case ERREUR:
            cout << "Erreur lexicale" << endl;
            return false;
        default:
            cout << "Erreur de syntaxe" << endl;
            break;
    }
    return false;
}

bool Etat5::transition(Automate & automate, Symbole * s) {
    switch((int)*s) {
        case INT:
            automate.decalage(s, new Etat3);
            break;
        case OPENPAR:
            automate.decalage(s, new Etat2);
            break;
        case EXPR:
            automate.transition(s, new Etat8);
            break;
        case ERREUR:
            cout << "Erreur lexicale" << endl;
            return false;
        default:
            cout << "Erreur de syntaxe" << endl;
            break;
    }
    return false;
}

bool Etat6::transition(Automate & automate, Symbole * s) {
    switch((int)*s) {
        case PLUS:
            automate.decalage(s, new Etat4);
            break;
        case MULT:
            automate.decalage(s, new Etat5);
            break;
        case CLOSEPAR:
            automate.decalage(s, new Etat9);
            break;
        case ERREUR:
            cout << "Erreur lexicale" << endl;
            return false;
        default:
            cout << "Erreur de syntaxe" << endl;
            break;
    }
    return false;
}

bool Etat7::transition(Automate & automate, Symbole * s) {
    switch((int)*s) {
        case MULT:
            automate.decalage(s, new Etat5);
            break;
        case PLUS:
        case CLOSEPAR:
        case FIN:
            Expr * s1 = (Expr*) automate.popSymbol();
            automate.popAndDestroySymbol();
            Expr * s2 = (Expr*) automate.popSymbol();
            automate.reduction(3, new ExprPlus(s2, s1));
            break;
        case ERREUR:
            cout << "Erreur lexicale" << endl;
            return false;
        default:
            cout << "Erreur de syntaxe" << endl;
            break;
    }
    return false;
}

bool Etat8::transition(Automate & automate, Symbole * s) {
    switch((int)*s) {
        case PLUS:
        case MULT:
        case CLOSEPAR:
        case FIN:
            Expr * s1 = (Expr*) automate.popSymbol();
            automate.popAndDestroySymbol();
            Expr * s2 = (Expr*) automate.popSymbol();
            automate.reduction(3, new ExprMult(s2, s1));
            break;
        case ERREUR:
            cout << "Erreur lexicale" << endl;
            return false;
        default:
            cout << "Erreur de syntaxe" << endl;
            break;
    }
    return false;
}

bool Etat9::transition(Automate & automate, Symbole * s) {
    switch((int)*s) {
        case PLUS:
        case MULT:
        case CLOSEPAR:
        case FIN:
            automate.popAndDestroySymbol();
            Expr * s1 = (Expr*) automate.popSymbol();
            automate.popAndDestroySymbol();
            automate.reduction(3, s1);
            break;
        case ERREUR:
            cout << "Erreur lexicale" << endl;
            return false;
        default:
            cout << "Erreur de syntaxe" << endl;
            break;
    }
    return false;
}