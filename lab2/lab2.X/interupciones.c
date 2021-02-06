//**************************
//IMPORTACION DE LIBRERIAS
//**************************
//#include <xc.h>
//#include "PIC16F887.h"  
//**************************
//IMPORTACION DE LIBRERIAS Y CONFIG DEL PIC
//**************************
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

//Frecuencia del oscilador
#define _XTAL_FREQ 8000000

//############## DECLARACION DE VARIABLES #######################

#include <xc.h>

//**************************
//PROTOTIPOS DE FUNCIONES
//**************************
void main(void);
void ADC(void);
void setup(void);
void multiplexor(void);
void aumentar(void);
void restar(void);
//**************************
//DECLARACION DE VARIABLES
//**************************
int cont0 = 0;
char ciclo = 1;
char todo = 1;
int adc;
float volt;
const unsigned char display[16] = {
    0x00111111, 
    0x00000110, 
    0x01011011, 
    0x01001111, 
    0x01100110, 
    0x01101101, 
    0x01111101, 
    0x00000111, 
    0x01111111, 
    0x01100111, 
    0x01110111, 
    0x01111100, 
    0x00111001, 
    0x01011110, 
    0x01011110, 
    0x01011110};
int seg_1;
int seg_2;
//**************************
//CICLO PRINCIPAL
//**************************
void main(void) {

    //while(1); 
    setup();
    while(1){
        __delay_ms(300);
        if (IOCBbits.IOCB0 = 1 && PORTBbits.RB0 == 1) {
            aumentar();
        }
        if (IOCBbits.IOCB3 = 1 && PORTBbits.RB3 == 1) {
            restar();
        }
        if (cont0 > 255) {
            cont0 = 0;
        }

        if (ADCON0bits.GO_DONE == 0) {
            multiplexor();
        }
    
    }
}
//**************************
//CONFIGURACION
//**************************

void setup(void){
    
    //oscilador de 8Mhz
    OSCCONbits.IRCF = 0b111;
    OSCCONbits.SCS = 0b00;

    // configurar puertos como salidas o entradas
    TRISA = 0b00000000;
    TRISB = 0b01111111;
    TRISC = 0b00000000;
    TRISD = 0b00000000;
    TRISE = 1;
    //limpiamos los puertos
    PORTA = 0;
    PORTB = 0; 
    PORTC = 0; 
    PORTD = 0;
    PORTE = 0b00010;
    ANSELH = 0; 
    //configuracion analogica
    ANSELbits.ANS6 = 0; //AN6 como analogico    
    ADCON0bits.ADCS0 = 1; //SELECCION DEL FOSC/8
    ADCON0bits.ADCS1 = 0;
    ADCON0bits.CHS0 = 0; //seleccion del canal
    ADCON0bits.CHS1 = 1;
    ADCON0bits.CHS2 = 1;
    ADCON0bits.CHS3 = 0; //AN6 Analog
    ADCON1bits.VCFG0 = 0; //VDD
    ADCON1bits.VCFG1 = 0; //VSS
    ADCON1bits.ADFM = 0;
    ADCON0bits.GO_DONE = 1;
    ADCON0bits.ADON = 1;        //habilimamos adc

    //-------------------------------Banderas-----------------------------------
    INTCONbits.GIE = 1; //Habilitar interrupciones globales
    PIE1bits.ADIE = 0;  //habilitamos la interrupcion del adc
    PIE1bits.ADIE = 1;
    INTCONbits.GIE = 1;     //interrupcion global  
    INTCONbits.RBIF = 0;    //limpiamos interrupcion 
    INTCONbits.RBIF = 1;
    IOCB = 1;               //habilitamos interrupciones purto B
    IOCBbits.IOCB0 = 1;     //Bandera B0
    IOCBbits.IOCB3 = 1;     //Bandera B3

}


//**************************
//FUNCIONES
//**************************
void multiplexor(void){
    //ADCON0bits.GO_DONE = 1;            
            seg_1 = ADRESH;
            seg_2 = ADRESH;
            seg_1 = ((seg_1/16)%16);//DIVISION DE H/16
            seg_2 = (seg_2%16);//RESIDUO DE LA DIVISION
            PORTD = display[seg_1];
            PORTCbits.RC0 = 1;
            PORTCbits.RC0 = 0;
            PORTD = display[seg_2];
            PORTCbits.RC1 = 1;
            PORTCbits.RC1 = 0;
            ADCON0bits.GO_DONE =1;
            
}
void aumentar(void){
    PORTBbits.RB7 = 1;
            cont0++;
            __delay_ms(500);
            IOCBbits.IOCB0 = 0;
            do { } while (PORTBbits.RB0 == 1);
            PORTA = cont0;
}
void restar(void){
            cont0--;
            __delay_ms(500);
            do {
                //****
            } while (PORTBbits.RB3 == 1);
            PORTA = cont0;
            IOCBbits.IOCB3 = 0;
}
