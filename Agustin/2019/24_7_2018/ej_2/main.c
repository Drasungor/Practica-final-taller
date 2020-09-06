#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define HOST "10.9.8.7"
#define PORT "7777"

int socket_send(int socket_fd, const void* message, int len) {
    int sent_bytes = 0;
    int current_bytes_sent = 0;
    const char* message_bytes = message;
    while (sent_bytes < len) {
        current_bytes_sent = send(socket_fd, message_bytes + sent_bytes, len - sent_bytes, MSG_NOSIGNAL);
        if (current_bytes_sent == 0) {
            return -1;
        } else if (current_bytes_sent < 0) {
            return -2;
        }
        sent_bytes += current_bytes_sent;
    }
    return 0;
}

int socket_receive(int socket_fd, void* message, int len) {
    int received_bytes = 0;
    int current_bytes_received = 0;
    char* message_bytes = message;
    while (received_bytes < len) {
        current_bytes_received = recv(socket_fd, message_bytes + received_bytes, len - received_bytes, MSG_NOSIGNAL);
        if (current_bytes_received == 0) {
            return -1;
        } else if (current_bytes_received < 0) {
            return -2;
        }
        received_bytes += current_bytes_received;
    }
    return 0;
}

int32_t process_number(int socket_fd) {
    char received_digit = 0;
    char number_buffer[12];//1 byte para el -, 10 para los digitos, 1 para el null byte
    int received_digits = 0;
    socket_receive(socket_fd, &received_digit, sizeof(char));
    while (received_digit != '\n') {
        number_buffer[received_digits] = received_digit;
        received_digits++;
        socket_receive(socket_fd, &received_digit, sizeof(char));
    }
    number_buffer[received_digits] = '\0';
    return atoi(number_buffer);
}

int get_socket_fd(char* host, char* port) {
    struct addrinfo* result;
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    int info_result = getaddrinfo(host, port, &hints, &result);
    if (info_result != 0) {
        return -1;
    }
    struct addrinfo* aux_ptr = result;
    bool could_connect = false;
    int socket_fd;
    int connect_value;
    while ((aux_ptr != NULL) && (!could_connect)) {
        socket_fd = socket(aux_ptr->ai_family, aux_ptr->ai_socktype, aux_ptr->ai_protocol);
        if (socket_fd != -1) {
            connect_value = connect(socket_fd, aux_ptr->ai_addr, aux_ptr->ai_addrlen);
            if (connect_value == -1) {
                close(socket_fd);
            } else {
                could_connect = true;
            }
        }
        aux_ptr = aux_ptr->ai_next;
    }
    freeaddrinfo(result);
    if (!could_connect) {
        return -1;
    }
    return socket_fd;
}

int main() {
    int socket_fd = get_socket_fd(HOST, PORT);
    int32_t received_number = process_number(socket_fd);
    while (received_number != 0) {
        socket_send(socket_fd, &received_number, sizeof(int32_t));
        received_number = process_number(socket_fd);
    }
    shutdown(socket_fd, SHUT_RDWR);
    close(socket_fd);
    return 0;
}
