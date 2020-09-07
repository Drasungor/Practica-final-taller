#include <iostream>
#include <list>

template <class T>
std::list<T> interseccion(std::list<T> a, std::list<T> b) {
    std::list<T> retorno;
    for (const auto& val_a: a) {
        for (const auto& val_b: b) {
            if (val_a == val_b) {
                retorno.push_back(val_a);
                break;
            }
        }
    }
    return retorno;
}

int main() {
    std::list<int> a = {1, 2, 3, 4, 5, 6};
    std::list<int> b = {10, 982, 5, 464, 3, 6569};
    std::list<int> ret = interseccion(a, b);
    for (const auto& v: ret) {
        std::cout << v << std::endl;
    }
    return 0;
}
