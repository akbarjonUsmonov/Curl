#include "../h/sock_process.h"
#include <stdio.h>
#include <stdlib.h>

char** extract_hostname_path(char* url)
{
    int url_length = my_strlen(url);
    int flag = 0;
    int host_length = 0;
    char** host_path = (char**)malloc(sizeof(char*) * 2);
    host_path[0] = calloc((url_length + 1), sizeof(char));
    for (int i = 0; i < url_length; i++)
    {
        if (url[i] == '/' && url[i - 1] == '/')
        {
            flag = 1;
        }
        else if (flag == 1)
        {
            host_path[0][host_length++] = url[i];
            if (url[i + 1] == '/')
            {
                flag = 2;
            }
        }
        else if (flag == 2)
        {
            host_path[1] = my_strdup(&url[i]);
            break;
        }
    }
    if (host_path[0][0] == '\0')
    {
        my_strcpy(host_path[0], url);
    }
    if (host_path[1] == NULL)
    {
        host_path[1] = my_strdup("/");
    }
    return host_path;
}

in_addr_t get_ipv4(char* host, sock_info* information)
{
    struct addrinfo hints;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    int status = getaddrinfo(host, "http", &hints, &(information->data));

    if (status != 0)
    {
        failure_statement("nodename nor servname provided, or not known\n");
    }

    if (information->data == NULL)
    {
        failure_statement("No address found for the given hostname.\n");
    }

    struct sockaddr_in* ipv4 = (struct sockaddr_in*)(information->data->ai_addr);
    information->inform.sin_addr = ipv4->sin_addr;
    return information->inform.sin_addr.s_addr;
}

int fill_sock(char* host, sock_info* information)
{
    in_addr_t addr = get_ipv4(host, information);
    if (addr == 0)
    {
        failure_statement("Failed to retrieve the IPv4 address.\n");
    }
    char ip_address[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(information->inform.sin_addr), ip_address, INET_ADDRSTRLEN);
    information->inform.sin_port = htons(80);
    information->inform.sin_family = AF_INET;
    return 0;
}

char* request_formatting(char** host_path)
{
    char* request_form[3] = {"GET ", " HTTP/1.1\r\nHost: ", "\r\n\r\n"};
    int length = my_strlen(host_path[1]) + my_strlen(host_path[0]);
    length += my_strlen(request_form[0]) + my_strlen(request_form[1]) + my_strlen(request_form[2]);
    char* request = calloc(length + 1 , sizeof(char));
    my_strcpy(request, request_form[0]);
    my_strcpy(request, host_path[1]);
    my_strcpy(request, request_form[1]);
    my_strcpy(request, host_path[0]);
    my_strcpy(request, request_form[2]);
    return request;
}

void send_receive_data(int fd, char* request)
{
    write(fd, request, my_strlen(request));
    char data[4097] = {0};
    char* head = NULL;
    int flag = 0;
    int quantity = 0;
    int length = 0;
    while (1)
    {
        fill_null(data, 4096);
        quantity = read(fd, data, 4096);

        if (flag == 0)
        {
            if((head = strstr(data, "\r\n\r\n")))
            {
                head += 4;
                write(1, head, my_strlen(head));
                flag = 1;
            }
        }
        else
        {
            length++;
            write(1, data, quantity);
        }
        if (quantity < 4096)
        {
            break;
        }
    }
    if (length > 0)
    {
        write(1, data, my_strlen(data));
    }
    free(request);
    close(fd);
}

void free_host_path(char** host)
{
    for (int i = 0; i < 2; i++)
    {
        free(host[i]);
    }
    free(host);
}

int sockat_preparation(char* url)
{
    char** host_path = extract_hostname_path(url);
    int fd = 0;
    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        failure_statement("Socket fault\n");
    }
    sock_info information;
    fill_sock(host_path[0], &information);
    char* request = request_formatting(host_path);

    if ((connect(fd, (struct sockaddr*)&(information.inform), sizeof(information.inform))) < 0)
    {
        failure_statement("Connection failture\n");
    }
    freeaddrinfo(information.data);
    free_host_path(host_path);
    send_receive_data(fd, request);
    return 0;
}