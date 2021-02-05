
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
#include <stdint.h>

//******************************************************************************
// Defines
//******************************************************************************

#define _XTAL_FREQ 4000000

#define tmr_preload 6;
#define push_debounce_time 200
#define mux_time 40


//******************************************************************************
// Variables
//******************************************************************************

uint8_t cont1 = 0;
uint8_t ban_B = 0;
uint8_t Timer = 0;
uint8_t timer_mux = 0;
uint8_t adc_datos = 0;
int seg1;
int seg2;
//******************************************************************************
// function declarations
//******************************************************************************

void setup(void);
void config_boton(void);
void config_adc(void);
void config_mux(void);

//******************************************************************************
// Main
//******************************************************************************

void main(void)
{
    setup();
    while(1) 
    {
        //**********************************************************************
        // Text goes here
        //**********************************************************************
        config_boton();
        config_adc();
        config_mux();

        PORTEbits.RE2 = adc_datos >= cont1 ? 1 : 0;

        PORTD = cont1;
    }
}

void __interrupt() isr(void)
{
    if (INTCONbits.RBIF)
    {
        INTCONbits.RBIF = 0;
        ban_B = PORTB;
    }

    if (INTCONbits.T0IF)
    {
        INTCONbits.T0IF = 0;
        TMR0 = tmr_preload;
        Timer++;
        timer_mux++;
    }

    if (PIR1bits.ADIF)
    {
        adc_datos = ADRESH;
    }
}

void config_mux(void)
{
    if (mux_time != timer_mux)
    {
        return;
    }

    timer_mux = 0;

}

void config_adc(void)
{
    if (ADCON0bits.GO)
    {
        return;
    }
}

void config_boton(void)
{
    if (push_debounce_time != Timer)
    {
        return;
    }

    Timer = 0;

    if (0x01 == ban_B)
    {
        cont1++;
    }

    if (0x02 == ban_B)
    {
        cont1--;
    }

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

    TMR0 = tmr_preload;

    INTCONbits.T0IF = 0;

    return;
}