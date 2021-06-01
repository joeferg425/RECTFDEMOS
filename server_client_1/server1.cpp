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
#include "frame_header.h"

// #define SERVER_DEBUG 1

int server1_send(int socket_fd, unsigned char* buffer, int *length);
int server1_recv(int socket_fd, unsigned char* buffer, int *length);

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

    if (argc < 3)
    {
        printf("Please pass the following arguments: password, flag\n");
        exit(-1);
    }

    printf("Server Launching...\n");

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
                // receive a buffer of data
                result_i = server1_recv(clientSocket_fd, recvBuf_c, &length_i);
                if (result_i == SUCCESS)
                {
                    // send a buffer of data
                    if (strcmp((char*)recvBuf_c, argv[1]) == 0)
                    {
                        // strcpy(sendBuf_c, argv[2]);
                        sprintf((char*)sendBuf_c, "Congratulation! you have flag now!: %s", argv[2]);
                        length_i = (strlen((char*)sendBuf_c)+1);
                    }
                    else
                    {
                        strcpy((char*)sendBuf_c, "Sorry, please try again.");
                        length_i = (strlen((char*)sendBuf_c)+1);
                    }
                    result_i = server1_send(clientSocket_fd, sendBuf_c, &length_i);
                }
                else
                {
                    // I guess it died
                }
                if (result_i == RECEIVE_TIMEOUT)
                {
                    // dont exit
                    result_i = SUCCESS;
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

int server1_send(int socket_fd, unsigned char* buffer, int *length_i)
{
    int result_i = frame_send(socket_fd, buffer, length_i);
    if (result_i == SUCCESS)
    {
        printf("server1_send sent data: %s (%d bytes)\n", buffer, *length_i);
    }
    else if (result_i == RECEIVE_TIMEOUT)
    {
        #ifdef SERVER_DEBUG
        printf("server1_send timeout\n");
        #endif
    }
    else
    {
        printf("server1_send failed\n");
    }
    return result_i;
}
int server1_recv(int socket_fd, unsigned char* buffer, int *length_i)
{
    int result_i = frame_recv(socket_fd, buffer, length_i);
    if (result_i == SUCCESS)
    {
        printf("server1_recv received data: %s (%d bytes)\n", buffer, *length_i);
    }
    else if (result_i == RECEIVE_TIMEOUT)
    {
        #ifdef SERVER_DEBUG
        printf("server1_recv timeout\n");
        #endif
    }
    else
    {
        printf("server1_recv failed\n");
    }
    return result_i;
}
