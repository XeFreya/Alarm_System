#include "Alarm_Status.h"
#include "lcd_i2c.h"
#include "keypad.h"
#include <string.h>

#include <string.h>
#include "Alarm_Status.h"
#include "mcc_generated_files/pin_manager.h"

#define _XTAL_FREQ 8000000

// --- Definición de Variables Globales ---
SistemaEstado_t g_estado_actual = DISARMED;
char g_pin_buffer[5];
uint8_t g_pin_index = 0;
volatile uint8_t g_intrusion_flag = 0;

// Variables locales estáticas para lectura de teclas
static char tecla = '\0';
static char tecla_ant = '\0';

// ------------------------------------------------------
// 1. ESTADO DESARMADO
// ------------------------------------------------------
void alarm_disarmed(void) {
    // Aquí solo esperamos la tecla 'A' para armar
    
    tecla = KPD_GetKey();

    if (tecla != '\0' && tecla_ant == '\0') {
        if (tecla == TECLA_ARMAR) {
            // Transición: Vamos a pedir el PIN
            LCD_Clear();
            LCD_SetCursor(0,0);
            LCD_SendString("Introduzca PIN:");
            
            // Reseteamos el buffer del PIN antes de cambiar de estado
            g_pin_index = 0;
            memset(g_pin_buffer, 0, sizeof(g_pin_buffer));
            
            // CAMBIO DE ESTADO
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
            LCD_SetCursor(1, g_pin_index); // Mueve cursor
            LCD_SendChar('*');             // Pone asterisco
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
            
            g_estado_actual = ARMED;
        } else {
            // --- PIN INCORRECTO -> REGRESAR A DESARMADO ---
            LCD_Clear();
            LCD_SetCursor(0,0);
            LCD_SendString("PIN Incorrecto");
            __delay_ms(1500); // Pequeña pausa para leer el mensaje
            
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