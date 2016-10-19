/*
 * gui.c
 *
 *  Created on: 2016��5��14��
 *      Author: Administrator
 */
#include "fs.h"
#include "gui.h"
#include "button.h"
#include "window.h"
#include "gui_config.h"

extern window_hwnd  window_handler;

int show(struct gui_handler *root);

int gui_create(const char *device_availdable_list)
{
	gui_device *gui_device_t  = gui_dev_ops_g();

	inode_vmn *p_vmn_start = inode_sched_getfiles();

	gui_message gui_msg_tmp =
	{
		0,
		0,
		0,
		0,
		"main_window",
		"/sdcard/main.bmp",
		0,
		0,
		__GUI_WIDGET_MODE_0     | /* pic mode , with caption */
		__GUI_WIDGET_TYPE_OCT   | /* right angle mode */
		__GUI_WIDGET_FRAME_NONE | /* without frame */
		__GUI_WIDGET_THEME_0    | /* theme 0 */
		__GUI_WIDGET_HANDLE       /* no ues */
	};
	
	gui_msg_tmp.xsize = 120;//gui_device_t->gui_device_msg.xsize;
	gui_msg_tmp.ysize = 80;//gui_device_t->gui_device_msg.ysize;
	gui_msg_tmp.x_size_pic = gui_device_t->gui_device_msg.xsize; /* full of window */
	gui_msg_tmp.y_size_pic = gui_device_t->gui_device_msg.ysize; /* full of window */
	
    /* create the default create */
	window_create(&window_handler,&gui_msg_tmp,NULL);

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
    show(&window_handler.window);
	return 0;
}

int widget_create(enum widget_type_t widget_type,struct gui_msg_t *p_gui_msg,int (*callback)(enum event_type,void *data))
{
    switch(widget_type)
    {
		case button:
			button_create(&window_handler,p_gui_msg,callback);
		  return 0;
		default:
		  break;
    }
	return 0;
}

window_hwnd * handler_current(void)
{
	return &window_handler;
}


/*
 *    insert the handler to the list
 *    and return the root pointer
 * */
struct gui_handler * handler_insert(window_hwnd * hwnd,struct gui_handler *insert_one)
{

  struct gui_handler *handler_t;

  for( handler_t = &hwnd->window;
	   handler_t->link!=NULL;
	   handler_t=handler_t->link)
	   {
		/*nothing to do with it*/
	   }
			/* insert it to the tail  */
	handler_t->link = insert_one;

	insert_one->parent_window = hwnd;

	return &hwnd->window;
}


int show(struct gui_handler *root)
{
	struct gui_handler *p_root;
	for(p_root=root;
			p_root!=NULL;
			p_root=p_root->link)
	{
		if(p_root->gui_ops->show!=NULL)
			p_root->gui_ops->show(p_root);
	}
	return 0;
}

int refresh(void)
{
	struct gui_handler *p_root , *root;
	
	root = &handler_current()->window;
	for(p_root=root;
			p_root!=NULL;
			p_root=p_root->link)
	{
		if(p_root->gui_ops->show!=NULL)
			p_root->gui_ops->show(p_root);
	}
	return 0;
}









