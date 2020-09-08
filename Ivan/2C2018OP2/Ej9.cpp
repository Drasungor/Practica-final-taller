#define _POSIX_C_SOURCE 200112L


#include <cstring>
#include <iostream>

#include<string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

int main(int argc, char** argv) {
    struct addrinfo hints;
    struct addrinfo *ptr, *results;

    const char* host = argv[1];
    const char* port = argv[2];

    int s;
    int skt = -1;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;
    hints.ai_protocol = 0;

    s = getaddrinfo(host, port, &hints, &results);
    if(s != 0) return -1;//error en getaddrinfo

    for (ptr = results; ptr != NULL; ptr->ai_next) {
        skt = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if(skt < 0) continue;

        s = connect(skt, ptr->ai_addr, ptr->ai_addrlen);
        if(s != -1) break;

        close(skt);
    }

    freeaddrinfo(results);
    if(ptr == NULL) return -1; //no me pude conectar;


    std::string packet;
    char received;
    bool connected;
    s = recv(skt, &received, 1, 0);
    connected = (s > 0);

    while (connected) {
        if (received == '<') {
            while (received != '>') {
                if (recv(skt, &received, 1, 0) <= 0) {
                    connected = false;
                    break;
                }
                if (received != '>') packet.push_back(received);
            }
            if (packet.empty()) {
                connected = false;
                break;
            } else {
                std::cout << packet << std::endl;
                packet.clear();
            }
        }
        s = recv(skt, &received, 1, 0);
        connected = (s > 0);
    }

    shutdown(skt, SHUT_RDWR);
    close(skt);
    return 0;
}
