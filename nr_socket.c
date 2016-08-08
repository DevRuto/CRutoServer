//
// Created by Ruto on 8/4/2016.
//
#include "nr_socket.h"

int nr_socket_create(void) {
#ifdef _WIN32
    WSADATA wsa_data;
    int result = WSAStartup(MAKEWORD(1, 1), &wsa_data);
    if (result != 0) {
        puts("WSAStartup Failed\n");
        return 0;
    }
#endif
    return socket(AF_INET, SOCK_STREAM, 0);
}

int nr_socket_shutdown(int sock) {
    int status = 0;
#ifdef _WIN32
    status = shutdown((SOCKET) sock, SD_BOTH);
    if (status == 0)
        status = closesocket((SOCKET) sock);
    status = WSACleanup();
#else
    status = shutdown(sock, SHUT_RDWR);
    if (status == 0)
        status = close(sock);
#endif
    return status;
}

int nr_socket_connect(int sock, char* hostname, int port) {
    struct hostent *host;
    if ((host = gethostbyname(hostname)) == NULL) {
        puts("Failed to resolve hostname\n");
        return 0;
    }

    struct sockaddr_in addr;
    addr.sin_port = htons((u_short) port);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = *((unsigned long*)host->h_addr);

    int result = 0;
    if ((result = connect((SOCKET) sock, (const struct sockaddr *) &addr, sizeof(addr))) != 0) {
        puts("Failed to connect to server\n");
        return nr_socket_shutdown(sock);
    }
    return result;
}

int nr_socket_bind(int sock, char* hostname, int port) {
    struct sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr(hostname);
    service.sin_port = htons((u_short) port);

    int result = bind((SOCKET)sock, (const struct sockaddr*)&service, sizeof(service));
    if (result == SOCKET_ERROR) {
        puts("Bind failed\n");
        return nr_socket_shutdown(sock);
    }
    return result;
}

int nr_socket_listen(int sock, int maxcon) {
    return listen((SOCKET)sock, maxcon);
}

int nr_socket_accept(int sock, struct sockaddr* addr, int* addrlen) {
    return accept((SOCKET)sock, NULL, NULL);
}

int nr_socket_send(int socket, char* data, size_t length) {
    int result = send((SOCKET) socket, data, length, 0);
    return result;
}

void  nr_socket_register_recv_callback(int socket, nr_socket_callback callback) {
    int result = 0;
    char buf[512];
    int buflen = 512;
    do {
        result = recv((SOCKET) socket, buf, buflen, 0);\
        callback(socket, buf);
    } while (result > 0);
    puts("\nEND RECV\n");
}