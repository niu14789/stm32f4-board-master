
#include "ff.h"
#include "diskio.h"
#include "stm32_sdio.h"
#include "fs.h"
#include "sd_interface.h"
#include "sd_gui.h"
#include "string.h"
#include "stdio.h"

#define MAX_OPEN_MULIPLE    (5)

/* Private functions ---------------------------------------------------------*/
	FATFS fs;                  // Work area (file system object) for logical drive
	FIL fsrc[MAX_OPEN_MULIPLE];               // file objects , open multiple file max support 5
	FRESULT res;     // FatFs function common result code
	UINT    bw;
	FILINFO finfo;
	DIR dirs;                  // File R/W count
/* Private function prototypes -----------------------------------------------*/
 
/* node status  */
static 	struct file sd_file[MAX_OPEN_MULIPLE];
/* end */

struct file_operations sd_ops =
{
	sd_device_open,
	sd_device_write,
	sd_device_read,
	sd_device_lseek,/* lseek  */
	sd_device_close,
	NULL,/* ioctl   */
	/* high-end function */
	NULL,/* opendir */
	NULL,/* readdir */
	sd_device_mkdir,/* mkdir   */
	NULL,/* mkfs    */
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
	sd_init,
	"sd.d"
};

FS_REGISTER(FS_FILE("sd.d"),inode_sd);

int sd_init(void)
{
	FRESULT ret;
	if (SD_Init_User() == 0 )
	{
		printf_d("good ! find a sd card\n");
		/* init okay */
		ret = f_mount(0, &fs);  //����SD��
		/* is mount ok ? */
		if(ret == FR_OK)
		{
		   printf_d("good ! mount sdcard ok\n");
           return OK;  /* sdcard node init ok    */
		}else
		{
		   printf_d("mount sdcard fail\n");
		   return ERR; /* sdcard node init fail  */
		}
	}else
	{
		printf_d("not good ! can not find a sdcard\n");
		return ERR;
	}
}

struct file * sd_device_open(struct file * filp)
{
	char f_name[50] = {0};  //most length support ? why we ues 'static',I dont know
    int multi;

    /* get the free block */
    multi = sd_device_multiple();
    /*
     * if we find the free block,then we do next
     *
     * */
    if(multi == ERR )
    {
    	printf_d("[sd]can not find the free block\n");
    	return NULL;
    }
    /*
     * create the file name
     *
     * example :
     *
     * if filp->f_path = "/sdcard/om.txt"
     *
     *  we will get:
     *
     *  f_name = "0:om.txt"
     *
     * */
    sd_path_transfer(filp->f_path,f_name,sizeof(f_name));

	if( !f_open(&fsrc[multi],f_name,(unsigned char)filp->f_oflags))
	{
		sd_file[multi].f_inode = &inode_sd;
		sd_file[multi].f_multi  = multi;
        return &sd_file[multi];
	}
	else
	{
		return NULL;
	}
}

int32_t sd_device_write(FAR struct file *filp, FAR const char *buffer, uint32_t buflen)
{
	int ret;

	if( !f_write(&fsrc[filp->f_multi],buffer,buflen,&bw))
		ret = 0;
	else
		ret = 1;
	
	f_sync(&fsrc[filp->f_multi]);
	return ret;
}

uint32_t sd_device_read(FAR struct file *filp, FAR char *buffer, uint32_t buflen)
{
	int ret;

	if( !f_read(&fsrc[filp->f_multi],buffer,buflen,&bw))
	{
		return bw;
	}

	return ret;
}

int  sd_device_close(FAR struct file *filp)
{
	/* start */
	if( !f_close(&fsrc[filp->f_multi]) )
	{
		sd_file[filp->f_multi].f_inode = NULL;
		return OK;
	}

	return ERR;
}

int32_t sd_device_lseek(FAR struct file *filp, unsigned int offset, unsigned int whence)
{
	/* start */
	if( !f_lseek(&fsrc[filp->f_multi] , offset) )
	{
		return OK;
	}

	return ERR;
}

int sd_device_mkdir( const char * dir )
{
	 FRESULT ret;
	 static char f_dir[50] = {0};  //most length support ? why we ues 'static',I dont know
     /*
	 * create the f_dir
	 *
	 * example :
	 *
	 * if filp->f_path = "/sdcard/om.txt"
	 *
	 *  we will get:
	 *
	 *  f_name = "0:om.txt"
	 *
	 */
	 sd_path_transfer(dir,f_dir,sizeof(f_dir));

	 ret = f_mkdir(f_dir);

	 if(ret == FR_OK)
	 {
		 return OK;
	 }
	 else
	 {
		 return ERR;
	 }
}


int sd_device_multiple(void)
{
  int i;
  for( i = 0 ; i < MAX_OPEN_MULIPLE ; i++ )
  {
	  if( sd_file[i].f_inode == NULL )
	  {
		  return i;
	  }
  }
  return ERR;
}

int sd_path_transfer(FAR const char * filp , char * f_path , int len)
{
	if( strlen(filp) >= len )
	   return ERR; //not support this format

	/* path transfer */
	sprintf(f_path,"0:%s",filp + strlen(FS_FILE()));

	return OK;
}










