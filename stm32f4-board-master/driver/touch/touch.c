/*
 * touch.c
 *
 *  Created on: 2016Äê10ÔÂ12ÈÕ
 *      Author: Administrator
 */

#include "stm32f4xx.h"
#include "fs.h"

struct file_operations touch2_ops =
{
  touch2_device_open,
  touch2_write,
  touch2_read,
};

struct inode inode_touch2 =
{
	NULL,
	NULL,
	0,
	FS_INODE_USABLE,
	&touch2_ops,
	NULL,
	NULL,
	touch2_init,
	"touch2"
};

FS_REGISTER(FS_INPUT("touch2.d"),inode_touch2);


























