#include "cartas.h"

using namespace KabCartas;

void printInventario (INVENTARIO& inv);

int main() {

    KABALLAH ctBencao("Benção de Cromm", 0, 4, 4, 0, asciiRetratoTemp()); 
    KABALLAH ctPocaoDeVida("Poção de Vida", 5, 0, 0, 0, asciiRtPocaodeVida()); 
    ARTEFATO ctCajadoMagico("Cajado Mágico", 0, 5, 2, 3, asciiRetratoTemp()); 
    INVOCADO ctLoboAtroz("Lobo Atroz", 10, 4, 3, 0, Classes::Fera, asciiRetratoTemp());
    INVOCADO ctGoblinMaldito("Goblin Maldito", 7, 3, 2, 4, Classes::Demonio, asciiRetratoTemp());
    INVOCADO ctMagoDasTrevas("Alexi, o Tombado", 7, 3, 0, 0, Classes::MortoVivo, asciiRtZumbi());
    
    std::vector<CARTA> vec {};

    vec.push_back(ctPocaoDeVida); 
    vec.push_back(ctBencao); 
    vec.push_back(ctGoblinMaldito);  
    vec.push_back(ctMagoDasTrevas);
    vec.push_back(ctCajadoMagico);

    for (int i = 0; i < 11; i++) 
        vec.push_back(ctPocaoDeVida);

    vec.push_back(ctLoboAtroz);
    vec.push_back(ctLoboAtroz);
    vec.push_back(ctLoboAtroz);

    INVENTARIO inventario(vec);

   // printInventario(inventario);
    
      
}
std::ostream& operator<< (std::ostream& obj, const INVENTARIO& inv) {
    
    std::vector<CARTA> vec {inv.getInventario()};
    int numCartas {static_cast<int>(vec.size())};  
    unsigned short contAcentos[5][3] {0};
    std::string mapa[5][3] {""};
    std::string tmp {R"()"}; 
    const int maxHor {5};  
    int controle {0};

    for (int i=numCartas; i>0; i -= 5) {
        // se o numero de cartas no vetor for maior do que cinco, imprime inco
        if (i>maxHor) {
            for (int j=0; j<16; j++) {  
                for (int k=0; k<maxHor; k++) {
                    // o acesso de cartas por vetor no loop exterior deve "andar" 5 cartas
                    tmp = vec[k + numCartas - i ].getRetrato();
                    // linha por linha da carta. total = 16
                    switch (j) { 

                        case 0: obj << tmp.substr(1,25);  break;
                        case 1: obj << tmp.substr(27,35);  break;  // 5x T
                        case 2: obj << tmp.substr(63,25);  break;
                        case 3: obj << tmp.substr(89,25);  break;
                        case 4: obj << tmp.substr(115,25);  break;
                        case 5: obj << tmp.substr(141,25);  break;
                        case 6: obj << tmp.substr(167,25);  break;
                        case 7: obj << tmp.substr(193,25);  break;
                        case 8: obj << tmp.substr(219,39);  break; // 7x T 
                        // casos com caracteres especiais da linha 9 a 11
                        case 9: {
                            // marcador para achar o ultimo caracter %c independente do numero de char especiais
                            size_t marcador = tmp.find(" ||\n    || ESS");
                            // parse de tmp - do primeiro caractere de %n até o último de %c
                            std::string base {tmp.substr(266, marcador - 266)}; 
                            // parse de base - %n
                            size_t marcador1 {base.find_first_of("\n")};
                            mapa[k][0] = base.substr(0,marcador1-3); 
                            // parse de base - %m 
                            mapa[k][1] = base.substr(marcador1+8);
                            size_t marcador2 {mapa[k][1].find_first_of("\n")};
                            mapa[k][1] = mapa[k][1].substr(0, marcador2-3);  
                            // parse de base - %c 
                            mapa[k][2] = base.substr(marcador2+8);
                            size_t marcador3 {base.rfind("\n")};
                            mapa[k][2] = mapa[k][2].substr(0, marcador3-3); 
                            size_t marcador4 {mapa[k][2].find_first_of("\n")};
                            mapa[k][2] = mapa[k][2].substr(marcador4+8); 
                            // preenchimento do array com contagem de acentos
                            contAcentos[k][0] = charQuantos(mapa[k][0]);
                            contAcentos[k][1] = charQuantos(mapa[k][1]);
                            contAcentos[k][2] = charQuantos(mapa[k][2]); 
                            obj << tmp.substr(259,25+contAcentos[k][0]); } break; 
                        case 10: obj << tmp.substr(285 + contAcentos[k][0], 25+contAcentos[k][1]); break;
                        case 11: obj << tmp.substr(311 + contAcentos[k][0] + contAcentos[k][1], 25 + contAcentos[k][2]); break;
                        // fim dos casos especiais        
                        case 12: obj << tmp.substr(337 + contAcentos[k][0] + contAcentos[k][1] + contAcentos[k][2],25);  break;
                        case 13: obj << tmp.substr(363 + contAcentos[k][0] + contAcentos[k][1] + contAcentos[k][2],25);  break;
                        case 14: obj << tmp.substr(389 + contAcentos[k][0] + contAcentos[k][1] + contAcentos[k][2],47);  break; // 11x T
                        case 15: obj << tmp.substr(437 + contAcentos[k][0] + contAcentos[k][1] + contAcentos[k][2],25);  break;

                    }
 
                } 
                obj << std::endl;
            } 
        } 
        // quando são menos de cinco cartas para imprir/ ou restam menos de cinco cartas para imprimir
        else {
            for (int j=0; j<16; j++) {  
                for (int k=0; k<numCartas - (controle*5) ; k++) { 
                    tmp = vec[k + numCartas - i].getRetrato();
                    // linha por linha da carta. total = 16
                    switch (j) {
                        
                        case 0: obj << tmp.substr(1,25);  break;
                        case 1: obj << tmp.substr(27,35);  break;  // 5x T
                        case 2: obj << tmp.substr(63,25);  break;
                        case 3: obj << tmp.substr(89,25);  break;
                        case 4: obj << tmp.substr(115,25);  break;
                        case 5: obj << tmp.substr(141,25);  break;
                        case 6: obj << tmp.substr(167,25);  break;
                        case 7: obj << tmp.substr(193,25);  break;
                        case 8: obj << tmp.substr(219,39);  break; // 7x T 
                        // casos com caracteres especiais da linha 9 a 11
                        case 9: {
                            // marcador para achar o ultimo caracter %c independente do numero de char especiais
                            size_t marcador = tmp.find(" ||\n    || ESS");
                            // parse de tmp - do primeiro caractere de %n até o último de %c
                            std::string base {tmp.substr(266, marcador - 266)}; 
                            // parse de base - %n
                            size_t marcador1 {base.find_first_of("\n")};
                            mapa[k][0] = base.substr(0,marcador1-3); 
                            // parse de base - %m 
                            mapa[k][1] = base.substr(marcador1+8);
                            size_t marcador2 {mapa[k][1].find_first_of("\n")};
                            mapa[k][1] = mapa[k][1].substr(0, marcador2-3);  
                            // parse de base - %c 
                            mapa[k][2] = base.substr(marcador2+8);
                            size_t marcador3 {base.rfind("\n")};
                            mapa[k][2] = mapa[k][2].substr(0, marcador3-3); 
                            size_t marcador4 {mapa[k][2].find_first_of("\n")};
                            mapa[k][2] = mapa[k][2].substr(marcador4+8); 
                            // preenchimento do array com contagem de acentos
                            contAcentos[k][0] = charQuantos(mapa[k][0]);
                            contAcentos[k][1] = charQuantos(mapa[k][1]);
                            contAcentos[k][2] = charQuantos(mapa[k][2]); 
                            obj << tmp.substr(259,25+contAcentos[k][0]); } break; 
                        case 10: obj << tmp.substr(285 + contAcentos[k][0], 25+contAcentos[k][1]); break;
                        case 11: std::cout << tmp.substr(311 + contAcentos[k][0] + contAcentos[k][1], 25 + contAcentos[k][2]); break;
                        // fim dos casos especiais        
                        case 12: obj << tmp.substr(337 + contAcentos[k][0] + contAcentos[k][1] + contAcentos[k][2],25);  break;
                        case 13: obj << tmp.substr(363 + contAcentos[k][0] + contAcentos[k][1] + contAcentos[k][2],25);  break;
                        case 14: obj << tmp.substr(389 + contAcentos[k][0] + contAcentos[k][1] + contAcentos[k][2],47);  break; // 11x T
                        case 15: obj << tmp.substr(437 + contAcentos[k][0] + contAcentos[k][1] + contAcentos[k][2],25);  break;

                    }
 
                } 
                obj << std::endl;
            } 
        
        }
        controle++;

    }
    return obj; 
}
/*
void printInventario (INVENTARIO& inv) {
    
    std::vector<CARTA> vec {inv.getInventario()};
    int numCartas {static_cast<int>(vec.size())};  
    unsigned short contAcentos[5][3] {0};
    std::string mapa[5][3] {""};
    std::string tmp {R"()"}; 
    const int maxHor {5};  
    int controle {0}; 

    std::cout << numCartas << std::endl;

    for (int i=numCartas; i>0; i -= 5) {
        // se o numero de cartas no vetor for maior do que cinco, imprime inco
        if (i>maxHor) {
            for (int j=0; j<16; j++) {  
                for (int k=0; k<maxHor; k++) {
                    // o acesso de cartas por vetor no loop exterior deve "andar" 5 cartas
                    tmp = vec[k + numCartas - i ].getRetrato();
                    // linha por linha da carta. total = 16
                    switch (j) { 

                        case 0: std::cout << tmp.substr(1,25);  break;
                        case 1: std::cout << tmp.substr(27,35);  break;  // 5x T
                        case 2: std::cout << tmp.substr(63,25);  break;
                        case 3: std::cout << tmp.substr(89,25);  break;
                        case 4: std::cout << tmp.substr(115,25);  break;
                        case 5: std::cout << tmp.substr(141,25);  break;
                        case 6: std::cout << tmp.substr(167,25);  break;
                        case 7: std::cout << tmp.substr(193,25);  break;
                        case 8: std::cout << tmp.substr(219,39);  break; // 7x T 
                        // casos com caracteres especiais da linha 9 a 11
                        case 9: {
                            // marcador para achar o ultimo caracter %c independente do numero de char especiais
                            size_t marcador = tmp.find(" ||\n    || ESS");
                            // parse de tmp - do primeiro caractere de %n até o último de %c
                            std::string base {tmp.substr(266, marcador - 266)}; 
                            // parse de base - %n
                            size_t marcador1 {base.find_first_of("\n")};
                            mapa[k][0] = base.substr(0,marcador1-3); 
                            // parse de base - %m 
                            mapa[k][1] = base.substr(marcador1+8);
                            size_t marcador2 {mapa[k][1].find_first_of("\n")};
                            mapa[k][1] = mapa[k][1].substr(0, marcador2-3);  
                            // parse de base - %c 
                            mapa[k][2] = base.substr(marcador2+8);
                            size_t marcador3 {base.rfind("\n")};
                            mapa[k][2] = mapa[k][2].substr(0, marcador3-3); 
                            size_t marcador4 {mapa[k][2].find_first_of("\n")};
                            mapa[k][2] = mapa[k][2].substr(marcador4+8); 
                            // preenchimento do array com contagem de acentos
                            contAcentos[k][0] = charQuantos(mapa[k][0]);
                            contAcentos[k][1] = charQuantos(mapa[k][1]);
                            contAcentos[k][2] = charQuantos(mapa[k][2]); 
                            std::cout << tmp.substr(259,25+contAcentos[k][0]); } break; 
                        case 10: std::cout << tmp.substr(285 + contAcentos[k][0], 25+contAcentos[k][1]); break;
                        case 11: std::cout << tmp.substr(311 + contAcentos[k][0] + contAcentos[k][1], 25 + contAcentos[k][2]); break;
                        // fim dos casos especiais        
                        case 12: std::cout << tmp.substr(337 + contAcentos[k][0] + contAcentos[k][1] + contAcentos[k][2],25);  break;
                        case 13: std::cout << tmp.substr(363 + contAcentos[k][0] + contAcentos[k][1] + contAcentos[k][2],25);  break;
                        case 14: std::cout << tmp.substr(389 + contAcentos[k][0] + contAcentos[k][1] + contAcentos[k][2],47);  break; // 11x T
                        case 15: std::cout << tmp.substr(437 + contAcentos[k][0] + contAcentos[k][1] + contAcentos[k][2],25);  break;

                    }
 
                } 
                std::cout << std::endl;
            } 
        } 
        // quando são menos de cinco cartas para imprir/ ou restam menos de cinco cartas para imprimir
        else {
            for (int j=0; j<16; j++) {  
                for (int k=0; k<numCartas - (controle*5) ; k++) { 
                    tmp = vec[k + numCartas - i].getRetrato();
                    // linha por linha da carta. total = 16
                    switch (j) {
                        
                        case 0: std::cout << tmp.substr(1,25);  break;
                        case 1: std::cout << tmp.substr(27,35);  break;  // 5x T
                        case 2: std::cout << tmp.substr(63,25);  break;
                        case 3: std::cout << tmp.substr(89,25);  break;
                        case 4: std::cout << tmp.substr(115,25);  break;
                        case 5: std::cout << tmp.substr(141,25);  break;
                        case 6: std::cout << tmp.substr(167,25);  break;
                        case 7: std::cout << tmp.substr(193,25);  break;
                        case 8: std::cout << tmp.substr(219,39);  break; // 7x T 
                        // casos com caracteres especiais da linha 9 a 11
                        case 9: {
                            // marcador para achar o ultimo caracter %c independente do numero de char especiais
                            size_t marcador = tmp.find(" ||\n    || ESS");
                            // parse de tmp - do primeiro caractere de %n até o último de %c
                            std::string base {tmp.substr(266, marcador - 266)}; 
                            // parse de base - %n
                            size_t marcador1 {base.find_first_of("\n")};
                            mapa[k][0] = base.substr(0,marcador1-3); 
                            // parse de base - %m 
                            mapa[k][1] = base.substr(marcador1+8);
                            size_t marcador2 {mapa[k][1].find_first_of("\n")};
                            mapa[k][1] = mapa[k][1].substr(0, marcador2-3);  
                            // parse de base - %c 
                            mapa[k][2] = base.substr(marcador2+8);
                            size_t marcador3 {base.rfind("\n")};
                            mapa[k][2] = mapa[k][2].substr(0, marcador3-3); 
                            size_t marcador4 {mapa[k][2].find_first_of("\n")};
                            mapa[k][2] = mapa[k][2].substr(marcador4+8); 
                            // preenchimento do array com contagem de acentos
                            contAcentos[k][0] = charQuantos(mapa[k][0]);
                            contAcentos[k][1] = charQuantos(mapa[k][1]);
                            contAcentos[k][2] = charQuantos(mapa[k][2]); 
                            std::cout << tmp.substr(259,25+contAcentos[k][0]); } break; 
                        case 10: std::cout << tmp.substr(285 + contAcentos[k][0], 25+contAcentos[k][1]); break;
                        case 11: std::cout << tmp.substr(311 + contAcentos[k][0] + contAcentos[k][1], 25 + contAcentos[k][2]); break;
                        // fim dos casos especiais        
                        case 12: std::cout << tmp.substr(337 + contAcentos[k][0] + contAcentos[k][1] + contAcentos[k][2],25);  break;
                        case 13: std::cout << tmp.substr(363 + contAcentos[k][0] + contAcentos[k][1] + contAcentos[k][2],25);  break;
                        case 14: std::cout << tmp.substr(389 + contAcentos[k][0] + contAcentos[k][1] + contAcentos[k][2],47);  break; // 11x T
                        case 15: std::cout << tmp.substr(437 + contAcentos[k][0] + contAcentos[k][1] + contAcentos[k][2],25);  break;

                    }
 
                } 
                std::cout << std::endl;
            } 
        
        }
        controle++;

    }
 
}

*/



    // std::cout << "Tamanhado do vetor: " << vec.size() << std::endl;

    // int controle {static_cast<int>(vec.size())}; 
    // std::string mapa[5][3] {""};
    // unsigned short contAcentos[5][3] {0};
    // const int maxHor {5}; 

    // std::string tmp {R"()"}; 
    // std::string tmp2 {""};
    // std::string tmp3 {""};  

    //     for (int j=0; j<16; j++) { 
            
    //         for (int k=0; k<maxHor; k++) {
                
    //             tmp = vec[k].getRetrato();
    //             // linha por linha da carta. total = 16
    //             switch (j) {
                    
    //                 case 0: std::cout << tmp.substr(1,25);  break;
    //                 case 1: std::cout << tmp.substr(27,35);  break;  // 5x T
    //                 case 2: std::cout << tmp.substr(63,25);  break;
    //                 case 3: std::cout << tmp.substr(89,25);  break;
    //                 case 4: std::cout << tmp.substr(115,25);  break;
    //                 case 5: std::cout << tmp.substr(141,25);  break;
    //                 case 6: std::cout << tmp.substr(167,25);  break;
    //                 case 7: std::cout << tmp.substr(193,25);  break;
    //                 case 8: std::cout << tmp.substr(219,39);  break; // 7x T 
    //                 // casos com caracteres especiais da linha 9 a 11
    //                 case 9: {
    //                     // marcador para achar o ultimo caracter %c independente do numero de char especiais
    //                     size_t marcador = tmp.find(" ||\n    || ESS");
    //                     // parse de tmp - do primeiro caractere de %n até o último de %c
    //                     std::string base {tmp.substr(266, marcador - 266)}; 
    //                     // parse de base - %n
    //                     size_t marcador1 {base.find_first_of("\n")};
    //                     mapa[k][0] = base.substr(0,marcador1-3); 
    //                     // parse de base - %m 
    //                     mapa[k][1] = base.substr(marcador1+8);
    //                     size_t marcador2 {mapa[k][1].find_first_of("\n")};
    //                     mapa[k][1] = mapa[k][1].substr(0, marcador2-3);  
    //                     // parse de base - %c 
    //                     mapa[k][2] = base.substr(marcador2+8);
    //                     size_t marcador3 {base.rfind("\n")};
    //                     mapa[k][2] = mapa[k][2].substr(0, marcador3-3); 
    //                     size_t marcador4 {mapa[k][2].find_first_of("\n")};
    //                     mapa[k][2] = mapa[k][2].substr(marcador4+8); 
    //                     // preenchimento do array com contagem de acentos
    //                     contAcentos[k][0] = charQuantos(mapa[k][0]);
    //                     contAcentos[k][1] = charQuantos(mapa[k][1]);
    //                     contAcentos[k][2] = charQuantos(mapa[k][2]); 
    //                     std::cout << tmp.substr(259,25+contAcentos[k][0]); } break; 
    //                 case 10: std::cout << tmp.substr(285 + contAcentos[k][0], 25+contAcentos[k][1]); break;
    //                 case 11: std::cout << tmp.substr(311 + contAcentos[k][0] + contAcentos[k][1], 25 + contAcentos[k][2]); break;
    //                 // fim dos casos especiais        
    //                 case 12: std::cout << tmp.substr(337 + contAcentos[k][0] + contAcentos[k][1] + contAcentos[k][2],25);  break;
    //                 case 13: std::cout << tmp.substr(363 + contAcentos[k][0] + contAcentos[k][1] + contAcentos[k][2],25);  break;
    //                 case 14: std::cout << tmp.substr(389 + contAcentos[k][0] + contAcentos[k][1] + contAcentos[k][2],47);  break; // 11x T
    //                 case 15: std::cout << tmp.substr(437 + contAcentos[k][0] + contAcentos[k][1] + contAcentos[k][2],25);  break;

    //             }

                
    //         } 
    //         std::cout << std::endl;
    //     }

/*
#include <iostream>
#include <string>
#include <algorithm>
#include "cartas.h"

using namespace KabCartas;

bool Especiais (const std::string& esp);


int main() {

    std::string teste{"Bencção de Crom"};

    std::cout << Especiais(teste) << std::endl;

    std::cout << charQuantos(teste) << std::endl;

    // ASCII mago(asciiTemp());
    // ASCII bruxo(asciiTemp());
    // ASCII capeta(asciiTemp());
    // ASCII santo(asciiTemp()); 

    // std::string nome {"Mago Trevoso da silva"};
    // std::string nom2 {"Luis da Silva"};
    // std::string nom3 {"Benedita Afrontosa"};
    // std::string nom4 {"Lui Di Pin Fu Shu Zeng"};


    // setAscii(nome, mago);
    // setAscii(nom2, bruxo);
    // setAscii(nom3, capeta);
    // setAscii(nom4, santo);


    // std::cout << mago << std::endl;
    // std::cout << bruxo << std::endl;
    // std::cout << capeta << std::endl;
    // std::cout << santo << std::endl;



}
bool Especiais (const std::string& esp) { 
    
    for (char c : esp) {
        if(!(c>=0x20 && c<=0x7e))
            return true; }
    return false;
} 

// void setAscii(const std::string& ss, ASCII& carta) {
  
//     std::string splitt[2] {"", ""};
//     // para nomes menores que 14 chars
//     if (ss.length()<14) {
//         splitt[0] += ss;
//         while (splitt[0].length()<14) {
//             splitt[0] += " "; }
//         splitt[1] += "              "; }
//     // para nomes com exatamente 14 chars
//     else if (ss.length()==14) {
//         splitt[0] += ss;
//         splitt[1] += "              "; }
//     // para nomes maiores 
//     else if (ss.length()>14 && ss.length()<28) {
//         int espacos = std::count(ss.begin(), ss.end(), ' ');

//     } 

//     std::cout << splitt[0] << " " << splitt[1] << std::endl;
//     carta.asciiArt.replace(carta.asciiArt.find("%n"), 14, splitt[0]);
//     carta.asciiArt.replace(carta.asciiArt.find("%m"), 14, splitt[1]);
 
// }

*/

/*
#include <iostream>
#include <algorithm>
#include "cartas.h"


//
// funcao para inserir nome e atriutos da carta no ascii
void splitNome(const std::string& ss ) {
  
    std::string splitt[2] {"", ""};

    // para nomes menores que 14 chars
    if (ss.length()<14) {
        splitt[0] += ss;
        while (splitt[0].length()<14) {
            splitt[0] += " "; }
        splitt[1] += "              "; 
        std::cout << splitt[0] << std::endl;
        std::cout << splitt[1] << std::endl;
        }

    // para nomes com exatamente 14 chars
    else if (ss.length()==14) {
        splitt[0] += ss;
        splitt[1] += "              ";
        std::cout << splitt[0] << std::endl;
        std::cout << splitt[1] << std::endl; }

    // para nomes maiores de 14 // max de 28
    else if (ss.length()>14 && ss.length()<28) {
        int espacos = std::count(ss.begin(), ss.end(), ' ');
        if (espacos==1) {
            splitt[0] = ss.substr(0, ss.find(" "));
            size_t temp = splitt[0].size();
            size_t temp2 = ss.length();
            splitt[1] = ss.substr(temp, temp2);
            }
        else if (espacos>2) {
            splitt[0] = ss.substr(0, ss.rfind(" "));
            size_t temp = splitt[0].size();
            size_t temp2 = ss.length();
            splitt[1] = ss.substr(temp, temp2);
        }
        
        std::cout << splitt[0] << std::endl;
        std::cout << splitt[1] << std::endl;
 
    }

}

void splitNome(const std::string& ss, KabCartas::ASCII& carta) {
  
    std::string splitt[2] {"", ""};

    // para nomes menores que 14 chars
    if (ss.length()<14) {
        splitt[0] += ss;
        while (splitt[0].length()<14) {
            splitt[0] += " "; }
        splitt[1] += "              "; 
        std::cout << splitt[0] << std::endl;
        std::cout << splitt[1] << std::endl;
        }

    // para nomes com exatamente 14 chars
    else if (ss.length()==14) {
        splitt[0] += ss;
        splitt[1] += "              ";
        std::cout << splitt[0] << std::endl;
        std::cout << splitt[1] << std::endl; }

    // para nomes maiores de 14 // max de 28
    else if (ss.length()>14 && ss.length()<28) {
        int espacos = std::count(ss.begin(), ss.end(), ' ');
        if (espacos==1) {
            splitt[0] = ss.substr(0, ss.find(" "));
            size_t temp = splitt[0].size();
            size_t temp2 = ss.length();
            splitt[1] = ss.substr(temp, temp2);
            }
        else if (espacos>2) {
            splitt[0] = ss.substr(0, ss.rfind(" "));
            size_t temp = splitt[0].size();
            size_t temp2 = ss.length();
            splitt[1] = ss.substr(temp, temp2);
        }
        
        std::cout << splitt[0] << std::endl;
        std::cout << splitt[1] << std::endl;
 
    }
    // carta.replace(carta.find("%n"), 14, splitt[0]);
    // carta.replace(carta.find("%m"), 14, splitt[1]);
}

    int main() {

        std::string teste {"Lula Bento da Silva"};

        std::cout << teste.length() << "\n" << teste.size() << std::endl;

        std::cout << ".------------." << std::endl;

        splitNome(teste);
    }
    */