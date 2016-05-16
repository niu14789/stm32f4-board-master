

#ifndef _BSP_H_
#define _BSP_H


#define STM32_X3

#if !defined (STM32_V5) && !defined (STM32_X3)
	#error "Please define the board model : STM32_X3 or STM32_V5"
#endif

#define __STM32F1_BSP_VERSION		"1.1"

#define ENABLE_INT()	__set_PRIMASK(0)	
#define DISABLE_INT()	__set_PRIMASK(1)


#define BSP_Printf		printf

#include "stm32f4xx.h"
#include <stdio.h>
#include <string.h>

#ifndef TRUE
	#define TRUE  1
#endif

#ifndef FALSE
	#define FALSE 0
#endif

#include "bsp_sdio_sd.h"

void bsp_Init(void);
void bsp_Idle(void);

#endif

