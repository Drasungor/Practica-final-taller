#define _POSIX_C_SOURCE 200112L


#include <cstring>
#include <iostream>

#include<string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

char obtenerDecimal(char digit) {
    if (digit >= '0' && digit <= '9') {
        return 0 + digit - '0';
    } else {
        return 10 + digit - 'A';
    }
}

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

    bool connected = true;
    char received;
    char endMsg[4];
    int endIndex = 0;
    std::string currNum;
    int sum = 0;
    s = recv(skt, &received, 1, 0);
    connected = (s>0);

    while (connected) {
        while (received != '=') {
            if (received == ',') {
                sum += stoi(currNum);
                currNum.clear();
            } else if (isdigit(received) != 0) {
                currNum.push_back(received);
            }
            if (received == 'F') {
                endIndex = 0;
                endMsg[endIndex] = 'F';
                endIndex++;
            }  else if (received == 'I') {
                endMsg[endIndex] = 'I';
                endIndex++;
            }  else if (received == 'N') {
                endMsg[endIndex] = 'N';
                endIndex++;
            }
            if (endIndex == 3) {
                endMsg[4] = '\0';
                if (strcmp(endMsg, "FIN") == 0) {
                    connected = false;
                    break;
                }
            }
            s = recv(skt, &received, 1, 0);
            connected = (s>0);
        }

        if (connected) {
            memset(endMsg, 0, 4);
            endIndex = 0;
            sum += stoi(currNum);
            currNum.clear();
            std::cout << sum << std::endl;
            sum = 0;
            s = recv(skt, &received, 1, 0);
            connected = (s>0);
        }
    }

    shutdown(skt, SHUT_RDWR);
    close(skt);
    return 0;
}
