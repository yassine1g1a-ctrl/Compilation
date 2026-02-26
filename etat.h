#ifndef ETAT_H
#define ETAT_H

#include <iostream>
#include <string>
#include "symbole.h"

using namespace std;

class Automate;

class Etat {
    public:
        Etat(const string &name) : name(name) {}
        virtual ~Etat() {}
        void print() const { cout << "Etat : " << name << endl; }
        const string & getName() const { return name; }
        virtual bool transition(Automate & automate, Symbole * s) = 0;

    protected:
        string name;
};

#endif