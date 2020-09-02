/*1) Declare la clase Numero para encapsular una cadena numerica larga.
Inclcluya al menos: Constructor(unsigned long), Constructor default y
Constructor move; Operador <<, (), =, long  y ++(int). Implemente el
operador >>*/

#include <string>
#include <iostream>

class Numero {
private:
    std::string number;

public:
    Numero() = default; /*constructor default*/
    Numero(unsigned long _number);
    Numero(Numero&& other); /*constructor move*/

    void operator()();
    Numero& operator=(const Numero& other);
    operator long();
    Numero& operator++(int) {
        printf("pene\n");
        return *this;
    };

    friend std::ostream& operator<<(std::ostream& os, const Numero& number);
    friend std::istream& operator>>(std::istream& is, Numero& number);
};

std::istream& operator>>(std::istream& is, Numero& number) {
    is >> number;
    return is;
}

int main() {
    return 0;
}