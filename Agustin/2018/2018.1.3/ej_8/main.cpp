//Me confundi y use c++, codee como si estuviera usando C

#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>

#define END_WORD "FIN"

int get_socket_fd(char* host, char* port) {
    int socket_fd = -1;
    struct addrinfo hints;
    struct addrinfo* result;
    struct addrinfo* ptr;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    if (getaddrinfo(host, port, &hints, &result) != 0) {
        return -1;
    }
    ptr = result;
    while((ptr != NULL) && (socket_fd == -1)) {
        socket_fd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (socket_fd != -1) {
            if (connect(socket_fd, ptr->ai_addr, ptr->ai_addrlen) == -1) {
                close(socket_fd);
                socket_fd = -1;
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

bool are_strings_equal(char* string1, char* string2) {
    if (strlen(string1) != strlen(string2)) {
        return false;
    }
    return !strcmp(string1, string2);
}


//Lee las siguientes letras de la palabra final y, si la termina recibiendo
//retorna 1, sino retorna 0
//Si hay un error de socket retorna -1
int receive_end_word(int socket_fd, char buf[4]) {
    int end_word_len = strlen(END_WORD);
    char char_buf;
    for (int i = 0; i < end_word_len - 1; ++i) {
        if (socket_receive_char(socket_fd, &char_buf) != 1) {
            return -1;
        }
        buf[1 + i] = char_buf;
    }
    if (are_strings_equal(buf, END_WORD)) {
        return 1;
    }
    return 0;
}


bool execute_program(int socket_fd) {
    bool should_keep_running = true;
    char end_buff[4];
    char char_buf;
    int aux;
    const char* end_word = END_WORD;
    memset(end_buff, 0, 4);
    while (should_keep_running) {
        if (socket_receive_char(socket_fd, &char_buf) != 1) {
            return -1;
        }
        if (char_buf == end_word[0]) {
            end_buff[0] = char_buf;
            aux = receive_end_word(socket_fd, end_buff);
            if (aux == 1) {
                should_keep_running = false;
            } else if (aux == 0) {
                printf("%s", end_buff);
                fflush(stdout);
                memset(end_buff, 0, 4);
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
        fprintf(stderr, "Cantidad incorrecta de parametros\n");
        return -1;
    }
    char* host = argv[1];
    if (!strcmp(argv[1], "localhost")) {
        host = NULL;
    }
    int socket_fd = get_socket_fd(host, argv[2]);
    if (socket_fd == -1) {
        fprintf(stderr, "Error de socket\n");
        return -1;
    }
    bool program_status = execute_program(socket_fd);

    shutdown(socket_fd, SHUT_RDWR);
    close(socket_fd);
    if (!program_status) {
        fprintf(stderr, "Error de socket\n");
        return -1;
    }
    return 0;
}
