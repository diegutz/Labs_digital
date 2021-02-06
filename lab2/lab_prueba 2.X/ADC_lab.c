
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT
#pragma config WDTE = OFF       
#pragma config PWRTE = OFF      
#pragma config MCLRE = OFF      
#pragma config CP = OFF         
#pragma config CPD = OFF        
#pragma config BOREN = OFF      
#pragma config IESO = OFF       
#pragma config FCMEN = OFF      
#pragma config LVP = OFF        

// CONFIG2
#pragma config BOR4V = BOR40V   
#pragma config WRT = OFF        

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

//******************************************************************************
// Includes
//******************************************************************************

#include <xc.h>
#DEVICE ADC=8
#USE DELAY(clock = 4000000)
//******************************************************************************
// Variables
//******************************************************************************

int adc_dato;
int seg1;
int seg2;
//******************************************************************************
// function declarations
//******************************************************************************

void setup(void);

void main(void) {
    set_adc_channel(0);
    delay_ms(1);
    adc_dato = read_adc();
    
    PORTD = adc_dato;
    return;
}
//******************************************************************************
// Configuration
//******************************************************************************
void setup(void)
{
    ANSEL  = 0x01;
    ANSELH = 0x00;
    
    TRISA = 0x01;
    TRISB = 0x03;
    TRISC = 0x00;
    TRISD = 0x00;
    TRISE = 0x00;
    
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0;

    // portb interrupts
    IOCB = 0x03;
    INTCONbits.RBIE = 1;
    INTCONbits.T0IE = 1;
    INTCONbits.GIE = 1;
    
    OSCCON = 0b01100001;

    OPTION_REGbits.T0CS = 0;
    OPTION_REGbits.PSA = 0;
    OPTION_REGbits.PS2 = 0;
    OPTION_REGbits.PS1 = 0;
    OPTION_REGbits.PS0 = 1;

    INTCONbits.T0IF = 0;
    

    return;
}