/*
 * window.c
 *
 *  Created on: 2016年5月26日
 *      Author: YJ-User17
 */

#include "fs.h"
#include "gui.h"
#include "string.h"
#include "lcd_hw.h"

/* as use the handler */
struct gui_handler  window_handler;
struct gui_operations window_ops;

int window_create_asparent(uint16_t x_pos,uint16_t y_pos,uint16_t x_size,uint16_t y_size,char *caption,char mode)
{
	extern void LCD_Fill_Rect(uint16_t _usX, uint16_t _usY, uint16_t _usHeight, uint16_t _usWidth, uint16_t _usColor);
	/* window without caption */
    if(caption==NULL)
    {
    	LCD_Fill_Rect(x_pos,y_pos,x_size,y_size,RGB(196,218,234));
    	return OK;
    }
    else
    {
       return ERR;
    }
}


int window_show(struct gui_msg_t*p_msg)
{
	return window_create_asparent(p_msg->x,p_msg->y,p_msg->xsize,p_msg->ysize,p_msg->caption,p_msg->mode);
}


struct gui_handler * window_create(struct gui_msg_t*p_msg,int (*callback)(enum event_type,void *data))
{
	/* widget message */
	memcpy(&window_handler.widget_msg,p_msg,sizeof(window_handler.widget_msg));
	window_handler.gui_ops = &window_ops;
	window_handler.callback = callback;
	window_handler.id = 1;
	window_handler.link = NULL;
	window_handler.status = p_msg->mode;

	/*
	 *   reserve function
	 *
	 *   window_insert(&window_handler);
	 *
	 * */
    return &window_handler;
}

struct gui_operations window_ops = {
		window_create,
		window_show,
};























