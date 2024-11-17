/*
	@file 	S08_RTC.c
	@brief	Funciones para el manejo de RTC
	@author	Bernardo Iñiguez 
	@date	16/11/24

	Este archivo contiene las funciones para el manejo del RTC de los MCUs con procesador S08 de NXP-Freescale
*/
#include "S08_RTC.h"

sTimer counterRTC;

/*
	@brief Inicializar RTC con reloj de 1KHz

	Esta funcion sirve para inicializar el RTC con el reloj interno de 1KHz que provee el MCU

	@param	u16count cuenta en la que se encendera el flag "RTCSC_RTIF"
	@param	ps sirve para seleccionar el preescaler
	@param	u8timeSelect tiempo que simboliza la cuenta milisegundos 'm' o segundos 's'

	@return No tiene retorno
*/
void rtc_init_1k(uint16_t u16count, uint8_t ps, uint8_t u8timeSelect)
{
	uint8_t RTSC_Mask = 0;
	if((ps == 1) && (u8timeSelect == 'm'))
	{
		if(u16count == 1) // 1ms 1KHz
		{
			RTSC_Mask = (0x08 << RTCSC_RTCPS);
		}
		else if(u16count == 2) // 2ms 1KHz
		{
			RTSC_Mask = (0x09 << RTCSC_RTCPS);
		}
		else if(u16count == 4) // 4ms 1KHz
		{
			RTSC_Mask = (0x0A << RTCSC_RTCPS);
		}
		else if(u16count == 8) // 8ms 1KHz
		{
			RTSC_Mask = (0x01 << RTCSC_RTCPS);
		}
		else if(u16count == 10) // 10ms 1KHz
		{
			RTSC_Mask = (0x0B << RTCSC_RTCPS);
		}
		else if(u16count == 16) // 16ms 1KHz
		{
			RTSC_Mask = (0x0C << RTCSC_RTCPS);
		}
		else if(u16count == 32) // 32ms 1KHz
		{
			RTSC_Mask = (0x02 << RTCSC_RTCPS);
		}
		else if(u16count  == 64) // 64ms 1KHz
		{
			RTSC_Mask = (0x03 << RTCSC_RTCPS);
		}
		else if(u16count == 128) // 128ms 1KHz
		{
			RTSC_Mask = (0x04 << RTCSC_RTCPS);
		}
		else if(u16count == 256) // 256ms 1KHz
		{
			RTSC_Mask = (0x05 << RTCSC_RTCPS);
		}
		else if(u16count == 512) // 512ms 1KHz
		{
			RTSC_Mask = (0x06 << RTCSC_RTCPS);
		}
		else if(u16count == 100) // 100ms 1KHz
		{
			RTSC_Mask = (0x0D << RTCSC_RTCPS);
		}
		else if(u16count == 500) // 500ms 1KHz
		{
			RTSC_Mask = (0x0E << RTCSC_RTCPS);
		}
	}
	else if((ps == 1) && (u8timeSelect == 's'))
	{
		if(u16count == 1) // 1s 1KHz
		{
			RTSC_Mask = (0x0F << RTCSC_RTCPS);
		}
		else if(u16count == 1024) // 1.024ms 1KHz
		{
			RTSC_Mask = (0x07 << RTCSC_RTCPS);
		}
	}
	
	RTCSC |= (0x00 << RTCSC_RTCLKS) | RTSC_Mask;
}

/*
	@brief	Inicializa el RTC en mS con interrupciones
	
	Funcion para iniciar el RTC a 1mS con reloj de 1KHz, así mismo inicilizar las interrupciones por cuenta de RTC

	@param void no requiere parametros de entrada

	@return No tiene retorno
*/
void rtc_atMs(void)
{
	rtc_enableInterupt();
	rtc_init_1k(1, 1, 'm');
	rtc_set_count(1);
}

/*
	@brief	Habilita las interrupciones del RTC
	
	Funcion para activar el bit en RTCSC que permite las interrupciones

	@param void no requiere parametros de entrada

	@return No tiene retorno
*/
void rtc_enableInterupt(void)
{
	RTCSC_RTIE |= 1;
}

/*
	@brief	Deshabilita las interrupciones del RTC
	
	Funcion para desactivar el bit en RTCSC que permite las interrupciones

	@param void no requiere parametros de entrada

	@return No tiene retorno
*/
void rtc_disableInterupt(void)
{
	RTCSC &= ~(1<<RTCSC_RTIE);
}

/*
	@brief	Borra el bit de interrupción

	@param void no requiere parametros de entrada

	@return No tiene retorno
*/
void rtc_reset(void)
{
	RTCSC = RTCSC | 0x80;
}

/*
	@brief	Establece la cuenta en la que  "RTCSC_RTIF" se activara

	@param	u8count cuenta que se desea

	@return No retorna nada
*/
void rtc_set_count(uint8_t u8count)
{
	RTCMOD = u8count;
}

/*
	@brief	Lee la cuenta actual del registro de RTC

	@param void no requiere parametros de entrada

	@return Retorna la cuenta del registro
*/
uint8_t rtc_get_count(void)
{
	return RTCCNT;
}

/*
	@brief	Establece la cuenta para un timer virtual

	@param IDChannel canal virtual al que se asignará la cuenta
	@param	u16countValue valor a asignar en el temporizador

	@return No retorna nada
*/
void timer_setCount(eTimerMs_Channel IDChannel, uint16_t u16countValue)
{
	counterRTC.u16counterTimer[IDChannel] = u16countValue;
}

/*
	@brief	Lee la cuenta de un temporizador virtual

	@param IDChannel canal virtual el cual se requiere leer

	@return cuenta actual del temporizador virtual hasta llegar a 0
	@warning solo es útil cuando se usa la interrupción cómo manejo de temporizadores
*/
uint16_t timer_getCount(eTimerMs_Channel IDChannel)
{
	return counterRTC.u16counterTimer[IDChannel];
}

/*
	@brief	Interrupcion de RTC

	@param void no requiere de arametros

	@return No retorna nada
	@warning Esta función está altamente acoplada a la gestión de temporizadores virtuales. Si necesitas utilizar esta interrupción para otros fines, deberás modificar las siguientes secciones del código:
		- **Configuración de la interrupción:** Ajustar la prioridad y el vector de interrupción para evitar conflictos.
 		- **Gestión de la cola de temporizadores:** Crear un mecanismo para almacenar y procesar eventos de temporización de forma independiente de la interrupción del RTC.
		- **Actualización de los contadores:** Modificar la lógica de actualización de los contadores para que se ejecute en el contexto adecuado.
		**Nota:** Modificar esta función puede afectar la precisión y el funcionamiento de los temporizadores virtuales. Se recomienda evaluar cuidadosamente las implicaciones de cualquier cambio antes de implementarlo.
*/
interrupt 24 void RTC_IRQ(void)
{
	uint8_t u8Timer_index = eTimer_count;
	DisableInterrupts;
	do
	{
		if(u8Timer_index != 0x00)
		{
			u8Timer_index--;
		}
		if(counterRTC.u16counterTimer[u8Timer_index] > 0x0000)
		{
			counterRTC.u16counterTimer[u8Timer_index]--;
		}
	}while(u8Timer_index > 0x00);
	rtc_reset();
	EnableInterrupts;
}
