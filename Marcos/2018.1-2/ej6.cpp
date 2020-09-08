/*6) Escriba una clase template llamada Sumador que reciba por constructor un vector
de elementos genericos. La clase Sumador debe incluir un metodo llamado sumar
que acumule los valores del tipo recibido y retorne un nuevo objeto del tipo generico.

Que restricciones se le piden al tipo generico en la definicion de Sumador?*/

#include <vector>
#include <iostream>

class Foo {
private:
    int number;

public:
    Foo(int x) {
        number = x;
    }

    Foo() {
        number = 0;
    }

    //Foo(const Foo& other) = delete;

    Foo& operator+=(const Foo& other) {
        number += other.number;
        return *this;
    }

    void print() {
        std::cout << number << std::endl;
    }

};

template <class T>
class Sumador {
private:
    std::vector<T> myElements;

public:
    Sumador(const std::vector<T>& elements) : myElements(elements) {}

    T sumar() const {
        T result{};
        for (auto & element : myElements) {
            result += element;
        }
        return result;
    }


};

int main() {
    std::vector<Foo> myVector = {1, 2, 3, 4};
    Sumador<Foo> sumador(myVector);
    sumador.sumar().print();
    return 0;
}

/*Las 3 condiciones para que el Sumador ande es que la clase con la que se complete
el template debe tener definidos un constructor default, el operador += y el constructor por
copia (para el constructor default y el de copia alcanza con no haberlos deleteado ya que
el compilador dara unos por default)*/