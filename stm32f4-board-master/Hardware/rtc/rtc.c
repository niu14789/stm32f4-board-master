

#include "stm32f4xx.h"
#include "fs.h"

struct Time_s{
u8 year;
u8 month;
u8 day;
u8 week;
u8 hours;
u8 min;
u8 sec;
};
struct Time_s time;
extern  u16 lflow;


void RTC_Config(void)
{
// 	RTC_InitTypeDef RTC_InitStructure;
//   RTC_TimeTypeDef  RTC_TimeStruct;
//   /* Enable the PWR clock */
//   RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

//   /* Allow access to RTC */
//   PWR_BackupAccessCmd(ENABLE);

//   /* Reset RTC Domain */
//   RCC_BackupResetCmd(ENABLE);
//   RCC_BackupResetCmd(DISABLE);

//   /* Enable the LSE OSC */
//   RCC_LSEConfig(RCC_LSE_ON);

//   /* Wait till LSE is ready */  
// //   while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
// //   {
// //   }

// //   /* Select the RTC Clock Source */
// //   RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
// //   RCC_RTCCLKCmd(ENABLE);
// //   RTC_WaitForSynchro();
// // 	
// //   /* Configure the RTC data register and RTC prescaler */
// //   RTC_InitStructure.RTC_AsynchPrediv = 0x7F;
// //   RTC_InitStructure.RTC_SynchPrediv  = 0xFF;
// //   RTC_InitStructure.RTC_HourFormat   = RTC_HourFormat_24;
// //   RTC_Init(&RTC_InitStructure);
// //   
// //   /* Set the time to 00h 00mn 00s AM */
// //   RTC_TimeStruct.RTC_H12     = RTC_H12_AM;
//   RTC_TimeStruct.RTC_Hours   =1;
//   RTC_TimeStruct.RTC_Minutes = 1;
//   RTC_TimeStruct.RTC_Seconds = 1;  
// //   RTC_SetTime(RTC_Format_BCD, &RTC_TimeStruct);
}

void rtc_settime( void )
{
	 RTC_InitTypeDef RTC_InitStructure;
   RTC_TimeTypeDef  RTC_TimeStruct;
   RTC_DateTypeDef  RTC_DataStruct;
  
  /* Set the time to 00h 00mn 00s AM */
  //RTC_TimeStruct.RTC_H12     = RTC_H12_PM;
  RTC_TimeStruct.RTC_Hours   = 0x21;
  RTC_TimeStruct.RTC_Minutes = 0x16;
  RTC_TimeStruct.RTC_Seconds = 0x10;  
	
	RTC_DataStruct.RTC_Year   =  0x15;
	RTC_DataStruct.RTC_Month  =  0x03;
	RTC_DataStruct.RTC_WeekDay = 0x0;
	RTC_DataStruct.RTC_Date   =  0x25;
	
	/* Configure the RTC data register and RTC prescaler */
  RTC_InitStructure.RTC_AsynchPrediv = 0x7F;
  RTC_InitStructure.RTC_SynchPrediv  = 0xFF;
  RTC_InitStructure.RTC_HourFormat   = RTC_HourFormat_24;
  RTC_Init(&RTC_InitStructure);
	
  RTC_SetTime(RTC_Format_BCD, &RTC_TimeStruct);
  RTC_SetDate(RTC_Format_BCD, &RTC_DataStruct);
}
void rtc_read( void )
{
  RTC_TimeTypeDef  RTC_TimeStruct;
  RTC_DateTypeDef  RTC_DateStruct;

  RTC_GetTime(RTC_Format_BCD,&RTC_TimeStruct);
  RTC_GetDate(RTC_Format_BCD,&RTC_DateStruct);
	
	time.year  = RTC_DateStruct.RTC_Year;
	time.month = RTC_DateStruct.RTC_Month;
	time.day   = RTC_DateStruct.RTC_Date;	
	
  time.hours = RTC_TimeStruct.RTC_Hours;
	time.min   = RTC_TimeStruct.RTC_Minutes;
  time.sec   = RTC_TimeStruct.RTC_Seconds;	
}
void stm32_backupsram_init(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_BKPSRAM, ENABLE);
	PWR_BackupAccessCmd(ENABLE);
	PWR_BackupRegulatorCmd(ENABLE);
}




