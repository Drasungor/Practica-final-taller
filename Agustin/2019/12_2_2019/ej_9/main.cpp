#include <iostream>
#include <list>
#include <string>
#include <sys/socket.h>
#include <cstdint>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <string>

int get_fd(const char* host, const char* port) {
    int socket_fd = -1;
    int aux;
    struct addrinfo hints;
    struct addrinfo* result;
    struct addrinfo* ptr;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    if (getaddrinfo(host, port, &hints, &result) != 0) {
        return  -1;
    }
    ptr = result;
    while ((ptr != NULL) && (socket_fd == -1)) {
        socket_fd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (socket_fd != -1) {
            aux = connect(socket_fd, ptr->ai_addr, ptr->ai_addrlen);
            if (aux == -1) {
                close(socket_fd);
                socket_fd = -1;
            }
        }
        ptr = ptr->ai_next;
    }
    freeaddrinfo(result);
    return socket_fd;
}

int socket_receive(int socket_fd, void* buffer, int message_len) {
    int total_received_bytes = 0;
    int current_received_bytes = 0;
    char* char_buffer = (char*) buffer;
    while (total_received_bytes < message_len) {
        current_received_bytes = recv(socket_fd, char_buffer + total_received_bytes,
                                      message_len - total_received_bytes, MSG_NOSIGNAL);
        if (current_received_bytes <= 0) {
            return current_received_bytes;
        }
        total_received_bytes += current_received_bytes;
    }
    return 1;
}


bool execute_program(int socket_fd) {
    char char_buf;
    std::string block;
    bool should_keep_running = true;
    while (should_keep_running) {
        if (socket_receive(socket_fd, &char_buf, sizeof(char)) != 1) {
            return false;
        }
        if (socket_receive(socket_fd, &char_buf, sizeof(char)) != 1) {
            return false;
        }
        if (char_buf == '>') {
            should_keep_running = false;
        }
        while (char_buf != '>') {
            block.push_back(char_buf);
            if (socket_receive(socket_fd, &char_buf, sizeof(char)) != 1) {
                return false;
            }
        }
        std::cout << block << std::endl;
        block.clear();
    }
    return true;
}


int main() {
    int socket_fd = get_fd(NULL, "8080");
    if (socket_fd == -1) {
        printf("Error de socket\n");
        return -1;
    }
    bool program_status = execute_program(socket_fd);
    shutdown(socket_fd, SHUT_RDWR);
    close(socket_fd);
    if (!program_status) {
        return  -1;
    }
    return 0;
}
