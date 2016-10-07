/*
 * display_device.c
 *
 *  Created on: 2016年10月7日
 *      Author: YJ-User17
 */

#include "fs.h"
#include "display_device.h"

gui_device *gui_device_g = NULL;

struct file_operations gui_ops =
{
  gui_device_open,
  NULL,
	gui_dev_read
};

struct inode inode_gui_device = 
{
	NULL,
	NULL,
	0,
	0,
	&gui_ops,
	NULL,
	NULL,
	gui_device_init,
	"gui_device"
};

FS_REGISTER(FS_DEVICE("gui_device"),inode_gui_device);

int gui_device_init(void)
{
	int fd;
	char buffer[4];
	printf_d("finding the gui device\n");
	
	fd = open("/dev/lcd2.d",__ONLYREAD);
	
	if(fd == ERR )
	{
		printf_d("can not find the gui devive\n");
		return (-1);
	}
	
	read(fd,buffer,4);
	
	gui_device_g = (gui_device *)(*((int *)buffer));
	
	printf_d("lcd driver id:0x%x,wigth:%d height:%d\n",gui_device_g->gui_device_msg.lcd_driver_id,gui_device_g->gui_device_msg.x,gui_device_g->gui_device_msg.y);

	return 0;
}

int gui_device_open(struct file * filp)
{
	if(gui_device_g != NULL)
		return OK;
	else
		return ERR;
}

int32_t gui_dev_read(FAR struct file *filp, FAR char *buffer, uint32_t buflen)
{
	unsigned int p ,*d;
	if(buflen == 4)
	{
		p = (unsigned int)gui_device_g;
    d = (unsigned int *)buffer;
		*d = p;
		return 4;
	}else
	{
		return (-1);//not support this format
	}
}
















