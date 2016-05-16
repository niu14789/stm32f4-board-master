/*
*********************************************************************************************************
*
*                                          main application
*
*                                     ST Microelectronics STM32
*                                              on the
*
*                                          
*                                       
*
* Filename      : app.c
* Version       : V1.00
* Programmer(s) : jackie
*                 DC
*********************************************************************************************************
*/

#ifndef __FLASHAPP_H__
#define __FLASHAPP_H__
#include "stm32f4xx.h"
typedef unsigned char  BOOLEAN;
typedef unsigned char  INT8U;                    /* Unsigned  8 bit quantity                           */
typedef signed   char  INT8S;                    /* Signed    8 bit quantity                           */
typedef unsigned short INT16U;                   /* Unsigned 16 bit quantity                           */
typedef signed   short INT16S;                   /* Signed   16 bit quantity                           */
typedef unsigned int   INT32U;                   /* Unsigned 32 bit quantity                           */
typedef signed   int   INT32S;                   /* Signed   32 bit quantity                           */

/* Base address of the Flash sectors */
#define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000) /* Base @ of Sector 0, 16 Kbyte */
#define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08004000) /* Base @ of Sector 1, 16 Kbyte */
#define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08008000) /* Base @ of Sector 2, 16 Kbyte */
#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x0800C000) /* Base @ of Sector 3, 16 Kbyte */
#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000) /* Base @ of Sector 4, 64 Kbyte */
#define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08020000) /* Base @ of Sector 5, 128 Kbyte */
#define ADDR_FLASH_SECTOR_6     ((uint32_t)0x08040000) /* Base @ of Sector 6, 128 Kbyte */
#define ADDR_FLASH_SECTOR_7     ((uint32_t)0x08060000) /* Base @ of Sector 7, 128 Kbyte */
#define ADDR_FLASH_SECTOR_8     ((uint32_t)0x08080000) /* Base @ of Sector 8, 128 Kbyte */
#define ADDR_FLASH_SECTOR_9     ((uint32_t)0x080A0000) /* Base @ of Sector 9, 128 Kbyte */
#define ADDR_FLASH_SECTOR_10    ((uint32_t)0x080C0000) /* Base @ of Sector 10, 128 Kbyte */
#define ADDR_FLASH_SECTOR_11    ((uint32_t)0x080E0000) /* Base @ of Sector 11, 128 Kbyte */




#define USER_FLASH_IAP_ADDRESS        0x08040000
/* End of the Flash address */
#define USER_FLASH_END_ADDRESS        0x080FFFFF
///* Define the user application size */
//#define USER_FLASH_SIZE   (USER_FLASH_END_ADDRESS - APPLICATION_ADDRESS + 1)

///* Define the address from where user application will be loaded.
//   Note: the 1st sector 0x08000000-0x08003FFF is reserved for the IAP code */
//#define APPLICATION_ADDRESS   		(uint32_t)0x08004000 
//#define APPLICATION_CONFIG     		ADDR_FLASH_SECTOR_3
//#define APPLICATION_CONFIG_SIZE		(ADDR_FLASH_SECTOR_3-ADDR_FLASH_SECTOR_2)
//#define APPLICATION_CONFIG_SEG		FLASH_Sector_3

//#define FLASH_DEBUG_ENABLE
#ifdef  FLASH_DEBUG_ENABLE
	#define FLASH_DEBUG(...)  printk(...)
#else
	#define FLASH_DEBUG(...)
#endif

////*****************************************************************************************************************
////函数:void* Flash_Read(INT32U addr,INT32U size)
////功能:	This function writes a data buffer in flash (data are 32-bit aligned).
////参数: addr: pointer on data buffer
////			size: length of data buffer (unit is 32-bit word)   
////说明: None
////*****************************************************************************************************************
//void Flash_Read(INT32U addr,INT8U *buf,INT32U size);
////*****************************************************************************************************************
////函数:void Flash_Write(INT32U addr,void *pbuf,INT32U size)
////功能:	This function writes a data buffer in flash (data are 32-bit aligned).
////参数: addr: pointer on data buffer
////			size: length of data buffer (unit is 32-bit word)   
////说明: None
////*****************************************************************************************************************
//INT32U Flash_Write(INT32U *pbuf,INT32U size);
INT8U IAP_Start(void);
 void FLASH_If_Init(void);
void IAP_Stop(void);
void Jump_To_APP(void);
INT32U IAP_Flash_Write(INT32U addr,INT8U *pbuf,INT32U size);
void IAP_Flash_Read(INT32U addr,INT8U *pbuf,INT32U size);
#endif

