/*
 * server.c
 *
 *  Created on: 2016��5��15��
 *      Author: Administrator
 */

#include "fs.h"
#include "gui.h"
#include "server.h"
#include "msg.h"

#define QUEUE_PATH  "/dev/queue.d"

int gui_server(void)
{
  /* gui event check
   * it can be exist anywhere
   * */
  gui_event_check();
  /*
   *   gui event idle
   *   it must in this place
   * */
  gui_event_idle();
  return 0;
}

int gui_event_idle(void)
{
	int ret;
	char buffer[20];
	gui_msg *p_gui_msg;

	ret = gui_read_msg(buffer,sizeof(gui_msg));

	if( ret != ERR )
	{
		/* got the a event */
		p_gui_msg = (gui_msg *)buffer;
        /* deal with uis */
		p_gui_msg->handler->gui_ops->event_process(p_gui_msg->handler,p_gui_msg->event_type,p_gui_msg->data);

		/* deal with the callback function */
		if(p_gui_msg->handler->callback!=NULL)
			p_gui_msg->handler->callback(p_gui_msg->event_type,p_gui_msg->data);
	}
	return 0;
}

int gui_event_check(void)
{
	int ret;
	struct gui_handler *p_gui;
	window_hwnd * p_hwnd_n;
	gui_msg_l0 gui_msgl0;
    unsigned short x_pos,y_pos;

	ret = gui_read_msgl0((char *)&gui_msgl0,sizeof(gui_msgl0));

	if( ret != OK )
      return ERR;

	if((p_hwnd_n = gui_find_window(gui_msgl0.x_pos,gui_msgl0.y_pos)) != NULL )
	{
		/* thansfer x and y to window */
		x_pos =  gui_msgl0.x_pos -  p_hwnd_n->window.widget_msg.x;
		y_pos =  gui_msgl0.y_pos -  p_hwnd_n->window.widget_msg.y;
        /* find the widget */
		for(p_gui = p_hwnd_n->window.link ; p_gui != NULL ; p_gui = p_gui->link)
		{
             /* we find a widget ? */
			 if(gui_with_in(p_gui,x_pos,y_pos) == OK)
			  {
					/*revert all focus widget in same parent window*/
					gui_revert_widget(p_hwnd_n->window.link,p_gui);
					/*send the data to the msg queue */
					gui_send_msg(p_gui,gui_msgl0.event_type,gui_msgl0.pri_data);

					p_gui->status = FOCUS_ON;

					return OK;
			  }
		}
        /* not good ! we find nothing , hahahaha */
		return ERR;
		/*------------*/
	}else
	{
	  /* maybe select other window */
       return ERR;
	}
}

static window_hwnd * gui_find_window(unsigned short x,unsigned short y)
{
   /* define a hwnd */
   window_hwnd * p_gui;
   window_hwnd * current_hwnd = handler_current();
   /* find from head */
   for(p_gui = current_hwnd;p_gui != NULL ; p_gui = p_gui->same_next)
   {
	   if( gui_with_in( &p_gui->window , x , y ) == OK)
	   {
		   if( current_hwnd == p_gui)
		      return p_gui;
		   else
		   {
			   set_handler_current(current_hwnd,p_gui);
			   return p_gui;
		   }
	   }
   }
   /* find from trail */
   for(p_gui = current_hwnd;p_gui != NULL ; p_gui = p_gui->same_pre)
   {
	   if( gui_with_in( &p_gui->window , x , y ) == OK)
	   {
		   if( current_hwnd == p_gui)
		      return p_gui;
		   else
		   {
			   set_handler_current(current_hwnd,p_gui);
			   return p_gui;
		   }
	   }
   }

   return NULL;
}

static int gui_with_in(struct gui_handler *gui_hander_root,unsigned short x,unsigned short y)
{
	if((x >= gui_hander_root->widget_msg.x) &&
	   (x <= gui_hander_root->widget_msg.x + gui_hander_root->widget_msg.xsize) &&
	   (y >= gui_hander_root->widget_msg.y) &&
	   (y <= gui_hander_root->widget_msg.y + gui_hander_root->widget_msg.ysize))
	{
		return OK;
	}else
	{
		return ERR;
	}
}


/* revert all focused widget */
static int gui_revert_widget(struct gui_handler * p_gui_root,struct gui_handler * p_gui_same)
{
	/* I want to say nothing */
	struct gui_handler * p_gui = p_gui_root;

	for(;p_gui!=NULL;p_gui=p_gui->link)
	{
	   if(p_gui->status == FOCUS_ON)
	   {
		   if(p_gui == p_gui_same)
			   return OK;

		   /* send the data to the msg queue */
		   gui_send_msg(p_gui,losefocus,NULL);

		   /* release the source */
		   p_gui->status = FOCUS_OFF;
		   return OK;
	   }
	}
	return ERR;
}











