#ifndef BATALHA_H
#define BATALHA_H

#include "cartas.h"

namespace KabCartas
{

class BATALHA {

    std::string p1Nome {}, p2Nome {};
    CARTA p1Deck[20] {}, p2Deck[20] {};
    std::vector<CARTA> p1Mesa {}, p2Mesa {};

    unsigned short round {0};

public:
    BATALHA() = default;
    // BATALHA(const AVATAR& _1, const AVATAR& _2)
    //     : p1Nome(_1.getNome()), p2Nome(_2.getNome()), p1Deck(), p2Deck() {}
    ~BATALHA() {}
    

};




} // namespace KabCartas



#endif