/*
 * f_mkdir.c
 *
 *  Created on: 2016Äê10ÔÂ16ÈÕ
 *      Author: Administrator
 */

#include "fs.h"

int mkdir( const char * path )
{
	inode_vmn   *p_vmn_start;
	struct fd_find *fd;
	/*
	* get inode sched getfiles
	* p vmn start
	* nothing
	* */
	p_vmn_start = inode_sched_getfiles();

	fd = inode_find(p_vmn_start,path,(const char **)NULL);

	if( fd != NULL )
	{
	  /* Yes...we match it */

	  if( fd->inode_find->inode->u.i_ops->mkdir != NULL )
		{
		 return fd->inode_find->inode->u.i_ops->mkdir(path);
		}
	  /* if we get the right value(OK),then we return fd */
	}
	return ERR;
}




















