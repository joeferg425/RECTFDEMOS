#include "socket_header.hpp"
#include "frame_header.hpp"
#include "crc16.hpp"

/* packet definition
Name                    | Index   | Description
packet_length_high_byte | 0       | total packet length / 256
packet_length_low_byte  | 1       | total packet length % 256
address_from_byte       | 2       | sender id
address_to_byte         | 3       | receiver id
sequence_number         | 4       | ascending transaction counter
function_code           | 5       | function id
data_identifier         | 6       | index of data item on server
data                    | 7-(n-2) | data bytes
crc                     | (n-2)-n | 16-bit crc
*/

// #define PACKET_DEBUG 1

enum packet_index_e
{
    PKT_FROM = 0,
    PKT_TO = 1,
    PKT_SEQ = 2,
    PKT_FUNC = 3,
    PKT_ID = 4,
    PKT_DATA = 5,
};

unsigned char SEQUENCE = 0;
#define HEADER_LENGTH 5
#define CRC_LENGTH 2
#define HEADER_LENGTH_PLUS_LENGTH_FIELD (HEADER_LENGTH + 2)
#define SERVER_MODEL "DEMO-3000-S"
#define CLIENT_MODEL "DEMO-3000-C"
#define SERVER_NAME "Jeffrey"
#define CLIENT_NAME "Stuart"
#define SERVER_ID 0xCA
#define CLIENT_ID 0xFE
#define FUNCTION_READ_REQUEST 36
#define FUNCTION_READ_RESPONSE 66
#define FUNCTION_WRITE_REQUEST 39
#define FUNCTION_WRITE_RESPONSE 69

enum FAILURES_e
{
    MENU_FAILURE = 10,
    CRC_CALCULATION_FAILURE = 11,
    CRC_CHECK_FAILURE = 12,
};

struct packet_data_s
{
    int length;
    unsigned char from;
    unsigned char to;
    unsigned char sequence;
    unsigned char function;
    unsigned char id;
    unsigned char data[BUFSIZE];
    unsigned short crc;
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

enum server_identifiers_e
{
    ID_NAME = 0,
    ID_MODL = 1,
    ID_AUTH = 2,
    ID_EXIT = 3,
    ID_LOGN = 4,
    ID_VOLT = 5,
    ID_CURR = 6,
    ID_POWR = 7,
    ID_FLAG = 8,
};
#define ID_COUNT ID_FLAG+1
#define ID_REQUIRES_AUTH ID_VOLT

#define CRC_POLYNOMIAL 0xBEEF

int pack_packet(unsigned char* buffer_c, struct packet_data_s* packet_s, int* length_i)
{
    int result_i = SUCCESS;
    packet_s->sequence = SEQUENCE++;
    buffer_c[PKT_FROM] = packet_s->from;
    buffer_c[PKT_TO] = packet_s->to;
    buffer_c[PKT_SEQ] = packet_s->sequence;
    buffer_c[PKT_FUNC] = packet_s->function;
    buffer_c[PKT_ID] = packet_s->id;
    strncpy((char*)&buffer_c[PKT_DATA], (char*)packet_s->data, packet_s->length);
    *length_i = (HEADER_LENGTH + packet_s->length);
    result_i = crc16((buffer_c+HEADER_LENGTH), *length_i-HEADER_LENGTH, &packet_s->crc, CRC_POLYNOMIAL);
    buffer_c[*length_i] = (unsigned char)(packet_s->crc / 256);
    buffer_c[*length_i +1] = (unsigned char)(packet_s->crc % 256);
    *length_i += CRC_LENGTH;
    return result_i;
}
int parse_packet(unsigned char* buffer_c, struct packet_data_s* packet_s, int* length_i)
{
    int result_i = SUCCESS;
    unsigned short crc_check = 0;
    packet_s->from = buffer_c[PKT_FROM];
    packet_s->to = buffer_c[PKT_TO];
    packet_s->sequence = buffer_c[PKT_SEQ];
    packet_s->function = buffer_c[PKT_FUNC];
    packet_s->id = buffer_c[PKT_ID];
    packet_s->length = (*length_i - HEADER_LENGTH - CRC_LENGTH);
    strncpy((char*)packet_s->data, (char*)&buffer_c[HEADER_LENGTH], packet_s->length);
    packet_s->crc = (256 * buffer_c[(*length_i - 2)]);
    packet_s->crc += buffer_c[(*length_i - 1)];
    result_i = crc16((buffer_c+HEADER_LENGTH), (*length_i-HEADER_LENGTH-CRC_LENGTH), &crc_check, CRC_POLYNOMIAL);
    if (crc_check != packet_s->crc)
    {
        result_i = CRC_CHECK_FAILURE;
    }
    return result_i;
}
