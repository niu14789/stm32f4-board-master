/*
 * sd_gui.c
 *
 *  Created on: 2016年5月14日
 *      Author: Administrator
 */




/*
 * sd_gui.c
 *
 *  Created on: 2016年5月14日
 *      Author: Administrator
 */

/*
 * sd_gui.c
 *
 *  Created on: 2016年5月14日
 *      Author: Administrator
 */
#include "fs.h"
#include "gui.h"
#include "button.h"

struct gui_handler* sd_sched_getfiles(void);

struct gui_msg_t sd_gui_msg = {
	100,     /* x position */
	100,     /* y position */
	50,     /* x size     */
	30,     /* y size     */
	"sd",  /* caption    */
	1       /* init mode  */
};

int sd_gui_create(struct gui_msg_t*p_msg)
{
	return button_create(p_msg->x,p_msg->y,p_msg->xsize,p_msg->ysize,p_msg->caption,p_msg->mode);
}

/* sd_gui_draw_ops */
struct gui_operations sd_gui_draw_ops={
		sd_gui_create
};
struct nxgui_object sd_gui_object={
		NULL,
		button,
		rect,
		&sd_gui_msg,
		NULL,
	  sd_sched_getfiles
};


static struct gui_handler sd_gui_handlder_t = {
	NULL,
	1,
	&sd_gui_draw_ops,
	&sd_gui_msg
};

struct gui_handler* sd_sched_getfiles(void)
{
	return &sd_gui_handlder_t;
}














