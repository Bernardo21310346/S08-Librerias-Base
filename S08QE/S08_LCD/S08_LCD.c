/*
	@file 	S08_LCD.c
	@brief	Funciones para el manejo de LCD
	@author	Bernardo Iniguez 
	@date	30/11/24

	Este archivo contiene las funciones para el manejo del purto LCD de la tarjeta de prueba MoonByte S08
*/
#include "S08_LCD.h"

const uint8_t u8LCD_initValues[6] = {0x38,0x38,0x38,0x0F,0x06,0x01};

eInitLCD lcd_init_moonbyte(eInitLCD setmode)
{
	if(setmode == eInitLCD_4bitMode)
	{
		return lcd_init_4b();
	}
	else if(setmode == eInitLCD_8bitMode)
	{
		return lcd_init_8b();
	}
	else
	{
		return eInitLCD_NoDefined;
	}
}

eInitLCD lcd_init_4b(void)
{
	return eInitLCD_4bitStarted;
}

eInitLCD lcd_init_8b(void)
{
	static eInitLCD initState;
	static uint8_t u8Aux;
	
	if(initState == eInitLCD_initPort)
	{
		PTBDD = 0xFF;
		DATA_PORT = 0x00;
		PTADD |= 0x03;
		RS_PIN = 0;
		ENABLE_PIN = 0;
		timer_setCount(eTimer_chLCD, 4);
		u8Aux = 0;
		initState = eInitLCD_8bitWorking;
	}
	else if(initState == eInitLCD_8bitWorking)
	{
		if(u8Aux < 7)
		{
			if(lcd_setComand(u8LCD_initValues[u8Aux]) == true)
			{
				u8Aux++;
			}
		}
		else
		{
			initState = eInitLCD_8bitStarted;
			RS_PIN = 1;
			return initState;
		}
	}
	else
	{
		initState = eInitLCD_initPort;
	}
	return eInitLCD_8bitWorking;
}

bool lcd_enable(void)
{
	if((timer_getCount(eTimer_chLCD) == 0x0000))
	{
		ENABLE_PIN = 0;
		timer_setCount(eTimer_chLCD, 4);
		return true;
	}
	else
	{
		ENABLE_PIN = 1;
		return false;
	}
}

bool lcd_setComand(uint8_t comand)
{
	if(lcd_enable() == false)
	{
		RS_PIN = 0x00;
		DATA_PORT = (uint8_t)comand;
		return false;
	}
	else
	{
		RS_PIN = 0x01;
		return true;
	}
}

bool lcd_setData(uint8_t data)
{
	if(lcd_enable() == false)
	{
		DATA_PORT = (uint8_t)data;
		return false;
	}
	else
	{
		return true;
	}
}

eLCD_arrayStates lcd_sendArray(uint8_t *dataArray)
{
	static eLCD_arrayStates arrayState;
	static uint8_t *pu8Array;
	if(arrayState == eArray_empty)
	{
		pu8Array = dataArray;
		arrayState = eArray_working;
	}
	else if(arrayState == eArray_working)
	{
		if(*pu8Array != 0x00)
		{
			if(lcd_setData(*pu8Array) == true)
			{
				pu8Array++;
			}
		}
		else
		{
			arrayState = eArray_finish;
		}
	}
	else if(arrayState == eArray_finish)
	{
		arrayState = eArray_empty;
		return eArray_finish;
	}
	else
	{
		arrayState = eArray_empty;
	}
	return eArray_working;
}

eLCD_makeCaracter lcd_make_character(uint8_t caracter, uint8_t *pu8data)
{
	static eLCD_makeCaracter caracterState;
	static uint8_t u8Aux;
	static uint8_t *pu8caracter;
	if(caracterState == eCaracter_empty)
	{
		pu8caracter = pu8data;
		u8Aux = 0;
		caracterState = eCaracter_goToCGRAM_Dir;
	}
	else if(caracterState == eCaracter_goToCGRAM_Dir)
	{
		if(lcd_setComand(lcd_getCGRAM_dir(caracter)) == true)
		{
			caracterState = eCaracter_working;
		}
	}
	else if(caracterState == eCaracter_working)
	{
		if(u8Aux < 8)
		{
			if(lcd_setData(*pu8caracter) == true)
			{
				u8Aux++;
				pu8caracter++;
			}
		}
		else
		{
			caracterState = eCaracter_finish;
		}
	}
	else if(caracterState == eCaracter_finish)
	{
		caracterState = eCaracter_empty;
		return eCaracter_finish;
	}
	else
	{
		caracterState = eCaracter_empty;
	}
	return caracterState;
}

bool lcd_setRow(uint8_t row, uint8_t offset)
{
	uint8_t ddram_dir;
	if(row == 1)
	{
		ddram_dir = LCD_HOME + offset;
	}
	else if(row == 2)
	{
		ddram_dir = LCD_R2 + offset;
	}
	else if(row == 3)
	{
		ddram_dir = LCD_R3 + offset;
	}
	else if(row == 4)
	{
		ddram_dir = LCD_R4 + offset;
	}
	return lcd_setComand(ddram_dir);
}

uint8_t lcd_getCGRAM_dir(uint8_t caracter)
{
	if(caracter == 1)
	{
		return LCD_CGRAM_CH1_HOME;
	}
	else if(caracter == 2)
	{
		return LCD_CGRAM_CH2_HOME;
	}
	else if(caracter == 3)
	{
		return LCD_CGRAM_CH3_HOME;
	}
	else if(caracter == 4)
	{
		return LCD_CGRAM_CH4_HOME;
	}
	else if(caracter == 5)
	{
		return LCD_CGRAM_CH5_HOME;
	}
	else if(caracter == 6)
	{
		return LCD_CGRAM_CH6_HOME;
	}
	else if(caracter == 7)
	{
		return LCD_CGRAM_CH7_HOME;
	}
	else if(caracter == 8)
	{
		return LCD_CGRAM_CH8_HOME;
	}
}
