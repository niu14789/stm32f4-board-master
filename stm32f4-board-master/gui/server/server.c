/*
 * server.c
 *
 *  Created on: 2016��5��15��
 *      Author: Administrator
 */

#include "fs.h"
#include "gui.h"
#include "server.h"

#define QUEUE_PATH  "/dev/queue.d"

static struct file * fd_queue = 0;
static struct file * fd_queuel0 = 0;


int gui_server(void)
{
  static char flag = 0;
  if(!flag) /* is first time enter */
  {
	  fd_queue = open("/dev/queue.d",__FS_OPEN_EXISTING | __FS_WRITE);
	  if(fd_queue != NULL)
	  {
		  printf_d("[gui_server] the queue open ok!\n");
		  flag = 1; /* ignore first time */
	  }else
	  {
		  printf_d("[gui_server] the queue open fail,server setup fail!\n");
		  return ERR;
	  }
  }
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

	ret = read(fd_queue,buffer,sizeof(gui_msg));

	if(ret!=ERR)
	{
		/* got the a event */
		p_gui_msg = (gui_msg *)buffer;

		p_gui_msg->handler->gui_ops->event_process(p_gui_msg->handler,p_gui_msg->event_type,p_gui_msg->data);

		/* idle the callback function */
		if(p_gui_msg->handler->callback!=NULL)
			p_gui_msg->handler->callback(p_gui_msg->event_type,p_gui_msg->data);
	}
	return 0;
}

int gui_event_check(void)
{
	struct gui_handler *p_gui;
	window_hwnd * p_hwnd_n;
	window_hwnd * gui_hwnd = handler_current();
	int ret;
	gui_msg gui_msg_buffer;
	gui_msg_l0 gui_msgl0;
    unsigned short x_pos,y_pos;

	if( fd_queue == NULL )
		return ERR;  /* queue init error ,direct return */

	if( fd_queuel0 == NULL )
		 fd_queuel0 = open("/dev/queuel0.d",__FS_OPEN_EXISTING | __FS_WRITE);

	ret = read(fd_queuel0,(char *)&gui_msgl0,sizeof(gui_msgl0));

	if( ret != OK )
      return ERR;

	if( (p_hwnd_n = gui_find_window(gui_hwnd,gui_msgl0.x_pos,gui_msgl0.y_pos)) != NULL )
	{
       /* find the window */
		x_pos =  gui_msgl0.x_pos -  p_hwnd_n->window.widget_msg.x;//;
		y_pos =  gui_msgl0.y_pos -  p_hwnd_n->window.widget_msg.y;

		for(p_gui=p_hwnd_n->window.link;p_gui!=NULL;p_gui=p_gui->link)
		{
             /* we find a widget ? */
			 if(gui_with_in(p_gui,x_pos,y_pos) == OK)
			  {
					gui_msg_buffer.handler = p_gui;
					gui_msg_buffer.event_type = gui_msgl0.event_type;
					gui_msg_buffer.data = gui_msgl0.pri_data;
					/*revert all focus widget in same parent window*/
					gui_revert_widget(&p_hwnd_n->window,p_gui);
					/*send the data to the msg queue */
					write(fd_queue,(const char *)&gui_msg_buffer,sizeof(gui_msg_buffer));

					p_gui->status = FOCUS_ON;

					return OK;
			  }
		}
		/* we can not find any widget  */
		gui_msg_buffer.handler = &p_hwnd_n->window;
		gui_msg_buffer.event_type = gui_msgl0.event_type;
		gui_msg_buffer.data = gui_msgl0.pri_data;
		/*revert all focus widget in same parent window*/
		gui_revert_widget(&p_hwnd_n->window,p_gui);
		/*send the data to the msg queue */
		write(fd_queue,(const char *)&gui_msg_buffer,sizeof(gui_msg_buffer));

		p_gui->status = FOCUS_ON;

		return OK;
	}else
	{
	  /* maybe select other window */
       return ERR;
	}

}
static window_hwnd * gui_find_window(window_hwnd * current_hwnd,unsigned short x,unsigned short y)
{
   /* define a hwnd */
   window_hwnd * p_gui;
   /* find from head */
   for(p_gui = current_hwnd;p_gui != NULL ; p_gui = p_gui->same_next)
   {
	   if( gui_with_in( &p_gui->window , x , y ) == OK)
	   {
		   set_handler_current(p_gui);
           return p_gui;
	   }
   }
   /* find from trail */
   for(p_gui = current_hwnd;p_gui != NULL ; p_gui = p_gui->same_pre)
   {
	   if( gui_with_in( &p_gui->window , x , y ) == OK)
	   {
		   set_handler_current(p_gui);
		   return p_gui;
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
	struct gui_handler * p_gui = p_gui_root;
	gui_msg gui_msg_buffer;

	for(;p_gui!=NULL;p_gui=p_gui->link)
	{
	   if(p_gui->status == FOCUS_ON)
	   {
		   if(!fd_queue)
			   fd_queue = open("/dev/queuel0.d",__FS_OPEN_EXISTING | __FS_WRITE);

		   if(p_gui == p_gui_same)
			   return ERR;

		   gui_msg_buffer.event_type = losefocus;
		   gui_msg_buffer.handler = p_gui;
		   /* send the data to the msg queue */
		   write(fd_queue,(const char *)&gui_msg_buffer,sizeof(gui_msg_buffer));
		   /* release the source */
		   p_gui->status = FOCUS_OFF;
		   return OK;
	   }
	}
	return ERR;
}

int gui_key_event_check(char *buffer)
{
	int ret;
	static struct file * fd_key = NULL;
	gui_msg_l0 gui_key;
	if(!fd_key)
	  fd_key = open("/dev/key.d",__FS_OPEN_EXISTING | __FS_WRITE);

	if(!fd_queuel0)
		 fd_queuel0 = open("/dev/queuel0.d",__FS_OPEN_EXISTING | __FS_WRITE);

	if(fd_key==NULL)
	  return ERR; /*open fail*/

    ret = read(fd_key,buffer,1);

    if(ret!=ERR)
    {
    	if(buffer[0]==1)
    	{
			gui_key.event_type = onfocus;
    	}else if(buffer[0]==2)
    	{
    		gui_key.event_type = losefocus;
    	}
			gui_key.x_pos = 125;
			gui_key.y_pos = 215;

			write(fd_queuel0,(const char *)&gui_key,sizeof(gui_key));

      return OK;
    }

    else
      return ERR;
}













