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
#include "socket_header.h"
#include "frame_header.h"
#include "packet_header.h"

#define CLIENT_DEBUG 1

int client2_send(int socket_fd, unsigned char* buffer_c, struct packet_data_s* packet_s, int *length);
int client2_recv(int socket_fd, unsigned char* buffer_c, struct packet_data_s* packet_s, int *length);
int interact(struct server_data_s serverData_s, struct packet_data_s* packet_s);

int main(int argc, char const **argv)
{
    int clientSocket_fd;
    struct sockaddr_in addr_s;
    int length_i = 0;
    unsigned char sendBuf_c[BUFSIZE] = {0};
    unsigned char recvBuf_c[BUFSIZE];
    int result_i = CONNECT_FAILED;
    char ch;
    struct server_data_s serverData_s = {0};
    struct packet_data_s packet_s = {0};

    printf("Client Launching...\n");

    // setup a default buffer_c
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
                result_i = interact(serverData_s, &packet_s);
                // Send a buffer_c
                // length_i++;
                // sendBuf_c[length_i] = 0;
                result_i = client2_send(clientSocket_fd, sendBuf_c, &packet_s, &length_i);
                if (result_i == SUCCESS)
                {
                    // receive a buffer_c
                    result_i = client2_recv(clientSocket_fd, recvBuf_c, &packet_s, &length_i);
                    if (result_i == SUCCESS)
                    {
                        packet_s.function = FUNC_AUTH;
                        packet_s.length = 0;
                        result_i = client2_send(clientSocket_fd, sendBuf_c, &packet_s, &length_i);
                        if (result_i == SUCCESS)
                        {
                            // receive a buffer_c
                            result_i = client2_recv(clientSocket_fd, recvBuf_c, &packet_s, &length_i);
                            if (result_i == SUCCESS)
                            {
                                if (strcmp((char*)packet_s.data, "true") == 0)
                                {
                                    serverData_s.authorized = true;
                                }
                                else
                                {
                                    serverData_s.authorized = false;
                                }
                            }
                        }
                        else
                        {
                            // it died
                        }
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

int interact(struct server_data_s data_s, struct packet_data_s* packet_s)//, unsigned char* buffer_c, int *length_i)
{
    int result_i = SUCCESS;
    char ch;
    unsigned char buffer_c[BUFSIZE];
    // struct packet_data_s packet_s = {0};
    packet_s->from = CLIENT_ID;
    packet_s->to = SERVER_ID;
    printf("Welcome to CTF Server!\n");
    if (data_s.authorized == false)
    {
        printf("l: Login\n");
        printf("n: Read Name\n");
        printf("m: Read Model\n");
        printf(">> ");
        buffer_c[0] = 0;
        for (packet_s->length = 0; (packet_s->length < (BUFSIZE-1)) && ((ch = getchar()) != EOF) && (ch != '\n'); packet_s->length++)
        {
            buffer_c[packet_s->length] = (char) ch;
        }
        switch(buffer_c[0])
        {
            case 'n':
            case 'N':
            {
                packet_s->function = FUNC_NAME;
                packet_s->length = 0;
                // pack_packet(buffer_c, &packet_s);
                break;
            }
            case 'm':
            case 'M':
            {
                packet_s->function = FUNC_MODL;
                packet_s->length = 0;
                // pack_packet(buffer_c, &packet_s);
                break;
            }
            case 'l':
            case 'L':
            {
                printf("Enter Password\n");
                printf(">> ");
                for (packet_s->length = 0; (packet_s->length < (BUFSIZE-1)) && ((ch = getchar()) != EOF) && (ch != '\n'); packet_s->length++)
                {
                    packet_s->data[packet_s->length] = (char) ch;
                }
                packet_s->data[packet_s->length] = 0;
                packet_s->length++;
                packet_s->function = FUNC_LOGN;
                // pack_packet(buffer_c, &packet_s);
                break;
            }
            default:
            {
                printf("Invalid option: \"%c\"\n", ch);
                packet_s->length = -1;
                result_i = MENU_FAILURE;
                break;
            }
        }
    }
    else
    {
        printf("n: Read Name\n");
        printf("m: Read Model\n");
        printf("v: Read Voltage\n");
        printf("c: Read Current\n");
        printf("a: Read Authorization\n");
        printf("p: Read Password\n");
        printf("e: Exit\n");
        printf("q: Quit\n");
        printf(">> ");
        ch = getchar();
        switch(ch)
        {
            case 'n':
            case 'N':
            {
                packet_s->function = FUNC_NAME;
                packet_s->length = 0;
                // pack_packet(buffer_c, &packet_s);
                break;
            }
            case 'm':
            case 'M':
            {
                packet_s->function = FUNC_MODL;
                packet_s->length = 0;
                // pack_packet(buffer_c, &packet_s);
                break;
            }
            case 'v':
            case 'V':
            {
                packet_s->function = FUNC_VOLT;
                packet_s->length = 0;
                // pack_packet(buffer_c, &packet_s);
                break;
            }
            case 'c':
            case 'C':
            {
                packet_s->function = FUNC_CURR;
                packet_s->length = 0;
                // pack_packet(buffer_c, &packet_s);
                break;
            }
            case 'p':
            case 'P':
            {
                packet_s->function = FUNC_POWR;
                packet_s->length = 0;
                // pack_packet(buffer_c, &packet_s);
                break;
            }
            case 'a':
            case 'A':
            {
                packet_s->function = FUNC_AUTH;
                packet_s->length = 0;
                // pack_packet(buffer_c, &packet_s);
                break;
            }
            case 'e':
            case 'E':
            {
                packet_s->function = FUNC_EXIT;
                packet_s->length = 0;
                // pack_packet(buffer_c, &packet_s);
                break;
            }
            default:
            {
                printf("Invalid option: \"%c\"\n", ch);
                packet_s->length = -1;
                result_i = MENU_FAILURE;
                break;
            }
        }
    }
    // *length_i = packet_s->length;
    return result_i;
}

int client2_send(int socket_fd, unsigned char* buffer_c, struct packet_data_s* packet_s, int *length_i)
{
    int result_i = pack_packet(buffer_c, packet_s, length_i);
    frame_send(socket_fd, buffer_c, length_i);
    #ifdef SOCKET_DEBUG
    printf("client2_send sent data:\n");
    printf(" From    : %d\n", packet_s->from);
    printf(" To      : %d\n", packet_s->to);
    printf(" Sequence: %d\n", packet_s->sequence);
    printf(" Function: %d\n", packet_s->function);
    printf(" Data    : %s\n", (char*)packet_s->data);
    printf(" DataLen : %d\n", packet_s->length);
    #endif
    return result_i;
}

int client2_recv(int socket_fd, unsigned char* buffer_c, struct packet_data_s* packet_s, int *length_i)
{
    int result_i = frame_recv(socket_fd, buffer_c, length_i);
    result_i = parse_packet(buffer_c, packet_s, length_i);
    printf("server2_recv received data:\n");
    printf(" From    : %d\n", packet_s->from);
    printf(" To      : %d\n", packet_s->to);
    printf(" Sequence: %d\n", packet_s->sequence);
    printf(" Function: %d\n", packet_s->function);
    printf(" Data    : %s\n", (char*)packet_s->data);
    printf(" DataLen : %d\n", packet_s->length);
    return result_i;
}