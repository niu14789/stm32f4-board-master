
#include "fs.h"
#include "lcd.h"
#include "lcd_fs.h"
#include "gui_config.h"

static struct file lcd_file;

struct file_operations lcd2_ops =
{
  lcd2_device_open,
};
struct inode inode_ili_lcd2 = 
{
	NULL,
	NULL,
	0,
	FS_INODE_USABLE,
	&lcd2_ops,
	NULL,
	NULL,
	lcd_ili_init,
	"lcd_ili2"
};

FS_REGISTER(FS_DEVICE("lcd2.d"),inode_ili_lcd2);

int lcd_ili_init(void)
{
	int id;
	
	if(inode_ili_lcd2.i_flags & __FS_IS_INODE_INIT)
	{
		if(inode_ili_lcd2.i_flags & __FS_IS_INODE_OK)
		{
			return OK;//has been inited
		}else
		{
			return ERR;//but fail
		}
	}

	id = LCD_Init();
	
	if( id == 0 )
	{
		printf_d("[lcd2]:lcd init error : can not find the lcd device");
		inode_ili_lcd2.i_flags =  __FS_IS_INODE_FAIL | __FS_IS_INODE_INIT;
		return (-1);
	}
	
	if(id == 0x9325)
	{
		/* register the lcd gui dev interface to gui system */
		gui_dev_register(id,                /* lcd driver id */
				         320,               /* x size witgh  */
						 240,               /* y size height */
						 LCD_Fast_DrawPoint,/* draw a point  */
						 LCD_ReadPoint,     /* read a point  */
						 LCD_DrawLine_ili,  /* draw line     */
						 LCD_Fill);         /* fill a rect   */
		inode_ili_lcd2.i_flags =  __FS_IS_INODE_OK | __FS_IS_INODE_INIT;
		return 0;
	}
	return (-1);
}


struct file * lcd2_device_open(struct file * filp)
{
	lcd_file.f_inode = &inode_ili_lcd2;
	if(OK == lcd_ili_init())
	{
		return &lcd_file;
	}else
	{
		return NULL;
	}
	/* open always ok */
}











