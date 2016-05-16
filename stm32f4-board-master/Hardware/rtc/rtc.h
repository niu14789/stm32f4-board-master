

#ifndef __RTC_H__
#define __RTC_H__


struct Time_s{
u8 year;
u8 month;
u8 day;
u8 week;
u8 hours;
u8 min;
u8 sec;
};

void stm32_backupsram_init(void);
void rtc_read( void );
void rtc_settime( void );
void RTC_Config(void);

#endif
