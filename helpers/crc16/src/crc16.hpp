#include <stdio.h>

#define CRC16_SUCCESS 0
#define CRC16_FAILURE 1

int crc16(unsigned char *buffer_c, int buffer_len_i, unsigned short* crc, unsigned int crc_polynomial)
{
    // unsigned short out = 0;
    int bits_counter = 0;
    int bit_flag = 0;
    int result_i = CRC16_SUCCESS;
    unsigned int temp_crc = 0xFFFF;

    /* Sanity check: */
    if(buffer_c == NULL)
    {
        result_i = CRC16_FAILURE;
    }
    if (result_i == CRC16_SUCCESS)
    {
        while(buffer_len_i > 0)
        {
            bit_flag = temp_crc >> 15;

            /* Get next bit: */
            temp_crc <<= 1;
            temp_crc &= 0xFFFF;
            temp_crc |= (*buffer_c >> bits_counter) & 1;
            bits_counter++;
            if(bits_counter > 7)
            {
                bits_counter = 0;
                buffer_c++;
                buffer_len_i--;
            }
            if(bit_flag)
            {
                temp_crc ^= crc_polynomial;
                temp_crc &= 0xFFFF;
            }
        }
        *crc = (unsigned short)temp_crc;
    }
    return result_i;
}
