#include <iostream>
#include <string>
#include "lexer.h"
#include "automate.h"

using namespace std;

int main(void) {
   string chaine("(1+34)*123");

   Lexer l(chaine);

   Symbole * s;
   while (*(s = l.Consulter()) != FIN) {
      s->Affiche();
      cout << endl;
      l.Avancer();
   }

   // rebuild lexer for parsing since the previous loop consumed all tokens
   Lexer l2(chaine);
   Automate automate(l2);
   automate.lecture();

   return 0;
}

