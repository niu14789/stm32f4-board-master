/*
 * fs.h
 *
 *  Created on: 2016��4��19��
 *      Author: YJ-User17
 */

#ifndef __FS_H__
#define __FS_H__

#include "f_typedef.h"
#include "gui.h"

#define FAR
#define FS_INODE_USABLE 0x56AB  /* magic */
#define ERR -1
#define OK   0
#define  DEVICE_END  0x8
#define printf_d(...)

#define __ONLYREAD 1

struct inode;

typedef struct inode_vmn_t
{
   char *path;
   struct inode *inode;
}inode_vmn;

#define __FS_DEVICE__   "/dev/"
#define __FS_FILE__     "/sdcard/"
#define __FS_DRV__      "/drv/"

#define FS_DEVICE(x)   __FS_DEVICE__##x
#define FS_FILE(x)     __FS_FILE__##x
#define FS_DRV(x)      __FS_DRV__##x

#define __INIT __attribute__((unused, section("fs_vmn")))
#define FS_REGISTER(inode_name,node_t) const inode_vmn __FS_##node_t __INIT =      \
{                                                                                  \
	inode_name,                                                                    \
	&node_t                                                                        \
}                                                                                  \

#define FS_REGISTER_START(inode_name,node_t) const inode_vmn __FS_START__ __INIT = \
{                                                                                  \
	inode_name,                                                                    \
	&node_t                                                                        \
}   

struct inode;

struct block_operations
{
	int     (*open)(void);
	int     (*read)(void);
//   int     (*open)(FAR struct inode *inode);
//   int     (*close)(FAR struct inode *inode);

//   int32_t (*read)(FAR struct inode *inode, FAR unsigned char *buffer,
//                          int32_t start_sector, unsigned int nsectors);
//   int32_t (*write)(FAR struct inode *inode, FAR const unsigned char *buffer,
//   uint32_t start_sector, unsigned int nsectors);
// #ifdef GEOMETRY
//   int     (*geometry)(FAR struct inode *inode, FAR struct geometry *geometry);
// #endif
//   int     (*ioctl)(FAR struct inode *inode, int cmd, unsigned long arg);
};

/* This structure represents one inode in the niufs pseudo-file system */

/* These are the various kinds of operations that can be associated with
 * an inode.
 */

union inode_ops_u
{
  FAR const struct file_operations    *i_ops;  /* Driver operations for inode */
#ifndef CONFIG_DISABLE_MOUNTPOUNT
  FAR const struct block_operations   *i_bops; /* Block driver operations */
  FAR const struct mountpt_operations *i_mops; /* Operations on a mountpoint */
#endif
};

struct inode
{
  FAR struct inode *i_peer;       /* Pointer to same level inode */
  FAR struct inode *i_child;      /* Pointer to lower level inode */
  int16_t           i_crefs;      /* References to inode */
  uint16_t          i_flags;      /* Flags for inode */
  union inode_ops_u u;            /* Inode operations */
#ifdef CONFIG_FILE_MODE
  mode_t            i_mode;       /* Access mode flags */
#endif
  struct nxgui_object *nxgui;     /* nuttx gui link */
  FAR void         *i_private;    /* Per inode driver private data */
  int (*init)(void);              /* node firmware init interface */
  const char        *i_name;    /* Name of inode (variable) */
};

struct file
{
  int               f_oflags; /* Open mode flags */
  int32_t           f_pos;    /* File position */
  FAR struct inode *f_inode;  /* Driver interface */
  void             *f_priv;   /* Per file driver private data */
};

struct fd_find
{
	inode_vmn * inode_find;
	int fd;
};	

struct file_operations
{
	int     (*open) (FAR struct file *filp);
	int32_t (*write)(FAR struct file *filp, FAR const char *buffer, uint32_t buflen);
	int32_t (*read )(FAR struct file *filp, FAR char *buffer, uint32_t buflen);
//  /* The device driver open method differs from the mountpoint open method */
//
//  int     (*open)(FAR struct file *filp);
//
//  /* The following methods must be identical in signature and position because
//   * the struct file_operations and struct mountp_operations are treated like
//   * unions.
//   */
//
//  int     (*close)(FAR struct file *filp);
//  int32_t (*read )(FAR struct file *filp, FAR char *buffer, uint32_t buflen);
//  int32_t (*write)(FAR struct file *filp, FAR const char *buffer, uint32_t buflen);
//  int32_t  (*seek)(FAR struct file *filp, int32_t offset, int whence);
//  int     (*ioctl)(FAR struct file *filp, int cmd, unsigned long arg);
//#ifdef CONFIG_ENABLE_POLL
//  int     (*poll)(FAR struct file *filp, struct pollfd *fds, char setup);
//#endif

  /* The two structures need not be common after this point */
};

extern FAR inode_vmn *inode_sched_getfiles(void);
extern const inode_vmn __FS_START__;
extern FAR struct fd_find *inode_find(inode_vmn *inode,FAR const char *path, FAR const char **relpath);
extern int system_initialization(char *device_availdable_list);
extern int read(int fd, FAR char *buffer, uint32_t buflen);
extern int open(const char *path, int oflags);
extern int32_t write(int fd, FAR const char *buffer, uint32_t buflen);

#endif /* FS_FS_H_ */


