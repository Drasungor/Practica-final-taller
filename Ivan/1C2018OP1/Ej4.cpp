#include<iostream>

class Base {
    public:
        static void f1() { std::cout << "Base.f1" << std::endl; }

        virtual void f2() { std::cout << "Base.f2" << std::endl; f1(); }
        virtual void f3() { std::cout << "Base.f3" << std::endl; f2(); f1(); }
};

class Derivada : public Base {
public:

    static void f1() { std::cout << "Derivada.f1" << std::endl; }

    void f2() { std::cout << "Derivada.f2" << std::endl; f1(); }
    void f3() { std::cout << "Derivada.f3" << std::endl; f2(); f1(); }
};

int main() {
    Derivada pD;
    Base* pB = &pD;

    pD.f1();
    pD.f2();

    pB->f1();
    pB->f2();
}
