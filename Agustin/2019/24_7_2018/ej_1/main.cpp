#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>

//Imprime también el 0
void print_even(int max_number, bool& was_last_number_even, std::condition_variable& cv, std::mutex& m) {
    int printed_number = 0;
    std::unique_lock<std::mutex> lk(m);
    while (printed_number <= max_number) {
        while (was_last_number_even) {
            cv.wait(lk);
        }
        std::cout << printed_number << std::endl;
        printed_number += 2;
        was_last_number_even = true;
        cv.notify_all();
    }
}


void print_odd(int max_number, bool& was_last_number_even, std::condition_variable& cv, std::mutex& m) {
    int printed_number = 1;
    std::unique_lock<std::mutex> lk(m);
    while (printed_number <= max_number) {
        while (!was_last_number_even) {
            cv.wait(lk);
        }
        std::cout << printed_number << std::endl;
        printed_number += 2;
        was_last_number_even = false;
        cv.notify_all();
    }
}

void print_numbers(int max_number) {
    bool was_last_number_even = false;
    std::condition_variable cv;
    std::mutex m;
    std::thread even(print_even, max_number, std::ref(was_last_number_even), std::ref(cv), std::ref(m));
    std::thread odd(print_odd, max_number, std::ref(was_last_number_even), std::ref(cv), std::ref(m));
    even.join();
    odd.join();
}

int main() {
    print_numbers(1000);
    return 0;
}
