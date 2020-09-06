#define _POSIX_C_SOURCE 200112L


#include <cstring>
#include <iostream>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>


int main(int argc, char const *argv[]) {
    struct addrinfo hints;
    struct addrinfo* results, *ptr;

    const char* host = "localhost";
    const char* port = "8081";

    int skt = -1;
    int s;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;
    hints.ai_protocol = 0;

    s = getaddrinfo(host, port, &hints, &results);

    for (ptr = results; ptr != NULL; ptr->ai_next) {
        skt = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (skt == -1) continue;

        s = connect(skt, ptr->ai_addr, ptr->ai_addrlen);
        if (skt != -1) break;

        close(skt);
    }

    freeaddrinfo(results);

    if (ptr == NULL) {
        return -1;
    }

    int suma = 0;
    char received;
    s = recv(skt, &received, 1, MSG_NOSIGNAL);
    bool connected = true;
    if (s == 0 || s == -1) connected == false;
    std::string currNum;

    while (connected) {
        if (received == '[') {
            while (received != ']' && connected) {
                if (received == '+') {
                    suma += stoi(currNum);
                    currNum.clear();
                } else if (received != '[') {
                    currNum.push_back(received);
                }
                s = recv(skt, &received, 1, MSG_NOSIGNAL);
                if (s == 0 || s == -1) connected == false;
            }
            if (suma == 0) {
                connected = false;
                break;
            } else {
                suma += stoi(currNum);
                currNum.clear();
                std::cout << suma << std::endl;
                suma = 0;
            }
        }
        s = recv(skt, &received, 1, MSG_NOSIGNAL);
        if (s == 0 || s == -1) connected == false;
    }
    close(skt);
    return 0;
}
