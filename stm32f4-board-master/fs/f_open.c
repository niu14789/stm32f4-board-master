

#include "fs.h"

int open(const char *path, int oflags)
{
  int ret; /* file device */
  inode_vmn   *p_vmn_start;
  struct file filp;
  struct fd_find *fd;
  /*
   * get inode sched getfiles
   * p vmn start
   * nothing
   * */
  p_vmn_start = inode_sched_getfiles();

  fd = inode_find(p_vmn_start,path,(const char **)NULL);
	
  if(fd!=NULL)
  {
	  /* Yes...we match it */
	  filp.f_oflags = oflags;
	  ret = fd->inode_find->inode->u.i_ops->open(&filp);
	  /* if we get the right value(OK),then we return fd */
	  if(ret!=ERR)
		  return fd->fd;
  }
  return ERR;
}

