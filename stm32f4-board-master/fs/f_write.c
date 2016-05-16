/*
 * f_write.c
 *
 *  Created on: 2016Äê5ÔÂ8ÈÕ
 *      Author: Administrator
 */

#include "fs.h"

int32_t write(int fd, FAR const char *buffer, uint32_t buflen)
{
	inode_vmn   *p_vmn_start;
	int32_t ret;
	struct file filp;
	p_vmn_start = inode_sched_getfiles();

	p_vmn_start += fd;

	ret = p_vmn_start->inode->u.i_ops->write(&filp,buffer,buflen);
	return ret;
}

