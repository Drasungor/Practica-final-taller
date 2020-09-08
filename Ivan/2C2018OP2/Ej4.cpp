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

void printer(int& n, std::mutex& m, std::condition_variable& cv, bool (*f)(int)) {
    std::unique_lock<std::mutex> lock(m);
    while(n < 100){
        while (!f(n)) {
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

    std::thread even(printer, std::ref(n), std::ref(m), std::ref(cv), &canPrintEven);
    std::thread odd(printer, std::ref(n), std::ref(m), std::ref(cv), &canPrintOdd);

    even.join();
    odd.join();
    return 0;

}
