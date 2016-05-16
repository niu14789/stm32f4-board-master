/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2007        */
/*-----------------------------------------------------------------------*/
/* by grqd_xp                                                            */
/* This is a stub disk I/O module that acts as front end of the existing */
/* disk I/O modules and attach it to FatFs module with common interface. */
/*-----------------------------------------------------------------------*/
#include <string.h>
#include "ff.h"
#include "diskio.h"
#include "bsp_sdio_sd.h"

/*-----------------------------------------------------------------------*/
/* Correspondence between physical drive number and physical drive.      */
/* Note that Tiny-FatFs supports only single drive and always            */
/* accesses drive number 0.                                              */

#define SECTOR_SIZE 512U

SD_Error err1;

//u32 buff2[512/4];
/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */

DSTATUS disk_initialize (
	BYTE drv				/* Physical drive nmuber (0..) */
)
{
	return 0;
}



/*-----------------------------------------------------------------------*/
/* Return Disk Status                                                    */

DSTATUS disk_status (
	BYTE drv		/* Physical drive nmuber (0..) */
)
{	
	return 0;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */

DRESULT disk_read (
	BYTE drv,		/* Physical drive nmuber (0..) */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address (LBA) */
	BYTE count		/* Number of sectors to read (1..255) */
)
{
	
	

	if(count==1)
  {
         err1 = SD_ReadBlock( &buff[0], sector , SECTOR_SIZE );
		
				 SD_WaitReadOperation();
		
         while(SD_GetStatus() != SD_TRANSFER_OK);
		
	}
	else
  {
         err1 = SD_ReadMultiBlocks( &buff[0] , sector ,SECTOR_SIZE , count );
		
		      SD_WaitReadOperation();
		
          while(SD_GetStatus() != SD_TRANSFER_OK);
 
       
	}
  if( err1 == SD_OK)
     return RES_OK;
	else
		return RES_ERROR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */

#if _READONLY == 0
DRESULT disk_write (
	BYTE drv,			/* Physical drive nmuber (0..) */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address (LBA) */
	BYTE count			/* Number of sectors to write (1..255) */
)
{
  //memset(buff2, 0, sizeof(buff2));
	if(count==1)
        {
          //memcpy(buff2,buff,SECTOR_SIZE);
          err1 =  SD_WriteBlock((uint8_t *)(&buff[0]),sector  ,SECTOR_SIZE);
					
					SD_WaitWriteOperation();
					
          while(SD_GetStatus() != SD_TRANSFER_OK);
					
	      }
	else
        {
          //memcpy(buff2,buff,SECTOR_SIZE * count);
          err1 = SD_WriteMultiBlocks((uint8_t *)(&buff[0]),sector  ,SECTOR_SIZE,count);
					
				  SD_WaitWriteOperation();          

					while(SD_GetStatus() != SD_TRANSFER_OK);
					
	      }
        
  if( err1 == SD_OK)
     return RES_OK;
	else
		return RES_ERROR;
}
#endif /* _READONLY */



/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */

DRESULT disk_ioctl (
	BYTE drv,		/* Physical drive nmuber (0..) */
	BYTE ctrl,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{

	return RES_OK;
}

DWORD get_fattime(void){
	return 0;
}























