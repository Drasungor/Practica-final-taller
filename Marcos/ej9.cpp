/*Implemente una funcion C++ denominada Sacar que reciba dos listas de elementos y devuelva
una nueva lista con los elementos de la primera que no estan en la segunda:

std::list<T> Sacar(std::list<T> a, std::list<T> b);*/

#include <iostream>
#include <list>

template <class T>
std::list<T> Sacar(std::list<T> a, std::list<T> b) {
    std::list<T> newList;
    bool repeated = false;

    for (auto & i : a) {

        for (auto & j : b) {
            if (i == j) {
                repeated = true;
                break;
            }
        }

        if (!repeated) {
            newList.emplace_back(i);
        }

        repeated = false;
    }

    return newList;
}

int main() {
    std::list<int> first = {1, 2, 3, 4, 5};
    std::list<int> second = {1, 3, 4};

    std::list<int> result = Sacar(first, second);

    for (auto & i : result) {
        std::cout << i << std::endl;
    }


    return 0;
}
