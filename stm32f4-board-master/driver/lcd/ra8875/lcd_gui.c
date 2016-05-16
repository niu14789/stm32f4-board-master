/*
 * lcd_gui.c
 *
 *  Created on: 2016Äê5ÔÂ14ÈÕ
 *      Author: Administrator
 */
#include "fs.h"
#include "gui.h"
#include "button.h"

struct gui_handler* lcd_sched_getfiles(void);
int lcd_gui_callback(enum event_type event,void *data);

struct gui_msg_t lcd_gui_msg = {
	150,    /* x position */
	20,     /* y position */
	50,     /* x size     */
	30,     /* y size     */
	"lcd",  /* caption    */
	0       /* init mode  */
};

/* widget create */
int lcd_gui_create(struct gui_msg_t*p_msg)
{
	return button_create(p_msg->x,p_msg->y,p_msg->xsize,p_msg->ysize,p_msg->caption,p_msg->mode); 
}
/* widget on focus */
int lcd_gui_onfocus(struct gui_msg_t*p_msg)
{
	return button_create(p_msg->x,p_msg->y,p_msg->xsize,p_msg->ysize,p_msg->caption,1); 
}
/* widget lose focus */
int lcd_gui_losefocus(struct gui_msg_t*p_msg)
{
	return button_create(p_msg->x,p_msg->y,p_msg->xsize,p_msg->ysize,p_msg->caption,0);
}
/* lcd_gui_draw_ops */
struct gui_operations lcd_gui_draw_ops={
		lcd_gui_create,
		NULL,
		lcd_gui_onfocus,
		lcd_gui_losefocus,
};
struct nxgui_object lcd_gui_object={
		NULL,
		button,
		rect,
		&lcd_gui_msg,
		NULL,
	    lcd_sched_getfiles
};

static struct gui_handler lcd_gui_handlder_t = {
	NULL,
	1,
	&lcd_gui_draw_ops,
	&lcd_gui_msg,
  lcd_gui_callback
};

struct gui_handler* lcd_sched_getfiles(void)
{
	return &lcd_gui_handlder_t;
}


int lcd_gui_callback(enum event_type event,void *data)
{
	extern int lcd_fd;
	switch(event)
	{
		case onfocus:
				 write(lcd_fd,"onfocus",1);
			break;
		case losefocus:
			write(lcd_fd,"losefocus",1);
			break;
		default:break;
	}
	return 0;
}









