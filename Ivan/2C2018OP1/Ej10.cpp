#include<iostream>
#include <list>

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>

template<class T>
std::list<T> interseccion(std::list<T> a, std::list<T> b) {
    std::list<T> finalList;
    for(auto & elementA : a) {
        for(auto & elementB : b) {
            if (elementA == elementB) {
                finalList.push_back(elementA);
                break;
            }
        }
    }
    return finalList;
}

int main(int argc, char** argv) {
    std::list<int> listA;
    std::list<int> listB;

    srand (time(NULL));


    int iSecret;
    std::cout << "listA: ";
    for (size_t i = 0; i < 10; i++) {
        iSecret = rand() % 10;
        listA.push_back(iSecret);
        std::cout << iSecret;
    }
    std::cout << std::endl;
    std::cout << "listB: ";
    for (size_t i = 0; i < 10; i++) {
        iSecret = rand() % 10;
        listB.push_back(iSecret);
        std::cout << iSecret;
    }
    std::cout << std::endl;


    std::list<int> finalList = interseccion(listA, listB);
    for(auto & element : finalList) {
        std::cout << element << std::endl;
    }

    return 0;
}
