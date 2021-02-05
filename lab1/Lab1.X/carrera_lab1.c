//******************************************************************************
//Creado Por: Diego Alejandro Gonzalez López
//electronica digital 2
//Laboratorio 1 carrera de leds
//******************************************************************************

//******************************************************************************
//IMPORTACION DE LIBRERIAS
//******************************************************************************
#include <xc.h>


//******************************************************************************
//CONFIGURACION
//******************************************************************************
// CONFIG1
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator: Crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
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

#define _XTAL_FREQ 8000000

//******************************************************************************
//VARIABLES
//******************************************************************************
int ban_1;          //banderas para el anti rebote de cada una de los botones
int ban_2;
int ban_3;
int ban_4;
int cont1;          //contador de pulsos de cada boton
int cont2;
int cont_alarm;

//******************************************************************************
//PROTOTIPOS DE FUNCIONES
//******************************************************************************
void setup(void);       //Funcion para definir la configuracion inicial
void semaforo(void);    //funcion para las luces del semaforo para dar comienzo
void avanza_1(void);    //la funcion avanza chequea el valor del contador
void avanza_2(void);    //y coloca la configuracion de leds pertinente
void fin(void);         //verifica si algun jugador llego a la meta para finali-
                        //zar la carrera

//******************************************************************************
//CICLO PRINCIPAL
//******************************************************************************

void main(void) {

    setup();

    //**************************************************************************
    //LOOP PRINCIPAL
    //**************************************************************************

    while (1) {
        if (PORTBbits.RB0 == 0) {   //chequea el boton de semaforo
            semaforo();             //si se activa, corre la funcion semaforo
        }

        if (PORTBbits.RB1 == 0) {   //si el boton esta desactivado coloca la 
            ban_1 = 1;              //bandera para permitir el aumento
        }
        if (PORTBbits.RB1 == 1 && ban_1 == 1) { //chequea el boton y la bandera
            ban_1 = 0;      //tanto la bandera como el boton deben estar en la
            cont1++;        //configuracion correcta para funcionar y 
        }                   //aumentar el contador 1
        
        if (PORTBbits.RB2 == 0) {   //si el boton esta desactivado coloca la
            ban_2 = 1;              //bandera para permitir el aumento
        }
        if (PORTBbits.RB2 == 1 && ban_2 == 1) {//chequea el boton y la bandera
            ban_2 = 0;       //tanto la bandera como el boton deben estar en la
            cont2++;         //configuracion correcta para funcionar y 
        }                    //aumentar el contador 2
        
        avanza_1();         //verifica cual es el valor del contador 1
        avanza_2();         //verifica cual es el valor del contador 2
        fin();              //chequea si un jugador ya gano


    }
}

//******************************************************************************
//CONFIGURACION
//******************************************************************************

void setup(void) {
    TRISE = 0; // todos las salidas del puerto E estan en OUTPUT
    PORTE = 0; // Todos los puertos de E empiezan apagados
    TRISC = 0; // TODO C esta en OUTPUT
    PORTC = 0; // TODO C empieza apagado
    TRISA = 0; // TODO A OUTPUT
    PORTA = 0; // TODA A APAGADO
    TRISD = 0; // TODO D OUTPUT
    PORTD = 0; // TODO D EMPIEZA APAGADO
    ANSEL = 0; // PARA NO USARLO COMO ANALOGICO
    ANSELH = 0; // PARA NO USARLO COMO ANALOGICO
    PORTBbits.RB0 = 1; //Puerto RB0 como input
    PORTBbits.RB1 = 1; 
}

//******************************************************************************
//FUNCIONES
//******************************************************************************

void semaforo(void) {
    cont1 = 0;          //reinicia los contadores
    cont2 = 0;
    PORTC = 0;          //apaga todos los leds
    PORTD = 0;
    PORTA = 0;
    
    //comienza la secuencia de inicio de semaforo
    
    //PORTEbits.RE2 = 0; //apago RE2
    PORTEbits.RE0 = 1; // Enciendo puerto RE0
    __delay_ms(500);
    PORTEbits.RE0 = 0; // apago led Roja
    PORTEbits.RE1 = 1; // enciendo led Amarilla
    __delay_ms(500);
    PORTEbits.RE1 = 0; // apago led amarilla
    PORTEbits.RE2 = 1; // enciendo led verde
    __delay_ms(500);
    PORTEbits.RE2 = 0; // apago led verde
}

void avanza_1(void) {
    switch(cont1){              //verifica el caso de contador con un swith case
        case 1:                 //depende el numero del contador enciende los 
            PORTCbits.RC0 = 1;  //led debidos
            break;
        case 2:
            PORTCbits.RC1 = 1;
            break;
        case 3:
            PORTCbits.RC2 = 1;
            break;
        case 4:
            PORTCbits.RC3 = 1;
            break;
        case 5:
            PORTCbits.RC4 = 1;
            break; 
        case 6:
            PORTCbits.RC5 = 1;
            break;
        case 7:
            PORTCbits.RC6 = 1;
            break;
        case 8:
            PORTCbits.RC7 = 1;
            break;
    }
    
}

void avanza_2(void) {
    switch(cont2){              //verifica el caso de contador con un swith case
        case 1:                 //depende el numero del contador enciende los 
            PORTDbits.RD0 = 1;  //led debidos
            break;
        case 2:
            PORTDbits.RD1 = 1;
            break;
        case 3:
            PORTDbits.RD2 = 1;
            break;
        case 4:
            PORTDbits.RD3 = 1;
            break;
        case 5:
            PORTDbits.RD4 = 1;
            break; 
        case 6:
            PORTDbits.RD5 = 1;
            break;
        case 7:
            PORTDbits.RD6 = 1;
            break;
        case 8:
            PORTDbits.RD7 = 1;
            break;       
              
        
    }
}

void fin(void) {
    if (cont1 >= 9) {   //si el contador 1 finaliza empieza la secuencia de fin
        PORTC = 0;      //apaga los leds
        PORTD = 0; 
    __delay_ms(500);    //enciende y apaga el ganador periodicamente
        PORTC = 255;
    __delay_ms(500);
    }
    if (cont2 >= 9) {   //si el contador 2 finaliza empieza la secuencia de fin
        PORTD = 0;      //apaga los leds
        PORTC = 0;
    __delay_ms(500);    //enciende y apaga el ganador periodicamente
        PORTD = 255;
    __delay_ms(500);
    }
}
