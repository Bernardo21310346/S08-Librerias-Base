/*
 * board_settings.h
 *
 *  Created on: Nov 30, 2024
 *      Author: Bernardo Iniguez
 */

#ifndef S08_BOARD_H_
#define S08_BOARD_H_

#include <hidef.h>
#include "derivative.h"

#define BOARD_TYPE 

typedef enum{
	/** Timer por defecto, Se puede modificar su nombre sin problema*/
	eTimer_ch0=0,
	// Agrega tus timers personalizados de aqui en adelante
	eTimer_chLCD,
	/** ultimo canal definido. No modificar directamente. */
	eTimer_last,
	/** Numero total de canales definidos. */
	eTimer_count = eTimer_last
}eTimerMs_Channel;

#endif /* S08_BOARD_H_ */
