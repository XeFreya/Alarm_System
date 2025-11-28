
/* * Archivo: lcd_i2c.c
 * Implementación de la librería del LCD I2C (Software I2C).
 */

// Incluye los archivos generados por MCC
#include "mcc_generated_files/mcc.h"
#include "lcd_i2c.h"

// --- Configuración Clave ---

// Dirección I2C de 7 bits
// (Según tu esquemático de Proteus, A0,A1,A2 a GND = 0x20)
#define LCD_I2C_ADDRESS    0x27

// --- Mapeo de pines del PCF8574 al LCD ---
#define LCD_RS             0b00000001  // P0
#define LCD_RW             0b00000010  // P1 (No lo usamos)
#define LCD_EN             0b00000100  // P2
#define LCD_BACKLIGHT      0b00001000  // P3
#define LCD_D4             0b00010000  // P4
#define LCD_D5             0b00100000  // P5
#define LCD_D6             0b01000000  // P6
#define LCD_D7             0b10000000  // P7

// --- Definiciones de Software I2C ---
// (Esta es la corrección - usando los nombres personalizados)
// Asegúrate de que RC3/SDA y RC4/SCL estén como "Open Drain" en MCC
#define I2C_SCL_SetHigh()   SCL_SetHigh()
#define I2C_SCL_SetLow()    SCL_SetLow()
#define I2C_SDA_SetHigh()   SDA_SetHigh()
#define I2C_SDA_SetLow()    SDA_SetLow()
#define I2C_SDA_Read()      SDA_GetValue()
#define I2C_SDA_SetInput()  SDA_SetDigitalInput()
#define I2C_SDA_SetOutput() SDA_SetDigitalOutput()

// Delay corto para el reloj I2C (aprox 100kHz)
#define I2C_Delay()         __delay_us(5)

// Variable global interna
static uint8_t _backlight_state = LCD_BACKLIGHT;

// --- Funciones de Software I2C (Privadas) ---

/**
 * @brief Genera la condición de START de I2C
 */
static void I2C_Start(void) {
    I2C_SDA_SetOutput();
    I2C_SDA_SetHigh();
    I2C_SCL_SetHigh();
    I2C_Delay();
    I2C_SDA_SetLow(); // SDA baja MIENTRAS SCL está alta
    I2C_Delay();
    I2C_SCL_SetLow();
    I2C_Delay();
}

/**
 * @brief Genera la condición de STOP de I2C
 */
static void I2C_Stop(void) {
    I2C_SDA_SetOutput();
    I2C_SCL_SetLow();
    I2C_SDA_SetLow();
    I2C_Delay();
    I2C_SCL_SetHigh();
    I2C_Delay();
    I2C_SDA_SetHigh(); // SDA sube MIENTRAS SCL está alta
    I2C_Delay();
}

/**
 * @brief Envía un byte por I2C
 * @return 1 si recibe ACK, 0 si recibe NACK
 */
static uint8_t I2C_Write(uint8_t byte) {
    uint8_t i, ack_bit;
    I2C_SDA_SetOutput();

    // Envía los 8 bits del byte
    for (i = 0; i < 8; i++) {
        if ((byte << i) & 0x80) { // Si el bit MSB es 1
            I2C_SDA_SetHigh();
        } else {
            I2C_SDA_SetLow();
        }
        I2C_SCL_SetHigh(); // Pulso de reloj
        I2C_Delay();
        I2C_SCL_SetLow();
        I2C_Delay();
    }

    // Leer el bit de ACK del esclavo
    I2C_SDA_SetInput();  // Pone SDA como entrada
    I2C_SCL_SetHigh();
    I2C_Delay();
    ack_bit = !I2C_SDA_Read(); // Lee el pin. ACK es 0 (LOW), NACK es 1 (HIGH)
    I2C_SCL_SetLow();
    I2C_Delay();
    return ack_bit;
}

// --- Funciones de la Librería LCD (Privadas) ---

/**
 * @brief Envía un byte de datos al PCF8574
 */
static void LCD_SendByteI2C(uint8_t byte) {
    I2C_Start();
    // Envía la dirección del esclavo (con bit de escritura 0)
    I2C_Write((LCD_I2C_ADDRESS << 1) | 0x00); 
    // Envía el byte de datos
    I2C_Write(byte);
    I2C_Stop();
}

/**
 * @brief Envía 4 bits (un nibble) al LCD, con pulso de Enable
 */
static void LCD_SendNibble(uint8_t nibble, uint8_t isData) {
    uint8_t byte_to_send;
    // Combina el nibble (D4-D7) con los pines de control (RS, RW, E, BL)
    byte_to_send = (nibble & 0xF0) | (isData ? LCD_RS : 0) | _backlight_state;

    // 1. Envía el dato con Enable=1
    LCD_SendByteI2C(byte_to_send | LCD_EN);
    __delay_us(2); // Delay para el pulso de Enable
    
    // 2. Envía el dato con Enable=0
    LCD_SendByteI2C(byte_to_send & ~LCD_EN);
    __delay_us(50); // Delay para que el LCD procese
}

/**
 * @brief Envía un byte completo (8 bits) al LCD
 */
static void LCD_SendByte(uint8_t byte, uint8_t isData) {
    // Envía primero los 4 bits de arriba
    LCD_SendNibble(byte & 0xF0, isData);
    // Envía los 4 bits de abajo
    LCD_SendNibble((byte << 4) & 0xF0, isData);
}

// --- Implementación de Funciones Públicas ---

void LCD_Init(void) {
    // Secuencia de inicialización del LCD
    __delay_ms(50);
    LCD_SendNibble(0x30, 0); // 0 = Comando
    __delay_ms(5);
    LCD_SendNibble(0x30, 0);
    __delay_us(100);
    LCD_SendNibble(0x30, 0);
    __delay_us(100);
    LCD_SendNibble(0x20, 0); // Pone en modo 4-bit
    __delay_us(100);
    
    LCD_SendByte(0x28, 0); // Modo 4-bit, 2 líneas, 5x8
    LCD_SendByte(0x0C, 0); // Display ON, Cursor OFF
    LCD_SendByte(0x01, 0); // Limpiar pantalla
    __delay_ms(2);         // El comando "clear" es lento
    LCD_SendByte(0x06, 0); // Modo de entrada: incrementa cursor
}

void LCD_Clear(void) {
    LCD_SendByte(0x01, 0); // Comando "Clear Display"
    __delay_ms(2);         // Este comando es lento
}

void LCD_SetCursor(uint8_t row, uint8_t col) {
    static const uint8_t row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
    if (row > 3) row = 3; // Limita a 4 filas
    // Combina la dirección base de la fila con la columna
    LCD_SendByte(0x80 | (uint8_t)(row_offsets[row] + col), 0);
}

void LCD_SendChar(char c) {
    LCD_SendByte((uint8_t)c, 1); // 1 = es un dato
}

void LCD_SendString(char *str) {
    while (*str) {
        LCD_SendChar(*str++);
    }
}

void LCD_Backlight(uint8_t state) {
    if (state) {
        _backlight_state = LCD_BACKLIGHT;
    } else {
        _backlight_state = 0;
    }
    // Envía un comando nulo solo para actualizar el pin del backlight
    I2C_Start();
    I2C_Write((LCD_I2C_ADDRESS << 1) | 0x00);
    I2C_Write(_backlight_state);
    I2C_Stop();
}