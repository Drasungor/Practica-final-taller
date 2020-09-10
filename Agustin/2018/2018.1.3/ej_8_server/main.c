#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#define END_WORD "FIN"

int get_server_fd(char* host, char* port) {
    int socket_fd = -1;
    int val = 1;
    struct addrinfo hints;
    struct addrinfo* result;
    struct addrinfo* ptr;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    if (getaddrinfo(host, port, &hints, &result) != 0) {
        return -1;
    }
    ptr = result;
    while ((ptr != NULL) && (socket_fd == -1)) {
        socket_fd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (socket_fd != -1) {
            if ((setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(int))) ||
                (bind(socket_fd, ptr->ai_addr, ptr->ai_addrlen) == -1)) {
                close(socket_fd);
                socket_fd = -1;
            } else {
                if (listen(socket_fd, 1) == -1) {
                    shutdown(socket_fd, SHUT_RDWR);
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

int socket_receive_char(int socket_fd, char* char_buf) {
    int aux = recv(socket_fd, char_buf, sizeof(char), MSG_NOSIGNAL);
    if (aux <= 0) {
        return aux;
    }
    return 1;
}

int receive_end_word(int socket_fd, char end_word_buffer[4]) {
    int end_word_len = strlen(END_WORD);
    char char_buf;
    for (int i = 0; i < end_word_len - 1; ++i) {
        if (socket_receive_char(socket_fd, &char_buf) != 1) {
            return -1;
        }
        end_word_buffer[i + 1] = char_buf;
    }
    if (!strcmp(end_word_buffer, END_WORD)) {
        return 1;
    }
    return 0;
}

bool execute_program(int socket_fd) {
    int char_buf;
    bool should_program_run = true;
    int aux;
    const char* end_word = END_WORD;
    char word_buf[4];
    memset(word_buf, 0,4);
    while (should_program_run) {
        if (socket_receive_char(socket_fd, &char_buf) != 1) {
            return false;
        }
        if (char_buf == end_word[0]) {
            word_buf[0] = char_buf;
            aux = receive_end_word(socket_fd, word_buf);
            if (aux == 1) {
                should_program_run = false;
            } else if (aux == 0) {
                printf("%s", word_buf);
                fflush(stdout);
                memset(word_buf, 0, 4);
            } else {
                return false;
            }
        } else {
            printf("%c", char_buf);
            fflush(stdout);
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Cantidad de parametros erronea\n");
        return -1;
    }
    const char* host = argv[1];
    if (!strcmp(argv[1], "localhost")) {
        host = NULL;
    }
    int server_socket = get_server_fd(host, argv[2]);
    if (server_socket == -1) {
        fprintf(stderr, "Error de socket\n");
        return -1;
    }
    int client_fd = accept(server_socket, NULL, NULL);
    if (client_fd == -1) {
        shutdown(server_socket, SHUT_RDWR);
        close(server_socket);
        fprintf(stderr, "Error de socket\n");
        return -1;
    }
    bool program_status = execute_program(client_fd);
    shutdown(client_fd, SHUT_RDWR);
    close(client_fd);
    shutdown(server_socket, SHUT_RDWR);
    close(server_socket);
    if (!program_status) {
        return -1;
    }
    return 0;
}
