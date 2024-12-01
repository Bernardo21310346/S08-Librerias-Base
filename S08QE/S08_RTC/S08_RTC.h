/*
 * rtc_1k.h
 *
 *  Created on: Sep 14, 2024
 *      Author: shado
 */
#ifndef _S08_RTC_H_
#define _S08_RTC_H_

#include "S08_Board.h"
#include "S08_common/S08_variables.h"

#define rtc_get_flag() RTCSC_RTIF //Bandera de RTC

#ifndef BOARD_TYPE
#define BOARD_TYPE
/*
	@enum	eTimerMs_Channel
	@brief	Canales de temporizadores virtuales
	Este enum define los diferentes canales disponibles para crear temporizadores virtuales.
	Cada canal representa un contador independiente de 16 bits, utilizado para programar eventos en el tiempo.
	El valor maximo que puede alcanzar un contador es 65535.
*/
typedef enum{
	/** Timer por defecto, Se puede modificar su nombre sin problema*/
	eTimer_ch0=0,
	// Agrega tus timers personalizados de aqui en adelante
	
	/** ultimo canal definido. No modificar directamente. */
	eTimer_last,
	/** Numero total de canales definidos. */
	eTimer_count = eTimer_last
}eTimerMs_Channel;

#endif
/*
	@struct	sTimer
	@brief	Estructura para gestionar los contadores de los temporizadores virtuales

	Esta estructura contiene un array de contadores de 16 bits, uno por cada canal definido en el enum "eTimerMs_Channel".
	Cada contador se decrementa en una unidad en cada interrupcion del RTC y se reinicia cuando alcanza cero, generando asi un evento de temporizador.
*/
typedef struct{
	/**	Array de contadores de 16 bits para cada canal de temporizador.
	 * El indice del array corresponde al valor del enum "eTimerMs_Channel".
	 */
	uint16_t u16counterTimer[eTimer_count];
}sTimer;

void rtc_init_1k(uint16_t u16count, uint8_t ps, uint8_t u8timeSelect);
uint8_t rtc_get_count(void);
void rtc_set_count(uint8_t u8count);
void rtc_disableInterupt(void);
void rtc_enableInterupt(void);
void rtc_reset(void);

void rtc_atMs(void);
interrupt 24 void RTC_IRQ(void);
void timer_setCount(eTimerMs_Channel IDChannel, uint16_t u16countValue);
uint16_t timer_getCount(eTimerMs_Channel IDChannel);


#endif /* S08_RTC_H_ */
