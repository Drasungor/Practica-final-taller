/*4) Declare la clase IPv4 para almacenar una direccion IP. Incluya constructor
default, constructor move, constructor de copia, y los siguientes operadores:
operator<<, operator==, operator= y operator+*/

#include <string>

class IPv4 {
private:
    std::string ip;

public:
    IPv4() = default;
    IPv4(IPv4&& other) noexcept;
    IPv4(const IPv4& other);

    friend std::ostream& operator<<(std::ostream& os, const IPv4& ip);
    friend std::istream& operator>>(std::istream& is, IPv4& ip);
    bool operator==(const IPv4& other);
    IPv4& operator=(const IPv4& other);
    IPv4 operator+(const IPv4& other);
}