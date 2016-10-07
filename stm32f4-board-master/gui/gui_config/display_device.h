/*
 * display_device.h
 *
 *  Created on: 2016年10月7日
 *      Author: YJ-User17
 */

#ifndef STM32F4_BOARD_MASTER_STM32F4_BOARD_MASTER_GUI_GUI_CONFIG_DISPLAY_DEVICE_H_
#define STM32F4_BOARD_MASTER_STM32F4_BOARD_MASTER_GUI_GUI_CONFIG_DISPLAY_DEVICE_H_

#include "gui_config.h"
#include "fs.h"
/* gui display devive message */
typedef struct gui_device_msg_t
{
	unsigned short xsize;
	unsigned short ysize;
	unsigned int lcd_driver_id;
}gui_device_msg;

typedef struct gui_dev_ops_t
{
		void (*put_pixel)(unsigned short x,unsigned short y,unsigned short color);
		unsigned short  (*get_pixel)(unsigned short x,unsigned short y);
		/* if exist the hardware accel driver */
		//	void (*cl)
		void (*set_line)(unsigned short x,unsigned short y,unsigned short x_s,unsigned short y_s,unsigned short color);
		void (*fill_dect)(unsigned short x,unsigned short y,unsigned short height,unsigned short width,unsigned short color);
		//	void (*setcircle)
}gui_dev_ops;

/* interface */
typedef struct gui_dis_dev_t
{
	gui_device_msg gui_device_msg;
  gui_dev_ops * gui_dev_ops_g;
}gui_device;

int gui_device_init(void);
int gui_device_open(struct file * filp);
int32_t gui_dev_read(FAR struct file *filp, FAR char *buffer, uint32_t buflen);

#endif /* STM32F4_BOARD_MASTER_STM32F4_BOARD_MASTER_GUI_GUI_CONFIG_DISPLAY_DEVICE_H_ */















