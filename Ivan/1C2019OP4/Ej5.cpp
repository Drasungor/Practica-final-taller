/*Duplica los elementos de la primera q estan en la segunda */

#include <iostream>
#include<list>

template<class T>
void duplicate(std::list<T>& a, std::list<T>& b, std::list<T>& finalList) {
    for (auto & elementA : a) {
        for (auto & elementB : b) {
            if (elementB == elementA) {
                finalList.push_back(elementA);
                break;
            }
        }
        finalList.push_back(elementA);
    }
}

int main(int argc, char const *argv[]) {
    std::list<int> list1 = {1,2,3,4,5};
    std::list<int> list2 = {8,1,9,1};

    std::list<int> finalList;
    duplicate(list1, list2, finalList);

    for (auto & element : finalList) {
        std::cout << element << std::endl;
    }
    return 0;
}
