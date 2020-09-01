#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>

int contador = 1;

void imprimir_pares(std::mutex& m, std::condition_variable& cv) {
    std::unique_lock<std::mutex> lk(m);
    while (contador <= 100) {
        while (contador % 2 == 1) {
            cv.wait(lk);
        }
        std::cout << contador << std::endl;
        contador++;
        cv.notify_all();
    }
}

void imprimir_impares(std::mutex& m, std::condition_variable& cv) {
    std::unique_lock<std::mutex> lk(m);
    while (contador < 100) {
        while (contador % 2 == 0) {
            cv.wait(lk);
        }
        std::cout << contador << std::endl;
        contador++;
        cv.notify_all();
    }
}

int main() {
    std::mutex m;
    std::condition_variable cv;
    std::thread pares(imprimir_pares, std::ref(m), std::ref(cv));
    std::thread impares(imprimir_impares, std::ref(m), std::ref(cv));
    pares.join();
    impares.join();
    return 0;
}
