/*
 * sram.h
 *
 *  Created on: 2016年5月21日
 *      Author: YJ-User17
 */

#ifndef __SRAM_H__
#define __SRAM_H__

#define PIN0				1<<0
#define PIN1				1<<1
#define PIN2				1<<2
#define PIN3				1<<3
#define PIN4				1<<4
#define PIN5				1<<5
#define PIN6				1<<6
#define PIN7				1<<7
#define PIN8				1<<8
#define PIN9				1<<9
#define PIN10				1<<10
#define PIN11				1<<11
#define PIN12				1<<12
#define PIN13				1<<13
#define PIN14				1<<14
#define PIN15				1<<15

#define GPIO_MODE_IN    	0		//ÆÕÍ¨ÊäÈëÄ£Ê½
#define GPIO_MODE_OUT		1		//ÆÕÍ¨Êä³öÄ£Ê½
#define GPIO_MODE_AF		2		//AF¹¦ÄÜÄ£Ê½
#define GPIO_MODE_AIN		3		//Ä£ÄâÊäÈëÄ£Ê½

#define GPIO_SPEED_2M		0		//GPIOËÙ¶È2Mhz
#define GPIO_SPEED_25M		1		//GPIOËÙ¶È25Mhz
#define GPIO_SPEED_50M		2		//GPIOËÙ¶È50Mhz
#define GPIO_SPEED_100M		3		//GPIOËÙ¶È100Mhz

#define GPIO_PUPD_NONE		0		//²»´øÉÏÏÂÀ­
#define GPIO_PUPD_PU		1		//ÉÏÀ­
#define GPIO_PUPD_PD		2		//ÏÂÀ­
#define GPIO_PUPD_RES		3		//±£Áô

#define GPIO_OTYPE_PP		0		//ÍÆÍìÊä³ö
#define GPIO_OTYPE_OD		1		//¿ªÂ©Êä³ö




#endif /* __SRAM_H__ */
