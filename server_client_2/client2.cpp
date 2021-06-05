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
int client2_recv(int socket_fd, unsigned char* buffer_c, struct packet_data_s* packet_s, int *length, bool print);
int interact(struct server_data_s serverData_s, struct packet_data_s* packet_s);
bool first = true;

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
                    result_i = client2_recv(clientSocket_fd, recvBuf_c, &packet_s, &length_i, true);
                    if (result_i == SUCCESS)
                    {
                        packet_s.function = FUNCTION_READ_REQUEST;
                        packet_s.id = ID_AUTH;
                        packet_s.length = 0;
                        packet_s.data[0] = 0;
                        result_i = client2_send(clientSocket_fd, sendBuf_c, &packet_s, &length_i);
                        if (result_i == SUCCESS)
                        {
                            // receive a buffer_c
                            result_i = client2_recv(clientSocket_fd, recvBuf_c, &packet_s, &length_i, false);
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
    packet_s->from = CLIENT_ID;
    packet_s->to = SERVER_ID;
    if (first == true)
    {
        printf("Welcome to CTF Server!\n");
        first = false;
    }
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
                packet_s->function = FUNCTION_READ_REQUEST;
                packet_s->id = ID_NAME;
                packet_s->length = 0;
                break;
            }
            case 'm':
            case 'M':
            {
                packet_s->function = FUNCTION_READ_REQUEST;
                packet_s->id = ID_MODL;
                packet_s->length = 0;
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
                packet_s->function = FUNCTION_WRITE_REQUEST;
                packet_s->id = ID_LOGN;
                break;
            }
            default:
            {
                printf("Invalid option: \"%c\"\n", ch);
                packet_s->length = 0;
                result_i = MENU_FAILURE;
                break;
            }
        }
    }
    else
    {
        printf("Read or write\n");
        printf("R: Read\n");
        printf("W: Write\n");
        printf(">> ");
        buffer_c[0] = 0;
        result_i = SUCCESS;
        for (packet_s->length = 0; (packet_s->length < (BUFSIZE-1)) && ((ch = getchar()) != EOF) && (ch != '\n'); packet_s->length++)
        {
            buffer_c[packet_s->length] = (char) ch;
        }
        switch(buffer_c[0])
        {
            case 'r':
            case 'R':
            {
                packet_s->function = FUNCTION_READ_REQUEST;
                break;
            }
            case 'w':
            case 'W':
            {
                packet_s->function = FUNCTION_WRITE_REQUEST;
                break;
            }
            default:
            {
                result_i = MENU_FAILURE;
                break;
            }
        }
        if (result_i == SUCCESS)
        {
            printf("n: Name\n");
            printf("m: Model\n");
            printf("v: Voltage\n");
            printf("c: Current\n");
            printf("w: Power\n");
            printf("a: Authorization\n");
            printf("p: Password\n");
            printf("q: Quit\n");
            printf(">> ");
            for (packet_s->length = 0; (packet_s->length < (BUFSIZE-1)) && ((ch = getchar()) != EOF) && (ch != '\n'); packet_s->length++)
            {
                buffer_c[packet_s->length] = (char) ch;
            }
            switch (buffer_c[0])
            {
                case 'n':
                case 'N':
                {
                    packet_s->id = ID_NAME;
                    packet_s->data[0] = 0;
                    packet_s->length = 0;
                    break;
                }
                case 'm':
                case 'M':
                {
                    packet_s->id = ID_MODL;
                    packet_s->data[0] = 0;
                    packet_s->length = 0;
                    break;
                }
                case 'v':
                case 'V':
                {
                    packet_s->id = ID_VOLT;
                    packet_s->data[0] = 0;
                    packet_s->length = 0;
                    break;
                }
                case 'c':
                case 'C':
                {
                    packet_s->id = ID_CURR;
                    packet_s->data[0] = 0;
                    packet_s->length = 0;
                    break;
                }
                case 'w':
                case 'W':
                {
                    packet_s->id = ID_POWR;
                    packet_s->data[0] = 0;
                    packet_s->length = 0;
                    break;
                }
                case 'p':
                case 'P':
                {
                    packet_s->id = ID_LOGN;
                    packet_s->data[0] = 0;
                    packet_s->length = 0;
                    break;
                }
                case 'a':
                case 'A':
                {
                    packet_s->id = ID_AUTH;
                    packet_s->data[0] = 0;
                    packet_s->length = 0;
                    break;
                }
                case 'q':
                case 'Q':
                {
                    packet_s->id = ID_EXIT;
                    packet_s->data[0] = 0;
                    packet_s->length = 0;
                    break;
                }
                default:
                {
                    printf("Invalid option: \"%c\"\n", ch);
                    packet_s->data[0] = 0;
                    packet_s->length = 0;
                    result_i = MENU_FAILURE;
                    break;
                }
            }
            if (result_i == SUCCESS)
            {
                if (packet_s->function == FUNCTION_WRITE_REQUEST)
                {
                    printf("Enter Value\n");
                    printf(">> ");
                    buffer_c[0] = 0;
                    for (packet_s->length = 0; (packet_s->length < (BUFSIZE-1)) && ((ch = getchar()) != EOF) && (ch != '\n'); packet_s->length++)
                    {
                        packet_s->data[packet_s->length] = (char) ch;
                    }
                    packet_s->data[packet_s->length] = 0;
                    packet_s->length++;
                }
            }
        }
    }
    return result_i;
}

int client2_send(int socket_fd, unsigned char* buffer_c, struct packet_data_s* packet_s, int *length_i)
{
    int result_i = pack_packet(buffer_c, packet_s, length_i);
    frame_send(socket_fd, buffer_c, length_i);
    #ifdef PACKET_DEBUG
    printf("client2_send sent data:\n");
    printf(" From      : %d\n", packet_s->from);
    printf(" To        : %d\n", packet_s->to);
    printf(" Sequence  : %d\n", packet_s->sequence);
    printf(" Function  : %d\n", packet_s->function);
    printf(" Identifier: %d\n", packet_s->id);
    printf(" Data      : %s\n", (char*)packet_s->data);
    printf(" CRC       : %04X\n", packet_s->crc);
    printf(" DataLen   : %d\n", packet_s->length);
    #endif
    return result_i;
}

int client2_recv(int socket_fd, unsigned char* buffer_c, struct packet_data_s* packet_s, int *length_i, bool print)
{
    int result_i = frame_recv(socket_fd, buffer_c, length_i);
    result_i = parse_packet(buffer_c, packet_s, length_i);
    #ifdef PACKET_DEBUG
    printf("client2_recv received data:\n");
    printf(" From      : %d\n", packet_s->from);
    printf(" To        : %d\n", packet_s->to);
    printf(" Sequence  : %d\n", packet_s->sequence);
    printf(" Function  : %d\n", packet_s->function);
    printf(" Identifier: %d\n", packet_s->id);
    printf(" Data      : %s\n", (char*)packet_s->data);
    printf(" CRC       : %04X\n", packet_s->crc);
    printf(" DataLen   : %d\n", packet_s->length);
    #else
    if (print == true)
    {
        // printf("%d %d %s\n", packet_s->function, packet_s->id, (char*)packet_s->data);
        printf("%s\n\n", (char*)packet_s->data);
    }
    #endif
    return result_i;
}