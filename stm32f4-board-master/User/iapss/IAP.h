


#ifndef __IAP_H__
#define __IAP_H__

struct _stm32f4_id
{
	u32 id_code1;
	u32 id_code2;
	u32 id_code3;
};

typedef enum iap_err
{
  IAP_OK = 0,
  IAP_FILE_NOEXIST,
  IAP_FILE_INFO,
  IAP_NOUNSPECIFIED,
  IAP_FLASHERASE,
  IAP_READ_ERROR,
  IAP_WRITE_SECTION, 	
	IAP_SD_NOEXIST
}IAP_Error;


extern char stm32_id_code[24];

extern struct _stm32f4_id stm32_id;
void stm32_write_devid(void);

void getdevid( void );


#endif


