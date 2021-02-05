#include <xc.h>
#include "7_seg_config.h"

void Config_7(adc_datos){
    seg1 = adc_datos;
    seg2 = adc_datos >> 4;
    
    switch(seg1)
    {
        case 0:
            seg1= 0b01111111;
            break;
        case 1:
            seg1= 0b0000110;
            break;
        case 2:
            seg1= 0b1011011;
            break;
        case 3:
            seg1= 0b1001111;
            break;
        case 4:
            seg1= 0b1100110;
            break;
        case 5:
            seg1= 0b1101101;
            break;
        case 6:
            seg1= 0b1111101;
            break;
        case 7:
            seg1= 0b0000111;
            break;
        case 8:
            seg1= 0b1111111;
            break;
        case 9:
            seg1= 0b1101111;
            break;
        case 10:
            seg1= 0b1110111;
            break;
        case 11:
            seg1= 0b1111111;
            break;
        case 12:
            seg1= 0b0111001;
            break;
        case 13:
            seg1= 0b0111111;
            break;
        case 14:
            seg1= 0b1111001;
            break;
        case 15:
            seg1= 0b1110001;
            break;
    }
    
     switch(seg2)
    {
        case 0:
            seg2= 0b01111111;
            break;
        case 1:
            seg2= 0b0000110;
            break;
        case 2:
            seg2= 0b1011011;
            break;
        case 3:
            seg2= 0b1001111;
            break;
        case 4:
            seg2= 0b1100110;
            break;
        case 5:
            seg2= 0b1101101;
            break;
        case 6:
            seg2= 0b1111101;
            break;
        case 7:
            seg2= 0b0000111;
            break;
        case 8:
            seg2= 0b1111111;
            break;
        case 9:
            seg2= 0b1101111;
            break;
        case 10:
            seg2= 0b1110111;
            break;
        case 11:
            seg2= 0b1111111;
            break;
        case 12:
            seg2= 0b0111001;
            break;
        case 13:
            seg2= 0b0111111;
            break;
        case 14:
            seg2= 0b1111001;
            break;
        case 15:
            seg2= 0b1110001;
            break;
    }
}