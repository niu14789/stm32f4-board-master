/*
 * lcd_interface.c
 *
 *  Created on: 2016Äê5ÔÂ8ÈÕ
 *      Author: Administrator
 */
#include "fs.h"
#include "lcd_hw.h"
#include "lcd_interface.h"
#include "lcd_gui.h"

struct file_operations lcd_ops =
{
  lcd_device_open,
  lcd_write
};

struct inode inode_lcd = 
{
	NULL,
	NULL,
	0,
	FS_INODE_USABLE,
	&lcd_ops,
	&lcd_gui_object,
	NULL,
	LCD_InitHard,
	"led"
};

FS_REGISTER("/etc/lcd.d",inode_lcd);


int lcd_device_open(struct file * filp)
{
	/* open always ok */
	return 0;
}

int32_t lcd_write(FAR struct file *filp, FAR const char *buffer, uint32_t buflen) 
{
	static unsigned short y_pos = 0 , x_pos = 0;
	FONT_T _FONT=
	{
		0,
		0x0,
		RGB(240,240,240),
		0
	};
  if(!y_pos && !x_pos) LCD_ClrScr(RGB(255,255,255));
	
	LCD_DispStr(x_pos,y_pos,(char *)buffer,&_FONT);
	y_pos+=16;
	
	if(y_pos>=270)
	{
		x_pos +=200;
		y_pos = 0;
	}
	/* open always ok */
	return 0;
}



















