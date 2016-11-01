/*
 * window.c
 *
 *  Created on: 2016骞�5鏈�26鏃�
 *      Author: YJ-User17
 */

#include "fs.h"
#include "gui.h"
#include "string.h"
#include "lcd_hw.h"
#include "gui_config.h"
#include "window.h"

const char bitmap_frame_black[8] = { 0x07 , 0x18 , 0x20 , 0x40 , 0x40 , 0x80 , 0x80 , 0x80 };

const char bitmap_frmae_white[8] = { 0x00 , 0x07 , 0x18 , 0x20 , 0x20 , 0x40 , 0x40 , 0x40 };

extern int gui_draw_bmp( const struct gui_msg_t * p_msg , unsigned int __MODE__);


/* should be macro */
/* as use the handler */
window_hwnd  window_handler;

struct gui_operations window_ops;

int window_create_asparent( struct gui_msg_t * p_msg )
{
	int i , j;
    unsigned char rgb_color_r,rgb_color_g,rgb_color_b;
	gui_device *gui_device_t;

	gui_device_t = gui_dev_ops_g();
		/* window without caption */

	gui_device_t->gui_dev_ops_g.fill_dect(p_msg->x + 2 ,
			                              p_msg->y + 3 ,
			                              p_msg->ysize - 5,
										  2,
										  RGB(145,182,210));

	gui_device_t->gui_dev_ops_g.fill_dect(p_msg->x + p_msg->xsize -  4,
										  p_msg->y + 3 ,
										  p_msg->ysize - 5,
										  2,
										  RGB(145,182,210));


    for( j = 0 ; j < 8 ; j++ )
    {
    	for( i = 0 ; i < 8 ; i++ )
    	{
    		if(bitmap_frame_black[j] & (0x80 >> i))
    		{
    			gui_device_t->gui_dev_ops_g.put_pixel(p_msg->x + i , p_msg->y + j,0);//black
    			gui_device_t->gui_dev_ops_g.put_pixel(p_msg->x + p_msg->xsize - i , p_msg->y + j,0);//black
    		}

     		if(bitmap_frmae_white[j] & (0x80 >> i))
			{
				gui_device_t->gui_dev_ops_g.put_pixel(p_msg->x + i , p_msg->y + j,0xffff);//black
				gui_device_t->gui_dev_ops_g.put_pixel(p_msg->x + p_msg->xsize - i , p_msg->y + j,0xffff);//black
			}

    	}
    }
		
    gui_device_t->gui_dev_ops_g.set_line( p_msg->x , p_msg->y + 8,
    		                              p_msg->x , p_msg->y + p_msg->ysize ,
										  0x0);
		
    gui_device_t->gui_dev_ops_g.set_line( p_msg->x + p_msg->xsize , p_msg->y + 8,
    		                              p_msg->x + p_msg->xsize , p_msg->y + p_msg->ysize ,
										  0x0);


    gui_device_t->gui_dev_ops_g.set_line( p_msg->x + 1 , p_msg->y + 8,
										  p_msg->x + 1 , p_msg->y + p_msg->ysize ,
										  0xffff);

    gui_device_t->gui_dev_ops_g.set_line( p_msg->x + p_msg->xsize - 1, p_msg->y + 8,
										  p_msg->x + p_msg->xsize - 1, p_msg->y + p_msg->ysize ,
										  0xffff);

    gui_device_t->gui_dev_ops_g.set_line( p_msg->x + 1, p_msg->y + p_msg->ysize - 1,
										  p_msg->x + p_msg->xsize - 1, p_msg->y + p_msg->ysize - 1,
										  0xffff);
		
    gui_device_t->gui_dev_ops_g.set_line( p_msg->x , p_msg->y + p_msg->ysize,
										  p_msg->x + p_msg->xsize , p_msg->y + p_msg->ysize,
										  0x0);
    gui_device_t->gui_dev_ops_g.set_line( p_msg->x + 5 , p_msg->y + 18,
										  p_msg->x + p_msg->xsize - 5,  p_msg->y + 18,
										  RGB(145,182,210));

    gui_device_t->gui_dev_ops_g.set_line( p_msg->x + 5 , p_msg->y + p_msg->ysize - 3,
										  p_msg->x + p_msg->xsize - 5,  p_msg->y+p_msg->ysize - 3,
										  RGB(145,182,210));
    gui_device_t->gui_dev_ops_g.set_line( p_msg->x + 5 , p_msg->y + p_msg->ysize - 2,
										  p_msg->x + p_msg->xsize - 5,  p_msg->y+p_msg->ysize - 2,
										  RGB(145,182,210));

    gui_device_t->gui_dev_ops_g.set_line( p_msg->x + 8 , p_msg->y,
										  p_msg->x + p_msg->xsize - 8,  p_msg->y,
										  0x0);

    gui_device_t->gui_dev_ops_g.set_line( p_msg->x + 8 , p_msg->y + 1,
										  p_msg->x + p_msg->xsize - 8,  p_msg->y + 1,
										  0xffff);

    rgb_color_r = 154;
    rgb_color_g = 182;
    rgb_color_b = 210;

    for(i=0;i<16;i++)
    {
    	 gui_device_t->gui_dev_ops_g.set_line( p_msg->x + 5 , p_msg->y + 2 + i,
											   p_msg->x + p_msg->xsize - 5,  p_msg->y + 2 + i,
											   RGB(rgb_color_r,rgb_color_g,rgb_color_b));
    	    rgb_color_r += 3;
    	    rgb_color_g += 3;
    	    rgb_color_b += 3;
    }


    gui_device_t->gui_dev_ops_g.fill_dect( p_msg->x + 5 ,  p_msg->y + 19 ,
    		p_msg->ysize - 19 - 4 ,p_msg->xsize - 10,
			RGB(192,192,192));

    return OK;
}


int window_show(struct gui_handler * g_hmd)
{
	if(g_hmd->widget_msg.mode & (__GUI_WIDGET_MODE_2))
	{
		gui_draw_bmp(&g_hmd->widget_msg,0);
	}else if(g_hmd->widget_msg.mode & (__GUI_WIDGET_MODE_0))
	{
		window_create_asparent(&g_hmd->widget_msg);
	}

	return 0;//window_create_asparent(p_msg->x,p_msg->y,p_msg->xsize,p_msg->ysize,p_msg->caption,p_msg->mode);
}


window_hwnd * window_create(window_hwnd * hwnd,struct gui_msg_t*p_msg,int (*callback)(enum event_type,void *data))
{
	/* widget message */
	memcpy(&hwnd->window.widget_msg,p_msg,sizeof(window_handler.window.widget_msg));
	hwnd->window.gui_ops = &window_ops;
	hwnd->window.callback = callback;
	hwnd->window.id = 1;
	hwnd->window.link = NULL;
	hwnd->window.status = p_msg->mode;

	/*
	 *   reserve function
	 */
    window_insert(hwnd);
	/*
	 *
	 */
    return hwnd;
}

int window_move(struct gui_msg_t*p_msg,void *data)
{
 
	unsigned short *p_dx = (unsigned short *)data;

	p_msg->x += 	p_dx[0];
	p_msg->y += 	p_dx[1];
	
	 refresh();
	
	return 0;
}

int window_event_process(struct gui_handler * h_hmd,enum event_type event , void * data)
{
	switch(event)
	{
	case onfocus:

		break;
	case widget_move:
		window_move(&h_hmd->widget_msg,data);
		break;
	default:
		break;
	}
	return 0;
}
struct gui_operations window_ops = {
		window_create,
		window_show,
		window_event_process
};

int window_insert(window_hwnd * hwnd)
{
	window_hwnd * root;

	root =  handler_current();

	if( root == NULL )
	{
		/* first insert */
		set_handler_current(hwnd);

		return OK;
	}

	/* as child */
	if( hwnd->window.widget_msg.mode & __GUI_WIDGET_HANDLE )
	{
		/* as child */
		root->child = hwnd;
		hwnd->parent = root;
		set_handler_current(hwnd);
	}else
	{
		/* ad same class */
		root->same_next = hwnd;
		hwnd->same_pre = root;
		set_handler_current(hwnd);
	}

    return OK;
}

int window_delete(window_hwnd * hwnd)
{
return OK;
}


















