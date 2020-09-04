//Se considera que el enunciado dice que

#include <iostream>
#include <list>


template <class T>
bool EstaRepetido(const std::list<T> lista, const T& a_comparar) {
    for (const auto& valor: lista) {
        if (a_comparar == valor) {
            return true;
        }
    }
    return false;
}

template <class T>
std::list<T> DobleSegunda(std::list<T> a, std::list<T> b) {
    std::list<T> retorno;
    for (const auto& valor_a: a) {
        retorno.push_back(valor_a);
        if (EstaRepetido(b, valor_a)) {
            retorno.push_back(valor_a);
        }
    }
    return retorno;
}


int main() {
    std::list<int> a = {1, 2, 3, 4, 5, 6};
    std::list<int> b = {1, 6, 5, 10};
    for (const auto& valor: DobleSegunda(a, b)) {
        std::cout << valor << std::endl;
    }
    return 0;
}
