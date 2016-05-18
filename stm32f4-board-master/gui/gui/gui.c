/*
 * gui.c
 *
 *  Created on: 2016��5��14��
 *      Author: Administrator
 */
#include "fs.h"
#include "gui.h"
#include "button.h"

int gui_create(const char *device_availdable_list)
{
	inode_vmn *p_vmn_start = inode_sched_getfiles();

    while(*device_availdable_list != DEVICE_END )
    {
       if(p_vmn_start->inode->nxgui!=NULL && *device_availdable_list == OK)/* nothing */
       {
    	   widget_create(p_vmn_start->inode->nxgui->widget_type,p_vmn_start->inode->nxgui->gui_msg,
    			   p_vmn_start->inode->nxgui->callback);
       }
       p_vmn_start++;
	   device_availdable_list++;
    }

	return 0;
}

int widget_create(enum widget_type_t widget_type,struct gui_msg_t *p_gui_msg,int (*callback)(enum event_type,void *data))
{
    switch(widget_type)
    {
    case button:
    	return button_create(p_gui_msg,callback);
    default:
    	break;
    }
	return 0;
}













