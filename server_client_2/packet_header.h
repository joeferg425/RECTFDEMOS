#include "socket_header.h"

/* packet definition
Name                    | Index | Description
packet_length_high_byte | 0     | total packet length / 256
packet_length_low_byte  | 1     | total packet length % 256
address_from_byte       | 2     | sender id
address_to_byte         | 3     | receiver id
sequence_number         | 4     | ascending transaction counter
function_code           | 5     | function id
data                    | 6+    | data bytes
*/

unsigned char SEQUENCE = 0;
#define HEADER_LENGTH 4
#define HEADER_LENGTH_PLUS_LENGTH_FIELD (HEADER_LENGTH + 2)
#define SERVER_MODEL "DEMO-3000-S"
#define CLIENT_MODEL "DEMO-3000-C"
#define SERVER_NAME "Jeffrey"
#define CLIENT_NAME "Stuart"
#define SERVER_ID 0xCA
#define CLIENT_ID 0xFE

enum FAILURES_e
{
    MENU_FAILURE = 10,
};

struct packet_data_s
{
    int length;
    unsigned char from;
    unsigned char to;
    unsigned char function;
    unsigned char sequence;
    // int dataLength;
    unsigned char data[BUFSIZE];
};

struct server_data_s
{
    char name[BUFSIZE];
    float voltage;
    float current;
    float power;
    char password[BUFSIZE];
    bool authorized;
    bool exit;
};

enum server_function_e
{
    FUNC_NAME = 0,
    FUNC_MODL = 1,
    FUNC_VOLT = 2,
    FUNC_CURR = 3,
    FUNC_POWR = 4,
    FUNC_LOGN = 5,
    FUNC_AUTH = 6,
    FUNC_EXIT = 7,
};
#define FUNC_MAX FUNC_EXIT


int pack_packet(unsigned char* buffer_c, struct packet_data_s* packet_s, int* length_i)
{
    // buffer[0] = (unsigned char)(packetHeader.length / 256);
    // buffer[1] = (unsigned char)(packetHeader.length % 256);
    packet_s->sequence = SEQUENCE++;
    buffer_c[0] = packet_s->from;
    buffer_c[1] = packet_s->to;
    buffer_c[2] = packet_s->sequence;
    buffer_c[3] = packet_s->function;
    strncpy((char*)&buffer_c[HEADER_LENGTH], (char*)packet_s->data, packet_s->length);
    *length_i = (HEADER_LENGTH + packet_s->length);
    return SUCCESS;
}
int parse_packet(unsigned char* buffer_c, struct packet_data_s* packet_s, int* length_i)
{
    // packetHeader.length = (256 * buffer[0]);
    // packetHeader.length += buffer[1];
    packet_s->from = buffer_c[0];
    packet_s->to = buffer_c[1];
    packet_s->sequence = buffer_c[2];
    packet_s->function = buffer_c[3];
    packet_s->length = (*length_i - HEADER_LENGTH);
    strncpy((char*)packet_s->data, (char*)&buffer_c[HEADER_LENGTH], packet_s->length);
    return SUCCESS;
}