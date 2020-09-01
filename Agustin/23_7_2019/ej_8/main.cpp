#define _POSIX_C_SOURCE 200112L
#include <iostream>
#include <string>
#include <vector>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>

//Se usa el puerto 8080
int get_socket_fd(std::string port){
    struct addrinfo hints;

    struct addrinfo *result;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    int fd = -1;
    int aux;
    struct addrinfo *aux_ptr;

    aux = getaddrinfo(NULL, port.data(), &hints, &result);
    if (aux != 0) {
        return -1;
    }
    aux_ptr = result;
    while ((aux_ptr != NULL) && (fd == -1)) {
        fd = socket(aux_ptr->ai_family, aux_ptr->ai_socktype, aux_ptr->ai_protocol);
        if (fd != -1) {
            aux = connect(fd, aux_ptr->ai_addr, aux_ptr->ai_addrlen);
            if (aux == -1) {
                close(fd);
                fd = -1;
            }
        }
        aux_ptr = aux_ptr->ai_next;
    }
    freeaddrinfo(result);
    return fd;
}

int socket_receive(int fd, void* buffer, int message_len) {
    char* char_buffer = (char*)buffer;
    int total_received_bytes = 0;
    int current_received_bytes = 0;
    while (total_received_bytes < message_len) {
        current_received_bytes = recv(fd, char_buffer + total_received_bytes, message_len - total_received_bytes, MSG_NOSIGNAL);
        if (current_received_bytes <= 0) {
            return  -1;
        }
        total_received_bytes += current_received_bytes;
    }
    return 0;
}

int socket_send(int fd, const void* message, int message_len) {
    const char* char_buffer = (char*)message;
    int total_sent_bytes = 0;
    int current_sent_bytes = 0;
    while (total_sent_bytes < message_len) {
        current_sent_bytes = send(fd, char_buffer + total_sent_bytes, message_len - total_sent_bytes, MSG_NOSIGNAL);
        if (current_sent_bytes <= 0) {
            return  -1;
        }
        total_sent_bytes += current_sent_bytes;
    }
    return 0;
}

//Retorna true si el programa debe continuar ejecutandose, sino retorna false
bool get_pack_sum(int socket_fd, int& result) {
    std::string buffer;
    std::vector<int> numbers_to_sum;
    result = 0;
    char char_storer;
    int aux = socket_receive(socket_fd, &char_storer, sizeof(char));
    if (aux == -1) {
        return  false;
    }
    while (char_storer != ']') {
        aux = socket_receive(socket_fd, &char_storer, sizeof(char));
        if ((aux == -1) || (char_storer == ']')) {
            return  false;
        }
        while ((char_storer != '+') && (char_storer != ']')) {
            buffer.push_back(char_storer);
            aux = socket_receive(socket_fd, &char_storer, sizeof(char));
            if (aux == -1) {
                return  false;
            }
        }
        numbers_to_sum.push_back(std::stoi(buffer));
        buffer.clear();
    }
    for (unsigned int i = 0; i < numbers_to_sum.size(); ++i) {
        result += numbers_to_sum[i];
    }
    return true;
}

int main() {
    int socket_fd = get_socket_fd("8082");
    if (socket_fd == -1) {
        return -1;
    }
    int result;
    while (get_pack_sum(socket_fd, result)) {
        std::cout << result << std::endl;
    }
    shutdown(socket_fd, SHUT_RDWR);
    close(socket_fd);
    return 0;
}