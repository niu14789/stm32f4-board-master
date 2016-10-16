/*
 * f_read.c
 *
 *  Created on: 2016骞�5鏈�6鏃�
 *      Author: YJ-User17
 */

#include "fs.h"



int32_t read(struct file * filp, FAR char *buffer, uint32_t buflen)
{
    if( filp->f_inode->u.i_ops->read != NULL )
    {
    	return filp->f_inode->u.i_ops->read(filp,buffer,buflen);
    }
    else
    {
    	return ERR;
    }
}











