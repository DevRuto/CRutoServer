#include<stdio.h>
#include <stdlib.h>
//#include <afxres.h>
#include "nr_dictionary.h"
#include "nr_socket.h"
#include "nr_thread.h"
#include <time.h>

void recv_callback(int sock, char* data);
void handle_client(int sock, struct sockaddr_in addr);
void thread_callback(void* args);

typedef struct nr_socket_args {
    int socket;
    struct sockaddr_in addr;
};

void main90() {
    srand(time(NULL));
    int i;
    for (i = 0; i < 100; i++)
        printf("NUM: %d\n", rand());
}

void main() {
    int socket = nr_socket_create();
    int result = nr_socket_bind(socket, "0.0.0.0", 810);
    if (result != 0) {
        puts("Error binding\n");
        return;
    }
    nr_socket_listen(socket, 5);
    struct sockaddr_in addr;
    int len;
    int clientsocket;
    while((clientsocket = nr_socket_accept(socket, (struct sockaddr *) &addr, &len)) != INVALID_SOCKET) {
        struct nr_socket_args args;
        args.socket = clientsocket;
        args.addr = addr;
        int handle = nr_invokethread(thread_callback, &args);
    }

    nr_socket_shutdown(socket);
    puts("\nEND\n");
}

void thread_callback(void* args) {
    struct nr_socket_args *nargs = args;
    handle_client(nargs->socket, nargs->addr);
}

void handle_client(int sock, struct sockaddr_in addr) {
    static int connectionCount = 0;
    connectionCount++;
    printf("\nConnection #%d\n", connectionCount);
    nr_socket_register_recv_callback(sock, recv_callback);
}

void recv_callback(int sock, char* data) {
    printf("Data: %s\n\n", data);
    char* tosend = "HTTP/1.1 200 OK\r\nContent-Length: 11\r\n\r\nHELLO WORLD";
    nr_socket_send(sock, tosend, strlen(tosend));
}


dict() {
    nr_dictionary_t dict;
    nr_dictionary_init(&dict);
    printf("Size of char pointer: %d\n", sizeof(char*));
    int i;
    nr_dictionary_add(&dict, "a", "value");
    nr_dictionary_add(&dict, "b", "value");
    nr_dictionary_add(&dict, "c", "value");
    nr_dictionary_add(&dict, "d", "value");
    nr_dictionary_add(&dict, "e", "value");
    nr_dictionary_add(&dict, "f", "value");
    nr_dictionary_remove(&dict, "c");
    nr_dictionary_add(&dict, "g", "value");
    nr_dictionary_add(&dict, "h", "value");
    nr_dictionary_add(&dict, "asdf", "fda");
    for (i = 0; i < dict.count; i++) {
        printf("Key: %s - Value: %s\n", dict.headers[i].key, dict.headers[i].value);
    }
    printf("Size: %d\n", dict.count);
    nr_dictionary_free(&dict);
    puts("Hello World");
}