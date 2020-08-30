/*1)
Escriba un programa que escriba por salida estandar los numeros entre

0 y 1000 ordenadamente. Se pide que los numeros pares sean escritos por un

hilo mientras los impares sean escritos por otro.

Contemple la correcta sincronizacion entre los hilos y la liberacion de los

recursos utilizados.*/


#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>


class PairCounter {
private:
    std::mutex& m;
    int& number;

public:
    PairCounter(std::mutex& _m, int& _number) : m(_m), number(_number) {}

    void count(std::condition_variable& cv) {
        int lastNumber = -2;
        while (number < 1000) {
            std::unique_lock<std::mutex> l(m);
            while (number == lastNumber) {
                cv.wait(l);
            }
            ++number;
            std::cout << number << std::endl;
            lastNumber = number;
            cv.notify_all();
        }
    }
};


class OddCounter {
private:
    std::mutex& m;
    int& number;

public:
    OddCounter(std::mutex& _m, int& _number) : m(_m), number(_number) {}

    void count(std::condition_variable& cv) {
        int lastNumber = -2;
        while (number < 999) {
            std::unique_lock<std::mutex> l(m);
            while (number == lastNumber || number < 0) {
                cv.wait(l);
            }
            ++number;
            std::cout << number << std::endl;
            lastNumber = number;
            cv.notify_all();
        }
    }
};



int main() {
    std::mutex m;
    std::condition_variable cv;
    int number = -1;

    PairCounter pCounter(m, number);
    OddCounter oCounter(m, number);

    std::thread t1(&PairCounter::count, &pCounter, std::ref(cv));
    oCounter.count(cv);

    t1.join();

    return 0;
}
