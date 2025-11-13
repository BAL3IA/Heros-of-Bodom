#ifndef CARTAS_H
#define CARTAS_H

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <iomanip>
#include <vector>
#include <ctime>
#include "ascii.h"

namespace KabCartas
{ 
    
    // diferentes classes para as cartas de Invocados
    enum class Classes
    {
        Avatar,
        Warrior,
        Wizard,
        Hunter,
        Assassin,
        Demon,
        Beast, 
        Undead,
        Artifact,
        Kaballah
    };
    
    // predecçaracoes de classe
    class CARTA; class AVATAR; class Classe; class KABALLAH; 
    class INVOCADO; class ARTEFATO; class INVENTARIO; class BATALHA;
    
    // predeclaração de funções
    void printInventario (INVENTARIO& inv);
    bool charEspeciais(const std::string &esp);
    std::string asciiClasse(const Classes &cls);
    unsigned short charQuantos(const std::string &esp);
    void setAscii(const std::string &ss, ASCII &carta, int *arr, 
                  Classes &cls, const std::string &ret);

     
    // super classe das cartas
    class CARTA
    {
    private:
        // ascii art da carta
        ASCII ascii{asciiCarta()};
        Classes classe{};
        // atributos são: Essencia, Potencia, Defesa e Sabedoria
        std::string nome{};
        int atributos[4]{0};
        //
    public:
        CARTA() = default;
        // parametros anteriores: nome, 4 atributos, classe, ascii carta e retrato
        // parametros: nome, 4 atributos, classe, retrato

        CARTA(const std::string &nom, const int &ess, const int &pot,
              const int &def, const int &sab, const Classes &cls, const std::string &rt)
            : nome(nom), atributos{ess, pot, def, sab}, classe(cls) 
        {
            setAscii(this->nome, this->ascii, this->atributos, this->classe, rt);
        }
        virtual ~CARTA() {}
        // setters, getters e helpers
        void setAtributos(const int &a, const int &b, const int &c, const int &d)
        {
            this->atributos[0] = a;
            this->atributos[1] = b;
            this->atributos[2] = c;
            this->atributos[3] = d;
        }
        // retorna vetor de atributos
        std::vector<int> getAtributos() const
        {
            std::vector<int> temp{};
            temp.push_back(atributos[0]);
            temp.push_back(atributos[1]);
            temp.push_back(atributos[2]);
            temp.push_back(atributos[3]);
            temp.shrink_to_fit();
            return temp;
        }
        // print de ascii
        void printCarta() const
        {
            std::cout << ascii;
        }

        int getESS() { return this->atributos[0]; }
        int getPOT() { return this->atributos[1]; }
        int getDEF() { return this->atributos[2]; }
        int getSAB() { return this->atributos[3]; }
        std::string getNome() { return this->nome; }
        std::string getRetrato() { return this->ascii.asciiArt; }
        Classes getClasse() { return this->classe; }
        friend std::ostream &operator<<(std::ostream &obj, const CARTA &carta);
        friend void setAscii(const std::string &ss, ASCII &carta, CARTA &ct);

        bool operator== (const std::string&ss) {
            return (this->nome == ss)?true:false;
        }
    };

    // classe do inventario ## template? classe wraper para Kaballah e Artefato
    class INVENTARIO {
    private:
        std::vector<CARTA> inventario {};
    public:
        INVENTARIO() = default;
        INVENTARIO(const std::vector<CARTA> vec)
            : inventario(vec) {} 
        ~INVENTARIO() {}
        // adiciona carta ao vetor
        void addCarta(const CARTA& ct) {
            this->inventario.push_back(ct);
        }  
        // remove do vetor apenas uma ocorrencia da carta
        void removerCarta(const std::string& ss) {
            this->inventario.erase(std::remove(inventario.begin(), inventario.end(), ss));
        }
        // remove do vetor todas as ocorrencias da carta
        void removerTodas(const std::string& ss) {
            this->inventario.erase(std::remove(inventario.begin(), inventario.end(), ss), inventario.end());
        }
        // remove todos os itens do inventario
        void limparInventario() {
            this->inventario.clear();
        }
        // retorna o tamanho do vetor
        unsigned int printSize() {
            return this->inventario.size();
        }
        // retorna inventario como vetor de Cartas
        std::vector<CARTA> getInventario () const { return this->inventario; }
        friend std::ostream& operator<< (std::ostream&obj, const INVENTARIO& inv);
    };
  
    // classe do jogador
    class AVATAR : public CARTA
    { 
        const int vidaAvatar{20};  
        INVENTARIO inventario{};
        CARTA deck[20] {};

    public:
        AVATAR() = default;
        //AVATAR(const std::string &nom) : nome(nom) {}
        AVATAR (const std::string &nom, const std::string &asc)
            : CARTA(nom, 0, 0, 0, 0, Classes::Avatar, asc) {}
        ~AVATAR() {}
 
        void setDeck(const std::vector<CARTA>& vec) {
            for (int i=0; i<20; i++) {
                this->deck[i] = vec[i];
            }
        }
        int getVida() const { return this->vidaAvatar; } 
    };
     
    // atributos de classe ### revisar
    class CLASSE
    {
    private:
        // Atributos: Essencia, Potencia, Defesa, Sabedoria
        const int atributos[10][4]{
            // Guerreiro, Mago, Cacador, Assassino, Demonio, Fera, Besta, MortoVivo, Artefato, Kaballah
            {4, 2, 2, 0}, // Guerreiro
            {0, 2, 2, 4}, // Mago
            {0, 2, 4, 2}, // Cacador
            {0, 4, 2, 2}, // Assassino
            // distribuir os pontos abaixo corretamente
            {0, 2, 2, 4}, // Demonio
            {0, 2, 4, 2}, // Fera
            {0, 2, 2, 4}, // Besta
            {0, 2, 4, 2}, // MortoVivo
            {0, 2, 2, 4}, // Artefato
            {0, 2, 4, 2}, // Kaballah
        };

    public:
        void printClasse()
        {
        }
    };
     
    // classe das magias
    class KABALLAH : public CARTA
    {
    public:
        KABALLAH() = default;
        KABALLAH(const std::string &nom, const int &a, const int &b,
                 const int &c, const int &d, const std::string &asc)
            : CARTA(nom, a, b, c, d, Classes::Kaballah, asc) {}
        ~KABALLAH() {}
    };
    
    // classe dos antagonistas
    class INVOCADO : public CARTA
    {
    public:
        INVOCADO() = default;
        INVOCADO(const std::string &nom, const int &a, const int &b,
                 const int &c, const int &d, const Classes &cls,
                 const std::string &asc)
            : CARTA(nom, a, b, c, d, cls, asc) {}
        ~INVOCADO() {}
        //
    };
     
    // classe de itens
    class ARTEFATO : public CARTA
    {
    public:
        ARTEFATO() = default;
        ARTEFATO(const std::string &nom, const int &a, const int &b,
                 const int &c, const int &d, const std::string &asc)
            : CARTA(nom, a, b, c, d, Classes::Artifact, asc) {}
        ~ARTEFATO() {}
    };
  
 
    // funcao para gerar output sempre com o mesmo quadro da tela

   
    // funcao para inserir nome e atriutos da carta no ascii
    void setAscii(const std::string &ss, ASCII &carta, int *arr, 
                  Classes &cls, const std::string &ret)
    {
        //
        // Primeiro: acerto do nome //
        std::string split[7]{""};
        // primeira parte : para nomes sem caracteres especiais
        if (!(charEspeciais(ss)))
        {
            // para nomes menores que 15 chars
            if (ss.length() < 15)
            {
                split[0] += ss;
                while (split[0].length() < 15)
                {
                    split[0] += " ";
                }
                split[1] += "               ";
                split[0].swap(split[1]);
            }

            // para nomes com exatamente 15 chars // problemas aqui com ACENTUACAO grafica
            else if (ss.length() == 15)
            {
                split[0] += ss;
                split[1] += "               ";
                split[0].swap(split[1]);
            }

            // para nomes maiores
            else if (ss.length() < 30)
            {
                int espacos = std::count(ss.begin(), ss.end(), ' '); 
                // se tiver apenas um espaço em branco no nome
                if (espacos == 1)
                {
                    split[0] += ss.substr(0, ss.find(" "));
                    split[1] += ss.substr(ss.find(" ") + 1, ss.size());
                    while (split[0].length() < 15)
                    {
                        split[0] += " ";
                    }
                    while (split[1].length() < 15)
                    {
                        split[1] += " ";
                    }
                }
                // se tiver mais de um espaço em branco no nome
                if (espacos > 1)
                {
                    split[0] += ss.substr(0, ss.rfind(" "));
                    split[1] += ss.substr(ss.rfind(" ") + 1, ss.size());
                    // se o tamanho da de split0 for emenor que 15, completa com espacos em branco
                    if (split[0].length() < 15)
                    {
                        while (split[0].length() < 15)
                        {
                            split[0] += " ";
                        }
                        while (split[1].length() < 15)
                        {
                            split[1] += " ";
                        }
                    }
                    // se o tamanho de split0 for mais do que 15, ocorre outra divisão e ajustamento
                    // com split1 + preenchimento de espaçoes em branco se houver
                    if (split[0].length() > 15)
                    {
                        split[1] = split[0].substr(split[0].rfind(" ") + 1, split[0].size()) +
                                   " " + ss.substr(ss.rfind(" ") + 1, ss.size());
                        split[0].erase(split[0].rfind(" "), split[0].size());
                        while (split[0].length() < 15)
                        {
                            split[0] += " ";
                        }
                        while (split[1].length() < 15)
                        {
                            split[1] += " ";
                        }
                    }
                }
            }
        }
        // segunda parte: nomes com acentuação
        else
        {
            unsigned short temp{charQuantos(ss)};
            // para nomes menores que 15 chars
            if (ss.length() < 15 + temp)
            {
                split[0] += ss;
                while (split[0].length() < 15 + temp)
                {
                    split[0] += " ";
                }
                split[1] += "               ";
                split[0].swap(split[1]);
            }

            // para nomes com exatamente 15 chars // problemas aqui com ACENTUACAO grafica
            else if (ss.length() == 15 + temp)
            {
                split[0] += ss;
                split[1] += "               ";
                split[0].swap(split[1]);
            }

            // para nomes maiores
            else if (ss.length() < 30 + temp)
            {
                int espacos = std::count(ss.begin(), ss.end(), ' ');
                // se tiver apenas um espaço em branco no nome
                if (espacos == 1)
                {
                    split[0] += ss.substr(0, ss.find(" "));
                    split[1] += ss.substr(ss.find(" ") + 1, ss.size());
                    while (split[0].length() < 15 + temp)
                    {
                        split[0] += " ";
                    }
                    while (split[1].length() < 15 + temp)
                    {
                        split[1] += " ";
                    }
                }
                // se tiver mais de um espaço em branco no nome
                if (espacos > 1)
                {
                    split[0] += ss.substr(0, ss.rfind(" "));
                    split[1] += ss.substr(ss.rfind(" ") + 1, ss.size());
                    // se o tamanho da de split0 for menor que 15, completa com espacos em branco
                    if (split[0].length() < 15 + temp)
                    {
                        while (split[0].length() < 15 + charQuantos(split[0]))
                        {
                            split[0] += " ";
                        }
                    }
                    // correcao de tamanho de split1 se houver caracteres especiais
                    if (charEspeciais(split[1]))
                    {
                        while (split[1].length() < 15 + charQuantos(split[1]))
                        {
                            split[1] += " ";
                        }
                    }
                    else
                    {
                        while (split[1].length() < 15 + charQuantos(split[1]))
                        {
                            split[1] += " ";
                        }
                    }
                    // se o tamanho de split0 for maior que 15, ocorre outra divisão e ajustamento
                    // com split1 + preenchimento de espaçoes em branco se houver
                    if (split[0].length() > 15 + temp)
                    {
                        split[1] = split[0].substr(split[0].rfind(" ") + 1, split[0].size()) +
                                   " " + ss.substr(ss.rfind(" ") + 1, ss.size() + temp);
                        split[0].erase(split[0].rfind(" "), split[0].size() + temp);
                        while (split[0].length() < 15 + charQuantos(split[0]))
                        {
                            split[0] += " ";
                        }
                        while (split[1].length() < 15 + charQuantos(split[1]))
                        {
                            split[1] += " ";
                        }
                    }
                }
            }
        }
        //
        // Segundo: acerto dos atributos
        // Ess
        if (arr[0] == 0)
            split[2] += " ~";
        else
        {
            if (arr[0] < 10)
            {
                split[2] += std::to_string(arr[0]);
                while (split[2].length() < 2)
                {
                    split[2] += " ";
                }
                std::reverse(split[2].begin(), split[2].end());
            }
            else
            {
                split[2] += std::to_string(arr[0]);
            }
        }
        // Pot
        if (arr[1] == 0)
            split[3] += " ~";
        else
        {
            if (arr[1] < 10)
            {
                split[3] += std::to_string(arr[1]);
                while (split[3].length() < 2)
                {
                    split[3] += " ";
                }
                std::reverse(split[3].begin(), split[3].end());
            }
            else
            {
                split[3] += std::to_string(arr[1]);
            }
        }
        // Def
        if (arr[2] == 0)
            split[4] += " ~";
        else
        {
            if (arr[2] < 10)
            {
                split[4] += std::to_string(arr[2]);
                while (split[4].length() < 2)
                {
                    split[4] += " ";
                }
                std::reverse(split[4].begin(), split[4].end());
            }
            else
            {
                split[4] += std::to_string(arr[2]);
            }
        }
        // Sab
        if (arr[3] == 0)
            split[5] += " ~";
        else
        {
            if (arr[3] < 10)
            {
                split[5] += std::to_string(arr[3]);
                while (split[5].length() < 2)
                {
                    split[5] += " ";
                }
                std::reverse(split[5].begin(), split[5].end());
            }
            else
            {
                split[5] += std::to_string(arr[3]);
            }
        }
        //
        // Terceiro: acerto de classe
        split[6] += asciiClasse(cls);
        //
        // Quarto: retrato
        std::string retrato[6]{};
        retrato[0] = ret.substr(1, 17);
        retrato[1] = ret.substr(19, 17);
        retrato[2] = ret.substr(37, 17);
        retrato[3] = ret.substr(55, 17);
        retrato[4] = ret.substr(73, 17);
        retrato[5] = ret.substr(91, 17);

        // troca os trechos de ascii antecedidos por %
        // nome e sobrenome
        carta.asciiArt.replace(carta.asciiArt.find("%n"), 15, split[0]);
        carta.asciiArt.replace(carta.asciiArt.find("%m"), 15, split[1]);
        // classe
        carta.asciiArt.replace(carta.asciiArt.find("%c"), 15, split[6]);
        // atributos
        carta.asciiArt.replace(carta.asciiArt.find("%e"), 2, split[2]);
        carta.asciiArt.replace(carta.asciiArt.find("%p"), 2, split[3]);
        carta.asciiArt.replace(carta.asciiArt.find("%d"), 2, split[4]);
        carta.asciiArt.replace(carta.asciiArt.find("%s"), 2, split[5]);
        // retrato
        carta.asciiArt.replace(carta.asciiArt.find("%1"), 17, retrato[0]);
        carta.asciiArt.replace(carta.asciiArt.find("%2"), 17, retrato[1]);
        carta.asciiArt.replace(carta.asciiArt.find("%3"), 17, retrato[2]);
        carta.asciiArt.replace(carta.asciiArt.find("%4"), 17, retrato[3]);
        carta.asciiArt.replace(carta.asciiArt.find("%5"), 17, retrato[4]);
        carta.asciiArt.replace(carta.asciiArt.find("%6"), 17, retrato[5]);
    }
    
    // verifica se existem caractes especiais de uma string
    bool charEspeciais(const std::string &esp)
    {
        for (char c : esp)
        {
            if (!(c >= 0x20 && c <= 0x7e))
                return true;
        }
        return false;
    }
     
    // contagem de caracteres especiais
    unsigned short charQuantos(const std::string &esp)
    {
        unsigned short chars{0};
        for (char c : esp)
        {
            if (!(c >= 0x20 && c <= 0x7e))
            {
                chars++;
            }
        }
        return chars / 2;
    }
    
    // Guerreiro, Mago, Cacador, Assassino, Demonio, Fera, Besta, MortoVivo, Artefato, Kaballah
    std::string asciiClasse(const Classes &cls)
    {
        std::string temp{""};
        switch (cls)
        {
        case Classes::Avatar:
            temp += "       - Avatar";
            break;
        case Classes::Warrior:
            temp += "      - Warrior";
            break;
        case Classes::Wizard:
            temp += "       - Wizard";
            break;
        case Classes::Hunter:
            temp += "       - Hunter";
            break;
        case Classes::Assassin:
            temp += "     - Assassin";
            break;
        case Classes::Demon:
            temp += "        - Demon";
            break; 
        case Classes::Beast:
            temp += "        - Beast";
            break;
        case Classes::Undead:
            temp += "       - Undead";
            break;
        case Classes::Artifact:
            temp += "     - Artifact";
            break;
        case Classes::Kaballah:
            temp += "     - Kaballah";
            break;
        default:
            temp += "               ";
            break;
        }
        return temp;
    }

    // imprime todas as cartas de um inventario // POSSO DELETAR ESSA FUNCAO
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
  

    // overloads

    // cout para ascii de Carta
    std::ostream& operator<< (std::ostream& obj, const CARTA &carta)
    {
        obj << carta.ascii;
        return obj;
    }
    
    // cout para as Cartas no Inventario
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
                        case 1: obj << tmp.substr(27,35);  break;   
                        case 2: obj << tmp.substr(63,25);  break;
                        case 3: obj << tmp.substr(89,25);  break;
                        case 4: obj << tmp.substr(115,25);  break;
                        case 5: obj << tmp.substr(141,25);  break;
                        case 6: obj << tmp.substr(167,25);  break;
                        case 7: obj << tmp.substr(193,25);  break;
                        case 8: obj << tmp.substr(219,39);  break;  
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
                        case 1: obj << tmp.substr(27,35);  break;   
                        case 2: obj << tmp.substr(63,25);  break;
                        case 3: obj << tmp.substr(89,25);  break;
                        case 4: obj << tmp.substr(115,25);  break;
                        case 5: obj << tmp.substr(141,25);  break;
                        case 6: obj << tmp.substr(167,25);  break;
                        case 7: obj << tmp.substr(193,25);  break;
                        case 8: obj << tmp.substr(219,39);  break;  
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
 

}



#endif