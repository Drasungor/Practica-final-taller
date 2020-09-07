/*4) Indicar la salida del siguiente programa:*/
/*Arreglo todos los errores de V porque originalmente esto ni compilaba*/

#include <iostream>
using namespace std;

class Base {
public:
        static void f1() { cout << "Base.f1" << endl; }
        virtual void f2() { cout << "Base.f2" << endl; f1(); }
        virtual void f3() { cout << "Base.f3" << endl; f2(); f1(); }
};

class Derivada : public Base {
public:
    static void f1() { cout << "Derivada.f1" << endl; }
    void f2() { cout << "Derivada.f2" << endl; f1(); }
    void f3() { cout << "Derivada.f3" << endl; f2(); f1(); }
};

int main() {
    Derivada pD;
    Base* pB = &pD;

    pD.f1(); /*imprime Derivada.f1*/
    pD.f2(); /*imprime Derivada.f2 y Derivada.f1*/

    pB->f1(); /*imrpime Base.f1*/
    pB->f2();  /*imprime Derivada.f2 y Derivada.f1*/

    return 0;
}