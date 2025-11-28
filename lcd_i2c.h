/* * Archivo: lcd_i2c.h
 * Librería para controlar un LCD I2C (PCF8574)
 * usando "bit-banging" (Software I2C).
 */

#ifndef LCD_I2C_H
#define	LCD_I2C_H

#include <stdint.h> // Para usar uint8_t

// --- Funciones Públicas ---

/**
 * @brief Inicializa el LCD en modo 4-bits y lo enciende.
 */
void LCD_Init(void);

/**
 * @brief Limpia toda la pantalla del LCD y pone el cursor en (0,0).
 */
void LCD_Clear(void);

/**
 * @brief Mueve el cursor a una posición específica.
 * @param row Fila (0-3)
 * @param col Columna (0-19)
 */
void LCD_SetCursor(uint8_t row, uint8_t col);

/**
 * @brief Envía un solo carácter al LCD.
 * @param c Carácter a mostrar.
 */
void LCD_SendChar(char c);

/**
 * @brief Envía una cadena de texto (string) al LCD.
 * @param str Puntero a la cadena de texto (debe terminar en '\0').
 */
void LCD_SendString(char *str);

/**
 * @brief Enciende o apaga la luz de fondo (backlight).
 * @param state 1 para encender, 0 para apagar.
 */
void LCD_Backlight(uint8_t state);


#endif	/* LCD_I2C_H */