/**
  Generated Pin Manager File

  Company:
    Microchip Technology Inc.

  File Name:
    pin_manager.c

  Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18F46K22
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.36 and above
        MPLAB             :  MPLAB X 6.00

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "pin_manager.h"
extern volatile uint8_t g_zona_alarma;



void (*IOCB4_InterruptHandler)(void);
void (*IOCB5_InterruptHandler)(void);
void (*IOCB6_InterruptHandler)(void);
void (*IOCB7_InterruptHandler)(void);


void PIN_MANAGER_Initialize(void)
{
    /**
    LATx registers
    */
    LATE = 0x00;
    LATD = 0x00;
    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x00;

    /**
    TRISx registers
    */
    TRISE = 0x04;
    TRISA = 0xBF;
    TRISB = 0xFF;
    TRISC = 0xE7;
    TRISD = 0xF0;

    /**
    ANSELx registers
    */
    ANSELD = 0x00;
    ANSELC = 0xE4;
    ANSELB = 0x00;
    ANSELE = 0x04;
    ANSELA = 0x2F;

    /**
    WPUx registers
    */
    WPUB = 0xF7;
    INTCON2bits.nRBPU = 0;



    /**
    IOCx registers 
    */
    //interrupt on change for group IOCB - flag
    IOCBbits.IOCB4 = 1;
    //interrupt on change for group IOCB - flag
    IOCBbits.IOCB5 = 1;
    //interrupt on change for group IOCB - flag
    IOCBbits.IOCB6 = 1;
    //interrupt on change for group IOCB - flag
    IOCBbits.IOCB7 = 1;



    // register default IOC callback functions at runtime; use these methods to register a custom function
    IOCB4_SetInterruptHandler(IOCB4_DefaultInterruptHandler);
    IOCB5_SetInterruptHandler(IOCB5_DefaultInterruptHandler);
    IOCB6_SetInterruptHandler(IOCB6_DefaultInterruptHandler);
    IOCB7_SetInterruptHandler(IOCB7_DefaultInterruptHandler);
   
    // Enable RBI interrupt 
    INTCONbits.RBIE = 1; 
    
}
  
void PIN_MANAGER_IOC(void)
{
    // Interrupción por Cambio (IOC) para Ventanas
    if(INTCONbits.RBIE == 1 && INTCONbits.RBIF == 1)
    {
        if (g_zona_alarma == 0) {
            if      (PORTBbits.RB4 == 0) g_zona_alarma = 3; // Ventana 1
            else if (PORTBbits.RB5 == 0) g_zona_alarma = 4; // Ventana 2
            else if (PORTBbits.RB6 == 0) g_zona_alarma = 5; // Ventana 3
            else if (PORTBbits.RB7 == 0) g_zona_alarma = 6; // Ventana 4
        }
        
        // Limpiar bandera IOC
        INTCONbits.RBIF = 0;
    }
}

/**
   IOCB4 Interrupt Service Routine
*/
void IOCB4_ISR(void) {

    // Add custom IOCB4 code

    // Call the interrupt handler for the callback registered at runtime
    if(IOCB4_InterruptHandler)
    {
        IOCB4_InterruptHandler();
    }
}

/**
  Allows selecting an interrupt handler for IOCB4 at application runtime
*/
void IOCB4_SetInterruptHandler(void (* InterruptHandler)(void)){
    IOCB4_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCB4
*/
void IOCB4_DefaultInterruptHandler(void){
    // add your IOCB4 interrupt custom code
    // or set custom function using IOCB4_SetInterruptHandler()
}

/**
   IOCB5 Interrupt Service Routine
*/
void IOCB5_ISR(void) {

    // Add custom IOCB5 code

    // Call the interrupt handler for the callback registered at runtime
    if(IOCB5_InterruptHandler)
    {
        IOCB5_InterruptHandler();
    }
}

/**
  Allows selecting an interrupt handler for IOCB5 at application runtime
*/
void IOCB5_SetInterruptHandler(void (* InterruptHandler)(void)){
    IOCB5_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCB5
*/
void IOCB5_DefaultInterruptHandler(void){
    // add your IOCB5 interrupt custom code
    // or set custom function using IOCB5_SetInterruptHandler()
}

/**
   IOCB6 Interrupt Service Routine
*/
void IOCB6_ISR(void) {

    // Add custom IOCB6 code

    // Call the interrupt handler for the callback registered at runtime
    if(IOCB6_InterruptHandler)
    {
        IOCB6_InterruptHandler();
    }
}

/**
  Allows selecting an interrupt handler for IOCB6 at application runtime
*/
void IOCB6_SetInterruptHandler(void (* InterruptHandler)(void)){
    IOCB6_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCB6
*/
void IOCB6_DefaultInterruptHandler(void){
    // add your IOCB6 interrupt custom code
    // or set custom function using IOCB6_SetInterruptHandler()
}

/**
   IOCB7 Interrupt Service Routine
*/
void IOCB7_ISR(void) {

    // Add custom IOCB7 code

    // Call the interrupt handler for the callback registered at runtime
    if(IOCB7_InterruptHandler)
    {
        IOCB7_InterruptHandler();
    }
}

/**
  Allows selecting an interrupt handler for IOCB7 at application runtime
*/
void IOCB7_SetInterruptHandler(void (* InterruptHandler)(void)){
    IOCB7_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCB7
*/
void IOCB7_DefaultInterruptHandler(void){
    // add your IOCB7 interrupt custom code
    // or set custom function using IOCB7_SetInterruptHandler()
}

/**
 End of File
*/