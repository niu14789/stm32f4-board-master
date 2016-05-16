/*
 * f_read.c
 *
 *  Created on: 2016年5月6日
 *      Author: YJ-User17
 */
#include "stm32f4xx.h"
#include "string.h"
#include "fs.h"



int read(int fd, FAR char *buffer, uint32_t buflen)
{
	inode_vmn   *p_vmn_start;
	int32_t ret;
	struct file filp;
	p_vmn_start = inode_sched_getfiles();

	p_vmn_start += fd;

	ret = p_vmn_start->inode->u.i_ops->read(&filp,buffer,buflen);
	return ret;
}











