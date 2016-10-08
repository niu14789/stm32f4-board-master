/*
 * lcd_gui.c
 *
 *  Created on: 2016/5/14
 *      Author: Administrator
 */
#include "fs.h"
#include "gui.h"
#include "button.h"


int lcd_gui_callback(enum event_type event,void *data);

struct gui_msg_t lcd_gui_msg = { /* as a button */
	20,        /* x position */
	20,        /* y position */
	20,         /* x size     */
	30,         /* y size     */
	"lcd",      /* caption    */
	FOCUS_OFF   /* init mode  */
};

struct nxgui_object lcd_gui_object = {
	NULL,
	button,
	&lcd_gui_msg,
	lcd_gui_callback,
};

int lcd_gui_callback(enum event_type event,void *data)
{
// 	extern int lcd_fd;
// 	switch(event)
// 	{
// 		case onfocus:
// 		    write(lcd_fd,"lcd_onfocus",1);
// 			break;
// 		case losefocus:
// 			write(lcd_fd,"lcd_losefocus",1);
// 			break;
// 		default:break;
// 	}
	return 0;
}




























































