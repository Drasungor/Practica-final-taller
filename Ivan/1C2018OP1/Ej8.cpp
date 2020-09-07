/* La clase Oracion utiliza un char *a para almacenar un string terminado en \0.
Escriba la declaracion de esta clase no olvidando: constructor por default,
constructor por copia, operadores +, -, =, >> y <<.
Implemente el operador = y el operador -. Este ultimo debe eliminar de la primer
cadena todas las ocurrencias de la segunda.*/

#include<iostream>

class Oracion {
private:
    char *a;

public:
    Oracion() = default;
    Oracion(const Oracion& other);//Constructor por copia

    Oracion operator+(const Oracion& oracion);
    Oracion operator-(const Oracion& oracion) {

    }
    Oracion& operator=(const Oracion& oracion) {
        
    }
    friend std::ostream& operator>>(std::ostream& os, Oracion& oracion);
    friend std::istream& operator<<(std::istream& is, const Oracion& oracion);
};

int main(int argc, char** argv) {
    Oracion oracion;

    std::cin >> oracion;

    return 0;
}
