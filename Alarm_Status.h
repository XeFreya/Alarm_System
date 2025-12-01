/* 
 * File:   Alarm_Status.h
 * Author: josem
 *
 * Created on 15 de noviembre de 2025, 11:51 AM
 */

#ifndef ALARM_STATUS_H
#define	ALARM_STATUS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h> // Necesario para uint8_t

// --- 1. Estados de la Alarma (Tus variables) ---
typedef enum {
    DISARMED,
    FIN_SCREEN, // Pantalla de pedir PIN
    ARMED,
    INTRUSION
} SistemaEstado_t;

// --- 2. Constantes ---
#define MASTER_PIN "1234"
#define TECLA_ARMAR 'A'
#define TECLA_BORRAR '*'

// --- 3. Variables Globales (Declaración externa) ---
extern SistemaEstado_t g_estado_actual;
extern char g_pin_buffer[5];
extern uint8_t g_pin_index;
extern volatile uint8_t g_zona_alarma;

// --- 4. Prototipos de Funciones (Tus funciones) ---
void alarm_disarmed(void);
void show_pin_screen(void);
void armed_alarm(void);
void alert_alarm(void);
void mostrar_zona_alarma(void);

#ifdef	__cplusplus
}
#endif

#endif	/* ALARM_STATUS_H */

