/*
 * f_write.c
 *
 *  Created on: 2016��5��8��
 *      Author: Administrator
 */

#include "fs.h"

int32_t write(struct file * filp, FAR const char *buffer, uint32_t buflen)
{
    if( filp->f_inode->u.i_ops->write != NULL )
    {
    	return filp->f_inode->u.i_ops->write(filp,buffer,buflen);
    }
    else
    {
    	return ERR;
    }
}

