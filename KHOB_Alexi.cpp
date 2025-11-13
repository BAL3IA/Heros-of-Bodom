#include <iostream>
#include <vector>
#include <algorithm>
 
enum class Classes
    {
        Avatar,       //      
        Warrior,      //                
        Wizard,       //      
        Hunter,       //        
        Assassin,     //         
        Demon,        //     
        Beast,        //  
        Undead,       //   
        Artifact,     //    
        Kaballah      //           
    };

class CARTA;
 
std::string getLogo ();
std::string getRetrato ();
std::string getCarta ();
std::string getInfo ();
std::string asciiClasse (const Classes& cls);
void printInventario (std::vector<std::string>& vec);
void setAscii(const std::string &ss, std::string &carta, int *arr, Classes &cls, const std::string &ret);  
unsigned short charQuantos(const std::string &esp); 
bool charEspeciais(const std::string &esp);
  
class CARTA
{
    private: 
        std::string ascii{R"(
     ___________________ 
    |†_\_\_\_†††_/_/_/_†|
    ||%1               ||
    ||%2               ||
    ||%3               ||
    ||%4               ||
    ||%5               ||
    ||%6               ||
    |†/_/_/_†††††_\_\_\†|
    || %n              ||
    || %m              ||
    || %c              ||
    || ESS:%e   POT:%p ||
    || DEF:%d   WIS:%s ||
    |†/_/_†††††††††_\_\†|
     ``````````````````` 
)"};
        Classes classe{}; 
        std::string nome{};
        int atributos[4]{0}; 

    public:  
        
        CARTA() = default;

        CARTA(const std::string &nom, const int &ess, const int &pot,
              const int &def, const int &sab, const Classes &cls, const std::string &rt)
            : classe(cls), nome(nom), atributos{ess, pot, def, sab}  {

            setAscii(this->nome, this->ascii, this->atributos, this->classe, rt);
        } 

        std::string getCarta() const {

            return this->ascii;
        }
           
        void printCarta() const  {

            std::cout << ascii << "\n";
        } 

        void printAtributos() const {

            std::string temp {asciiClasse(this->classe)};
            temp = temp.substr(temp.rfind(' ')+1);

            std::cout << "  Name:    " << nome << "\n"
                << "  Class:   " << temp << "\n" 
                << "  Essence: " << atributos[0] << "\n"  
                << "  Potency: " << atributos[1] << "\n" 
                << "  Defense: " << atributos[2] << "\n" 
                << "  Wisdom:  " << atributos[3] << "\n\n";
        }
         
};


int main(int argc, char *argv[]) {

    bool mInventario {false}, mInfo {false}, mArtes {false}, mStats {false}, mCarta {false};

    unsigned long uInv {};
    
    CARTA cAlexi ("Alexi, the Death Strider", 7, 3, 1, 0, Classes::Undead, getRetrato()); 

    if (argc == 1) {

        std::cout << getLogo() << "\n\n";
        cAlexi.printCarta();

        std::cout << "\n" << getInfo();
 
        return 0;

    }

    else { 

        for (int i = 1; i < argc; i++) {

            std::string argTemp {argv[i]};
             
            if (std::string(argv[i])=="art") mArtes = true; 

            else if (std::all_of(argTemp.begin(), argTemp.end(), [](unsigned char c){ return std::isdigit(c);} )) {
                
                uInv = std::stoul(argv[i]);
                mInventario = true;
            }

            else if (std::string(argv[i])=="stats") mStats = true;

            else if (std::string(argv[i])=="card") mCarta = true;

            else if (std::string(argv[i])=="info") mInfo = true;

            else {

                std::cout <<    "\n PARAMETERS ARE:\n\n"
                          <<    " card, to print only this card\n\n"
                          <<    " info, to print only this program info\n\n" 
                          <<    " art, to look into the pieces that made this card\n\n"
                          <<    " stats, to also print this card's name and attributes outside the art\n\n"
                          <<    " number n between 1 and 4294967295, to print this card n times (fixed width of 6 cards)\n"
                          <<    "\t\t^tBE CAREFUL, AS THIS CREATES AN ART VECTOR AND WILL CONSUME MEMORY RELEATED TO n'S VALUE!\n\n";

                return -1;
            }
        }

        if (mCarta) {

            cAlexi.printCarta();

            return 0;
        }
        
        if (mInfo) {
            
            std::cout << getInfo();

            return 0; 
        }

        std::cout << getLogo() << "\n\n"; 

        if (mStats) cAlexi.printAtributos();

        if (mInventario==false) cAlexi.printCarta();

        if (mInventario==true) {

            std::vector<std::string> tempVec {};

            for (unsigned int i = 0; i < uInv; i++) {

                tempVec.emplace_back(cAlexi.getCarta()); 
            }
 
            printInventario(tempVec);
        }
 
        if (mArtes==true) {

            std::cout << getRetrato() << "\n" << getCarta();
        }   

        std::cout << "\n" << getInfo();   

        return 0;
    } 
}
 

std::string getLogo () {

    std::string ascii { R"(
                                 /:†††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††
                                ;.:†††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††
                                |.:††††¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨;††††
                                |.:††††    ``.                            .'            ;                         .; ;††††
                                |.:††††                                                                              ;††††
                                |.:††††     /††   /††   /††††††††   /†††††††     /††††††    /††††††††    /††††††     ;††††
                                |.:††††    | ††  | ††  | ††_____/  | ††__  ††   /††__  ††  | ††_____/   /††._  ††    ;††††
                                |.:††††    | ††  ; ††  | ††        | ††  \ ††  l ††  \ ††  | ††        | ††  \__/    ;††††
                                |.:††††    | ††††††††  | †††††     | †††††††/  | ††  | ††  ! †††††     ;  ††††††     ;††††
                                |.:††††    | ††__  ††  | ††__/  .; | ††__  ††  | ††  | ††  | ††__/      \____  ††    ;††††
                                |.:††††    l ††  | ††  | ††   .    l ††  \ ††  | ††  l ††  | ††         /††  \ ††    ;††††
                                |.:††††    | ††  | ††  | ††††††††  | ††  | ††  |  ††††††/  | ††††††††  l  ††††††/    ;††††
                                \.:††††    |__/  l__/  !__x_____/  |__/  |__/   \______/   l________/   \______/     ;††††
                                ;.:††††                                                                              ;††††
                                |.:††††       `,                 ,.`                        ,                  x     ;††††
                                |.:††††               /††            /††††††   /††††††††     ;     /††               ;††††
                                |.:††††              | ††           /††__  †† | ††_____/          | ††               ;††††
                                |.:††††  .       \\  | ††  //      l ††  \ †† ; ††            \\  | ††  //           ;††††
                                |.:††††              | ††          | ††  ; †† | †††††             | ††               ;††††
                                |.:††††           /††††††††††      | ††  | †† | ††__/    `     /††††††††††       ';  ;††††
                                |.:††††          |____/††___/   ,  | ††  ! †† | ††            |____/††___/           ;††††
                                |.:††††  ,.          | ††        . !  ††††††/ l ††                | ††               ;††††
                                |.:††††          //  |/_/  \\       \______/  l__/            //  |/_/  \\           ;††††
                                |.:††††                                                                              ;††††
                                l.:††††                                           ,;                                 ;††††
                                /.:††††         /†††††††     /††††††    /†††††††     /††††††    /††      /††         ;††††
                                |.:††††        l ††__  ††   /††__  ††  : ††__  ††   /††__  ††  | †††    /††† .,      ;††††
                                |.:††††        | ††  \ ††  | ††  \ ††  | ††  \ ††  | ††  \ ††  ! ††††  /††††      ,  ;††††
                                |.:††††     .: | †††††††   | ††  | ††  | ††  l ††  l ††  | ††  | †† ††/†† ††         ;††††
                                |.:††††    ,   | ††._  ††  | †† .| ††  ; ††  | ††  | ††  | ††  | ††  †††| ††         ;††††
                                '.:††††        | ††  \ ††  | ††  I ††  | ††  | ††  | ††  ! ††  : ††\  † | ††         ;††††
                                '.:††††        l †††††††/  l  ††††††/  | †††††††/  |  ††††††/  | †† \/  l ††         ;††††
                                |.:††††        |____x__/    \______/   l_______/    \_.____/   l__/   ` |__/         ;††††
                                |.:†††† :.                                       ``                           ,.     ;††††
                                |.:††††                 .                             ,.                             ;††††
                                |.:†††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††
                                |.:†††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††††
                                :/______/_________,_________________________________________.,,...._____//____________;__/
)"}; return ascii;  
}

std::string getRetrato () {

    std::string asciiAlexi {R"(
     z~''` ~``;\\
    ;~   ~~  ,)])
   (o) `(O )  })}
   (  !!    )`  )
    \nmnm ; / z |
       cwww  / `L
)"}; return asciiAlexi;
}
  
std::string getCarta () {

    std::string asciiCarta {R"(
     ___________________ 
    |†_\_\_\_†††_/_/_/_†|
    ||                 ||
    ||                 ||
    ||                 ||
    ||                 ||
    ||                 ||
    ||                 ||
    |†/_/_/_†††††_\_\_\†|
    ||                 ||
    ||                 ||
    ||                 ||
    || ESS:     POT:   ||
    || DEF:     WIS:   ||
    |†/_/_†††††††††_\_\†|
     ``````````````````` 
)"}; return asciiCarta;
}

std::string getInfo () {
    
    std::string info { R"(
 †††††††††††††††††††††††††††††††††††††
    
    Created by Gabriel F. Gonçalves
    
    e-mail: ccainnetto@gmail.com
    
    November 25, 2021

)"}; return info;
}

void setAscii(const std::string &ss, std::string &carta, int *arr, Classes &cls, const std::string &ret) {
    
        // Primeiro: acerto do nome 
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
            if (ss.length() < (long unsigned int)(15 + temp))
            {
                split[0] += ss;
                while (split[0].length() < (long unsigned int)(15 + temp))
                {
                    split[0] += " ";
                }
                split[1] += "               ";
                split[0].swap(split[1]);
            }

            // para nomes com exatamente 15 chars // problemas aqui com ACENTUACAO grafica
            else if (ss.length() == (long unsigned int)(15 + temp))
            {
                split[0] += ss;
                split[1] += "               ";
                split[0].swap(split[1]);
            }

            // para nomes maiores
            else if (ss.length() < (long unsigned int)(30 + temp))
            {
                int espacos = std::count(ss.begin(), ss.end(), ' ');
                // se tiver apenas um espaço em branco no nome
                if (espacos == 1)
                {
                    split[0] += ss.substr(0, ss.find(" "));
                    split[1] += ss.substr(ss.find(" ") + 1, ss.size());
                    while (split[0].length() < (long unsigned int)(15 + temp))
                    {
                        split[0] += " ";
                    }
                    while (split[1].length() < (long unsigned int)(15 + temp))
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
                    if (split[0].length() < (long unsigned int)(15 + temp))
                    {
                        while (split[0].length() < (long unsigned int)(15 + charQuantos(split[0])))
                        {
                            split[0] += " ";
                        }
                    }
                    // correcao de tamanho de split1 se houver caracteres especiais
                    if (charEspeciais(split[1]))
                    {
                        while (split[1].length() < (long unsigned int)(15 + charQuantos(split[1])))
                        {
                            split[1] += " ";
                        }
                    }
                    else
                    {
                        while (split[1].length() < (long unsigned int)(15 + charQuantos(split[1])))
                        {
                            split[1] += " ";
                        }
                    }
                    // se o tamanho de split0 for maior que 15, ocorre outra divisão e ajustamento
                    // com split1 + preenchimento de espaçoes em branco se houver
                    if (split[0].length() > (long unsigned int)(15 + temp))
                    {
                        split[1] = split[0].substr(split[0].rfind(" ") + 1, split[0].size()) +
                                   " " + ss.substr(ss.rfind(" ") + 1, ss.size() + temp);
                        split[0].erase(split[0].rfind(" "), split[0].size() + temp);
                        while (split[0].length() < (long unsigned int)(15 + charQuantos(split[0])))
                        {
                            split[0] += " ";
                        }
                        while (split[1].length() < (long unsigned int)(15 + charQuantos(split[1])))
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
                while (split[2].length() < (long unsigned int)(2))
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
                while (split[3].length() < (long unsigned int)(2))
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
                while (split[4].length() < (long unsigned int)(2))
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
                while (split[5].length() < (long unsigned int)(2))
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
         
        // Terceiro: acerto de classe
        split[6] += asciiClasse(cls);
         
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
        carta.replace(carta.find("%n"), 15, split[0]);
        carta.replace(carta.find("%m"), 15, split[1]);
        // classe
        carta.replace(carta.find("%c"), 15, split[6]);
        // atributos
        carta.replace(carta.find("%e"), 2, split[2]);
        carta.replace(carta.find("%p"), 2, split[3]);
        carta.replace(carta.find("%d"), 2, split[4]);
        carta.replace(carta.find("%s"), 2, split[5]);
        // retrato
        carta.replace(carta.find("%1"), 17, retrato[0]);
        carta.replace(carta.find("%2"), 17, retrato[1]);
        carta.replace(carta.find("%3"), 17, retrato[2]);
        carta.replace(carta.find("%4"), 17, retrato[3]);
        carta.replace(carta.find("%5"), 17, retrato[4]);
        carta.replace(carta.find("%6"), 17, retrato[5]);
    }
  
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
 
bool charEspeciais(const std::string &esp)
    {
        for (char c : esp)
        {
            if (!(c >= 0x20 && c <= 0x7e))
                return true;
        }
        return false;
    }
 
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

void printInventario (std::vector<std::string>& vec) {  
     
        unsigned int numCartas {(unsigned int)(vec.size())};  
        unsigned short contAcentos[6][3] {0};
        std::string mapa[6][3] {""};
        std::string tmp {R"()"}; 
        const int maxHor {6};  
        unsigned  int controle {0};  

        for (unsigned int i=numCartas; i>0; i -= 6) {
            
            // se o numero de cartas no vetor for maior do que cinco, imprime maxHor
            if (i>maxHor) {
                for (int j=0; j<16; j++) {  
                    for (int k=0; k<maxHor; k++) {
                        // o acesso de cartas por vetor no loop exterior deve "andar" n cartas = maxHor
                        tmp = vec[k + numCartas - i ];
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

                for (unsigned int j=0; j<16; j++) {  
                    for (unsigned int k=0; k<numCartas - (controle*6) ; k++) { 
                        tmp = vec[k + numCartas - i];
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

            if (i<maxHor) break;
        }
    
        std::cout << "\n"; 
}    