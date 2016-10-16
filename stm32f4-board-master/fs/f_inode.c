/*
 * fs.c
 *
 *  Created on: 2016骞�5鏈�7鏃�
 *      Author: YJ-User17
 */

#include "fs.h"

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: _inode_compare
 *
 * Description:
 *   Compare two inode names
 *
 ****************************************************************************/

static int _inode_compare(FAR const char *fname,
                          FAR inode_vmn *node)
{
   char *nname = node->path;

   if (!nname)
    {
      return 1;
    }

   if (!fname)
    {
      return -1;
    }

    while( (*nname == *fname) || ((*nname == '\0')) )
    {
        if(*nname == '\0')
            return OK;

        nname++;
        fname++;
    }
    return *nname - *fname;
}


FAR inode_vmn *inode_sched_getfiles(void)
{
	extern inode_vmn  fs_vmn$$Base;
	return (inode_vmn *)&fs_vmn$$Base;
}

FAR int inode_sched_limit(void)
{
	extern inode_vmn  fs_vmn$$Base;
	extern inode_vmn  fs_vmn$$Limit;
	
	return (&fs_vmn$$Limit-&fs_vmn$$Base);
}

/****************************************************************************
 * Name: inode_find
 *
 * Description:
 *   This is called from the open() logic to get a reference to the inode
 *   associated with a path.
 *
 ****************************************************************************/
FAR struct fd_find *inode_find(inode_vmn *inode,FAR const char *path, FAR const char **relpath)
{
	inode_vmn * inode_head;
	int result,i,n;
	int fd_head=0;
	static struct fd_find fd;
	inode_head = inode;
	
    n = inode_sched_limit();
	
	for( i = 0 ; i < n ; i++ )
	{
		result = _inode_compare(path,inode_head);

		if( result > 0 )
		{
			  /* not match link the next child inode */
//			  inode_head->inode->i_peer = inode_head->inode->i_peer->i_child;
		}
		else if( result < 0 )
		{
			  /* not match link the next ipeer inode */
//		  inode_head->inode->i_peer = inode_head->inode->i_peer->i_peer;
		}
		else
		{
          /* Yes...match return*/
		    fd.inode_find = inode_head;
		    fd.fd = fd_head;
            return &fd;
		}
		inode_head++;
		fd_head++;
	}
	return NULL;
}


int system_initialization(char *device_availdable_list)
{
  int ret,i,n;

	inode_vmn * p_vmn_start = inode_sched_getfiles();
    n = inode_sched_limit();
	
	/* while(p_vmn_start->inode->i_flags == FS_INODE_USABLE) */
	for( i = 0 ; i < n ; i++ )
	{
		ret = p_vmn_start->inode->init();
		if(ret != ERR){
		   /* inode init ok*/
		  if(device_availdable_list!=NULL)/*just initialization*/
		    *device_availdable_list = OK;
		   printf_d("the device:%s init ok at path:%s\n",p_vmn_start->inode->i_name,p_vmn_start->path);
		}
		else{
		   if(device_availdable_list!=NULL)/*just initialization*/
		     *device_availdable_list = 1;
		   printf_d("the device:%s init err at path:%s\n",p_vmn_start->inode->i_name,p_vmn_start->path);
		}
		if(device_availdable_list!=NULL)/*just initialization*/
		   device_availdable_list++;
		p_vmn_start++;
	}
	if(device_availdable_list!=NULL)/*just initialization*/
      *device_availdable_list = DEVICE_END;
	return 0;
}



























