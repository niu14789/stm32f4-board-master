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

typedef struct touch_t
{
	unsigned short x_cali_k;
	unsigned short x_cali_d;
	unsigned short y_cali_k;
	unsigned short y_cali_d;
}touch_msg_def;

typedef struct gui_touch_dev_t{
	unsigned short x_size;
	unsigned short y_size;
	touch_msg_def touch_cali_msg;
	unsigned short (*measure_x)(void);
	unsigned short (*measure_y)(void);
}gui_touch_dev;

/* interface */
typedef struct gui_dis_dev_t
{
	gui_device_msg  gui_device_msg;
    gui_dev_ops     gui_dev_ops_g;
    gui_touch_dev   gui_touch_ops_g;
}gui_device;

int gui_dev_register(unsigned short driver_id,
		                unsigned short x_size,
		                unsigned short y_size,
						void (*put_pixel)(unsigned short x,unsigned short y,unsigned short color),
						unsigned short  (*get_pixel)(unsigned short x,unsigned short y),
						void (*set_line)(unsigned short x,unsigned short y,unsigned short x_s,unsigned short y_s,unsigned short color),
						void (*fill_dect)(unsigned short x,unsigned short y,unsigned short height,unsigned short width,unsigned short color)
						);
int gui_touch_dev_register(unsigned short width,unsigned short height , unsigned short (*read_x)(void),unsigned short(*read_y)(void));
int gui_touch_calibration(touch_msg_def * touch_msg);
gui_device * gui_dev_ops_g(void);
int gui_config_init(void);

#endif /* STM32F4_BOARD_MASTER_STM32F4_BOARD_MASTER_GUI_GUI_CONFIG_GUI_CONFIG_H_ */
