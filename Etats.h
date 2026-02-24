#include "Etat.h"

class Etat0 : public Etat {
public:
    Etat0() : Etat("E0") {}
    virtual ~Etat0() {}
    bool transition(Automate& automate, Symbole* s) override;
};