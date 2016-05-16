/*
 * gui.c
 *
 *  Created on: 2016Äê5ÔÂ14ÈÕ
 *      Author: Administrator
 */
#include "fs.h"
#include "gui.h"

static struct gui_handler* gui_hander_root = NULL;

struct gui_handler** gui_sched_root(void)
{
	return &gui_hander_root;
}

int gui_create(void)
{
	struct gui_handler * p_gui;
	
	for(p_gui=gui_hander_root;
	    p_gui!=NULL;p_gui=p_gui->link)
	{
		p_gui->gui_ops->create(p_gui->widget_msg);
	}
	return 0;
}

