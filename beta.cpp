#include <string>
#include <iostream>

int main() {

    std::string teste {"um dois, tres quatro cinco"}, str1, str2;

    str1 = teste.substr(0, teste.find(" "));
    str2 = teste.substr(teste.find(" "), teste.size());

    std::cout << teste << std::endl;
    std::cout << str1 << std::endl;
    std::cout << str2 << std::endl;

    
}