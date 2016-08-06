//
// Created by Ruto on 8/4/2016.
//

typedef void (*nr_socket_callback)(int, char*);

int nr_socket_create(void);

int nr_socket_shutdown(int);

int nr_socket_connect(int, char*, int);

int nr_socket_bind(int, char*, int);

int nr_socket_listen(int, int);

int nr_socket_accept(int, struct sockaddr*, int*);

void nr_socket_register_recv_callback(int, nr_socket_callback);

int nr_socket_send(int socket, char* data, size_t length);