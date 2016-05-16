/*
 * server.c
 *
 *  Created on: 2016Äê5ÔÂ15ÈÕ
 *      Author: Administrator
 */

#include "fs.h"
#include "gui.h"
#include "server.h"

#define QUEUE_PATH  "/etc/queue.d"

static int fd_queue = 0;
int gui_key_event_check(char *buffer);
int gui_event_check(void);
int gui_event_done(gui_msg *p_msg,enum event_type event);
int gui_event_idle(void);

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
				p_msg->handler->gui_ops->onfocus(p_msg->handler->widget_msg);
			break;
		case losefocus:
			if(p_msg->handler->gui_ops->losefocus != NULL)
				p_msg->handler->gui_ops->losefocus(p_msg->handler->widget_msg);
			break;
		case onclick:
			if(p_msg->handler->gui_ops->onclick != NULL)
				p_msg->handler->gui_ops->onclick(p_msg->handler->widget_msg);
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
	struct gui_handler **gui_hander_root_t = gui_sched_root();
	struct gui_handler *gui_hander_root = *gui_hander_root_t,*p_gui;
	int x,y;
	char buffer[1];
	gui_msg gui_msg_buffer;

	if( fd_queue == 0 )
		return ERR;  /* queue init error ,direct return */

	if(gui_key_event_check(buffer)!=ERR)
	{
        x = 175;
        y = 35;
        if(buffer[0]==1)
        	gui_msg_buffer.event_type = onfocus;
        else if(buffer[0]==2)
        	gui_msg_buffer.event_type = losefocus;

		for(p_gui=gui_hander_root;
				p_gui!=NULL;p_gui=p_gui->link)
		{
            if(x>=p_gui->widget_msg->x &&
               x<=(p_gui->widget_msg->xsize+p_gui->widget_msg->x) &&
			   y>=p_gui->widget_msg->y	&&
			   y<=(p_gui->widget_msg->ysize+p_gui->widget_msg->y))
            {
            	gui_msg_buffer.handler = p_gui;
            	/*send the data to the msg queue */
            	write(fd_queue,(const char *)&gui_msg_buffer,sizeof(gui_msg_buffer));
            	return OK;
            }
		}
	}
	return ERR;
}

int gui_key_event_check(char *buffer)
{
	int ret;
	static int fd_key = 0;

	if(!fd_key)
	  fd_key = open("/etc/key.d",__ONLYREAD);

	if(fd_key==ERR)
	 return ERR; /*open fail*/

    ret = read(fd_key,buffer,1);

    if(ret!=ERR)
    	return OK;
    else
    	return ERR;
}













