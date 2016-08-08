//
// Created by Ruto on 8/4/2016.
//

#include <stdio.h>
#ifdef _WIN32
/* See http://stackoverflow.com/questions/12765743/getaddrinfo-on-win32 */
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501  /* Windows XP. */
#endif
#include <winsock2.h>
#include <Ws2tcpip.h>
#pragma comment (lib, "Ws2_32.lib")
#else
#ifndef SOCKET
#define SOCKET int
#endif
#ifndef SOCKET_ERROR
#define SOCKET_ERROR	(-1)
#endif
/* Assume that any non-Windows platform uses POSIX-style sockets instead. */
  #include <sys/socket.h>
  #include <arpa/inet.h>
  #include <netdb.h>  /* Needed for getaddrinfo() and freeaddrinfo() */
  #include <unistd.h> /* Needed for close() */
#endif

typedef void (*nr_socket_callback)(int, char*);

int nr_socket_create(void);

int nr_socket_shutdown(int);

int nr_socket_connect(int, char*, int);

int nr_socket_bind(int, char*, int);

int nr_socket_listen(int, int);

int nr_socket_accept(int, struct sockaddr*, int*);

void nr_socket_register_recv_callback(int, nr_socket_callback);

int nr_socket_send(int socket, char* data, size_t length);