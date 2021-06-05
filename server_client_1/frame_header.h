#ifndef __PACKET_HEADER__
#define __PACKET_HEADER__
#include "socket_header.h"
#include <string.h>
#include <stdio.h>
// unsigned char packetBuffer_c[BUFSIZE];
// int packetLength_i;

// #define FRAME_DEBUG 1

#define FRAME_HEADER_LENGTH 2

/* packet definition
Name             | Description
length_high_byte | total packet length / 256
length_low_byte  | total packet length % 256
*/


int frame_send(int socket_fd, unsigned char* buffer_c, int *length_i)
{
    int result_i = SUCCESS;
    int counter_i = 0;
    unsigned char frameBuffer_c[FRAME_HEADER_LENGTH];
    int frameLength_i = 0;

    frameBuffer_c[counter_i++] = (unsigned char)(*length_i / 256);
    frameBuffer_c[counter_i++] = (unsigned char)(*length_i % 256);
    // strncpy((char*)&frameBuffer_c[counter_i], (char*)frameBuffer_c, *length_i);
    // *length_i += counter_i;

    frameLength_i = FRAME_HEADER_LENGTH;
    result_i = socket_send(socket_fd, frameBuffer_c, &frameLength_i);
    if (frameLength_i == FRAME_HEADER_LENGTH)
    {
        result_i = SUCCESS;
        #ifdef FRAME_DEBUG
        printf("frame_send sent header data: ");
        for (int i = 0; i < FRAME_HEADER_LENGTH; i++)
        {
            printf("%02X ", frameBuffer_c[i]);
        }
        printf(" (%d bytes)\n", frameLength_i);
        #endif
    }
    else
    {
        #ifdef FRAME_DEBUG
        printf("frame_send send header failed\n");
        #endif
        result_i = SEND_FAILED;
    }

    frameLength_i = *length_i;
    result_i = socket_send(socket_fd, buffer_c, &frameLength_i);
    if (frameLength_i == *length_i)
    {
        result_i = SUCCESS;
        #ifdef FRAME_DEBUG
        printf("frame_send sent data: %s (%d bytes)\n", (char*)buffer_c, frameLength_i);
        #endif
    }
    else
    {
        #ifdef FRAME_DEBUG
        printf("frame_send send data failed\n");
        #endif
        frameLength_i = -1;
        result_i = SEND_FAILED;
    }
    *length_i = frameLength_i;
    return result_i;
}

int frame_recv(int socket_fd, unsigned char* buffer_c, int *length_i)
{
    int result_i = SUCCESS;
    unsigned char frameBuffer_c[FRAME_HEADER_LENGTH];
    int frameLength_i;
    // int header_length = 2;

    // read length
    frameLength_i = FRAME_HEADER_LENGTH;
    result_i = socket_recv(socket_fd, frameBuffer_c, &frameLength_i);
    // packetBuffer_c[packetLength_i+1] = 0;
    if (result_i == SUCCESS)
    {
        if (frameLength_i == FRAME_HEADER_LENGTH)
        {
            #ifdef FRAME_DEBUG
            printf("frame_recv header received data: ");
            for (int i = 0; i < FRAME_HEADER_LENGTH; i++)
            {
                printf("%02X ", frameBuffer_c[i]);
            }
            printf(" (%d bytes)\n", frameLength_i);
            #endif
            result_i = SUCCESS;
        }
        else
        {
            result_i = RECEIVE_FAILED;
            frameLength_i = -1;
            #ifdef FRAME_DEBUG
            printf("frame_recv header received data: ");
            #endif
        }
    }
    if (result_i == SUCCESS)
    {
        // header_length = 0;
        *length_i = (frameBuffer_c[0] * 256);
        *length_i += frameBuffer_c[1];
        #ifdef FRAME_DEBUG
        printf("frame_recv packet length: %d\n", *length_i);
        #endif

        // if (packetLength_i < *length)
        // {
        //     *length = packetLength_i;
        //     result_i = socket_recv(socket_fd, &packetBuffer_c[header_length], length);
        // }
        // else
        // {
        //     buffer += 2;
        // }
        frameLength_i = *length_i;
        result_i = socket_recv(socket_fd, buffer_c, &frameLength_i);
        if (result_i == SUCCESS)
        {
            if (*length_i == frameLength_i)
            {
                result_i = SUCCESS;
                // strncpy((char*)buffer_c, (char*)&packetBuffer_c, *length_i);
                #ifdef FRAME_DEBUG
                printf("frame_recv received data: %s (%d bytes)\n", buffer_c, frameLength_i);
                #endif
            }
            else
            {
                result_i = RECEIVE_FAILED;
                *length_i = -1;
                #ifdef FRAME_DEBUG
                printf("frame_recv receive failed\n");
                #endif
            }
        }
    }
    return result_i;
}

#endif