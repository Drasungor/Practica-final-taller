#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#define LAST_WORD "FIN"

int get_fd(char* host, char* port) {
    int socket_fd = -1;
    int aux;
    struct addrinfo hints;
    struct addrinfo* result;
    struct addrinfo* ptr;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    aux = getaddrinfo(host, port, &hints, &result);
    if (aux != 0) {
        return -1;
    }
    ptr = result;
    while ((socket_fd == -1) && (ptr != NULL)) {
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
    int total_bytes_received = 0;
    int current_bytes_received = 0;
    char* char_buffer = (char*)buffer;
    while (total_bytes_received < message_len) {
        current_bytes_received = recv(socket_fd, char_buffer + total_bytes_received, message_len - total_bytes_received, MSG_NOSIGNAL);
        if (current_bytes_received <= 0) {
            return -1;
        }
        total_bytes_received += current_bytes_received;
    }
    return 0;
}

//Retorna -1 si hay un error, 0 si no deberia seguir corriendo, 1 si deberia
//seguir corriendo
int should_program_keep_running(int socket_fd, char buffer[4]) {
    if (socket_receive(socket_fd, buffer + 1, 2) != 0) {
        return -1;
    }
    if (!strcmp(buffer, LAST_WORD)) {
        return 0;
    }
    return 1;
}

bool run_program(int socket_fd) {
    bool is_running = true;
    char char_buffer;
    char buffer[4];
    const char* final_word = LAST_WORD;
    int aux;
    memset(buffer, 0, 4);
    while (is_running) {
        socket_receive(socket_fd, &char_buffer, sizeof(char));
        if (char_buffer == final_word[0]) {
            buffer[0] = char_buffer;
            aux = should_program_keep_running(socket_fd, buffer);
            if (aux == -1) {
                return false;
            }
            if (!aux) {
                return true;
            }
        }
        printf("%c", char_buffer);
        if (strlen(buffer + 1) != 0) {
            printf("%s", buffer + 1);
        }
        memset(buffer, 0, 4);
        fflush(stdout);
    }
    return true;
}

bool are_strings_equal(char* str1, char* str2) {
    if (strlen(str1) != strlen(str2)) {
        return false;
    }
    return !strcmp(str1, str2);
}

int main(int argc, char* argv[]) {
    char* host = argv[1];
    if (are_strings_equal(host, "localhost")) {
        host = NULL;
    }
    int socket_fd = get_fd(host, argv[2]);
    if (socket_fd == -1) {
        printf("Error de socket\n");
        return -1;
    }
    run_program(socket_fd);
    shutdown(socket_fd, SHUT_RDWR);
    close(socket_fd);
    return 0;
}
