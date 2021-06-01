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
#include "packet_header.h"

#define SERVER_DEBUG 1

int server2_send(int socket_fd, unsigned char* buffer, struct packet_data_s* packet_s, int *length);
int server2_recv(int socket_fd, unsigned char* buffer, struct server_data_s*, struct packet_data_s* packet_s, int *length);
int parse(struct server_data_s, unsigned char* recvBuffer_c, unsigned char* sendBuffer_c, int* length_i);

unsigned char PASSWORD[BUFSIZE];
unsigned char FLAG[BUFSIZE];

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
    struct server_data_s serverData = {0};
    serverData.authorized = false;
    struct packet_data_s packet_s = {0};

    if (argc < 3)
    {
        printf("Please pass the following arguments: password, flag\n");
        exit(-1);
    }

    printf("Server Launching...\n");

    strcpy((char*)PASSWORD, argv[1]);
    strcpy((char*)FLAG, argv[2]);

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
                result_i = server2_recv(clientSocket_fd, recvBuf_c, &serverData, &packet_s, &length_i);
                if (result_i == SUCCESS)
                {
                    // result_i = parse(serverData, recvBuf_c, sendBuf_c, &length_i);
                    // if (result_i == SUCCESS)
                    // {
                        result_i = server2_send(clientSocket_fd, sendBuf_c, &packet_s, &length_i);
                        if (result_i == SUCCESS)
                        {

                        }
                        else
                        {

                        }
                    // }
                }
                else if (result_i == RECEIVE_TIMEOUT)
                {
                    result_i = SUCCESS;
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
        serverData.authorized = false;
    }
    // kill the socket
    #ifdef __linux__
        close(serverSocket_fd);
    #elif _WIN32
        closesocket(serverSocket_fd);
    #endif
    return 0;
}

int server2_send(int socket_fd, unsigned char* buffer_c, struct packet_data_s* packet_s, int *length_i)
{
    packet_s->from = SERVER_ID;
    packet_s->to = CLIENT_ID;
    int result_i = pack_packet(buffer_c, packet_s, length_i);
    result_i = frame_send(socket_fd, buffer_c, length_i);
    #ifdef SOCKET_DEBUG
    printf("server2_send sent data:\n");
    printf(" From    : %d\n", packet_s->from);
    printf(" To      : %d\n", packet_s->to);
    printf(" Sequence: %d\n", packet_s->sequence);
    printf(" Function: %d\n", packet_s->function);
    printf(" Data    : %s\n", (char*)packet_s->data);
    printf(" DataLen :%d\n", packet_s->length);
    #endif
    return result_i;
}
int server2_recv(int socket_fd, unsigned char* buffer_c, struct server_data_s* server_s, struct packet_data_s* packet_s, int *length_i)
{
    int result_i = frame_recv(socket_fd, buffer_c, length_i);
    if (result_i == SUCCESS)
    {
        if (*length_i >= HEADER_LENGTH)
        {
            // struct packet_header_s recvHeader_s = {0};
            // struct packet_header_s sendHeader_s = {0};
            parse_packet(buffer_c, packet_s, length_i);
            printf("server2_recv received data:\n");
            printf(" From    : %d\n", packet_s->from);
            printf(" To      : %d\n", packet_s->to);
            printf(" Sequence: %d\n", packet_s->sequence);
            printf(" Function: %d\n", packet_s->function);
            printf(" Data    : %s\n", (char*)packet_s->data);
            printf(" DataLen :%d\n", packet_s->length);
            // sendHeader_s.from = SERVER_ID;
            // sendHeader_s.to = recvHeader_s.from;
            switch (packet_s->function)
            {
                case FUNC_LOGN:
                {
                    if (server_s->authorized == false)
                    {
                        // send a buffer of data
                        if (strcmp((char*)packet_s->data, (char*)PASSWORD) == 0)
                        {
                            // strcpy(sendBuf_c, argv[2]);
                            sprintf((char*)packet_s->data, "Congratulation! you have flag now!: %s", (char*)FLAG);
                            packet_s->length = (strlen((char*)packet_s->data)+1);
                            server_s->authorized = true;
                        }
                        else
                        {
                            strcpy((char*)packet_s->data, "Sorry, please try again.");
                            packet_s->length = (strlen((char*)packet_s->data)+1);
                            server_s->authorized = false;
                        }
                    }
                    else
                    {
                        strcpy((char*)packet_s->data, (char*)PASSWORD);
                        packet_s->length = (strlen((char*)packet_s->data)+1);
                    }
                    *length_i = packet_s->length;
                    break;
                }
                case FUNC_MODL:
                {
                    strcpy((char*)packet_s->data, SERVER_MODEL);
                    packet_s->length = (strlen((char*)packet_s->data)+1);
                    *length_i = packet_s->length;
                    break;
                }
                case FUNC_NAME:
                {
                    strcpy((char*)packet_s->data, SERVER_NAME);
                    packet_s->length = (strlen((char*)packet_s->data)+1);
                    *length_i = packet_s->length;
                    break;
                }
                case FUNC_VOLT:
                {
                    if (server_s->authorized == false)
                    {
                        strcpy((char*)packet_s->data, "Not Authorized");
                        packet_s->length = (strlen((char*)packet_s->data)+1);
                    }
                    else
                    {
                        strcpy((char*)packet_s->data, "119.5");
                        packet_s->length = (strlen((char*)packet_s->data)+1);
                    }
                    *length_i = packet_s->length;
                    break;
                }
                case FUNC_CURR:
                {
                    if (server_s->authorized == false)
                    {
                        strcpy((char*)packet_s->data, "Not Authorized");
                        packet_s->length = (strlen((char*)packet_s->data)+1);
                    }
                    else
                    {
                        strcpy((char*)packet_s->data, "9001");
                        packet_s->length = (strlen((char*)packet_s->data)+1);
                    }
                    *length_i = packet_s->length;
                    break;
                }
                case FUNC_POWR:
                {
                    if (server_s->authorized == false)
                    {
                        strcpy((char*)packet_s->data, "Not Authorized");
                        packet_s->length = (strlen((char*)packet_s->data)+1);
                    }
                    else
                    {
                        strcpy((char*)packet_s->data, "1.0");
                        packet_s->length = (strlen((char*)packet_s->data)+1);
                    }
                    *length_i = packet_s->length;
                    break;
                }
                case FUNC_AUTH:
                {
                    if (server_s->authorized == false)
                    {
                        strcpy((char*)packet_s->data, "false");
                        packet_s->length = (strlen((char*)packet_s->data)+1);
                    }
                    else
                    {
                        strcpy((char*)packet_s->data, "true");
                        packet_s->length = (strlen((char*)packet_s->data)+1);
                    }
                    *length_i = packet_s->length;
                    break;
                }
                case FUNC_EXIT:
                {
                    if (server_s->authorized == false)
                    {
                        strcpy((char*)packet_s->data, "Not Authorized");
                        packet_s->length = (strlen((char*)packet_s->data)+1);
                    }
                    else
                    {
                        strcpy((char*)packet_s->data, "Exiting");
                        packet_s->length = (strlen((char*)packet_s->data)+1);
                        exit(100);
                    }
                    *length_i = packet_s->length;
                    break;
                }
                default:
                {
                    printf("Invalid function: \"%d\"\n", packet_s->function);
                    result_i = MENU_FAILURE;
                    break;
                }
            }
        }
    }
    return result_i;
}