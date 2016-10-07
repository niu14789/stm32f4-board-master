/*
 * display_device.h
 *
 *  Created on: 2016年10月7日
 *      Author: YJ-User17
 */



#ifndef STM32F4_BOARD_MASTER_STM32F4_BOARD_MASTER_GUI_GUI_CONFIG_DISPLAY_DEVICE_H_
#define STM32F4_BOARD_MASTER_STM32F4_BOARD_MASTER_GUI_GUI_CONFIG_DISPLAY_DEVICE_H_

#include "gui_config.h"

/* gui display devive message */
typedef struct gui_device_msg_t{
	unsigned short xsize;
	unsigned short ysize;
}gui_device_msg;

/* interface */
typedef struct gui_dis_dev_t{
	void (*put_pixel)(unsigned short x,unsigned short y,unsigned short color);
	int  (*get_pixel)(unsigned short x,unsigned short y);
	/* if exist the hardware accel driver */
//	void (*cl)
	void (*set_vline)(unsigned short x,unsigned short y,unsigned short size,unsigned short color);
	void (*set_hline)(unsigned short x,unsigned short y,unsigned short size,unsigned short color);
	void (*fill_dect)(unsigned short x,unsigned short y,unsigned short height,unsigned short width,unsigned short color);
//	void (*setcircle)
}gui_device;



#endif /* STM32F4_BOARD_MASTER_STM32F4_BOARD_MASTER_GUI_GUI_CONFIG_DISPLAY_DEVICE_H_ */
