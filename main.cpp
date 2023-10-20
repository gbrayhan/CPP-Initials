#include <iostream>

class Animal {
public:
    virtual void hablar() {
        std::cout << "Algún sonido" << std::endl;
    }
};

class Perro : public Animal {
public:
    void hablar() override {
        std::cout << "Guau" << std::endl;
    }
};





int main() {

    int entero = 10;
    float flotante = 5.3;
    char caracter = 'A';
    bool condicion = true;



    Perro p;
    p.hablar();  // Imprime "Guau"

    std::cout << "¡Hola, mundo!" << std::endl;
    return 0;

}