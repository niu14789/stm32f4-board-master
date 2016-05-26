/*
 * queue.c
 *
 *  Created on: 2016��5��14��
 *      Author: Administrator
 */
#include "fs.h"
#include "queue.h"
#include "string.h"

/* the queue of msg define
 * base on a simple queue.
 * */
static queue_msg_t queue_msg[QUEUE_DEEPTH_MSG] __attribute__((at(QUEUE_MEM)));

struct file_operations queue_msg_ops =
{
  queue_device_open,
  queue_write,
  queue_read
};

struct inode inode_queue =
{
	NULL,
	NULL,
	0,
	FS_INODE_USABLE,
	&queue_msg_ops,
	NULL,
	NULL,
	queue_init,
	"queue"
};

FS_REGISTER(FS_DEVICE("queue.d"),inode_queue);

/* interface functions */
int queue_device_open(struct file * filp)
{
	/* open always ok */
	return 0;
}

int32_t queue_write(FAR struct file *filp, FAR const char *buffer, uint32_t buflen)
{
   return queue_write_t(buffer,buflen);
}
int32_t queue_read(FAR struct file *filp, FAR char *buffer, uint32_t buflen)
{
   return queue_read_t(buffer,buflen);
}

/* main function */
int queue_init(void)
{
	queue_create(QUEUE_MSG_ID,QUEUE_DEEPTH_MSG);
	return 0;
}
int queue_create(unsigned short ID,unsigned short deepth)
{
	int i;
	switch(ID)
	{
		case QUEUE_MSG_ID:
			for(i=0;i<QUEUE_DEEPTH_MSG;i++)
			{
				queue_msg[i].useable = USEABLE;
				queue_msg[i].link = &queue_msg[(i+1)%QUEUE_DEEPTH_MSG];
			}
			return 0;/* create okay */
		case QUEUE_EVENT_ID:
			break;
		default:
			break;
	}
    return 1;
}

int queue_write_t(const char *data,unsigned short len)
{
	int i;
	sem_take();
	for(i=0;i<QUEUE_DEEPTH_MSG;i++)
	{
		if(queue_msg[i].useable == USEABLE)
		{
			/* write enable */
			queue_msg[i].useable = NONUSEABLE;
			memcpy(queue_msg[i].payload,data,len>QUEUE_DEFINE_SIZE?QUEUE_DEFINE_SIZE:len);
			return OK;
		}
	}
	sem_give();
	return ERR;
}

int queue_read_t(void *data,unsigned short len)
{
	int i;
	sem_take();
	for(i=0;i<QUEUE_DEEPTH_MSG;i++)
	{
		if(queue_msg[QUEUE_DEEPTH_MSG-i-1].useable == NONUSEABLE)
		{
			/* read enable */
			queue_msg[QUEUE_DEEPTH_MSG-i-1].useable = USEABLE;
			memcpy(data,queue_msg[QUEUE_DEEPTH_MSG-i-1].payload,len>QUEUE_DEFINE_SIZE?QUEUE_DEFINE_SIZE:len);
			return OK;
		}
	}
	sem_give();
	return ERR;
}

















