/*
 * f_ioctl.c
 *
 *  Created on: 2016Äê10ÔÂ16ÈÕ
 *      Author: Administrator
 */
#include "fs.h"

//int     (*ioctl)(FAR struct file *filp, int cmd, unsigned long arg,void *pri_data);

int ioctl(FAR struct file *filp,int cmd, unsigned long arg,void *pri_data)
{
    if( filp->f_inode->u.i_ops->ioctl != NULL )
    {
    	return filp->f_inode->u.i_ops->ioctl(filp,cmd,arg,pri_data);
    }
    else
    {
    	return ERR;
    }
}
