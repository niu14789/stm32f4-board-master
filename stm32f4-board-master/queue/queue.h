/*
 * queue.h
 *
 *  Created on: 2016��5��14��
 *      Author: Administrator
 */

#ifndef __QUEUE_H__
#define __QUEUE_H__

#define USEABLE      0x14
#define NONUSEABLE   0x38

#pragma once 

static char sem_flag = 0;
	 
#define sem_give(...)   { sem_flag = 0; } 
#define sem_take(...)   { if(sem_flag)return -1; sem_flag = 1;}

/* base on a simple queue
 *
 * the data size config as following down
 *
 * the MARCO : QUEUE_DEFINE_SIZE
 * */
#define QUEUE_DEFINE_SIZE 20

/* config */
#define USE_MEM
#define QUEUE_DEEPTH_MSG  10

#define QUEUE_DEEPTH_L0   10

#define QUEUE_MSG_ID      0x14
#define QUEUE_EVENT_ID    0x38
#define QUEUE_MSG_ID      0x14

#define QUEUE_L0_ID       0x35
/*  end   */

#ifdef USE_MEM
   #define QUEUE_MEM 0x10000000
#endif

#ifdef USE_MEM
   #define QUEUE_L0_MEM 0x10000200
#endif

typedef struct queue_t{
	struct queue_t *link;
	int useable;
    char payload[QUEUE_DEFINE_SIZE];
}queue_msg_t;


	/* function queue msg*/
	int queue_device_open(struct file * filp);
	int32_t queue_write(FAR struct file *filp, FAR const char *buffer, uint32_t buflen);
	int32_t queue_read(FAR struct file *filp, FAR char *buffer, uint32_t buflen);
	int queue_init(void);
	int queue_create(unsigned short ID,unsigned short deepth);
	int queue_write_t(const char *data,unsigned short len);
	int queue_read_t(void *data,unsigned short len);
	/* for l0*/
	int queuel0_device_open(struct file * filp);
	int32_t queuel0_write(FAR struct file *filp, FAR const char *buffer, uint32_t buflen);
	int32_t queuel0_read(FAR struct file *filp, FAR char *buffer, uint32_t buflen);
	int queuel0_init(void);
	int queuel0_create(unsigned short ID,unsigned short deepth);
	int queuel0_write_t(const char *data,unsigned short len);
	int queuel0_read_t(void *data,unsigned short len);

#endif /* __QUEUE_H__ */



