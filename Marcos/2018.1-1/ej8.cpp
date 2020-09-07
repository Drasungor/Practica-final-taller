/*8) La clase Oracion utiliza un char *a para almacenar un string terminado en \0.
Escriba la declaracion de esta clase no olvidando: constructor por default,
constructor por copia, operadores +, -, =, >> y <<.
Implemente el operador = y el operador -. Este ultimo debe eliminar de
la primer cadena todas las ocurrencias de la segunda.*/

/*Este ejercicio es nefasto. NE FAS TO.*/

#include <cstring>
#include <iostream>

class Oracion {
public:
    char* a;

public:
    Oracion() : a(nullptr) {}
    Oracion(const char* b) {
        if (b != nullptr) {
            int size = std::strlen(b) + 1;
            a = new char[size];
            memcpy(a, b, size);
        } else {
            a = nullptr;
        }
    }
    Oracion(const Oracion& other) {
        if (other.a != nullptr) {
            int size = std::strlen(other.a) + 1;
            a = new char[size];
            memcpy(a, other.a, size);
        } else {
            a = nullptr;
        }
    }

    Oracion operator+(const Oracion& other);

    Oracion operator-(const Oracion& other) {
        int ocurrences = 0;
        char* currOcurrence = std::strstr(a, other.a);
        while (currOcurrence != nullptr) {
            ++ocurrences;
            currOcurrence += std::strlen(other.a);
            currOcurrence = std::strstr(currOcurrence, other.a);
        }
        if (ocurrences = 0) {
            return *this;
        }

        Oracion result;
        result.a = new char[strlen(a) - strlen(other.a)*ocurrences + 1];
        memset(result.a, 0, strlen(a) - strlen(other.a)*ocurrences + 1);
        int i = 0;
        char* currByte = a;
        currOcurrence = std::strstr(a, other.a);

        while (*currByte != '\0') {

            if (currByte == currOcurrence) {
                currOcurrence += std::strlen(other.a);
                currByte = currOcurrence;
                currOcurrence = std::strstr(currOcurrence, other.a);
            } else {
                result.a[i] = *currByte;
                ++i;
                ++currByte;
            }
        }

        return result;
    }
    Oracion& operator=(const Oracion& other) {
        delete[] a;
        if (other.a != nullptr) {
            int size = std::strlen(other.a) + 1;
            a = new char[size];
            memcpy(a, other.a, size);
        } else {
            a = nullptr;
        }
        return *this;
    }
    friend std::ostream& operator<<(std::ostream& os, const Oracion& oracion);
    friend std::istream& operator>>(std::istream& is, Oracion& oracion);
    ~Oracion() {
        delete[] a;
    }
};

int main() {
    const char* x = "Hola andas como andas";
    Oracion oracion(x);
    oracion = oracion - "andas";
    std::cout << oracion.a << std::endl;
    return 0;
}