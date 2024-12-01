/*
 * S08_LCD.h
 *
 *  Created on: Nov 30, 2024
 *      Author: shado
 */

#ifndef S08_LCD_H_
#define S08_LCD_H_

#include "S08_Board.h"
#include "S08QE/S08_RTC/S08_RTC.h"


// Definición de pines LCD
#define DATA_PORT PTBD 			// Asignación de puerto de datos D0..D7 a PTB0..PTB7
#define ENABLE_PIN PTAD_PTAD1 	// Asignación del pin A1 cómo Enable
#define RS_PIN PTAD_PTAD0 		// Asignación del pin A0 cómo RS, 0 para comandos

// Direcciones de lineas LCD
#define LCD_HOME 0x80
#define LCD_R2 0xC0
#define LCD_R3 0x94
#define LCD_R4 0xD4

// Comandos de LCD
#define LCD_CLEAR 0x01

// Direcciones iniciales de CGRAM
#define LCD_CGRAM_CH1_HOME 0x40
#define LCD_CGRAM_CH2_HOME 0x48
#define LCD_CGRAM_CH3_HOME 0x50
#define LCD_CGRAM_CH4_HOME 0x58
#define LCD_CGRAM_CH5_HOME 0x60
#define LCD_CGRAM_CH6_HOME 0x68
#define LCD_CGRAM_CH7_HOME 0x70
#define LCD_CGRAM_CH8_HOME 0x78

typedef enum{
	eInitLCD_4bitMode,
	eInitLCD_8bitMode,
	eInitLCD_initPort,
	eInitLCD_4bitWorking,
	eInitLCD_8bitWorking,
	eInitLCD_4bitStarted,
	eInitLCD_8bitStarted,
	eInitLCD_NoDefined,
}eInitLCD;

typedef enum{
	eArray_empty,
	eArray_working,
	eArray_finish
}eLCD_arrayStates;

typedef enum{
	eCaracter_empty,
	eCaracter_goToCGRAM_Dir,
	eCaracter_working,
	eCaracter_finish
}eLCD_makeCaracter;

//Inicialización LCD
eInitLCD lcd_init_moonbyte(eInitLCD setmode);
eInitLCD lcd_init_4b(void);
eInitLCD lcd_init_8b(void);

// Funciones Base del LCD
bool lcd_enable(void);					// Habilitar tiempo de enable
bool lcd_setComand(uint8_t comand);		// Mandar un comando a la pantalla
bool lcd_setData(uint8_t data);			// Mandar un carácter a la pantalla
uint8_t lcd_getCGRAM_dir(uint8_t caracter); 

// Funciones complejas del LCD
eLCD_arrayStates lcd_sendArray(uint8_t *dataArray);			// Mandar un array de carácteres a la pantalla
bool lcd_setRow(uint8_t row, uint8_t offset);				// Posicionar cursor en coordenada específica
eLCD_makeCaracter lcd_make_character(uint8_t caracter, uint8_t *pu8data);	// Mandar un array para crear un carácter especial

#endif /* S08_LCD_H_ */
