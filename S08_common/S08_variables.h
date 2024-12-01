#ifndef _S08_VARIABLES_H
#define _S08_VARIABLES_H

/*
	@enum	bool
	@brief	valores boolenos
	Este enum define los tipos boolenaos para su uso en C ya que no estexisten por defecto
*/
typedef enum{
	false,
	true
}bool;

typedef unsigned char uint8_t;	// Variables de 8 bits sin signo
typedef char int8_t;			// Variables de 8 bits con signo
typedef unsigned int uint16_t;	// Variables de 16 bits sin signo
typedef int int16_t;			// Variables de 16 bits con signo

#endif
