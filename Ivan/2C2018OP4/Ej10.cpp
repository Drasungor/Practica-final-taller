#include<iostream>
#include <list>

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>

template<class T>
std::list<T> Suprimir(std::list<T>& a, std::list<T>& b) {
    std::list<T> finalList;
    bool isInBoth = false;

    for(auto & elementA : a) {
        for(auto & elementB : b) {
            if (elementA == elementB) {
                isInBoth = true;
            }
        }
        if(!isInBoth) finalList.push_back(elementA);
        isInBoth = false;
    }

    return finalList;
}

int main(int argc, char** argv) {
    std::list<int> listA;
    std::list<int> listB;
    std::list<int> result;

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

    result = Suprimir(listA, listB);

    for(auto & element : result) {
        std::cout << element << std::endl;
    }
}
