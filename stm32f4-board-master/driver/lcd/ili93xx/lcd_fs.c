

#include "fs.h"
#include "lcd.h"
#include "lcd_fs.h"
#include "display_device.h"

static unsigned char is_lcd2_ok = 0xff;

static gui_device gui_dev; 

gui_dev_ops gui_dev_ops_d = 
{
	LCD_Fast_DrawPoint,
	LCD_ReadPoint,
  LCD_DrawLine_ili,
	LCD_Fill
};


struct file_operations lcd_ili_ops =
{
  lcd2_device_open,
  NULL,
	lcd2_read
};

struct inode inode_ili_lcd2 = 
{
	NULL,
	NULL,
	0,
	FS_INODE_USABLE,
	&lcd_ili_ops,
	NULL,
	NULL,
	lcd_ili_init,
	"lcd_ili2"
};

FS_REGISTER(FS_DEVICE("lcd2.d"),inode_ili_lcd2);

int lcd_ili_init(void)
{
	int id;
	
	id = LCD_Init();
	
	is_lcd2_ok = 0;
	
	if( id == 0 )
	{
		printf_d("[lcd2]:lcd init error : can not find the lcd device");
		return (-1);
	}
	
	if(id == 0x9325)
	{
		gui_dev.gui_device_msg.lcd_driver_id = 0x9325;
		gui_dev.gui_device_msg.xsize = 240;
		gui_dev.gui_device_msg.ysize = 320;
		gui_dev.gui_dev_ops_g = &gui_dev_ops_d;
		is_lcd2_ok = 1;
// 		printf_d("[lcd2]:lcd driver 9325:240*320");
		return 0;
	}
	return (-1);
}

int lcd2_device_open(struct file * filp)
{
	int ret = ERR;
	if( is_lcd2_ok == 0xff )
	{
		/*lcd2 has not init*/
		ret = lcd_ili_init();
		return ret;
	}
	else if(is_lcd2_ok == 1)
	{
		return OK;
	}else
	{
		return ERR;
	}
}

int32_t lcd2_read(FAR struct file *filp, FAR char *buffer, uint32_t buflen)
{
	unsigned int p ,*d;
	if(buflen == 4)
	{
		p = (unsigned int)&gui_dev;
    d = (unsigned int *)buffer;
		*d = p;
		return 4;
	}else
	{
		return (-1);//not support this format
	}
}













