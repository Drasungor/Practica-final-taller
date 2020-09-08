/*Escriba un programa que reciba paquetes de 10 bytes por el puerto TCP 815 y
los imprima por pantalla. Al recibir el byte 0xff debe cerrarse ordenadamente.
No considere errore.*/


//Toy asumiendo q el 0xff me llega adentro de un paquete
#define _POSIX_C_SOURCE 200112L

#include<string.h>
#include<stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include<stdbool.h>

int main(int argc, char** argv) {
    struct addrinfo hints;
    struct addrinfo *ptr, *results;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;
    hints.ai_protocol = 0;

    int s;
    int skt = -1;

    const char* host = "localhost";
    const char* port = "8150";

    s = getaddrinfo(host, port, &hints, &results);
    if(s == -1) return -1;

    for(ptr = results; ptr != NULL; ptr->ai_next) {
        skt = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if(s == -1) continue;

        s = connect(skt, ptr->ai_addr, ptr->ai_addrlen);
        if(s != -1) break;

        close(skt);
    }

    freeaddrinfo(results);
    if(ptr == NULL) return -1;

    char rec[10];
    int bytesReceived = 0;
    memset(rec, 0, 10);
    bool connected = true;
    while (connected) {
        if (connected) {
            memset(rec, 0, 10);
            while (bytesReceived < 10) {
                s = recv(skt, rec + bytesReceived, 10 - bytesReceived, 0);
                if(s < 1) return -1;
                bytesReceived += s;
            }
        }
        for (size_t i = 0; i < 10; i++) {
            if (rec[i] == 'q') {
                connected = false;
                break;
            }
            printf("%0x\n", rec[i]);
        }
        bytesReceived = 0;
    }

    shutdown(skt, SHUT_RDWR);
    close(skt);
}
