
#include "ff.h"
#include "diskio.h"
#include "stm32_sdio.h"

#include "fs.h"
#include "sd_interface.h"
#include "sd_gui.h"

/* Private functions ---------------------------------------------------------*/
     FATFS fs;                  // Work area (file system object) for logical drive
     FIL fsrc, fdst,mp3fs,txtfs;      // file objects
     FRESULT res,res1,res2;     // FatFs function common result code
     UINT br,br1,br2, bw; 
	   FILINFO finfo;
     DIR dirs;                  // File R/W count
/* Private function prototypes -----------------------------------------------*/

struct file_operations sd_ops =
{
    sd_device_open,
	sd_device_write
};

struct inode inode_sd = 
{
	NULL,
	NULL,
	0,
	FS_INODE_USABLE,
	&sd_ops,
	&sd_gui_object,
	NULL,
	SD_Init_User,
	"sd.d"
};

FS_REGISTER(FS_FILE("sd.d"),inode_sd);

int sd_device_open(struct file * filp)
{
	f_mount(0, &fs);  //����SD��
	
	if( !f_open(&fsrc, "0:Om.txt",FA_CREATE_ALWAYS | FA_WRITE))
	  return 0;
	else
	  return 1;
}

int32_t sd_device_write(FAR struct file *filp, FAR const char *buffer, uint32_t buflen)
{
	int ret;
	if( !f_write(&fsrc,buffer,buflen,&bw))
		ret = 0;
	else
		ret = 1;
	
	f_sync(&fsrc); 
	return ret;
}

















