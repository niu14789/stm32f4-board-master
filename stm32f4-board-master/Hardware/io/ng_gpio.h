
/**
  ******************************************************************************
  * @file    ng_gpio.c
  * @author  dmfc gps niu
  * @version V0.1.0
  * @date    1-March-2014
  * @brief   This file provides all the GPIO function.
  ******************************************************************************
  
             ===================================================================      
  *                                 How to use this driver
  *          =================================================================== 
  *          1. Define the Device type.
	                This macro can be one of the following values:
									 @arg STM32F10x
									 @arg STM32F40x
  * 
  *          2. Define the Device I/O type
  *               This macro can be one of the following values:
	                 @arg STM32F10xCx    < 48pin   GPIOA~GPIOB >
									 @arg STM32F10xRx    < 64pin   GPIOA~GPIOC >
									 @arg STM32F10xVx    < 100pin  GPIOA~GPIOE >
									 @arg STM32F10xZx    < 144pin  GPIOA~GPIOG >
									 @arg STM32F4xxVx    < 100pin  GPIOA~GPIOE >
									 @arg STM32F4xxZx    < 144pin  GPIOA~GPIOG >
									 @arg STM32F4xxIx    < 176pin  GPIOA~GPIOI >
									This maroc will specified the I/Os type and nums
  */


/*   Define the Device type   */
//#define  STM32F10x

#define  STM32F40x





#ifdef STM32F10x  
 #include "stm32f10x.h"
#elif  defined STM32F40x
 #include "stm32f4xx.h"
#else
 #error Device type unspecified from ng_gpio.c at line : 33
#endif



typedef struct
{
  u8 bit0:1;
	u8 bit1:1;
	u8 bit2:1;
	u8 bit3:1;
	u8 bit4:1;
	u8 bit5:1;
	u8 bit6:1;
	u8 bit7:1;
	u8 bit8:1;
	u8 bit9:1;
	u8 bit10:1;
	u8 bit11:1;
	u8 bit12:1;
	u8 bit13:1;
	u8 bit14:1;
	u8 bit15:1;
	
} GPIOx_TypeDef;

#define GPIOx_BASE_A     ((u32)(&GPIOA->ODR))
#define GPIO_A           ((GPIOx_TypeDef *) GPIOx_BASE_A)

#define GPIOx_BASE_B     ((u32)(&GPIOB->ODR))
#define GPIO_B           ((GPIOx_TypeDef *) GPIOx_BASE_B)

#define GPIOx_BASE_C     ((u32)(&GPIOC->ODR))
#define GPIO_C           ((GPIOx_TypeDef *) GPIOx_BASE_C)

#define GPIOx_BASE_D     ((u32)(&GPIOD->ODR))
#define GPIO_D           ((GPIOx_TypeDef *) GPIOx_BASE_D)

#define GPIOx_BASE_E     ((u32)(&GPIOE->ODR))
#define GPIO_E           ((GPIOx_TypeDef *) GPIOx_BASE_E)

#define GPIOx_BASE_F     ((u32)(&GPIOF->ODR))
#define GPIO_F           ((GPIOx_TypeDef *) GPIOx_BASE_F)

#define GPIOx_BASE_G     ((u32)(&GPIOG->ODR))
#define GPIO_G           ((GPIOx_TypeDef *) GPIOx_BASE_G)

#define GPIOx_BASE_H     ((u32)(&GPIOH->ODR))
#define GPIO_H           ((GPIOx_TypeDef *) GPIOx_BASE_H)

#define GPIOx_BASE_I     ((u32)(&GPIOI->ODR))
#define GPIO_I           ((GPIOx_TypeDef *) GPIOx_BASE_I)

#define   PA0            GPIO_A->bit0
#define   PA1            GPIO_A->bit1
#define   PA2            GPIO_A->bit2
#define   PA3            GPIO_A->bit3
#define   PA4            GPIO_A->bit4
#define   PA5            GPIO_A->bit5
#define   PA6            GPIO_A->bit6
#define   PA7            GPIO_A->bit7
#define   PA8            GPIO_A->bit8
#define   PA9            GPIO_A->bit9
#define   PA10           GPIO_A->bit10
#define   PA11           GPIO_A->bit11
#define   PA12           GPIO_A->bit12
#define   PA13           GPIO_A->bit13
#define   PA14           GPIO_A->bit14
#define   PA15           GPIO_A->bit15

#define   PA(x)          GPIO_A->x


#define   PB0            GPIO_B->bit0
#define   PB1            GPIO_B->bit1
#define   PB2            GPIO_B->bit2
#define   PB3            GPIO_B->bit3
#define   PB4            GPIO_B->bit4
#define   PB5            GPIO_B->bit5
#define   PB6            GPIO_B->bit6
#define   PB7            GPIO_B->bit7
#define   PB8            GPIO_B->bit8
#define   PB9            GPIO_B->bit9
#define   PB10           GPIO_B->bit10
#define   PB11           GPIO_B->bit11
#define   PB12           GPIO_B->bit12
#define   PB13           GPIO_B->bit13
#define   PB14           GPIO_B->bit14
#define   PB15           GPIO_B->bit15

#define   PB(x)          GPIO_B->x


#define   PC0            GPIO_C->bit0
#define   PC1            GPIO_C->bit1
#define   PC2            GPIO_C->bit2
#define   PC3            GPIO_C->bit3
#define   PC4            GPIO_C->bit4
#define   PC5            GPIO_C->bit5
#define   PC6            GPIO_C->bit6
#define   PC7            GPIO_C->bit7
#define   PC8            GPIO_C->bit8
#define   PC9            GPIO_C->bit9
#define   PC10           GPIO_C->bit10
#define   PC11           GPIO_C->bit11
#define   PC12           GPIO_C->bit12
#define   PC13           GPIO_C->bit13
#define   PC14           GPIO_C->bit14
#define   PC15           GPIO_C->bit15

#define   PC(x)          GPIO_C->x


#define   PD0            GPIO_D->bit0
#define   PD1            GPIO_D->bit1
#define   PD2            GPIO_D->bit2
#define   PD3            GPIO_D->bit3
#define   PD4            GPIO_D->bit4
#define   PD5            GPIO_D->bit5
#define   PD6            GPIO_D->bit6
#define   PD7            GPIO_D->bit7
#define   PD8            GPIO_D->bit8
#define   PD9            GPIO_D->bit9
#define   PD10           GPIO_D->bit10
#define   PD11           GPIO_D->bit11
#define   PD12           GPIO_D->bit12
#define   PD13           GPIO_D->bit13
#define   PD14           GPIO_D->bit14
#define   PD15           GPIO_D->bit15

#define   PD(x)          GPIO_D->x


#define   PE0            GPIO_E->bit0
#define   PE1            GPIO_E->bit1
#define   PE2            GPIO_E->bit2
#define   PE3            GPIO_E->bit3
#define   PE4            GPIO_E->bit4
#define   PE5            GPIO_E->bit5
#define   PE6            GPIO_E->bit6
#define   PE7            GPIO_E->bit7
#define   PE8            GPIO_E->bit8
#define   PE9            GPIO_E->bit9
#define   PE10           GPIO_E->bit10
#define   PE11           GPIO_E->bit11
#define   PE12           GPIO_E->bit12
#define   PE13           GPIO_E->bit13
#define   PE14           GPIO_E->bit14
#define   PE15           GPIO_E->bit15

#define   PE(x)          GPIO_E->x


#define   PF0            GPIO_F->bit0
#define   PF1            GPIO_F->bit1
#define   PF2            GPIO_F->bit2
#define   PF3            GPIO_F->bit3
#define   PF4            GPIO_F->bit4
#define   PF5            GPIO_F->bit5
#define   PF6            GPIO_F->bit6
#define   PF7            GPIO_F->bit7
#define   PF8            GPIO_F->bit8
#define   PF9            GPIO_F->bit9
#define   PF10           GPIO_F->bit10
#define   PF11           GPIO_F->bit11
#define   PF12           GPIO_F->bit12
#define   PF13           GPIO_F->bit13
#define   PF14           GPIO_F->bit14
#define   PF15           GPIO_F->bit15

#define   PF(x)          GPIO_F->x


#define   PG0            GPIO_G->bit0
#define   PG1            GPIO_G->bit1
#define   PG2            GPIO_G->bit2
#define   PG3            GPIO_G->bit3
#define   PG4            GPIO_G->bit4
#define   PG5            GPIO_G->bit5
#define   PG6            GPIO_G->bit6
#define   PG7            GPIO_G->bit7
#define   PG8            GPIO_G->bit8
#define   PG9            GPIO_G->bit9
#define   PG10           GPIO_G->bit10
#define   PG11           GPIO_G->bit11
#define   PG12           GPIO_G->bit12
#define   PG13           GPIO_G->bit13
#define   PG14           GPIO_G->bit14
#define   PG15           GPIO_G->bit15

#define   PG(x)          GPIO_G->x


#define   PH0            GPIO_H->bit0
#define   PH1            GPIO_H->bit1
#define   PH2            GPIO_H->bit2
#define   PH3            GPIO_H->bit3
#define   PH4            GPIO_H->bit4
#define   PH5            GPIO_H->bit5
#define   PH6            GPIO_H->bit6
#define   PH7            GPIO_H->bit7
#define   PH8            GPIO_H->bit8
#define   PH9            GPIO_H->bit9
#define   PH10           GPIO_H->bit10
#define   PH11           GPIO_H->bit11
#define   PH12           GPIO_H->bit12
#define   PH13           GPIO_H->bit13
#define   PH14           GPIO_H->bit14
#define   PH15           GPIO_H->bit15

#define   PH(x)          GPIO_H->x


#define   PI0            GPIO_I->bit0
#define   PI1            GPIO_I->bit1
#define   PI2            GPIO_I->bit2
#define   PI3            GPIO_I->bit3
#define   PI4            GPIO_I->bit4
#define   PI5            GPIO_I->bit5
#define   PI6            GPIO_I->bit6
#define   PI7            GPIO_I->bit7
#define   PI8            GPIO_I->bit8
#define   PI9            GPIO_I->bit9
#define   PI10           GPIO_I->bit10
#define   PI11           GPIO_I->bit11
#define   PI12           GPIO_I->bit12
#define   PI13           GPIO_I->bit13
#define   PI14           GPIO_I->bit14
#define   PI15           GPIO_I->bit15

#define   PI(x)          GPIO_I->x






