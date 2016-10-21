/*
 * button.c
 *
 *  Created on: 2016��5��11��
 *      Author: Administrator
 */


#include "fs.h"
#include "string.h"
#include "gui.h"
#include "gui_config.h"
#include "button.h"

/* memory  manager */
#define RGB(R,G,B)	(((R >> 3) << 11) | ((G >> 2) << 5) | (B >> 3))
struct gui_handler handler[10];
static unsigned char handler_cnt = 0;

const char bitmap_button_black[4] = {0x00,0x30,0x40,0x40};
const char bitmap_button_white[4] = {0x00,0x00,0x30,0x20};

int button_create_aschild(struct gui_handler * h_hmd)
{
		gui_device *gui_device_t;
		int i,j;
			unsigned short button_real_width = 0, button_real_height = 0;
			unsigned short x_b,y_b,x_size,y_size,half_size;
		gui_device_t = gui_dev_ops_g();

		if( ((h_hmd->widget_msg.x - h_hmd->parent_window->window.widget_msg.x) > h_hmd->parent_window->window.widget_msg.xsize) ||
			((h_hmd->widget_msg.y - h_hmd->parent_window->window.widget_msg.y) > h_hmd->parent_window->window.widget_msg.ysize)	)
		{
			printf_d("button position out of the parent window\n");
			return ERR;
		}

		if(h_hmd->parent_window->window.widget_msg.xsize > (h_hmd->widget_msg.x + h_hmd->widget_msg.xsize) )
		{
			 button_real_width = h_hmd->widget_msg.xsize;
		}else
		{
			button_real_width = h_hmd->parent_window->window.widget_msg.xsize - h_hmd->widget_msg.x;
		}

		if(h_hmd->parent_window->window.widget_msg.ysize > (h_hmd->widget_msg.y + h_hmd->widget_msg.ysize) )
		{
			button_real_height = h_hmd->widget_msg.ysize;

		}else
		{
			button_real_height = h_hmd->parent_window->window.widget_msg.ysize - h_hmd->widget_msg.y;
		}

		x_b = h_hmd->parent_window->window.widget_msg.x + h_hmd->widget_msg.x;
		y_b = h_hmd->parent_window->window.widget_msg.y + h_hmd->widget_msg.y;

		x_size = h_hmd->widget_msg.xsize;
		y_size = h_hmd->widget_msg.ysize;

		half_size = (y_size - 4)/2;

		for(i=0;i<((y_size - 4)/2);i++)
		{
			gui_device_t->gui_dev_ops_g.set_line(x_b+2,y_b+2+i,x_size+x_b-2,y_b+2+i,RGB(243-i,243-i,243-i));

			gui_device_t->gui_dev_ops_g.set_line(x_b+2,y_b+2+i+half_size,x_size+x_b-2,y_b+2+i+half_size,RGB(223-i,223-i,223-i));
		}
	
    for(j=0;j<4;j++)
    {
    	for(i=0;i<4;i++)
    	{
    		if(bitmap_button_black[j] & (0x80 >> i))
    		{
      			gui_device_t->gui_dev_ops_g.put_pixel(x_b + i , y_b + j,RGB(112,112,112));//black
        		gui_device_t->gui_dev_ops_g.put_pixel(x_b + x_size - i , y_b + j,RGB(112,112,112));//black
        		gui_device_t->gui_dev_ops_g.put_pixel(x_b + i , y_size + y_b - j,RGB(112,112,112));//black
        		gui_device_t->gui_dev_ops_g.put_pixel(x_b + x_size - i , y_size + y_b - j,RGB(112,112,112));//black
    		}

    		if(bitmap_button_white[j] & (0x80 >> i))
    		{
      			gui_device_t->gui_dev_ops_g.put_pixel(x_b + i , y_b + j,RGB(70,216,251));//white
        		gui_device_t->gui_dev_ops_g.put_pixel(x_b + x_size - i , y_b + j,RGB(70,216,251));//white
        		gui_device_t->gui_dev_ops_g.put_pixel(x_b + i , y_size + y_b - j,RGB(70,216,251));//white
        		gui_device_t->gui_dev_ops_g.put_pixel(x_b + x_size - i , y_size + y_b - j,RGB(70,216,251));//white
    		}
    	}
    }

    gui_device_t->gui_dev_ops_g.set_line(x_b,y_b+4,x_b,y_size + y_b - 4,RGB(112,112,112));
    gui_device_t->gui_dev_ops_g.set_line(x_b+x_size,y_b+4,x_b+x_size,y_size + y_b - 4,RGB(112,112,112));

    gui_device_t->gui_dev_ops_g.set_line(x_b+1,y_b+4,x_b+1,y_size + y_b - 4,RGB(70,216,251));
    gui_device_t->gui_dev_ops_g.set_line(x_b+x_size-1,y_b+4,x_b+x_size-1,y_size + y_b - 4,RGB(70,216,251));


    gui_device_t->gui_dev_ops_g.set_line(x_b+4,y_b,x_size+x_b-4,y_b,RGB(112,112,112));
    gui_device_t->gui_dev_ops_g.set_line(x_b+4,y_b+y_size,x_size+x_b-4,y_size+y_b,RGB(112,112,112));

    gui_device_t->gui_dev_ops_g.set_line(x_b+4,y_b+1,x_size+x_b-4,y_b+1,RGB(70,216,251));
    gui_device_t->gui_dev_ops_g.set_line(x_b+4,y_b+y_size-1,x_size+x_b-4,y_size+y_b-1,RGB(70,216,251));

	return 0;
}

#define MOVE_RECT_SIXE   10

void rect_move(unsigned short next_xpos,unsigned short next_ypos,unsigned color)
{
	static unsigned short gbuf[MOVE_RECT_SIXE*MOVE_RECT_SIXE];
	static short last_xpost = 0,last_ypost = 0;
	static char first_flag = 0;
	int i;
	int pixel_cnt = 0;
	gui_device *gui_device_t;
	
	gui_device_t = gui_dev_ops_g();

	if(!first_flag) /* first time ? */
	{
		first_flag = 1;
		for(i=0,pixel_cnt=0;i<MOVE_RECT_SIXE*MOVE_RECT_SIXE;i++)
		{
			gbuf[pixel_cnt] = gui_device_t->gui_dev_ops_g.get_pixel(next_xpos+pixel_cnt/MOVE_RECT_SIXE,next_ypos+pixel_cnt%MOVE_RECT_SIXE);
			pixel_cnt++;
		}

		for(i=0,pixel_cnt=0;i<MOVE_RECT_SIXE*MOVE_RECT_SIXE;i++)
		{
			gui_device_t->gui_dev_ops_g.put_pixel(next_xpos+pixel_cnt/MOVE_RECT_SIXE,next_ypos+pixel_cnt%MOVE_RECT_SIXE,color);
			pixel_cnt++;
		}
	}
	else
	{
			for(i=0,pixel_cnt=0;i<MOVE_RECT_SIXE*MOVE_RECT_SIXE;i++)/* put last pixel */
			{
			    gui_device_t->gui_dev_ops_g.put_pixel(last_xpost+pixel_cnt/MOVE_RECT_SIXE,last_ypost+pixel_cnt%MOVE_RECT_SIXE,gbuf[pixel_cnt]);
				pixel_cnt++;
			}

			for(i=0,pixel_cnt=0;i<MOVE_RECT_SIXE*MOVE_RECT_SIXE;i++)/* get the new field */
			{
				gbuf[pixel_cnt] = gui_device_t->gui_dev_ops_g.get_pixel(next_xpos+pixel_cnt/MOVE_RECT_SIXE,next_ypos+pixel_cnt%MOVE_RECT_SIXE);
				pixel_cnt++;
			}

			for(i=0,pixel_cnt=0;i<MOVE_RECT_SIXE*MOVE_RECT_SIXE;i++)
			{
				gui_device_t->gui_dev_ops_g.put_pixel(next_xpos+pixel_cnt/MOVE_RECT_SIXE,next_ypos+pixel_cnt%MOVE_RECT_SIXE,color);
				pixel_cnt++;
			}
	}
	last_xpost = next_xpos;
	last_ypost  = next_ypos;
}

/* lcd_gui_draw_ops */
struct gui_operations button_draw_ops = {
	button_create,
	button_show,
	button_onfocus,
	button_losefocus,
};

/* widget create */
window_hwnd * button_create(window_hwnd * hwnd,struct gui_msg_t * p_msg,int (*callback)(enum event_type,void *data))
{
	unsigned char now = handler_cnt;
	/* copy the widget msg to handler */
	memcpy(&handler[now].widget_msg,p_msg,sizeof(handler[now].widget_msg));
	
	/* copy the handler.ops */
	handler[now].gui_ops = &button_draw_ops;
	/* callback */
	handler[now].callback = callback;
	/* ID no use */
	handler[now].id = 1;
	/* widget status */
	handler[now].status =  p_msg->mode;
	/* link */
	handler[now].link = NULL;

	/* template */
	handler_cnt++;
#if 1
	handler_insert(hwnd,&handler[now]);
#endif
	return NULL;
}

int button_show(struct gui_handler * g_hmd)
{
	return button_create_aschild(g_hmd);
}

/* widget on focus */
int button_onfocus(struct gui_msg_t*p_msg)
{
//	return button_create_aschild(p_msg->x,p_msg->y,p_msg->xsize,p_msg->ysize,p_msg->caption,1);
	return 0;
}
/* widget lose focus */
int button_losefocus(struct gui_msg_t*p_msg)
{
//	return button_create_aschild(p_msg->x,p_msg->y,p_msg->xsize,p_msg->ysize,p_msg->caption,0);
	return 0;
}











