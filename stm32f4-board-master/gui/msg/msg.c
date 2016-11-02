/*
 * msg.c
 *
 *  Created on: 2016年11月2日
 *      Author: YJ-User17
 */

#include "fs.h"
#include "gui.h"
#include "msg.h"

/*
 *
 * gui send message to queue
 *
 * high level
 *
 * */
int gui_send_msg(struct gui_handler* handler,enum event_type event_type,void *data)
{
	int ret;
	/* define some buffer as same */
	static struct file * fd_queue = NULL;
    /* define some buffer as same */
	gui_msg gui_msg_buffer;

	/* first open the queue */
	if(fd_queue == NULL)
		fd_queue = open("/dev/queue.d",__FS_OPEN_EXISTING | __FS_WRITE);

	/* open ok */
	gui_msg_buffer.handler = handler;
	gui_msg_buffer.event_type = event_type;
	gui_msg_buffer.data = data;

	/* write data to queue */
	ret = write(fd_queue,(const char *)&gui_msg_buffer,sizeof(gui_msg_buffer));

	return ret;//ok or fail
}

/*
 *
 * gui read a message from high level
 *
 * */
int gui_read_msg(char * data,unsigned int len)
{
	int ret;
	/* define some buffer as same */
	static struct file * fd_queue = NULL;

	/* first open the queue */
	if(fd_queue == NULL)
		fd_queue = open("/dev/queue.d",__FS_OPEN_EXISTING | __FS_WRITE);

	ret = read(fd_queue,data,len);

	return ret;//ok or fail
}

/*
 *
 * gui send message to queue
 *
 * low level
 *
 * */
int gui_send_msgl0(enum event_type event_type , unsigned short x_pos , unsigned short y_pos , unsigned short id , void *pri_data)
{
	int ret;
	/* define some buffer as same */
	static struct file * fd_queue = NULL;
    /* define some buffer as same */
	gui_msg_l0 gui_msg_buffer;

	/* first open the queue */
	if(fd_queue == NULL)
		fd_queue = open("/dev/queuel0.d",__FS_OPEN_EXISTING | __FS_WRITE);

	/* open ok */
	gui_msg_buffer.event_type = event_type;
	gui_msg_buffer.id = id;
	gui_msg_buffer.pri_data = pri_data;
	gui_msg_buffer.x_pos = x_pos;
	gui_msg_buffer.y_pos = y_pos;

	/* write data to queue */
	ret = write(fd_queue,(const char *)&gui_msg_buffer,sizeof(gui_msg_buffer));

	return ret;//ok or fail
}

/*
 *
 * gui read a message from low level
 *
 * */
int gui_read_msgl0(char * data,unsigned int len)
{
	int ret;
	/* define some buffer as same */
	static struct file * fd_queue = NULL;

	/* first open the queue */
	if(fd_queue == NULL)
		fd_queue = open("/dev/queuel0.d",__FS_OPEN_EXISTING | __FS_WRITE);

	ret = read(fd_queue,data,len);

	return ret;//ok or fail
}

































