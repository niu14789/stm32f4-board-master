/*
 * gui_config.h
 *
 *  Created on: 2016骞�10鏈�7鏃�
 *      Author: YJ-User17
 */

#ifndef __GUI_CONFIG_H__
#define __GUI_CONFIG_H__

#define GUI_OPTIMIZE_SUPPORT          (1)

#define GUI_WIDTH_PIXEL_DEFAULT       (320)
#define GUI_HEIGHT_PIXEL_DEFAULT      (240)

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
    gui_dev_ops  gui_dev_ops_g;
}gui_device;

int gui_dev_register(unsigned short driver_id,
		                unsigned short x_size,
		                unsigned short y_size,
						void (*put_pixel)(unsigned short x,unsigned short y,unsigned short color),
						unsigned short  (*get_pixel)(unsigned short x,unsigned short y),
						void (*set_line)(unsigned short x,unsigned short y,unsigned short x_s,unsigned short y_s,unsigned short color),
						void (*fill_dect)(unsigned short x,unsigned short y,unsigned short height,unsigned short width,unsigned short color)
						);

gui_device * gui_dev_ops_g(void);

#endif /* STM32F4_BOARD_MASTER_STM32F4_BOARD_MASTER_GUI_GUI_CONFIG_GUI_CONFIG_H_ */
