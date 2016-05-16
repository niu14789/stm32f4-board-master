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
#include "stm32f4xx.h"
#include "flashapp.h"

void Jump_To_APP(void)
{
          void (*pUserApp)(void);
					 INT32U JumpAddress;  
					// __asm("CPSID  I");					
					JumpAddress = *(volatile uint32_t*) (USER_FLASH_IAP_ADDRESS+4);
					pUserApp = (void (*)(void)) JumpAddress;
					/* Initialize user application's Stack Pointer */
					__set_PSP(*(volatile uint32_t*) USER_FLASH_IAP_ADDRESS);
					__set_CONTROL(0);
					__set_MSP(*(volatile uint32_t*) USER_FLASH_IAP_ADDRESS);
					pUserApp();
}
////*****************************************************************************************************************
////函数:static INT32U GetSector(INT32U Address)
////功能:	Gets the sector of a given address
////参数: Address: Flash address   
////说明: The sector of a given address
////*****************************************************************************************************************
//static INT32U GetSector(INT32U Address)
//{
//  uint32_t sector = 0;
//  
//  if((Address < ADDR_FLASH_SECTOR_1) && (Address >= ADDR_FLASH_SECTOR_0))
//  {
//    sector = FLASH_Sector_0;  
//  }
//  else if((Address < ADDR_FLASH_SECTOR_2) && (Address >= ADDR_FLASH_SECTOR_1))
//  {
//    sector = FLASH_Sector_1;  
//  }
//  else if((Address < ADDR_FLASH_SECTOR_3) && (Address >= ADDR_FLASH_SECTOR_2))
//  {
//    sector = FLASH_Sector_2;  
//  }
//  else if((Address < ADDR_FLASH_SECTOR_4) && (Address >= ADDR_FLASH_SECTOR_3))
//  {
//    sector = FLASH_Sector_3;  
//  }
//  else if((Address < ADDR_FLASH_SECTOR_5) && (Address >= ADDR_FLASH_SECTOR_4))
//  {
//    sector = FLASH_Sector_4;  
//  }
//  else if((Address < ADDR_FLASH_SECTOR_6) && (Address >= ADDR_FLASH_SECTOR_5))
//  {
//    sector = FLASH_Sector_5;  
//  }
//  else if((Address < ADDR_FLASH_SECTOR_7) && (Address >= ADDR_FLASH_SECTOR_6))
//  {
//    sector = FLASH_Sector_6;  
//  }
//  else if((Address < ADDR_FLASH_SECTOR_8) && (Address >= ADDR_FLASH_SECTOR_7))
//  {
//    sector = FLASH_Sector_7;  
//  }
//  else if((Address < ADDR_FLASH_SECTOR_9) && (Address >= ADDR_FLASH_SECTOR_8))
//  {
//    sector = FLASH_Sector_8;  
//  }
//  else if((Address < ADDR_FLASH_SECTOR_10) && (Address >= ADDR_FLASH_SECTOR_9))
//  {
//    sector = FLASH_Sector_9;  
//  }
//  else if((Address < ADDR_FLASH_SECTOR_11) && (Address >= ADDR_FLASH_SECTOR_10))
//  {
//    sector = FLASH_Sector_10;  
//  }
//  else/*(Address < FLASH_END_ADDR) && (Address >= ADDR_FLASH_SECTOR_11))*/
//  {
//    sector = FLASH_Sector_11;  
//  }
//    return sector;
//}
////*****************************************************************************************************************
////函数:INT32U FLASH_If_DisableWriteProtection(void)
////功能:	Disables the write protection of user flash area.
////参数: None
////说明: 1: Write Protection successfully disabled 2: Error: Flash write unprotection failed
////*****************************************************************************************************************
//static INT32U FLASH_If_DisableWriteProtection(void)
//{
//  __IO uint32_t UserStartSector = FLASH_Sector_1, UserWrpSectors = OB_WRP_Sector_1;

//  /* Get the sector where start the user flash area */
//  UserStartSector = GetSector(APPLICATION_ADDRESS);

//  /* Mark all sectors inside the user flash area as non protected */  
//  UserWrpSectors = 0xFFF-((1 << (UserStartSector/8))-1);
//   
//  /* Unlock the Option Bytes */
//  FLASH_OB_Unlock();

//  /* Disable the write protection for all sectors inside the user flash area */
//  FLASH_OB_WRPConfig(UserWrpSectors, DISABLE);

//  /* Start the Option Bytes programming process. */  
//  if (FLASH_OB_Launch() != FLASH_COMPLETE)
//  {
//    /* Error: Flash write unprotection failed */
//    return (2);
//  }

//  /* Write Protection successfully disabled */
//  return (1);
//}
////*****************************************************************************************************************
////函数:INT16U FLASH_If_GetWriteProtectionStatus(void)
////功能:	Returns the write protection status of user flash area.
////参数: None
////说明: 0: No write protected sectors inside the user flash area 
////      1: Some sectors inside the user flash area are write protected
////*****************************************************************************************************************
//static INT16U FLASH_If_GetWriteProtectionStatus(void)
//{
//  uint32_t UserStartSector = FLASH_Sector_1;

//  /* Get the sector where start the user flash area */
//  UserStartSector = GetSector(APPLICATION_ADDRESS);

//  /* Check if there are write protected sectors inside the user flash area */
//  if ((FLASH_OB_GetWRP() >> (UserStartSector/8)) == (0xFFF >> (UserStartSector/8)))
//  { /* No write protected sectors inside the user flash area */
//    return 1;
//  }
//  else
//  { /* Some sectors inside the user flash area are write protected */
//    return 0;
//  }
//}
//*****************************************************************************************************************
//函数:INT32U FLASH_If_Write(__IO INT32U* FlashAddress, INT32U* Data ,INT32U DataLength)
//功能:	This function writes a data buffer in flash (data are 32-bit aligned).
//参数: FlashAddress: start address for writing data buffer
//      Data: pointer on data buffer
//			DataLength: length of data buffer (unit is 32-bit word)   
//说明: 0: Data successfully written to Flash memory
//      1: Error occurred while writing data in Flash memory
//			2: Written Data in flash memory is different from expected one
//*****************************************************************************************************************
static INT32U FLASH_If_Write(__IO INT32U* FlashAddress, INT32U* Data ,INT32U DataLength)
{
  uint32_t i = 0;

  for (i = 0; (i < DataLength) && (*FlashAddress <= (USER_FLASH_END_ADDRESS-4)); i++)
  {
    /* Device voltage range supposed to be [2.7V to 3.6V], the operation will
       be done by word */ 
    if (FLASH_ProgramWord(*FlashAddress, *(uint32_t*)(Data+i)) == FLASH_COMPLETE)
    {
     /* Check the written value */
      if (*(uint32_t*)*FlashAddress != *(uint32_t*)(Data+i))
      {
        /* Flash content doesn't match SRAM content */
        return(2);
      }
      /* Increment FLASH destination address */
      *FlashAddress += 4;
    }
    else
    {
      /* Error occurred while writing data in Flash memory */
      return (1);
    }
  }

  return (0);
}
////*****************************************************************************************************************
////函数:INT32U FLASH_If_Erase(INT32U StartSector)
////功能:	This function does an erase of all user flash area
////参数: StartSector: start of user flash area
////说明: 0: user flash area successfully erased
////      1: error occurred
////*****************************************************************************************************************
uint32_t FLASH_If_Erase(uint32_t StartSector)
{
  uint32_t i = 0;

  /* Get the sector where start the user flash area */

  for(i = StartSector; i <= FLASH_Sector_11; i += 8)
  {
    /* Device voltage range supposed to be [2.7V to 3.6V], the operation will
       be done by word */ 
    if (FLASH_EraseSector(i, VoltageRange_3) != FLASH_COMPLETE)
    {
      /* Error occurred while page erase */
      return (1);
    }
  }
  
  return (0);
}

//*****************************************************************************************************************
//函数:void FLASH_If_Init(void)
//功能:	Unlocks Flash for write access
//参数: None
//说明: None
//*****************************************************************************************************************
/**
  * @brief  Unlocks Flash for write access
  * @param  None
  * @retval None
  */
void FLASH_If_Init(void)
{ 
  FLASH_Unlock(); 

  /* Clear pending flags (if any) */  
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
                  FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);
}
////*****************************************************************************************************************
////函数:void Flash_Write(INT32U addr,void *pbuf,INT32U size)
////功能:	This function writes a data buffer in flash (data are 32-bit aligned).
////参数: addr: pointer on data buffer
////			size: length of data buffer (unit is 32-bit word)   
////说明: None
////*****************************************************************************************************************
//INT32U Flash_Write(INT32U addr,INT32U *pbuf,INT32U size){
//	
//#if OS_CRITICAL_METHOD == 3                                         /* Allocate storage for CPU status register             */
//    OS_CPU_SR  cpu_sr = 0;
//#endif  
//	 INT32U ret;
//	 INT32U flashdst=APPLICATION_CONFIG;
//	/* enter interrupt */
//		OS_ENTER_CRITICAL();		
//		FLASH_If_Init();
//		if (FLASH_EraseSector(APPLICATION_CONFIG_SEG, VoltageRange_3) != FLASH_COMPLETE){
//      /* Error occurred while page erase */
//			FLASH_Lock();
//			OS_EXIT_CRITICAL();  
//      FLASH_DEBUG("\tErase Failure!\n");
//			return (3);
//    }
//		ret=FLASH_If_Write(&flashdst,pbuf,size);	
//		FLASH_Lock();
//		OS_EXIT_CRITICAL();  
//		return ret;
//}
////*****************************************************************************************************************
////函数:void* Flash_Read(INT32U addr,INT8U *buf,INT32U size)
////功能:	This function writes a data buffer in flash (data are 32-bit aligned).
////参数: buf: pointer on data buffer
////			addr: address of read
////			size: length of data buffer (unit is 32-bit word)   
////说明: None
////*****************************************************************************************************************
//void Flash_Read(INT32U addr,INT8U *buf,INT32U size){
//		
//		INT32U i;
//	  INT32U *p=(INT32U*)buf;
//		for(i=0;i<(size/sizeof(INT32U));i++)
//			*(p+i) = *(__IO INT32U*)(addr+i*4);
//}
//*****************************************************************************************************************
//函数:void* Flash_Read(INT32U addr,INT8U *buf,INT32U size)
//功能:	This function writes a data buffer in flash (data are 32-bit aligned).
//参数: buf: pointer on data buffer
//			addr: address of read
//			size: length of data buffer (unit is 32-bit word)   
//说明: None
//*****************************************************************************************************************

INT8U IAP_Start(void){
	
      FLASH_If_Init();
	
			//FLASH_ITConfig(FLASH_IT_ERR|FLASH_IT_EOP, DISABLE);
	   return FLASH_If_Erase(FLASH_Sector_6);
}

//*****************************************************************************************************************
//函数:void* Flash_Read(INT32U addr,INT8U *buf,INT32U size)
//功能:	This function writes a data buffer in flash (data are 32-bit aligned).
//参数: buf: pointer on data buffer
//			addr: address of read
//			size: length of data buffer (unit is 32-bit word)   
//说明: None
//*****************************************************************************************************************
void IAP_Stop(void){
	FLASH_Lock();
}
//*****************************************************************************************************************
//函数:void* Flash_Read(INT32U addr,INT8U *buf,INT32U size)
//功能:	This function writes a data buffer in flash (data are 32-bit aligned).
//参数: buf: pointer on data buffer
//			addr: address of read
//			size: length of data buffer (unit is 32-bit word)   
//说明: None
//*****************************************************************************************************************
INT32U IAP_Flash_Write(INT32U addr,INT8U *pbuf,INT32U size){
	
		INT32U ret;
	  //FLASH_If_Init();
		ret=FLASH_If_Write(&addr,(INT32U*)pbuf,size);	
		return ret;
}
//*****************************************************************************************************************
//函数:void* Flash_Read(INT32U addr,INT8U *buf,INT32U size)
//功能:	This function writes a data buffer in flash (data are 32-bit aligned).
//参数: buf: pointer on data buffer
//			addr: address of read
//			size: length of data buffer (unit is 32-bit word)   
//说明: None
//*****************************************************************************************************************
void IAP_Flash_Read(INT32U addr,INT8U *pbuf,INT32U size){
	
#if OS_CRITICAL_METHOD == 3                                         /* Allocate storage for CPU status register             */
    OS_CPU_SR  cpu_sr = 0;
#endif
		INT32U i;
	  INT32U *p=(INT32U*)pbuf;
		for(i=0;i<(size/sizeof(INT32U));i++)
			*(p+i) = *(__IO INT32U*)(addr+i*4);

}
