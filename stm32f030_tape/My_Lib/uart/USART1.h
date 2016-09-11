
#ifndef _USART1_H
#define _USART1_H
#include "ALL_Includes.h"
//#include "board.h"

#if 0
//#define debug(format, ...)  do{ printf ( "[%s: %d: %s> : "format, __FILE__, __LINE__, __FUNCTION__,## __VA_ARGS__); }while(0)
#define debug(format, ...)  do{ printf ( "[%d: %s]:"format, __LINE__, __FUNCTION__,## __VA_ARGS__); }while(0)
#else
#define debug(format, ...) do{}while(0)

#endif


void USART1_Init(uint32_t baud);

#endif
