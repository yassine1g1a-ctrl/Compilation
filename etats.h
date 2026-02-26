#ifndef ETATS_H
#define ETATS_H

#include "etat.h"

// forward declarations to break circular dependency
class Automate;
class Symbole;

class Etat0 : public Etat {
    public:
        Etat0() : Etat("E0") {}
        virtual ~Etat0() {}
        bool transition(Automate& automate, Symbole* s) override;
};


class Etat1 : public Etat {
    public:
        Etat1() : Etat("E1") {}
        virtual ~Etat1() {}
        bool transition(Automate& automate, Symbole* s) override;
};

class Etat2 : public Etat {
    public:
        Etat2() : Etat("E2") {}
        virtual ~Etat2() {}
        bool transition(Automate& automate, Symbole* s) override;
};

class Etat3 : public Etat {
    public:
        Etat3() : Etat("E3") {}
        virtual ~Etat3() {}
        bool transition(Automate& automate, Symbole* s) override;
};

class Etat4 : public Etat {
    public:
        Etat4() : Etat("E4") {}
        virtual ~Etat4() {}
        bool transition(Automate& automate, Symbole* s) override;
};

class Etat5 : public Etat {
    public:
        Etat5() : Etat("E5") {}
        virtual ~Etat5() {}
        bool transition(Automate& automate, Symbole* s) override;
};

class Etat6 : public Etat {
    public:
        Etat6() : Etat("E6") {}
        virtual ~Etat6() {}
        bool transition(Automate& automate, Symbole* s) override;
};

class Etat7 : public Etat {
    public:
        Etat7() : Etat("E7") {}
        virtual ~Etat7() {}
        bool transition(Automate& automate, Symbole* s) override;
};

class Etat8 : public Etat {
    public:
        Etat8() : Etat("E8") {}
        virtual ~Etat8() {}
        bool transition(Automate& automate, Symbole* s) override;
};

class Etat9 : public Etat {
    public:
        Etat9() : Etat("E9") {}
        virtual ~Etat9() {}
        bool transition(Automate& automate, Symbole* s) override;
};

#endif