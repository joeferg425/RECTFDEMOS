// #define WIN32_LEAN_AND_MEAN

#ifdef __linux__
    //linux code goes here
    #include <unistd.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
#elif _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
    #pragma comment (lib, "Mswsock.lib")
#endif
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "socket_header.hpp"

#define DEBUG_CLIENT 1

int client0_send(int socket_fd, unsigned char* buffer, int *length);
int client0_recv(int socket_fd, unsigned char* buffer, int *length);

int main(int argc, char const **argv)
{
    int clientSocket_fd;
    struct sockaddr_in addr_s;
    int length_i = 0;
    unsigned char sendBuf_c[BUFSIZE] = {0};
    unsigned char recvBuf_c[BUFSIZE];
    int result_i = CONNECT_FAILED;

    printf("Client Launching...\n");

    // setup a default buffer
    strcpy((char*)sendBuf_c, "YO");
    length_i = READ_WRITE_LEN;

    // create the client socket
    while (true)
    {
        result_i = client_connect(&clientSocket_fd, PORT);
        if (result_i != SUCCESS)
        {
            // nobody is talking to us, so go to sleep for a bit
            #ifdef __linux__
                sleep(2);
            #elif _WIN32
                Sleep(2000);
            #endif
        }
        else
        {
            // Send & receive loop
            while(result_i == SUCCESS)
            {
                // Send a buffer
                length_i = READ_WRITE_LEN;
                result_i = client0_send(clientSocket_fd, sendBuf_c, &length_i);
                if (result_i == SUCCESS)
                {
                    // receive a buffer
                    result_i = client0_recv(clientSocket_fd, recvBuf_c, &length_i);
                    if (result_i == SUCCESS)
                    {
                        printf("Client Received data: %s (%d bytes)\n", recvBuf_c, length_i);
                    }
                }
                else
                {
                    // it died
                }
            }
        }
        // kill the socket
        #ifdef __linux__
            close(clientSocket_fd);
        #elif _WIN32
            closesocket(clientSocket_fd);
        #endif
    }
    return result_i;
}


int client0_send(int socket_fd, unsigned char* buffer, int *length_i)
{
    int result_i = socket_send(socket_fd, buffer, length_i);
    if (result_i == SUCCESS)
    {
        printf("client0_send sent data: %s (%d bytes)\n", buffer, *length_i);
    }
    else
    {
        printf("client0_send failed\n");
    }
    return result_i;
}

int client0_recv(int socket_fd, unsigned char* buffer, int *length_i)
{
    int result_i = socket_recv(socket_fd, buffer, length_i);
    if (result_i == SUCCESS)
    {
        printf("client0_recv received data: %s (%d bytes)\n", buffer, *length_i);
    }
    else
    {
        printf("client0_recv failed\n");
    }
    return result_i;
}