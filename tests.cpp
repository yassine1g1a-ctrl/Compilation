#include <iostream>
#include <sstream>
#include "automate.h"
using namespace std;

void executerTest(string expression, double valeurAttendue, bool doitEchouer = false)
{
    cout << "\n=========================\n";
    cout << "Test: " << expression << endl;

    Lexer lexer(expression);
    Automate automate(lexer);
    
    // capturer la sortie
    stringstream buffer;
    streambuf* old = cout.rdbuf(buffer.rdbuf());
    
    automate.lecture();
    
    cout.rdbuf(old);
    string output = buffer.str();
    
    // on teste la sortie correspond au comportement attendu (un résultat ou une erreur)
    if (doitEchouer) {
        if (output.find("Erreur") != string::npos || output.find("invalide") != string::npos) {
            cout << "(OK) ATTENDU: Erreur de syntaxe" << endl;
        } else {
            cout << "ERREUR: Expression acceptée alors qu'elle devrait échouer !" << endl;
        }
    } else {
        if (output.find("Résultat") != string::npos) {
            cout << "(OK) ATTENDU: " << valeurAttendue << endl;
        } else {
            cout << "ERREUR: Expression invalide alors qu'elle devrait être correcte !" << endl;
        }
    }
    cout << "=========================\n";
}

int main()
{
    cout << "\n========== DÉBUTS DES TESTS ==========\n";

    // Tests valides
    executerTest("5+7", 12);
    executerTest("5 + 7 ", 12);
    executerTest("2*5", 10);
    executerTest("(1+4)*6", 30);
    executerTest("5+(8*2)", 21);
    executerTest("(4+2)*(6+3)", 54);
    executerTest("(4*12)+5*1*6+5", 73);
    executerTest("5", 5);
    executerTest("         7  ", 7);
    executerTest("(5)", 5);
    executerTest("((5))", 5);
    executerTest("((5)+2)", 7);

    // Tests invalides
    executerTest("+5", 0, true);
    executerTest("5+", 0, true);
    executerTest("()", 0, true);
    executerTest("(5+7", 0, true);
    executerTest("5++7", 0, true);
    executerTest("5*/7", 0, true);
    executerTest("abc+5", 0, true);
    executerTest("5-4", 0, true);
    executerTest("5/4", 0, true);
    executerTest("8*", 0, true);
    executerTest("*8", 0, true);
    executerTest("", 0, true);

    cout << "\n========== FIN DES TESTS ==========\n";

    return 0;
}
