

#include "stm32f4xx.h"
#include "IAP.h"
#include "ff.h"
#include "string.h"
#include "stdio.h"

struct _stm32f4_id stm32_id;

char stm32_id_code[24];
extern u8 SD_Init_User(void);

void getdevid( void )
{
	stm32_id.id_code1=*((volatile uint32_t *)0x1fff7a10);
  stm32_id.id_code2=*((volatile uint32_t *)0x1fff7a14);
	stm32_id.id_code3=*((volatile uint32_t *)0x1fff7a18);
}
/* write device id to sd card */
void stm32_write_devid(void)
{
 FIL fsac;
 FRESULT res;	
 UINT br;

 memset(stm32_id_code,0,24);
	
 getdevid();
	
 sprintf(stm32_id_code,"%x%x%x",stm32_id.id_code1,stm32_id.id_code2,stm32_id.id_code3);
	
 res = f_open(&fsac,"0:devid.txt",FA_CREATE_ALWAYS | FA_WRITE);
 
 if(res != FR_OK)
 {
   printf("device id file open  error---->%d",res);
 }	 
 
 res = f_write(&fsac,stm32_id_code,24,&br);
 
 if(res != FR_OK)
 {
   printf("device id write to sd card error---->%d",res);
 }	 
 
 f_close(&fsac);
 
}

