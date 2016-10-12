

#include "fs.h"
#include "lcd.h"
#include "lcd_fs.h"
#include "gui_config.h"


struct inode inode_ili_lcd2 = 
{
	NULL,
	NULL,
	0,
	FS_INODE_USABLE,
	NULL,
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
	
	if( id == 0 )
	{
		printf_d("[lcd2]:lcd init error : can not find the lcd device");
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
		return 0;
	}
	return (-1);
}














