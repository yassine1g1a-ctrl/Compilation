#pragma once

#include <string>
#include <map>
#include <iostream>
using namespace std;

enum Identificateurs { OPENPAR, CLOSEPAR, PLUS, MULT, INT, FIN, ERREUR, EXPR };

const string Etiquettes[] = { "OPENPAR", "CLOSEPAR", "PLUS", "MULT", "INT", "FIN", "ERREUR", "EXPR" };

class Symbole {
   public:
      Symbole(int i) : ident(i) {  }
      virtual ~Symbole() { }
      operator int() const { return ident; }
      virtual void Affiche();
      int getType() const { return ident; };

   protected:
      int ident;
};

class Entier : public Symbole {
   public:
      Entier(int v) : Symbole(INT), valeur(v) { }
      ~Entier() { }
      virtual void Affiche();
      int getValeur() const { return valeur; }
   protected:
      int valeur;
};

class Expr: public Symbole {
   public:
      Expr() : Symbole(EXPR) { }
      virtual ~Expr() {}
      virtual double eval(const map<string, double> &valeurs) const = 0;
};

class ExprEntier : public Expr
{
public:
   ExprEntier(int v) : valeur(v) {}
   double eval(const std::map<std::string, double> &valeurs) const override
   {
      (void)valeurs;
      return valeur;
   }

   void Affiche() override
   {
      cout << valeur;
   }

private:
   int valeur;
};

class ExprBin : public Expr
{
public:
    // Le constructeur prend les deux opérandes comme dans le schéma
    ExprBin(Expr *g, Expr *d) : gauche(g), droite(d) {}
    
    // Le destructeur s'occupe de nettoyer la mémoire
    virtual ~ExprBin()
    {
        delete gauche;
        delete droite;
    }
    virtual void Affiche() override = 0;

protected:
    Expr *gauche;
    Expr *droite;
};

class ExprPlus : public ExprBin
{
public:
    // On passe les pointeurs à la classe parente ExprBin
    ExprPlus(Expr *g, Expr *d) : ExprBin(g, d) {}

    double eval(const map<string, double> &valeurs) const override
    {
        // On utilise les pointeurs hérités de ExprBin
        return gauche->eval(valeurs) + droite->eval(valeurs);
    }

    void Affiche() override
    {
        cout << "(";
        gauche->Affiche();
        cout << " + ";
        droite->Affiche();
        cout << ")";
    }
};

class ExprMult : public ExprBin
{
public:
    ExprMult(Expr *g, Expr *d) : ExprBin(g, d) {}

    double eval(const map<string, double> &valeurs) const override
    {
        return gauche->eval(valeurs) * droite->eval(valeurs);
    }

    void Affiche() override
    {
        cout << "(";
        gauche->Affiche();
        cout << " * ";
        droite->Affiche();
        cout << ")";
    }
};



