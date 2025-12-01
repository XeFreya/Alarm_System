/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18F46K22
        Driver Version    :  2.00
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



#include "mcc_generated_files/mcc.h"
#include "lcd_i2c.h"
#include "keypad.h"
#include "ADC.h"
#include "Alarm_Status.h"
#include <stdio.h>
#include <string.h>
/*
                         Main application
 */
#include <stdio.h> // Para sprintf
#include <string.h> // Para memset
    
void main(void) {
    SYSTEM_Initialize();

    // --- ARREGLO DE HARDWARE ---
    INTCON2bits.nRBPU = 0; // Habilita la "llave general" de Pull-Ups
    WPUB = 0xFF;
    
    // Habilitar Interrupciones y Pull-ups
    INTCON2bits.nRBPU = 0; 
    INTCONbits.GIE = 1;   
    INTCONbits.PEIE = 1;  
    
 

    LCD_Init();
    
    // Inicio
    LCD_Clear();
    LCD_SetCursor(0,0);
    LCD_SendString("Sistema DESARMADO");
    LCD_SetCursor(1,0);
    LCD_SendString("Presione A");

    while (1) {
        
        // 1. Ejecutar Lógica de Estados
        switch (g_estado_actual) {
            case DISARMED:   alarm_disarmed();  break;
            case FIN_SCREEN: show_pin_screen(); break;
            case ARMED:      armed_alarm();     break;
            case INTRUSION:  alert_alarm();     break;
        }

        if (g_zona_alarma > 0) { 
            
            if (g_estado_actual == ARMED) {
                 
                 // --- ¡AGREGA ESTAS 3 LÍNEAS AQUÍ! ---
                 // Borramos cualquier rastro del PIN anterior
                 // para que la alarma no se desactive sola.
                 g_pin_index = 0;
                 memset(g_pin_buffer, 0, sizeof(g_pin_buffer));
                 // -------------------------------------

                 mostrar_zona_alarma(); 
                 g_estado_actual = INTRUSION;
            } 
            
            else if (g_estado_actual == INTRUSION) {
                // No hacer nada
            }
            else {
                 g_zona_alarma = 0; 
            }
        }
        
        __delay_ms(20); 
    }
}