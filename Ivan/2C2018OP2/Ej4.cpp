#include<thread>
#include<iostream>
#include<mutex>
#include<condition_variable>

bool canPrintEven(int n) {
    return (n % 2 == 0);
}

bool canPrintOdd(int n) {
    return (n % 2 != 0);
}

void printEven(int& n, std::mutex& m, std::condition_variable& cv) {
    std::unique_lock<std::mutex> lock(m);
    while(n < 100){
        while (!((n % 2) == 0)) {
            cv.wait(lock);
        }
        std::cout << n << std::endl;
        ++n;
        cv.notify_all();
    }
}

void printOdd(int& n, std::mutex& m, std::condition_variable& cv) {
    std::unique_lock<std::mutex> lock(m);
    while(n < 100){
        while (!((n % 2) != 0)) {
            cv.wait(lock);
        }
        std::cout << n << std::endl;
        ++n;
        cv.notify_all();
    }
}

int main(int argc, char** argv){
    std::mutex m;
    std::condition_variable cv;

    int n = 1;

    std::thread even(printEven, std::ref(n), std::ref(m), std::ref(cv));
    std::thread odd(printOdd, std::ref(n), std::ref(m), std::ref(cv));

    even.join();
    odd.join();
    return 0;

}
