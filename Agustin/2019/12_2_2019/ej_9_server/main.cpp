#include <iostream>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <string>

int get_server_fd(char* port) {
    int socket_fd = -1;
    struct addrinfo hints;
    struct addrinfo* result;
    struct addrinfo* ptr;
    int val = 1;
    int aux;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    if (getaddrinfo(NULL, port, &hints, &result) != 0) {
        return -1;
    }
    ptr = result;
    while ((ptr != NULL) && (socket_fd == -1)) {
        socket_fd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (socket_fd != -1) {
            if ((setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(int)) == -1) ||
                (bind(socket_fd, ptr->ai_addr, ptr->ai_addrlen) == -1) ||
                    (listen(socket_fd, 1) != 0)) {
                close(socket_fd);
                socket_fd = -1;
            }
        }
        ptr = ptr->ai_next;
    }
    freeaddrinfo(result);
    return socket_fd;
}

int socket_receive(int client_socket, void* buffer, int message_len) {
    int total_bytes = 0;
    int current_bytes = 0;
    char* char_buf = (char*)buffer;
    while (total_bytes < message_len) {
        current_bytes = recv(client_socket, char_buf + total_bytes, message_len - total_bytes, MSG_NOSIGNAL);
        if (current_bytes <= 0) {
            return current_bytes;
        }
        total_bytes += current_bytes;
    }
    return 1;
}

bool execute_program(int client_socket) {
    char char_buf;
    bool should_program_run = true;
    std::string buf;
    while (should_program_run) {
        if ((socket_receive(client_socket, &char_buf, sizeof(char)) != 1) ||
            (socket_receive(client_socket, &char_buf, sizeof(char)) != 1)) {
            return false;
        }
        if (char_buf == '>') {
            should_program_run = false;
        }
        while (char_buf != '>') {
            buf.push_back(char_buf);
            if (socket_receive(client_socket, &char_buf, sizeof(char)) != 1) {
                return false;
            }
        }
        std::cout << buf << std::endl;
        buf.clear();
    }
    return true;
}

int main() {
    int server_socket = get_server_fd("8080");
    if (server_socket == -1) {
        printf("Error de socket\n");
    }
    int client_socket = accept(server_socket, NULL, NULL);
    if (client_socket == -1) {
        shutdown(server_socket, SHUT_RDWR);
        close(server_socket);
        printf("Error de socket\n");
    }
    bool program_status = execute_program(client_socket);
    shutdown(client_socket, SHUT_RDWR);
    close(client_socket);
    shutdown(server_socket, SHUT_RDWR);
    close(server_socket);
    if (!program_status) {
        return -1;
    }
    return 0;
}
