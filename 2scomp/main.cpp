#include <iostream>
#include <stdint.h>

const uint32_t ADC_DC_OFFSET_ADD     = (0xFFFFFF/2);   // 2^24 half-scale, added to 2's comp. ADC data

void give_me(uint8_t* data) {
    data[0] = 0x8c;  // msb
    data[1] = 0x2;
    data[2] = 0x1;  // lsb
}

int main()
{
    uint8_t recv[3] = {0,0,0};
    give_me(recv);

    uint32_t dc_offset = ADC_DC_OFFSET_ADD;

    uint32_t high = (uint32_t)((uint8_t)recv[0] & 0xff) << 16;
    uint32_t mid = (uint32_t)((uint8_t)recv[1] & 0xff) << 8;
    uint32_t low = (uint32_t)((uint8_t)recv[2] & 0xff);
    uint32_t adc_data = high | mid | low;

    int32_t realneg;
    bool is_neg = (adc_data & 0x800000) > 0;
    if (is_neg) {
        adc_data = (~adc_data + 1) & 0x7fffff;
        realneg = -1 * static_cast<int32_t>(adc_data);
    }
    else
    {
        realneg = static_cast<int32_t>(adc_data);
    }
    uint32_t res = (uint32_t)(realneg + (int32_t)dc_offset) & 0xffffff;

    printf("[0x%X:0x%X:0x%X] => 0x%X(0x%X:%d) + 0x%X(%d) => 0x%X(%d)\n",recv[0],recv[1],recv[2],adc_data,(uint32_t)realneg,realneg,dc_offset,dc_offset,res,res);

    return 0;
}
