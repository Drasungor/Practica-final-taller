#include<iostream>
#include<list>

template<class T>
std::list<T> sacar(std::list<T> a, std::list<T> b) {
    std::list<T> finalList;
    bool isRepeated = false;
    for (auto & aElement : a) {
        for (auto & bElement : b) {
            if (bElement == aElement){
                isRepeated = true;
            }
        }
        if (!isRepeated) {
            finalList.push_back(aElement);
        }
        isRepeated = false;
    }
    return finalList;
}

int main(int argc, char const *argv[]) {
    std::list<int> list1 = { 7, 5, 16, 8 };
    std::list<int> list2 = { 7, 8, 19, 8 };

    std::list<int> list3 = sacar(list1, list2);

    for (auto & element : list3) {
        std::cout << element << '\n';
    }

    return 0;
}
