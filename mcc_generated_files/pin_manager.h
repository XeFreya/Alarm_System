/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18F46K22
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.36 and above
        MPLAB 	          :  MPLAB X 6.00	
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

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set channel_AN0 aliases
#define channel_AN0_TRIS                 TRISAbits.TRISA0
#define channel_AN0_LAT                  LATAbits.LATA0
#define channel_AN0_PORT                 PORTAbits.RA0
#define channel_AN0_ANS                  ANSELAbits.ANSA0
#define channel_AN0_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define channel_AN0_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define channel_AN0_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define channel_AN0_GetValue()           PORTAbits.RA0
#define channel_AN0_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define channel_AN0_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define channel_AN0_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define channel_AN0_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)

// get/set RA6 procedures
#define RA6_SetHigh()            do { LATAbits.LATA6 = 1; } while(0)
#define RA6_SetLow()             do { LATAbits.LATA6 = 0; } while(0)
#define RA6_Toggle()             do { LATAbits.LATA6 = ~LATAbits.LATA6; } while(0)
#define RA6_GetValue()              PORTAbits.RA6
#define RA6_SetDigitalInput()    do { TRISAbits.TRISA6 = 1; } while(0)
#define RA6_SetDigitalOutput()   do { TRISAbits.TRISA6 = 0; } while(0)

// get/set RB0 procedures
#define RB0_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define RB0_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define RB0_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define RB0_GetValue()              PORTBbits.RB0
#define RB0_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define RB0_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define RB0_SetPullup()             do { WPUBbits.WPUB0 = 1; } while(0)
#define RB0_ResetPullup()           do { WPUBbits.WPUB0 = 0; } while(0)
#define RB0_SetAnalogMode()         do { ANSELBbits.ANSB0 = 1; } while(0)
#define RB0_SetDigitalMode()        do { ANSELBbits.ANSB0 = 0; } while(0)

// get/set RB1 procedures
#define RB1_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define RB1_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define RB1_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define RB1_GetValue()              PORTBbits.RB1
#define RB1_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define RB1_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define RB1_SetPullup()             do { WPUBbits.WPUB1 = 1; } while(0)
#define RB1_ResetPullup()           do { WPUBbits.WPUB1 = 0; } while(0)
#define RB1_SetAnalogMode()         do { ANSELBbits.ANSB1 = 1; } while(0)
#define RB1_SetDigitalMode()        do { ANSELBbits.ANSB1 = 0; } while(0)

// get/set RB2 procedures
#define RB2_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define RB2_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define RB2_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define RB2_GetValue()              PORTBbits.RB2
#define RB2_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define RB2_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define RB2_SetPullup()             do { WPUBbits.WPUB2 = 1; } while(0)
#define RB2_ResetPullup()           do { WPUBbits.WPUB2 = 0; } while(0)
#define RB2_SetAnalogMode()         do { ANSELBbits.ANSB2 = 1; } while(0)
#define RB2_SetDigitalMode()        do { ANSELBbits.ANSB2 = 0; } while(0)

// get/set SCL aliases
#define SCL_TRIS                 TRISCbits.TRISC3
#define SCL_LAT                  LATCbits.LATC3
#define SCL_PORT                 PORTCbits.RC3
#define SCL_ANS                  ANSELCbits.ANSC3
#define SCL_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define SCL_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define SCL_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define SCL_GetValue()           PORTCbits.RC3
#define SCL_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define SCL_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define SCL_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define SCL_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set SDA aliases
#define SDA_TRIS                 TRISCbits.TRISC4
#define SDA_LAT                  LATCbits.LATC4
#define SDA_PORT                 PORTCbits.RC4
#define SDA_ANS                  ANSELCbits.ANSC4
#define SDA_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define SDA_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define SDA_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define SDA_GetValue()           PORTCbits.RC4
#define SDA_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define SDA_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define SDA_SetAnalogMode()      do { ANSELCbits.ANSC4 = 1; } while(0)
#define SDA_SetDigitalMode()     do { ANSELCbits.ANSC4 = 0; } while(0)

// get/set KPD_R1 aliases
#define KPD_R1_TRIS                 TRISDbits.TRISD0
#define KPD_R1_LAT                  LATDbits.LATD0
#define KPD_R1_PORT                 PORTDbits.RD0
#define KPD_R1_ANS                  ANSELDbits.ANSD0
#define KPD_R1_SetHigh()            do { LATDbits.LATD0 = 1; } while(0)
#define KPD_R1_SetLow()             do { LATDbits.LATD0 = 0; } while(0)
#define KPD_R1_Toggle()             do { LATDbits.LATD0 = ~LATDbits.LATD0; } while(0)
#define KPD_R1_GetValue()           PORTDbits.RD0
#define KPD_R1_SetDigitalInput()    do { TRISDbits.TRISD0 = 1; } while(0)
#define KPD_R1_SetDigitalOutput()   do { TRISDbits.TRISD0 = 0; } while(0)
#define KPD_R1_SetAnalogMode()      do { ANSELDbits.ANSD0 = 1; } while(0)
#define KPD_R1_SetDigitalMode()     do { ANSELDbits.ANSD0 = 0; } while(0)

// get/set KPD_R2 aliases
#define KPD_R2_TRIS                 TRISDbits.TRISD1
#define KPD_R2_LAT                  LATDbits.LATD1
#define KPD_R2_PORT                 PORTDbits.RD1
#define KPD_R2_ANS                  ANSELDbits.ANSD1
#define KPD_R2_SetHigh()            do { LATDbits.LATD1 = 1; } while(0)
#define KPD_R2_SetLow()             do { LATDbits.LATD1 = 0; } while(0)
#define KPD_R2_Toggle()             do { LATDbits.LATD1 = ~LATDbits.LATD1; } while(0)
#define KPD_R2_GetValue()           PORTDbits.RD1
#define KPD_R2_SetDigitalInput()    do { TRISDbits.TRISD1 = 1; } while(0)
#define KPD_R2_SetDigitalOutput()   do { TRISDbits.TRISD1 = 0; } while(0)
#define KPD_R2_SetAnalogMode()      do { ANSELDbits.ANSD1 = 1; } while(0)
#define KPD_R2_SetDigitalMode()     do { ANSELDbits.ANSD1 = 0; } while(0)

// get/set KPD_R3 aliases
#define KPD_R3_TRIS                 TRISDbits.TRISD2
#define KPD_R3_LAT                  LATDbits.LATD2
#define KPD_R3_PORT                 PORTDbits.RD2
#define KPD_R3_ANS                  ANSELDbits.ANSD2
#define KPD_R3_SetHigh()            do { LATDbits.LATD2 = 1; } while(0)
#define KPD_R3_SetLow()             do { LATDbits.LATD2 = 0; } while(0)
#define KPD_R3_Toggle()             do { LATDbits.LATD2 = ~LATDbits.LATD2; } while(0)
#define KPD_R3_GetValue()           PORTDbits.RD2
#define KPD_R3_SetDigitalInput()    do { TRISDbits.TRISD2 = 1; } while(0)
#define KPD_R3_SetDigitalOutput()   do { TRISDbits.TRISD2 = 0; } while(0)
#define KPD_R3_SetAnalogMode()      do { ANSELDbits.ANSD2 = 1; } while(0)
#define KPD_R3_SetDigitalMode()     do { ANSELDbits.ANSD2 = 0; } while(0)

// get/set KPD_R4 aliases
#define KPD_R4_TRIS                 TRISDbits.TRISD3
#define KPD_R4_LAT                  LATDbits.LATD3
#define KPD_R4_PORT                 PORTDbits.RD3
#define KPD_R4_ANS                  ANSELDbits.ANSD3
#define KPD_R4_SetHigh()            do { LATDbits.LATD3 = 1; } while(0)
#define KPD_R4_SetLow()             do { LATDbits.LATD3 = 0; } while(0)
#define KPD_R4_Toggle()             do { LATDbits.LATD3 = ~LATDbits.LATD3; } while(0)
#define KPD_R4_GetValue()           PORTDbits.RD3
#define KPD_R4_SetDigitalInput()    do { TRISDbits.TRISD3 = 1; } while(0)
#define KPD_R4_SetDigitalOutput()   do { TRISDbits.TRISD3 = 0; } while(0)
#define KPD_R4_SetAnalogMode()      do { ANSELDbits.ANSD3 = 1; } while(0)
#define KPD_R4_SetDigitalMode()     do { ANSELDbits.ANSD3 = 0; } while(0)

// get/set KPD_C1 aliases
#define KPD_C1_TRIS                 TRISDbits.TRISD4
#define KPD_C1_LAT                  LATDbits.LATD4
#define KPD_C1_PORT                 PORTDbits.RD4
#define KPD_C1_ANS                  ANSELDbits.ANSD4
#define KPD_C1_SetHigh()            do { LATDbits.LATD4 = 1; } while(0)
#define KPD_C1_SetLow()             do { LATDbits.LATD4 = 0; } while(0)
#define KPD_C1_Toggle()             do { LATDbits.LATD4 = ~LATDbits.LATD4; } while(0)
#define KPD_C1_GetValue()           PORTDbits.RD4
#define KPD_C1_SetDigitalInput()    do { TRISDbits.TRISD4 = 1; } while(0)
#define KPD_C1_SetDigitalOutput()   do { TRISDbits.TRISD4 = 0; } while(0)
#define KPD_C1_SetAnalogMode()      do { ANSELDbits.ANSD4 = 1; } while(0)
#define KPD_C1_SetDigitalMode()     do { ANSELDbits.ANSD4 = 0; } while(0)

// get/set KPD_C2 aliases
#define KPD_C2_TRIS                 TRISDbits.TRISD5
#define KPD_C2_LAT                  LATDbits.LATD5
#define KPD_C2_PORT                 PORTDbits.RD5
#define KPD_C2_ANS                  ANSELDbits.ANSD5
#define KPD_C2_SetHigh()            do { LATDbits.LATD5 = 1; } while(0)
#define KPD_C2_SetLow()             do { LATDbits.LATD5 = 0; } while(0)
#define KPD_C2_Toggle()             do { LATDbits.LATD5 = ~LATDbits.LATD5; } while(0)
#define KPD_C2_GetValue()           PORTDbits.RD5
#define KPD_C2_SetDigitalInput()    do { TRISDbits.TRISD5 = 1; } while(0)
#define KPD_C2_SetDigitalOutput()   do { TRISDbits.TRISD5 = 0; } while(0)
#define KPD_C2_SetAnalogMode()      do { ANSELDbits.ANSD5 = 1; } while(0)
#define KPD_C2_SetDigitalMode()     do { ANSELDbits.ANSD5 = 0; } while(0)

// get/set KPD_C3 aliases
#define KPD_C3_TRIS                 TRISDbits.TRISD6
#define KPD_C3_LAT                  LATDbits.LATD6
#define KPD_C3_PORT                 PORTDbits.RD6
#define KPD_C3_ANS                  ANSELDbits.ANSD6
#define KPD_C3_SetHigh()            do { LATDbits.LATD6 = 1; } while(0)
#define KPD_C3_SetLow()             do { LATDbits.LATD6 = 0; } while(0)
#define KPD_C3_Toggle()             do { LATDbits.LATD6 = ~LATDbits.LATD6; } while(0)
#define KPD_C3_GetValue()           PORTDbits.RD6
#define KPD_C3_SetDigitalInput()    do { TRISDbits.TRISD6 = 1; } while(0)
#define KPD_C3_SetDigitalOutput()   do { TRISDbits.TRISD6 = 0; } while(0)
#define KPD_C3_SetAnalogMode()      do { ANSELDbits.ANSD6 = 1; } while(0)
#define KPD_C3_SetDigitalMode()     do { ANSELDbits.ANSD6 = 0; } while(0)

// get/set KPD_C4 aliases
#define KPD_C4_TRIS                 TRISDbits.TRISD7
#define KPD_C4_LAT                  LATDbits.LATD7
#define KPD_C4_PORT                 PORTDbits.RD7
#define KPD_C4_ANS                  ANSELDbits.ANSD7
#define KPD_C4_SetHigh()            do { LATDbits.LATD7 = 1; } while(0)
#define KPD_C4_SetLow()             do { LATDbits.LATD7 = 0; } while(0)
#define KPD_C4_Toggle()             do { LATDbits.LATD7 = ~LATDbits.LATD7; } while(0)
#define KPD_C4_GetValue()           PORTDbits.RD7
#define KPD_C4_SetDigitalInput()    do { TRISDbits.TRISD7 = 1; } while(0)
#define KPD_C4_SetDigitalOutput()   do { TRISDbits.TRISD7 = 0; } while(0)
#define KPD_C4_SetAnalogMode()      do { ANSELDbits.ANSD7 = 1; } while(0)
#define KPD_C4_SetDigitalMode()     do { ANSELDbits.ANSD7 = 0; } while(0)

// get/set LED_ALARMA aliases
#define LED_ALARMA_TRIS                 TRISEbits.TRISE0
#define LED_ALARMA_LAT                  LATEbits.LATE0
#define LED_ALARMA_PORT                 PORTEbits.RE0
#define LED_ALARMA_ANS                  ANSELEbits.ANSE0
#define LED_ALARMA_SetHigh()            do { LATEbits.LATE0 = 1; } while(0)
#define LED_ALARMA_SetLow()             do { LATEbits.LATE0 = 0; } while(0)
#define LED_ALARMA_Toggle()             do { LATEbits.LATE0 = ~LATEbits.LATE0; } while(0)
#define LED_ALARMA_GetValue()           PORTEbits.RE0
#define LED_ALARMA_SetDigitalInput()    do { TRISEbits.TRISE0 = 1; } while(0)
#define LED_ALARMA_SetDigitalOutput()   do { TRISEbits.TRISE0 = 0; } while(0)
#define LED_ALARMA_SetAnalogMode()      do { ANSELEbits.ANSE0 = 1; } while(0)
#define LED_ALARMA_SetDigitalMode()     do { ANSELEbits.ANSE0 = 0; } while(0)

// get/set BUZZER aliases
#define BUZZER_TRIS                 TRISEbits.TRISE1
#define BUZZER_LAT                  LATEbits.LATE1
#define BUZZER_PORT                 PORTEbits.RE1
#define BUZZER_ANS                  ANSELEbits.ANSE1
#define BUZZER_SetHigh()            do { LATEbits.LATE1 = 1; } while(0)
#define BUZZER_SetLow()             do { LATEbits.LATE1 = 0; } while(0)
#define BUZZER_Toggle()             do { LATEbits.LATE1 = ~LATEbits.LATE1; } while(0)
#define BUZZER_GetValue()           PORTEbits.RE1
#define BUZZER_SetDigitalInput()    do { TRISEbits.TRISE1 = 1; } while(0)
#define BUZZER_SetDigitalOutput()   do { TRISEbits.TRISE1 = 0; } while(0)
#define BUZZER_SetAnalogMode()      do { ANSELEbits.ANSE1 = 1; } while(0)
#define BUZZER_SetDigitalMode()     do { ANSELEbits.ANSE1 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/