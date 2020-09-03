/*8) Escriba un programa (desde la inicializacion hasta la liberacion de
los recursos) que reciba paquetes de la forma [nnn+nn+...+nnnn] (numeros
separados por +, encerrados entre corchetes) e imprima el resultado de la
suma de cada paquete por pantalla. Al recibir un paquete vacio ("[]") debe
cerrarse ordenadamente. No considere errores (asumo que se refiere solo a que
los paquetes vienen siempre en ese formato)*/

#define _POSIX_C_SOURCE 200112L

#include <cstdint>
#include <iostream>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>


int processConnection(int fd) {
    char byteRecv = 0;
    std::string number;
    std::string stopCondition;
    int bytes = 0;
    int sum = 0;


    while (stopCondition != "[]") {

        while (byteRecv != ']') {
            while (bytes < 1) {
                recv(fd, &byteRecv, 1, MSG_NOSIGNAL); /*la condicion esta al pedo pero la pongo para practicar por si leyera de a mas bytes*/
                if (byteRecv < 1) return 1;
                bytes += byteRecv;
            }

            bytes = 0;

            stopCondition.push_back(byteRecv);

            if (byteRecv == '+' || byteRecv == ']') {
                if (!number.empty()) {
                    sum += std::stoi(number);
                }
                number.clear();
            } else if (byteRecv != '[') {
                number.push_back(byteRecv);
            }
        }

        if (stopCondition != "[]") {
            byteRecv = 0;
            std::cout << sum << std::endl;
            sum = 0;
            stopCondition.clear();
        }
    }


    return 0;

}

int main(int argc, char** argv) {

    if (argc < 3) return 1;
    char* ip = argv[1];
    char* serviceName = argv[2]; /*puerto*/

    int s = 0;
    int fd = -1;

    struct addrinfo hints;
    struct addrinfo *ai_list, *ptr;

    memset(&hints, 0, sizeof(struct addrinfo));

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0; /*AI_PASSIVE for server*/

    s = getaddrinfo(ip, serviceName, &hints, &ai_list);

    if (s < 0) {
        printf("Error in getaddrinfo: %s\n", gai_strerror(s));
        return 1;
    }

    for (ptr = ai_list; ptr != NULL; ptr = ptr->ai_next) {
        fd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (fd < 0)
            continue;
        s = connect(fd, ptr->ai_addr, ptr->ai_addrlen);
        if (s != -1)
            break;
        close(fd);
        fd = -1;
    }

    freeaddrinfo(ai_list); /*No lo necesito mas*/

    if (ptr == NULL) {
        printf("No se logro conectar\n");
        return 1;
    }

    processConnection(fd);

    close(fd);

    return 0;
}