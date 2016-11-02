/*
 *  gui_config.c
 *
 *  Created on: 2016骞�10鏈�7鏃�
 *      Author: YJ-User17
 */
#include "fs.h"
#include "gui_config.h"
#include "string.h"
/* origanme a gui device */
static gui_device gui_device_g;

struct inode inode_gui_config =
{
	NULL,
	NULL,
	0,
	FS_INODE_USABLE,
	NULL,
	NULL,
	NULL,
	gui_config_init,
	"gui_config"
};

FS_REGISTER(FS_DRV("gui_config.d"),inode_gui_config);

/* default set line,use as idoit foolish */
void set_line_default(unsigned short x,unsigned short y,unsigned short x_s,unsigned short y_s,unsigned short color)
{

}
/* default fill_dect,use as idoit foolish */
void fill_dect_default(unsigned short x,unsigned short y,unsigned short height,unsigned short width,unsigned short color)
{

}

int gui_config_init(void)
{
	struct file * file_touch;
    float buffer[5];

    /* open save file in eeprom*/
	file_touch = open("/less/eeprom/lcd2_default_cali.bin",__FS_OPEN_EXISTING | __FS_READ);

	if( open(FS_DEVICE("lcd2.d"), __FS_OPEN_EXISTING | __FS_READ) == NULL )
	{
		printf_d("touch we can not find the lcd2 device\n");
		return ERR;
	}

	if( open(FS_INPUT("touch2.d"), __FS_OPEN_EXISTING | __FS_READ) == NULL )
	{
		printf_d("touch we can not find the touch device\n");
		return ERR;
	}

    if(file_touch == NULL)
    {
		printf_d("touch cali:can not find the eeprom dev\n");
		printf_d("need calibration\n");
		gui_touch_calibration(&gui_dev_ops_g()->gui_touch_ops_g.touch_cali_msg);

		return OK;
    }

    if(read(file_touch,(char *)&buffer,sizeof(buffer)) != sizeof(buffer))
    {
    	/*read error*/
    	printf_d("touch:eeprom read cali error\n");
    	return ERR;
    }

    if(*(int *)&buffer[4] == 0xbaba)
    {
        /* has calirationed */

    	memcpy(&gui_dev_ops_g()->gui_touch_ops_g.touch_cali_msg,buffer,16);

    	return OK;
    }else
    {
    	gui_touch_calibration((touch_msg_def *)&buffer);

    	memcpy(&gui_dev_ops_g()->gui_touch_ops_g.touch_cali_msg,buffer,16);

    	*(int *)&buffer[4] = 0xbaba;

    	if(write(file_touch,(const char *)&buffer,sizeof(buffer)) == OK)
    	{
    		printf_d("touch cali save ok\n");
    		return OK;
    	}else
    	{
    		printf_d("touch cali save fail\n");
    		return ERR;
    	}
    }
}

int gui_touch_calibration(touch_msg_def * touch_msg)
{
    unsigned short x_k = 0,x_d = 0,y_k = 0,y_d = 0;
    unsigned short x_size,y_size;
    float cali_buffer[4];
    const char * show_msg1 = "tft touch pad calibration";
    const char * show_msg2 = "please touch the '+'";
    const char * show_msg3 = "fail try again";
    const char * show_msg4 = "ok";
    /* start calibration  */

    /* clear lcd with while */

    x_size = gui_dev_ops_g()->gui_device_msg.xsize;
    y_size = gui_dev_ops_g()->gui_device_msg.ysize;

    gui_dev_ops_g()->gui_dev_ops_g.fill_dect(0,0,y_size,x_size,0xffff);

    /* show some msg */

    GUI_DISPLAY_STRING((x_size - strlen(show_msg1))/2,y_size/2-16,show_msg1,0x0,GUI_DIS_STRING_MODE_TRANS);
    GUI_DISPLAY_STRING((x_size - strlen(show_msg2))/2,y_size/2- 0,show_msg2,0x0,GUI_DIS_STRING_MODE_TRANS);
    /* draw a big point at (15 , 15) */

    gui_dev_ops_g()->gui_dev_ops_g.set_line(10,15,20,15,0x0);
    gui_dev_ops_g()->gui_dev_ops_g.set_line(15,10,15,20,0x0);

    while(!(x_k && y_k))
    {
    	x_k = gui_dev_ops_g()->gui_touch_ops_g.measure_x();
    	y_k = gui_dev_ops_g()->gui_touch_ops_g.measure_y();
    }

    gui_dev_ops_g()->gui_dev_ops_g.set_line(10,15,20,15,0xffff);
    gui_dev_ops_g()->gui_dev_ops_g.set_line(15,10,15,20,0xffff);

    while(gui_dev_ops_g()->gui_touch_ops_g.measure_x()); // wait press off

    gui_dev_ops_g()->gui_dev_ops_g.set_line(x_size-15-5,y_size-15,x_size-10,y_size-15,0x0);
    gui_dev_ops_g()->gui_dev_ops_g.set_line(x_size-15,y_size-15-5,x_size-15,y_size-10,0x0);

    while(!(x_d && y_d))
    {
    	x_d = gui_dev_ops_g()->gui_touch_ops_g.measure_x();
    	y_d = gui_dev_ops_g()->gui_touch_ops_g.measure_y();
    }

    gui_dev_ops_g()->gui_dev_ops_g.set_line(x_size-15-5,y_size-15,x_size-10,y_size-15,0xffff);
    gui_dev_ops_g()->gui_dev_ops_g.set_line(x_size-15,y_size-15-5,x_size-15,y_size-10,0xffff);

    while(gui_dev_ops_g()->gui_touch_ops_g.measure_x()); // wait press off

    cali_buffer[0] = (float)(x_size-30)/(float)((short)x_d-(short)x_k); // x_k
    cali_buffer[1] = 15.0f - cali_buffer[0] * (float)x_k;//  x_d

    cali_buffer[2] = (float)(y_size-30)/(float)((short)y_d-(short)y_k);// y_k
    cali_buffer[3] = 15.0f - cali_buffer[2] * (float)y_k;// y_d

    /* verify */

    gui_dev_ops_g()->gui_dev_ops_g.set_line(x_size-15-5,15,x_size-10,15,0x0);
    gui_dev_ops_g()->gui_dev_ops_g.set_line(x_size-15,15-5,x_size-15,20,0x0);

    x_d = 0;
    y_d = 0;
    while(!(x_d && y_d))
    {
		x_d = gui_dev_ops_g()->gui_touch_ops_g.measure_x();
		y_d = gui_dev_ops_g()->gui_touch_ops_g.measure_y();
    }

    if(((int)(x_d * cali_buffer[0] + cali_buffer[1]) >= x_size - 15 - 5) &&
      ((int)(x_d * cali_buffer[0] + cali_buffer[1]) <= x_size - 10) &&
	  ((int)(y_d * cali_buffer[2] + cali_buffer[3]) >= 15 - 5) &&
	  ((int)(y_d * cali_buffer[2] + cali_buffer[3]) <= 20))
    {
    	 GUI_DISPLAY_STRING((x_size - strlen(show_msg3))/2,y_size/2+16,show_msg3,0x0,GUI_DIS_STRING_MODE_TRANS);
         memcpy(touch_msg,cali_buffer,sizeof(touch_msg_def));
         printf_d("touch calibration ok\n");
         return OK;
    }else
    {
    	 GUI_DISPLAY_STRING((x_size - strlen(show_msg4))/2,y_size/2+16,show_msg4,0x0,GUI_DIS_STRING_MODE_TRANS);
    	 printf_d("touch calibration err\n");
    	 return ERR;
    }
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

int gui_touch_dev_register(unsigned short width,unsigned short height , unsigned short (*read_x)(void),unsigned short (*read_y)(void))
{
	gui_device_g.gui_touch_ops_g.x_size =     width;
	gui_device_g.gui_touch_ops_g.y_size =    height;
	gui_device_g.gui_touch_ops_g.measure_x = read_x;
	gui_device_g.gui_touch_ops_g.measure_y = read_y;
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


















