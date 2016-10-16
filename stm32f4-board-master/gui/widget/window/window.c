/*
 * window.c
 *
 *  Created on: 2016骞�5鏈�26鏃�
 *      Author: YJ-User17
 */

#include "fs.h"
#include "gui.h"
#include "string.h"
#include "lcd_hw.h"
#include "gui_config.h"
#include "window.h"



extern int gui_draw_bmp( const struct gui_msg_t * p_msg , unsigned int __MODE__);

/* should be macro */
/* as use the handler */
window_hwnd  window_handler;

struct gui_operations window_ops;

int window_create_asparent(uint16_t x_pos,uint16_t y_pos,uint16_t x_size,uint16_t y_size,char *caption,char mode)
{
	gui_device *gui_device_t;

	gui_device_t = gui_dev_ops_g();
		/* window without caption */
    if(caption==NULL)
    {
    	gui_device_t->gui_dev_ops_g.fill_dect(x_pos,y_pos,x_size,y_size,RGB(196,218,234));
    	return OK;
    }
    else
    {
       return ERR;
    }
}


int window_show(struct gui_msg_t*p_msg)
{
	gui_draw_bmp(p_msg,0);
	return 0;//window_create_asparent(p_msg->x,p_msg->y,p_msg->xsize,p_msg->ysize,p_msg->caption,p_msg->mode);
}


window_hwnd * window_create(window_hwnd * hwnd,struct gui_msg_t*p_msg,int (*callback)(enum event_type,void *data))
{
	/* widget message */
	memcpy(&window_handler.window.widget_msg,p_msg,sizeof(window_handler.window.widget_msg));
	window_handler.window.gui_ops = &window_ops;
	window_handler.window.callback = callback;
	window_handler.window.id = 1;
	window_handler.window.link = NULL;
	window_handler.window.status = p_msg->mode;

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























