/*
 * led_gui.c
 *
 *  Created on: 2016年5月14日
 *      Author: Administrator
 */

/*
 * led_gui.c
 *
 *  Created on: 2016年5月14日
 *      Author: Administrator
 */
#include "fs.h"
#include "gui.h"
#include "button.h"

struct gui_handler* led_sched_getfiles(void);

struct gui_msg_t led_gui_msg = {
	100,     /* x position */
	200,     /* y position */
	50,     /* x size     */
	30,     /* y size     */
	"led",  /* caption    */
	0       /* init mode  */
};

int led_gui_create(struct gui_msg_t*p_msg)
{
	return button_create(p_msg->x,p_msg->y,p_msg->xsize,p_msg->ysize,p_msg->caption,p_msg->mode);
}

int led_gui_onfocus(struct gui_msg_t*p_msg)
{
	return button_create(p_msg->x,p_msg->y,p_msg->xsize,p_msg->ysize,p_msg->caption,1);
}

int led_gui_losefocus(struct gui_msg_t*p_msg)
{
	return button_create(p_msg->x,p_msg->y,p_msg->xsize,p_msg->ysize,p_msg->caption,0);
}

/* led_gui_draw_ops */
struct gui_operations led_gui_draw_ops={
	led_gui_create,
	NULL,
	led_gui_onfocus,
	led_gui_losefocus,
	NULL
};
struct nxgui_object led_gui_object = {
	NULL,
	button,
	rect,
	&led_gui_msg,
	NULL,
	led_sched_getfiles
};


static struct gui_handler led_gui_handlder_t = {
	NULL,
	1,
	&led_gui_draw_ops,
	&led_gui_msg
};

struct gui_handler* led_sched_getfiles(void)
{
	return &led_gui_handlder_t;
}














