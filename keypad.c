#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/pin_manager.h"
#include "keypad.h"


static const char keys[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};



char KPD_GetKey(void) {
    // Ponemos todas las filas en ALTO (inactivo)
    KPD_R1_SetHigh();
    KPD_R2_SetHigh();
    KPD_R3_SetHigh();
    KPD_R4_SetHigh();
    
    // --- Escaneo de Fila 1 ---
    KPD_R1_SetLow();    
    __delay_us(10); 
    if (KPD_C1_GetValue() == 0) { KPD_R1_SetHigh(); return keys[0][0]; }
    if (KPD_C2_GetValue() == 0) { KPD_R1_SetHigh(); return keys[0][1]; }
    if (KPD_C3_GetValue() == 0) { KPD_R1_SetHigh(); return keys[0][2]; }
    if (KPD_C4_GetValue() == 0) { KPD_R1_SetHigh(); return keys[0][3]; }
    KPD_R1_SetHigh();

    // --- Escaneo de Fila 2 ---
    KPD_R2_SetLow();
    __delay_us(10);
    if (KPD_C1_GetValue() == 0) { KPD_R2_SetHigh(); return keys[1][0]; }
    if (KPD_C2_GetValue() == 0) { KPD_R2_SetHigh(); return keys[1][1]; }
    if (KPD_C3_GetValue() == 0) { KPD_R2_SetHigh(); return keys[1][2]; }
    if (KPD_C4_GetValue() == 0) { KPD_R2_SetHigh(); return keys[1][3]; }
    KPD_R2_SetHigh();
    
    // --- Escaneo de Fila 3 ---
    KPD_R3_SetLow();
    __delay_us(10);
    if (KPD_C1_GetValue() == 0) { KPD_R3_SetHigh(); return keys[2][0]; }
    if (KPD_C2_GetValue() == 0) { KPD_R3_SetHigh(); return keys[2][1]; }
    if (KPD_C3_GetValue() == 0) { KPD_R3_SetHigh(); return keys[2][2]; }
    if (KPD_C4_GetValue() == 0) { KPD_R3_SetHigh(); return keys[2][3]; }
    KPD_R3_SetHigh();

    // --- Escaneo de Fila 4 ---
    KPD_R4_SetLow();
    __delay_us(10);
    if (KPD_C1_GetValue() == 0) { KPD_R4_SetHigh(); return keys[3][0]; }
    if (KPD_C2_GetValue() == 0) { KPD_R4_SetHigh(); return keys[3][1]; }
    if (KPD_C3_GetValue() == 0) { KPD_R4_SetHigh(); return keys[3][2]; }
    if (KPD_C4_GetValue() == 0) { KPD_R4_SetHigh(); return keys[3][3]; }
    KPD_R4_SetHigh();

    return '\0'; // Retorna nulo si no se presionó nada
}

