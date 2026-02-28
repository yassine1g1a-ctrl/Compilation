#include <iostream>
#include <sstream>
#include <vector>
#include "automate.h"
using namespace std;

bool executerTest(string expression, double valeurAttendue, bool doitEchouer = false)
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
    bool ok;
    if (doitEchouer) {
        ok = output.find("Erreur") != string::npos || output.find("invalide") != string::npos;
        if (ok)
            cout << "(OK) ATTENDU: Erreur de syntaxe" << endl;
        else
            cout << "ERREUR: Expression acceptée alors qu'elle devrait échouer !" << endl;
    } else {
        ok = output.find("Résultat") != string::npos;
        if (ok)
            cout << "(OK) ATTENDU: " << valeurAttendue << endl;
        else
            cout << "ERREUR: Expression invalide alors qu'elle devrait être correcte !" << endl;
    }
    cout << "=========================\n";
    return ok;
}

int main()
{
    int total = 0, reussis = 0;
    vector<string> echoues;
    auto test = [&](string expr, double val, bool doitEchouer = false) {
        total++;
        if (executerTest(expr, val, doitEchouer)) {       
            reussis++;  
        } else {       
            echoues.push_back('"' + expr + '"');
        } 
    };

    cout << "\n========== DÉBUTS DES TESTS ==========\n";

    // Tests valides
    test("5+7", 12);
    test("5 + 7 ", 12);
    test("2*5", 10);
    test("(1+4)*6", 30);
    test("5+(8*2)", 21);
    test("(4+2)*(6+3)", 54);
    test("(4*12)+5*1*6+5", 73);
    test("5", 5);
    test("         7  ", 7);
    test("(5)", 5);
    test("((5))", 5);
    test("((5)+2)", 7);

    // Tests invalides
    test("+5", 0, true);
    test("5+", 0, true);
    test("()", 0, true);
    test("(5+7", 0, true);
    test("5++7", 0, true);
    test("5*/7", 0, true);
    test("abc+5", 0, true);
    test("5-4", 0, true);
    test("5/4", 0, true);
    test("8*", 0, true);
    test("*8", 0, true);
    test("", 0, true);

    cout << "\n========== FIN DES TESTS ==========\n";

    cout << "\n========== BILAN ==========\n";
    cout << "Total   : " << total << endl;
    cout << "Réussis : " << reussis << endl;
    cout << "Échoués : " << (total - reussis) << endl;
    if (!echoues.empty()) {
        cout << "Tests en échec :" << endl;
        for (const string& e : echoues)
            cout << "  - " << e << endl;
    }
    cout << "============================\n";

    return total - reussis;
}
