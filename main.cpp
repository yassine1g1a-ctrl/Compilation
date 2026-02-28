#include <iostream>
#include <string>
#include "lexer.h"
#include "automate.h"

using namespace std;

int main(void) {
   string chaine;
   cout << "Entrez une expression arithmetique : ";
   getline(cin, chaine);

   Lexer lexer(chaine);
   Automate automate(lexer);
   automate.lecture();

   return 0;
}

