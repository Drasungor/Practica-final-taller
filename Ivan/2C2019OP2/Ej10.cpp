#include <iostream>
#include <list>

template<class T>
std::list<T> DobleSiNo(std::list<T> a, std::list<T> b) {
    std::list<T> finalList;
    bool isRepeated = false;

    for(auto & aElement : a) {
        for(auto & bElement : b) {
            if (aElement == bElement) {
                isRepeated = true;
            }
        }
        if (isRepeated) {
            finalList.push_back(aElement);
        }
        isRepeated = false;
        finalList.push_back(aElement);
    }

    return finalList;
}

int main(int argc, char const *argv[]) {
    std::list<int> list1 = {1,2,3,4,5,6,7,8,9,10};
    std::list<int> list2 = {1,2,3,4,5};
    std::list<int> result = DobleSiNo(list1, list2);
    for(auto & element : result){
        std::cout << element << std::endl;
    }
    return 0;
}
