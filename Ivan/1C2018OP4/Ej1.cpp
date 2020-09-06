// Escriba un programa que escriba por salida estandar los numeros entre
//
// 0 y 1000 ordenadamente. Se pide que los numeros pares sean escritos por un
//
// hilo mientras los impares sean escritos por otro.
//
// Contemple la correcta sincronizacion entre los hilos y la liberacion de los
//
// recursos utilizados.

#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>

bool canPrintOdd(int n) {
    return ((n % 2) != 0);
}

bool canPrintEven(int n) {
    return ((n % 2) == 0);
}

void printEvenNums(int& n, std::mutex& mtx, std::condition_variable& cond_var){
    std::unique_lock<std::mutex> lock(mtx);

    while (n < 1000) {
        while (!canPrintEven(n)) {
            cond_var.wait(lock);
        }
        std::cout << n << std::endl;
        ++n;
        cond_var.notify_all();
    }
}

void printOddNums(int& n, std::mutex& mtx, std::condition_variable& cond_var){
    std::unique_lock<std::mutex> lock(mtx);

    while (n < 1000) {
        while (!canPrintOdd(n)) {
            cond_var.wait(lock);
        }
        std::cout << n << std::endl;
        ++n;
        cond_var.notify_all();
    }
}


int main(int argc, char const *argv[]) {
    std::mutex mtx;
    std::condition_variable cond_var;

    int n = 0;

    std::thread evenPrinter(printEvenNums, std::ref(n), std::ref(mtx), std::ref(cond_var));
    std::thread oddPrinter(printOddNums, std::ref(n), std::ref(mtx), std::ref(cond_var));

    oddPrinter.join();
    evenPrinter.join();

    return 0;
}
