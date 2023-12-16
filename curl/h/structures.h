#ifndef CURL_H_STRUCTURES_H_
#define CURL_H_STRUCTURES_H_

#include <netinet/in.h>

typedef struct s_socket
{
    struct addrinfo* data;
    struct sockaddr_in inform;
} sock_info;

#endif