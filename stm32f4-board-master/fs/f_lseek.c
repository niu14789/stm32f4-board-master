/*
 * f_lseek.c
 *
 *  Created on: 2016Äê10ÔÂ16ÈÕ
 *      Author: Administrator
 */
#include "fs.h"

int32_t lseek(FAR struct file *filp, unsigned int offset, unsigned int whence)
{

    if( filp->f_inode->u.i_ops->lseek != NULL )
    {
    	return filp->f_inode->u.i_ops->lseek(filp,offset,whence);
    }
    else
    {
    	return ERR;
    }
}



