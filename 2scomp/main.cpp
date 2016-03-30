#include <iostream>
#include <stdint.h>
#include <string>

using namespace std;

const uint32_t ADC_DC_OFFSET_ADD     = (0xFFFFFF/2);   // 2^24 half-scale, added to 2's comp. ADC data

bool read_value(uint8_t* recv, uint32_t* pValue, uint32_t dc_offset) {

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

    //printf("[0x%X:0x%X:0x%X] => 0x%X(0x%X:%d) + 0x%X(%d) => 0x%X(%d)\n",recv[0],recv[1],recv[2],adc_data,(uint32_t)realneg,realneg,dc_offset,dc_offset,res,res);

    *pValue = res;
    return true;
}
int main()
{
    //  Don't sync C++ and C I/O
    // http://www.manticmoo.com/articles/jeff/programming/c++/making-io-streams-efficient-in-c++.php
    ios_base::sync_with_stdio(false);

    // get a line
    string str;
    while ( getline(cin,str)) {
        uint32_t in = stoi(str);

        uint8_t recv[3] = {0,0,0};
        recv[2] = (uint8_t)(in & 0xFF);
        recv[1] = (uint8_t)((in & 0xFF00) >> 8); 
        recv[0] = (uint8_t)((in & 0xFF0000) >> 16);

        uint32_t comp_val;
        if (read_value(recv, &comp_val,ADC_DC_OFFSET_ADD)) {
            printf("%d\n",comp_val);
            //printf("IN 0x%X -> %d (0x%X)\n",in,comp_val,comp_val);
        } else {
            fprintf(stderr,"FAIL: read_value(%s)\n",str.c_str());
        }
    }

    return 0;
}
