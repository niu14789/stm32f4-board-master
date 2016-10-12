/*
 *  gui_config.c
 *
 *  Created on: 2016骞�10鏈�7鏃�
 *      Author: YJ-User17
 */

#include "gui_config.h"

/* origanme a gui device */
static gui_device gui_device_g;

/* default set line,use as idoit foolish */
void set_line_default(unsigned short x,unsigned short y,unsigned short x_s,unsigned short y_s,unsigned short color)
{

}
/* default fill_dect,use as idoit foolish */
void fill_dect_default(unsigned short x,unsigned short y,unsigned short height,unsigned short width,unsigned short color)
{

}

int gui_dev_register(unsigned short driver_id,
		                unsigned short x_size,
		                unsigned short y_size,
						void (*put_pixel)(unsigned short x,unsigned short y,unsigned short color),
						unsigned short  (*get_pixel)(unsigned short x,unsigned short y),
						void (*set_line)(unsigned short x,unsigned short y,unsigned short x_s,unsigned short y_s,unsigned short color),
						void (*fill_dect)(unsigned short x,unsigned short y,unsigned short height,unsigned short width,unsigned short color)
						)
{
    /* we must have a driver id */
	if(driver_id == 0)
	{
		/* we can`t have a id */
		return (-1);
	}
	gui_device_g.gui_device_msg.lcd_driver_id = driver_id;

	/* we must have a driver x_size and y_size */
	if( x_size == 0 || y_size == 0 )
	   return (-2);// we do not have a x_size and y_size;

	gui_device_g.gui_device_msg.xsize = x_size;
	gui_device_g.gui_device_msg.ysize = y_size;

    /* we must have a put_pixel and get_pixel*/
    if( put_pixel == (void*)0 || get_pixel == (void*)0)
    	return (-3);//// we do not have a put_pixel and get_pixel;

	gui_device_g.gui_dev_ops_g.put_pixel = put_pixel;
	gui_device_g.gui_dev_ops_g.get_pixel = get_pixel;

    if( set_line != (void*)0)
	   gui_device_g.gui_dev_ops_g.set_line = set_line;
    else
       gui_device_g.gui_dev_ops_g.set_line = set_line_default;

    if( fill_dect != (void*)0 )
       gui_device_g.gui_dev_ops_g.fill_dect = fill_dect;
    else
       gui_device_g.gui_dev_ops_g.fill_dect = fill_dect_default;

    /* ok */
    return 0;
}

/*
 *
 * gui_dev_ops_g
 *
 * as global
 *
 * */
gui_device * gui_dev_ops_g(void)
{
	if( gui_device_g.gui_dev_ops_g.put_pixel != (void*)0 )
	{
	    return &gui_device_g;
	}else
	{
		return (void*)0;
	}
}


















