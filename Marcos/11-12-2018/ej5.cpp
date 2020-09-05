/*Ejemplifique que es y para que sirve una variable de clase (o atributo estatico)
en C++. Mediante un ejemplo de uso, indique como se define dicha variable,
su inicializacion y el acceso a su valor para realizar una impresion simple dentro
de un main*/

#include <iostream>

class Test {
private:
    static int number;

public:
    Test(int _number) {
        number = _number;
    }

    void printNumber() {
        std::cout << number << std::endl;
    }
};


int main () {
    Test x(3);
    x.printNumber();
    return 0;
}


int Test::number = 0;
