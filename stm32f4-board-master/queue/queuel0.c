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
static queue_msg_t queue_l0[QUEUE_DEEPTH_L0] __attribute__((at(QUEUE_L0_MEM)));

struct file_operations queue_l0_ops =
{
  queuel0_device_open,
  queuel0_write,
  queuel0_read
};

struct inode inode_queuel0 =
{
	NULL,
	NULL,
	0,
	FS_INODE_USABLE,
	&queue_l0_ops,
	NULL,
	NULL,
	queuel0_init,
	"queue"
};

FS_REGISTER("/etc/queuel0.d",inode_queuel0);

/* interface functions */
int queuel0_device_open(struct file * filp)
{
	/* open always ok */
	return 0;
}

int32_t queuel0_write(FAR struct file *filp, FAR const char *buffer, uint32_t buflen)
{
   return queuel0_write_t(buffer,buflen);
}
int32_t queuel0_read(FAR struct file *filp, FAR char *buffer, uint32_t buflen)
{
   return queuel0_read_t(buffer,buflen);
}

/* main function */
int queuel0_init(void)
{
	queuel0_create(QUEUE_L0_ID,QUEUE_DEEPTH_L0);
	return 0;
}
int queuel0_create(unsigned short ID,unsigned short deepth)
{
	int i;
	switch(ID)
	{
		case QUEUE_L0_ID:
			for(i=0;i<QUEUE_DEEPTH_L0;i++)
			{
				queue_l0[i].useable = USEABLE;
				queue_l0[i].link = &queue_l0[(i+1)%QUEUE_DEEPTH_L0];
			}
			return 0;/* create okay */
		case QUEUE_EVENT_ID:
			break;
		default:
			break;
	}
    return 1;
}

int queuel0_write_t(const char *data,unsigned short len)
{
	int i;
	sem_take();
	for(i=0;i<QUEUE_DEEPTH_L0;i++)
	{
		if(queue_l0[i].useable == USEABLE)
		{
			/* write enable */
			queue_l0[i].useable = NONUSEABLE;
			memcpy(queue_l0[i].payload,data,len>QUEUE_DEFINE_SIZE?QUEUE_DEFINE_SIZE:len);
			return OK;
		}
	}
	sem_give();
	return ERR;
}

int queuel0_read_t(void *data,unsigned short len)
{
	int i;
	sem_take();
	for(i=0;i<QUEUE_DEEPTH_L0;i++)
	{
		if(queue_l0[QUEUE_DEEPTH_L0-i-1].useable == NONUSEABLE)
		{
			/* read enable */
			queue_l0[QUEUE_DEEPTH_L0-i-1].useable = USEABLE;
			memcpy(data,queue_l0[QUEUE_DEEPTH_L0-i-1].payload,len>QUEUE_DEFINE_SIZE?QUEUE_DEFINE_SIZE:len);
			return OK;
		}
	}
	sem_give();
	return ERR;
}

















