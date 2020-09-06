//Compilacion: g++ -std=c++11 -o ej_1 ej_1.cpp
//Ejecucion: ./ej_1 <prueba_carga

#include <iostream>

class Complejo {
private:
        int real;
        int imaginaria;

public:

        Complejo(int real, int imaginaria) {
                this->real = real;
                this->imaginaria = imaginaria;
        }

        Complejo(Complejo&& other) {
                this->real = other.real;
                other.real = 0;
                this->imaginaria = other.imaginaria;
                other.imaginaria = 0;
        }

        Complejo& operator++() {
                ++real;
                ++imaginaria;
                return *this;
        }

        Complejo operator++(int) {
                Complejo retorno(real, imaginaria);
                ++real;
                ++imaginaria;
                return retorno;
        }

        Complejo operator-(const Complejo& other) {
                Complejo retorno(real - other.imaginaria, imaginaria - other.imaginaria);
                return retorno;
        }

        operator float() {
                return real + imaginaria;
        }

        friend std::ostream& operator<<(std::ostream& out, const Complejo& comp);

        friend std::istream& operator>>(std::istream& in, Complejo& comp);

};

        std::ostream& operator<<(std::ostream& out, const Complejo& comp) {
                out << comp.real << " + " << comp.imaginaria << "i";
                return out;
        }

        std::istream& operator>>(std::istream& in, Complejo& comp) {
                std::string buffer;
                char aux;

                in >> aux;
                while(aux != '+') {
                        buffer.push_back(aux);
                        in >> aux;
                }

                comp.real = std::stoi(buffer);
                buffer.clear();
                in >> aux;
                while(aux != ',') {
                        buffer.push_back(aux);
                        in >> aux;
                }
                comp.imaginaria = std::stoi(buffer);
                return in;
        }


        void prueba_move() {
            std::cout << "Prueba de move: " << std::endl;
            Complejo comp1(1, 1);
            std::cout << "Valor inicial comp1: " << comp1 << std::endl;
            Complejo comp2(std::move(comp1));
            std::cout << "Valor comp1 despues de construir comp2 con move: " << comp1 << std::endl;
            std::cout << "Valor comp2: " << comp2 << std::endl << std::endl;
        }

        void prueba_preincremento() {
            std::cout << "Prueba preincremento: " << std::endl;
            Complejo comp(0, 0);
            std::cout << "Valor inicial de comp: " << comp << std::endl;
            ++comp;
            std::cout << "Valor despues de preincremento: " << comp << std::endl << std::endl;
        }

        void prueba_postincremento() {
            std::cout << "Prueba postincremento: " << std::endl;
            Complejo comp(0, 0);
            std::cout << "Valor inicial de comp: " << comp << std::endl;
            comp++;
            std::cout << "Valor despues de postincremento: " << comp++ << std::endl << std::endl;
        }

        void prueba_carga() {
            Complejo comp(0, 0);
            std::cout << "Valor inicial del complejo: " << comp << std::endl;
            std::cout << "Siguientes valores cargados del archivo: " << std::endl;
            for(int i = 0; i < 3; i++) {
                std::cin >> comp;
                std::cout << comp << std::endl << std::endl;
            }
        }

        void prueba_resta() {
            std::cout << "Prueba resta: " << std::endl;
            Complejo comp1(0, 0);
            Complejo comp2(1, 1);
            std::cout << "Operacion: " << comp1 << " - (" << comp2 << ") = " << comp1 - comp2 << std::endl << std::endl;
        }

        void prueba_casteo_float() {
            std::cout << "Prueba casteo a float: " << std::endl;
            Complejo comp(1, 2);
            std::cout << "Complejo usado: " << comp << std::endl;
            float a = comp;
            float b = static_cast<float>(comp);
            std::cout << "Casteo implícito: " << a << std::endl;
            std::cout << "Casteo explicito: " << b << std::endl << std::endl;
        }

int main(int argc, char* argv[]) {
    prueba_move();
    prueba_preincremento();
    prueba_postincremento();
    prueba_carga();
    prueba_resta();
    prueba_casteo_float();
    return 0;
}
