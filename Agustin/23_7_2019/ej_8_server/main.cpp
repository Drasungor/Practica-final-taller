#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <cstring>
#include <vector>

int obtener_server_fd(std::string port) {
    int socket_fd = -1;
    struct addrinfo hints;
    struct addrinfo* result;
    struct addrinfo* ptr;
    int aux;
    int val = 1;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    aux = getaddrinfo(NULL, port.data(), &hints, &result);
    if (aux != 0) {
        return -1;
    }
    ptr = result;
    while ((ptr != NULL) && (socket_fd == -1)) {
        socket_fd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (socket_fd != -1) {
            aux = setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(int));
            if (aux == -1) {
                close(socket_fd);
                socket_fd = -1;
            } else {
                aux = bind(socket_fd, ptr->ai_addr, ptr->ai_addrlen);
                if ((aux == -1) || (listen(socket_fd, 1) != 0)) {
                    close(socket_fd);
                    socket_fd = -1;
                }
            }
        }
        ptr = ptr->ai_next;
    }
    freeaddrinfo(result);
    return socket_fd;
}

int socket_receive(int cliente_fd, void* buffer, int largo_mensaje) {
    int bytes_totales_leidos = 0;
    int bytes_actuales_leidos = 0;
    char* buffer_string = (char*) buffer;
    while (bytes_totales_leidos < largo_mensaje) {
        bytes_actuales_leidos = recv(cliente_fd, buffer_string + bytes_totales_leidos, largo_mensaje - bytes_totales_leidos, MSG_NOSIGNAL);
        if (bytes_actuales_leidos <= 0) {
            return -1;
        }
        bytes_totales_leidos += bytes_actuales_leidos;
    }
    return 0;
}

bool procesar_paquete(int cliente_fd) {
    char char_buffer;
    std::string buffer;
    std::vector<int> numeros_a_sumar;
    int suma = 0;
    if (socket_receive(cliente_fd, &char_buffer, sizeof(char)) != 0) {
        return false;
    }
    while (char_buffer != ']') {
        if (socket_receive(cliente_fd, &char_buffer, sizeof(char)) != 0) {
            return false;
        }
        if (char_buffer == ']') {
            return false;
        }
        while ((char_buffer != ']') && (char_buffer != '+')) {
            buffer.push_back(char_buffer);
            if (socket_receive(cliente_fd, &char_buffer, sizeof(char)) != 0) {
                return false;
            }
        }
        numeros_a_sumar.push_back(std::stoi(buffer));
        buffer.clear();
    }
    for (unsigned int i = 0; i < numeros_a_sumar.size(); ++i) {
        suma += numeros_a_sumar[i];
    }
    std::cout << suma << std::endl;
    return true;
}

void cerrar_sockets(int server_fd, int cliente_fd) {
    shutdown(cliente_fd, SHUT_RDWR);
    close(cliente_fd);
    shutdown(server_fd, SHUT_RDWR);
    close(server_fd);
}

int main() {
    int server_fd = obtener_server_fd("8080");
    int cliente_fd = accept(server_fd, NULL, NULL);
    bool sigue_ejecucion = procesar_paquete(cliente_fd);
    while (sigue_ejecucion) {
        sigue_ejecucion = procesar_paquete(cliente_fd);
    }
    cerrar_sockets(server_fd, cliente_fd);
    return 0;
}
