/*
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
////   _    _   ______   _____    ______   _        _        ______   _    _   ////
////  | |  / / |  __  | |  __ \  |  __  | | |      | |      |  __  | | |  | |  ////
////  | |./ /  | |__| | | |__| | | |__| | | |      | |      | |__| | | |__| |  ////
////  |    <   |  __  | |  __ <  |  __  | | |      | |      |  __  | |  __  |  ////
////  | |`\ \  | |  | | | |__| | | |  | | | |____  | |____  | |  | | | |  | |  ////
////  |_|  \_\ |_|  |_| |_____/  |_|  |_| |______| |______| |_|  |_| |_|  |_|  ////
////  _______________________________________________________________________  ////
////   ____________________________________________________________________    //// 
////                                                                           //// 
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
*/

#include <iostream>
#include <chrono>
#include "cartas.h" 
#include "batalha.h"

using namespace KabCartas;


int main() {
    srand(time(0));

    // para o baralho básico:
    // kaballah - poção de vida, benção, 
    // artefato - 
    // invocado - 

    std::chrono::time_point start1 = std::chrono::high_resolution_clock::now();

    KABALLAH ctBencao("Benção de Cromm", 0, 4, 4, 0, asciiRetratoTemp());
    KABALLAH ctTerremoto("Terremoto", 0, 0, 0, 0, asciiRetratoTemp());
    KABALLAH ctPocaoDeVida("Poção de Vida", 5, 0, 0, 0, asciiRtPocaodeVida());   
    ARTEFATO ctMachado("Machado de Guerra", 0, 5, 3, 0, asciiRetratoTemp());
    ARTEFATO ctCajadoMagico("Cajado Mágico", 0, 5, 2, 3, asciiCajado());  
    INVOCADO ctLoboAtroz("Dire Wolf", 10, 4, 3, 0, Classes::Beast, asciiLobo());
    INVOCADO ctGoblinMaldito("Goblin Maldito", 7, 3, 2, 4, Classes::Demon, asciiRetratoTemp());
    INVOCADO ctZumbi("Alexi, the Fallen", 7, 3, 0, 0, Classes::Undead, asciiRtZumbi());
    //INVOCADO ctVostradeis();

    std::chrono::time_point end1 = std::chrono::high_resolution_clock::now();

    std::chrono::duration<float> tempo = end1 - start1;
     
    std::cout << asciiBodomBemVindo() << std::endl; 
 
    std::chrono::time_point start2 = std::chrono::high_resolution_clock::now(); 
    INVENTARIO inv {};  
    unsigned int fill {}; 
    for (int i=0; i<5; i++) {
        fill = rand()%7+1; 
        switch (fill) {
            case 1: inv.addCarta(ctPocaoDeVida); break;
            case 2: inv.addCarta(ctGoblinMaldito); break;
            case 3: inv.addCarta(ctBencao); break;
            case 4: inv.addCarta(ctZumbi); break;
            case 5: inv.addCarta(ctMachado);; break;
            case 6: inv.addCarta(ctCajadoMagico); break;
            case 7: inv.addCarta(ctLoboAtroz); break; 
        }
    }
    std::chrono::time_point end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float>  tempo2 = end2 - start2;
    
    std::chrono::time_point start3 = std::chrono::high_resolution_clock::now();
    std::cout << inv; 
    std::chrono::time_point end3 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float>  tempo3 = end3 - start3;

    // std::cout << std::chrono::microseconds(sec).count() << " microseconds\n"

    std::cout << "Cartas:\t" << tempo.count() << std::endl;
    std::cout << "Vetor:\t" << tempo2.count() << std::endl;
    std::cout << "Print:\t" << tempo3.count() << std::endl;


    // AVATAR ctGabriel("Vostradeis, o mago", asciiAvatar());

    // ctGabriel.printCarta();



} // ~main