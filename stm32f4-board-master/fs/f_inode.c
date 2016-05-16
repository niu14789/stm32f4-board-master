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

    while(*nname == *fname)
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
	return (inode_vmn *)&__FS_START__;
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
	int result;
	int fd_head=0;
	static struct fd_find fd;
	inode_head = inode;
	
	while(inode_head->inode->i_flags == FS_INODE_USABLE)
	{
		result = _inode_compare(path,inode_head);

		if( result > 0 )
		{
			  /* not match link the next child inode */
		//	  inode_head->inode->i_peer = inode_head->inode->i_peer->i_child;
		}
		else if( result < 0 )
		{
			  /* not match link the next ipeer inode */
		//	  inode_head->inode->i_peer = inode_head->inode->i_peer->i_peer;
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


int fs_init(void)
{
   int ret,i;
   char first_time = 0;
   struct gui_handler **gui_link_root = gui_sched_root();
   struct gui_handler *gui_link = *gui_link_root;

	 inode_vmn *p_vmn_start = inode_sched_getfiles();

	 /*while(p_vmn_start->inode->i_flags == FS_INODE_USABLE)*/
	for(i=0;i<6;i++)
	{
	   ret = p_vmn_start->inode->init();
	   if(ret != ERR)
		   /* inode init ok*/
		   printf_d("the device:%s init ok at path:%s\n",p_vmn_start->inode->i_name,p_vmn_start->path);
	   else
		   printf_d("the device:%s init err at path:%s\n",p_vmn_start->inode->i_name,p_vmn_start->path);
		 
	   if(ret != ERR)
	   {
			 if(p_vmn_start->inode->nxgui != NULL)
			 {
				 if(!first_time)
				 {
					*gui_link_root = p_vmn_start->inode->nxgui->sched_getfiles();
					gui_link = *gui_link_root;
					first_time = 1;
				 }
				 else
				 {
					gui_link->link = p_vmn_start->inode->nxgui->sched_getfiles();
					gui_link = gui_link->link;
				 }
			 }
	   }
		 p_vmn_start++;
	 }
	 return 0;
}















