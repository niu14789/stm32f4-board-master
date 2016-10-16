
/*
 *
 *  f_close.c
 *
 */



#include "fs.h"

int close(struct file * filp)
{
    if( filp->f_inode->u.i_ops->close != NULL )
    {
    	return filp->f_inode->u.i_ops->close(filp);
    }
    else
    {
    	return ERR;
    }
}
