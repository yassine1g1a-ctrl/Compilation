#include <iostream>
#include <string>
#include "lexer.h"
#include "automate.h"

using namespace std;

int main(int argc, char* argv[]) {
   bool verbose = false;
   for (int i = 1; i < argc; i++) {
      if (string(argv[i]) == "-v" || string(argv[i]) == "--verbose")
         verbose = true;
   }

   string chaine;
   cout << "Entrez une expression arithmetique : ";
   getline(cin, chaine);

   Lexer lexer(chaine);
   Automate automate(lexer);
   automate.verbose = verbose;
   automate.lecture();

   return 0;
}

