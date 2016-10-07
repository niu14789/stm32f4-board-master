

#ifndef __LCD_FS_H__
#define __LCD_FS_H__
#include "fs.h"
	int lcd2_device_open(struct file * filp);
	int32_t lcd2_read(FAR struct file *filp, FAR char *buffer, uint32_t buflen);
#endif
