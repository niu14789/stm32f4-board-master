/*
 * server.c
 *
 *  Created on: 2016��5��15��
 *      Author: Administrator
 */

#include "fs.h"
#include "gui.h"
#include "server.h"

#define QUEUE_PATH  "/etc/queue.d"

static int fd_queue = 0;
static int fd_queuel0 = 0;


int gui_server(void)
{
  static char flag = 0;
  if(!flag) /* is first time enter */
  {
	  fd_queue = open("/etc/queue.d",__ONLYREAD);
	  if(fd_queue != ERR)
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

		gui_event_done(p_gui_msg,p_gui_msg->event_type);

		/* idle the callback function */
		if(p_gui_msg->handler->callback!=NULL)
			p_gui_msg->handler->callback(p_gui_msg->event_type,p_gui_msg->data);
	}
	return 0;
}

int gui_event_done(gui_msg *p_msg,enum event_type event)
{
	switch(event)
	{
		case onfocus:
			if(p_msg->handler->gui_ops->onfocus != NULL)
				p_msg->handler->gui_ops->onfocus(&p_msg->handler->widget_msg);
			break;
		case losefocus:
			if(p_msg->handler->gui_ops->losefocus != NULL)
				p_msg->handler->gui_ops->losefocus(&p_msg->handler->widget_msg);
			break;
		case onclick:
			if(p_msg->handler->gui_ops->onclick != NULL)
				p_msg->handler->gui_ops->onclick(&p_msg->handler->widget_msg);
			break;
		case doubleclick:
			break;
		case change_caption:
			break;
		case key_click:
			break;
		case key_long_press:
			break;
		default:break;
	}
	return 0;
}


int gui_event_check(void)
{
	extern struct gui_handler * handler_current(void);
	struct gui_handler *gui_hander_root_t= handler_current();
	struct gui_handler *gui_hander_root = gui_hander_root_t,*p_gui;
	int ret;
	gui_msg gui_msg_buffer;
	gui_msg_l0 gui_msgl0;

	if( fd_queue == 0 )
		return ERR;  /* queue init error ,direct return */

	if(!fd_queuel0)
		 fd_queuel0 = open("/etc/queuel0.d",__ONLYREAD);

	ret = read(fd_queuel0,(char *)&gui_msgl0,sizeof(gui_msgl0));

	if(ret!=OK)
      return ERR;

	for(p_gui=gui_hander_root;
			p_gui!=NULL;p_gui=p_gui->link)
	{
		 if(gui_msgl0.x_pos>=p_gui->widget_msg.x &&
			gui_msgl0.x_pos<=(p_gui->widget_msg.xsize+p_gui->widget_msg.x) &&
			gui_msgl0.y_pos>=p_gui->widget_msg.y	&&
			gui_msgl0.y_pos<=(p_gui->widget_msg.ysize+p_gui->widget_msg.y))
		  {
				gui_msg_buffer.handler = p_gui;
				gui_msg_buffer.event_type = gui_msgl0.event_type;

				/*revert all focus widget in same parent window*/
				gui_revert_widget(gui_hander_root,p_gui);
				/*send the data to the msg queue */
				write(fd_queue,(const char *)&gui_msg_buffer,sizeof(gui_msg_buffer));

				p_gui->status = FOCUS_ON;

				return OK;
		  }
	}
	return ERR;
}


/* revert all focused widget */
int gui_revert_widget(struct gui_handler * p_gui_root,struct gui_handler * p_gui_same)
{
	struct gui_handler * p_gui = p_gui_root;
	gui_msg gui_msg_buffer;

	for(;p_gui!=NULL;p_gui=p_gui->link)
	{
	   if(p_gui->status == FOCUS_ON)
	   {
		   if(!fd_queue)
			   fd_queue = open("/etc/queuel0.d",__ONLYREAD);

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
	static int fd_key = 0;
	gui_msg_l0 gui_key;
	if(!fd_key)
	  fd_key = open("/etc/key.d",__ONLYREAD);

	if(!fd_queuel0)
		 fd_queuel0 = open("/etc/queuel0.d",__ONLYREAD);

	if(fd_key==ERR)
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













