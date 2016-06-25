/*
 * gui.c
 *
 *  Created on: 2016��5��14��
 *      Author: Administrator
 */
#include "fs.h"
#include "gui.h"
#include "button.h"

extern struct gui_handler  window_handler;
int show(struct gui_handler *root);

int gui_create(const char *device_availdable_list)
{
	extern struct gui_handler * window_create(struct gui_msg_t*p_msg,int (*callback)(enum event_type,void *data));

	inode_vmn *p_vmn_start = inode_sched_getfiles();

	struct gui_msg_t sert={
			0,0,20,20,NULL,FOCUS_OFF
	};
    /* create the default create */
	window_create(&sert,NULL);

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
    show(&window_handler);
	return 0;
}

int widget_create(enum widget_type_t widget_type,struct gui_msg_t *p_gui_msg,int (*callback)(enum event_type,void *data))
{
    switch(widget_type)
    {
    case button:
        button_create(p_gui_msg,callback);
      return 0;
    default:
    	break;
    }
	return 0;
}

struct gui_handler * handler_current(void)
{
	return &window_handler;
}



/*
 *    insert the handler to the list
 *    and return the root pointer
 * */
struct gui_handler * handler_insert(struct gui_handler *insert_one)
{
	struct gui_handler * window_now_hwnd,*handler_t;

	window_now_hwnd = handler_current();

	if(handler_current==NULL) /* can not find the window handler */
		return NULL;

	for(handler_t = window_now_hwnd;
		handler_t->link!=NULL;
		handler_t=handler_t->link)
	{
		/*nothing to do with it*/
	}
    /* insert it to the tail  */
	handler_t->link = insert_one;

  return window_now_hwnd;
}


int show(struct gui_handler *root)
{
	struct gui_handler *p_root;
	for(p_root=root;
			p_root!=NULL;
			p_root=p_root->link)
	{
		if(p_root->gui_ops->show!=NULL)
			p_root->gui_ops->show(&p_root->widget_msg);
	}
	return 0;
}










