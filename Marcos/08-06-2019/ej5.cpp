/*5) Implemenete una funcion C++ denominada DobleSegunda que reciba dos listas
de elementos y devuelva una nueva lista duplicando los elementos de la primera
si estan en la segunda:

std::list<T> DobleSegunda(std::list<T> a, std::list<T> b);*/

#include <list>
#include <iostream>

template <class T>
std::list<T> DobleSegunda(std::list<T> a, std::list<T> b) {
    std::list<T> result;
    bool repeated = false;

    for (auto & elementA : a) {
        for (auto & elementB : b) {

            if (elementA == elementB) {
                repeated = true;
                break;
            }

        }

        if (repeated) {
            for (int i = 0; i < 2; ++i) {
                result.emplace_back(elementA);
            }
            repeated = false;
        } else {
            result.emplace_back(elementA);
        }
    }

    return result;
}

int main() {
    std::list<int> a = {1,2,3,4,5};
    std::list<int> b = {8,1,9,1};
    std::list<int> result = DobleSegunda(a, b);
    for (auto & element : result) {
        std::cout << element << std::endl;
    }
    return 0;
}