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
#include "socket_header.h"

#define CLIENT_DEBUG 1

int server0_send(int socket_fd, unsigned char* buffer, int *length);
int server0_recv(int socket_fd, unsigned char* buffer, int *length);

int main(int argc, char const **argv)
{
    int serverSocket_fd;
    int clientSocket_fd;
    int valread;
    struct sockaddr_in clientAddr_s;
    int length_i = 0;
    unsigned char sendBuf_c[BUFSIZE] = {0};
    unsigned char recvBuf_c[BUFSIZE] = {0};
    int result_i = SUCCESS;

    printf("Server0 Launching...\n");

    // setup default buffer
    strcpy((char*)sendBuf_c, "HI");
    length_i = READ_WRITE_LEN;

    // open server socket
    result_i = server_connect(&serverSocket_fd, PORT);
    if (result_i == SUCCESS)
    {
        // listen on server socket
        result_i = server_listen(serverSocket_fd);
    }
    else
    {
        // i guess its not going to work, so bail out
    }
    while (true)
    {
        // wait for client connections
        result_i = server_accept(serverSocket_fd, &clientSocket_fd, &clientAddr_s);
        if (result_i != SUCCESS)
        {
            // go to sleep while waiting for client
            #ifdef __linux__
                sleep(2);
            #elif _WIN32
                Sleep(2000);
            #endif
        }
        else
        {
            // loop while connected
            while (result_i == SUCCESS)
            {
                // send a buffer of data
                length_i = READ_WRITE_LEN;
                result_i = server0_send(clientSocket_fd, sendBuf_c, &length_i);
                if (result_i == SUCCESS)
                {
                    // receive a buffer of data
                    result_i = server0_recv(clientSocket_fd, recvBuf_c, &length_i);
                }
                else
                {
                    // I guess it died
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
    // kill the socket
    #ifdef __linux__
        close(serverSocket_fd);
    #elif _WIN32
        closesocket(serverSocket_fd);
    #endif
    return 0;
}

int server0_send(int socket_fd, unsigned char* buffer, int *length_i)
{
    int result_i = socket_send(socket_fd, buffer, length_i);
    if (result_i == SUCCESS)
    {
        printf("server0_send sent data: %s (%d bytes)\n", buffer, *length_i);
    }
    else
    {
        printf("server0_send failed\n");
    }
    return result_i;
}
int server0_recv(int socket_fd, unsigned char* buffer, int *length_i)
{
    int result_i = socket_recv(socket_fd, buffer, length_i);
    if (result_i == SUCCESS)
    {
        printf("server0_recv received data: %s (%d bytes)\n", buffer, *length_i);
    }
    else
    {
        printf("server0_recv failed\n");
    }
    return result_i;
}
