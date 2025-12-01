#include "Alarm_Status.h"
#include "lcd_i2c.h"
#include "keypad.h"
#include <string.h>
#include "ADC.h"
#include <stdio.h>
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/adc.h"

#define _XTAL_FREQ 8000000

// --- Definición de Variables Globales ---
SistemaEstado_t g_estado_actual = DISARMED;
char g_pin_buffer[5];
uint8_t g_pin_index = 0;
volatile uint8_t g_zona_alarma = 0;

// Variables locales estáticas para lectura de teclas
static char tecla = '\0';
static char tecla_ant = '\0';

// ------------------------------------------------------
// 1. ESTADO DESARMADO
// ------------------------------------------------------
void alarm_disarmed(void) {
    
    // 1. Lectura del Sensor de Temperatura (LM35)
    // ---------------------------------------------
    // Leemos el valor crudo del ADC (0 a 1023)
    adc_result_t valor_adc = ADC_GetConversion(channel_AN0);
    
    // Convertimos a voltaje y luego a grados Celsius
    // (5.0V * 1000mV) / 1023 bits = 4.88 mV por bit
    // LM35 entrega 10mV por grado.
    // Formula simplificada: (ADC * 500) / 1023
    uint16_t temperatura = (uint16_t)((valor_adc * 500) / 1023);
    
    // Preparamos el texto para el LCD
    char buffer_temp[16];
    sprintf(buffer_temp, "Temp: %d C   ", temperatura); // Espacios extra para limpiar
    
    // Mostramos en la línea 2 (dejando la línea 1 con "Sistema DESARMADO")
    LCD_SetCursor(1, 0);
    LCD_SendString(buffer_temp);
    // ---------------------------------------------


    // 2. Lógica del Teclado (La que ya tenías)
    tecla = KPD_GetKey();

    if (tecla != '\0' && tecla_ant == '\0') {
        if (tecla == TECLA_ARMAR) {
            
            // Limpiamos pantalla antes de irnos
            LCD_Clear();
            LCD_SetCursor(0,0);
            LCD_SendString("Introduzca PIN:");
            
            g_pin_index = 0;
            memset(g_pin_buffer, 0, sizeof(g_pin_buffer));
            
            g_estado_actual = FIN_SCREEN;
        }
    }
    tecla_ant = tecla;
}

// ------------------------------------------------------
// 2. PANTALLA DE PIN (FIN_SCREEN)
// ------------------------------------------------------
void show_pin_screen(void) {
    
    tecla = KPD_GetKey();

    if (tecla != '\0' && tecla_ant == '\0') {
        
        // Si es número
        if (g_pin_index < 4 && (tecla >= '0' && tecla <= '9')) {
            g_pin_buffer[g_pin_index] = tecla;
            LCD_SetCursor(1, g_pin_index); 
            LCD_SendChar('*');             
            g_pin_index++;
        }
        
        // Si es borrar (*)
        if (tecla == TECLA_BORRAR) {
            g_pin_index = 0;
            memset(g_pin_buffer, 0, sizeof(g_pin_buffer));
            LCD_Clear();
            LCD_SetCursor(0,0);
            LCD_SendString("Introduzca PIN:");
        }
    }
    tecla_ant = tecla;

    // Verificar si terminamos de escribir los 4 dígitos
    if (g_pin_index == 4) {
        g_pin_buffer[4] = '\0'; // Cerrar string

        if (strcmp(g_pin_buffer, MASTER_PIN) == 0) {
            // --- PIN CORRECTO -> ARMAR ---
            LCD_Clear();
            LCD_SetCursor(0,0);
            LCD_SendString("Sistema ARMADO");
            
            // --- ¡¡ESTAS SON LAS LÍNEAS QUE FALTABAN!! ---
            // Borramos el PIN de la memoria INMEDIATAMENTE
            g_pin_index = 0;
            memset(g_pin_buffer, 0, sizeof(g_pin_buffer));
            // ---------------------------------------------
            
            g_estado_actual = ARMED;
        } else {
            // --- PIN INCORRECTO -> REGRESAR A DESARMADO ---
            LCD_Clear();
            LCD_SetCursor(0,0);
            LCD_SendString("PIN Incorrecto");
            __delay_ms(1500); 
            
            // Restaurar pantalla de desarmado
            LCD_Clear();
            LCD_SetCursor(0,0);
            LCD_SendString("Sistema DESARMADO");
            LCD_SetCursor(1,0);
            LCD_SendString("Presione A");
            
            g_estado_actual = DISARMED;
        }
    }
}

// ------------------------------------------------------
// 3. ESTADO ARMADO
// ------------------------------------------------------
void armed_alarm(void) {
    // Este estado está "dormido". 
    // Solo espera que el main() detecte la interrupción.
    // No hace nada más.
}

// ------------------------------------------------------
// 4. ESTADO INTRUSIÓN (ALERTA)
// ------------------------------------------------------
void alert_alarm(void) {
    // 1. Actuadores (Sonar Alarma)
    LED_ALARMA_SetHigh();
    BUZZER_Toggle(); 

    // 2. Escanear teclado para desactivar
    tecla = KPD_GetKey();

    if (tecla != '\0' && tecla_ant == '\0') {
        if (g_pin_index < 4 && (tecla >= '0' && tecla <= '9')) {
            g_pin_buffer[g_pin_index] = tecla;
            LCD_SetCursor(1, g_pin_index);
            LCD_SendChar('*');
            g_pin_index++;
        }
    }
    tecla_ant = tecla;

    // 3. Verificar PIN para apagar alarma
    if (g_pin_index == 4) {
        g_pin_buffer[4] = '\0';
        
        if (strcmp(g_pin_buffer, MASTER_PIN) == 0) {
            // --- PIN CORRECTO -> DESACTIVAR ---
            LED_ALARMA_SetLow(); // Apagar LED rojo
            BUZZER_SetLow();     // Apagar Buzzer
            
            LCD_Clear();
            LCD_SetCursor(0,0);
            LCD_SendString("Sistema DESARMADO");
            LCD_SetCursor(1,0);
            LCD_SendString("Presione A");
            
            g_estado_actual = DISARMED;
        } else {
            // --- PIN INCORRECTO -> SEGUIR SONANDO ---
            g_pin_index = 0;
            memset(g_pin_buffer, 0, sizeof(g_pin_buffer));
            LCD_Clear();
            LCD_SetCursor(0,0);
            LCD_SendString("!! INTRUSION !!"); 
            // (Regresa al inicio de la función alert_alarm en el sig ciclo)
        }
    }
}

void mostrar_zona_alarma(void) {
    LCD_Clear();
    LCD_SetCursor(0, 0);
    LCD_SendString("!! INTRUSION !!");
    
    LCD_SetCursor(1, 0);
    
    // Revisamos qué número tiene la variable
    switch (g_zona_alarma) {
        case 1: LCD_SendString("P. PRINCIPAL"); break; // INT0
        case 2: LCD_SendString("P. TRASERA");   break; // INT1
        case 3: LCD_SendString("VENTANA 1");    break; // RB4
        case 4: LCD_SendString("VENTANA 2");    break; // RB5
        case 5: LCD_SendString("VENTANA 3");    break; // RB6
        case 6: LCD_SendString("VENTANA 4");    break; // RB7
        default: LCD_SendString("ZONA DESCONOC."); break;
    }
}