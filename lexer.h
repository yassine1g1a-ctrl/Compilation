#pragma once

#include <string>
#include "symbole.h"
using namespace std;

class Lexer {

   public:
      Lexer(string s) : flux(s), tete(0), tampon(nullptr) { }
      ~Lexer() { if (tampon) delete tampon; }

      Symbole * Consulter();
      void Avancer();

   protected:
      string flux;
      size_t tete;     // int modifié en size_t pour enlever warnings
      Symbole * tampon;
};
