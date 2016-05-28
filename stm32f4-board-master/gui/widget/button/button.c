/*
 * button.c
 *
 *  Created on: 2016��5��11��
 *      Author: Administrator
 */


#include "fs.h"
#include "lcd_hw.h"
#include "string.h"
#include "gui.h"
/* memory  manager */

struct gui_handler handler[10];
static unsigned char handler_cnt = 0;

/*                 */

extern void LCD_DrawLine(uint16_t _usX1 , uint16_t _usY1 , uint16_t _usX2 , uint16_t _usY2 , uint16_t _usColor);
extern void LCD_Fill_Rect(uint16_t _usX, uint16_t _usY, uint16_t _usHeight, uint16_t _usWidth, uint16_t _usColor);
struct gui_handler * button_create(struct gui_msg_t*p_msg,int (*callback)(enum event_type,void *data));
int button_onfocus(struct gui_msg_t*p_msg);
int button_losefocus(struct gui_msg_t*p_msg);
int button_show(struct gui_msg_t*p_msg);

struct color_rgb{
char r;
char g;
char b;
};

int button_create_aschild(uint16_t BUTTON_POS_X,uint16_t BUTTON_POS_Y,uint16_t BUTTON_SIZE_X,uint16_t BUTTON_SIZE_Y,char *caption,char mode )
{
	unsigned short len = 0;
	char event = mode;
	FONT_T _FONT=
	{
		0,
		0x0,
		CL_MASK,
		0	
	};
	struct color_rgb color[10];
	if(event==0)
	{
		color[0].r =color[0].g=color[0].b=112;
		color[1].r =color[1].g=color[1].b=144;
		color[2].r =color[2].g=color[2].b=119;
		color[3].r =color[3].g=color[3].b=226;
		color[4].r =color[4].g=color[4].b=150;
		color[5].r =color[5].g=color[5].b=120;
		color[6].r =color[6].g=color[6].b=200;
	}
	else if(event == 1)
	{
		color[0].r= 66;color[0].g=131;color[0].b=179;
		color[1].r=102;color[1].g=147;color[1].b=181;
		color[2].r=66;color[2].g=131;color[2].b=179;
		color[3].r=223;color[3].g=235;color[3].b=243;
		color[4].r=222;color[4].g=242;color[4].b=252;
		color[5].r=181;color[5].g=226;color[5].b=250;
		color[6].r=236;color[6].g=248;color[6].b=254;
	}
	else
	{
	}
	LCD_DrawLine(BUTTON_POS_X+3,BUTTON_POS_Y,BUTTON_POS_X+BUTTON_SIZE_X-3,BUTTON_POS_Y,RGB(color[0].r,color[0].g,color[0].b));
	LCD_DrawLine(BUTTON_POS_X,BUTTON_POS_Y+3,BUTTON_POS_X,BUTTON_POS_Y+BUTTON_SIZE_Y-3,RGB(color[0].r,color[0].g,color[0].b));
	LCD_DrawLine(BUTTON_POS_X+3,
	             BUTTON_POS_Y+BUTTON_SIZE_Y,
	             BUTTON_POS_X+BUTTON_SIZE_X-3,
	             BUTTON_POS_Y+BUTTON_SIZE_Y,
	             RGB(color[0].r,color[0].g,color[0].b));
	LCD_DrawLine( BUTTON_POS_X+BUTTON_SIZE_X,
								BUTTON_POS_Y+3,
								BUTTON_POS_X+BUTTON_SIZE_X,
								BUTTON_POS_Y+BUTTON_SIZE_Y-3,
								RGB(color[0].r,color[0].g,color[0].b));
	
	LCD_PutPixel(BUTTON_POS_X+1,BUTTON_POS_Y,RGB(color[1].r,color[1].g,color[1].b));
	LCD_PutPixel(BUTTON_POS_X,BUTTON_POS_Y+1,RGB(color[1].r,color[1].g,color[1].b));
	LCD_PutPixel(BUTTON_POS_X+1,BUTTON_POS_Y+1,RGB(color[1].r,color[1].g,color[1].b));
	
	LCD_PutPixel(BUTTON_POS_X+2,BUTTON_POS_Y,RGB(color[2].r,color[2].g,color[2].b));
	LCD_PutPixel(BUTTON_POS_X,BUTTON_POS_Y+2,RGB(color[2].r,color[2].g,color[2].b));
	
	LCD_PutPixel(BUTTON_POS_X+2,BUTTON_POS_Y+1,RGB(color[3].r,color[3].g,color[3].b));
	LCD_PutPixel(BUTTON_POS_X+1,BUTTON_POS_Y+2,RGB(color[3].r,color[3].g,color[3].b));
	
	/*---------*/
	
	LCD_PutPixel(BUTTON_POS_X+1,BUTTON_POS_Y+BUTTON_SIZE_Y,RGB(color[1].r,color[1].g,color[1].b));
	LCD_PutPixel(BUTTON_POS_X,BUTTON_POS_Y+BUTTON_SIZE_Y-1,RGB(color[1].r,color[1].g,color[1].b));
	LCD_PutPixel(BUTTON_POS_X+1,BUTTON_POS_Y+BUTTON_SIZE_Y-1,RGB(color[1].r,color[1].g,color[1].b));
	
	LCD_PutPixel(BUTTON_POS_X+2,BUTTON_POS_Y+BUTTON_SIZE_Y,RGB(color[2].r,color[2].g,color[2].b));
	LCD_PutPixel(BUTTON_POS_X,BUTTON_POS_Y+BUTTON_SIZE_Y-2,RGB(color[2].r,color[2].g,color[2].b));
	
	LCD_PutPixel(BUTTON_POS_X+2,BUTTON_POS_Y+BUTTON_SIZE_Y-1,RGB(color[3].r,color[3].g,color[3].b));
	LCD_PutPixel(BUTTON_POS_X+1,BUTTON_POS_Y+BUTTON_SIZE_Y-2,RGB(color[3].r,color[3].g,color[3].b));
	
	/*--------*/
	LCD_PutPixel(BUTTON_POS_X+BUTTON_SIZE_X-1,BUTTON_POS_Y+BUTTON_SIZE_Y,RGB(color[1].r,color[1].g,color[1].b));
	LCD_PutPixel(BUTTON_POS_X+BUTTON_SIZE_X,BUTTON_POS_Y-1+BUTTON_SIZE_Y,RGB(color[1].r,color[1].g,color[1].b));
	LCD_PutPixel(BUTTON_POS_X+BUTTON_SIZE_X-1,BUTTON_POS_Y-1+BUTTON_SIZE_Y,RGB(color[1].r,color[1].g,color[1].b));
	
	LCD_PutPixel(BUTTON_POS_X+BUTTON_SIZE_X-2,BUTTON_POS_Y+BUTTON_SIZE_Y,RGB(color[2].r,color[2].g,color[2].b));
	LCD_PutPixel(BUTTON_POS_X+BUTTON_SIZE_X,BUTTON_POS_Y-2+BUTTON_SIZE_Y,RGB(color[2].r,color[2].g,color[2].b));
	
	LCD_PutPixel(BUTTON_POS_X+BUTTON_SIZE_X-2,BUTTON_POS_Y+BUTTON_SIZE_Y-1,RGB(color[3].r,color[3].g,color[3].b));
	LCD_PutPixel(BUTTON_POS_X+BUTTON_SIZE_X-1,BUTTON_POS_Y+BUTTON_SIZE_Y-2,RGB(color[3].r,color[3].g,color[3].b));
	/*--*/
	LCD_PutPixel(BUTTON_POS_X+BUTTON_SIZE_X-1,BUTTON_POS_Y,RGB(color[1].r,color[1].g,color[1].b));
	LCD_PutPixel(BUTTON_POS_X+BUTTON_SIZE_X,BUTTON_POS_Y+1,RGB(color[1].r,color[1].g,color[1].b));
	LCD_PutPixel(BUTTON_POS_X+BUTTON_SIZE_X-1,BUTTON_POS_Y+1,RGB(color[1].r,color[1].g,color[1].b));
	
	LCD_PutPixel(BUTTON_POS_X+BUTTON_SIZE_X-2,BUTTON_POS_Y,RGB(color[2].r,color[2].g,color[2].b));
	LCD_PutPixel(BUTTON_POS_X+BUTTON_SIZE_X,BUTTON_POS_Y+2,RGB(color[2].r,color[2].g,color[2].b));
	/*----------*/
	LCD_PutPixel(BUTTON_POS_X+BUTTON_SIZE_X-2,BUTTON_POS_Y+1,RGB(color[3].r,color[3].g,color[3].b));
	LCD_PutPixel(BUTTON_POS_X+BUTTON_SIZE_X-1,BUTTON_POS_Y+2,RGB(color[3].r,color[3].g,color[3].b));
	/*--*/
	LCD_Fill_Rect(BUTTON_POS_X+2,BUTTON_POS_Y+2,BUTTON_SIZE_Y/2-2,BUTTON_SIZE_X-3,RGB(color[4].r,color[4].g,color[4].b));
	LCD_Fill_Rect(BUTTON_POS_X+2,BUTTON_POS_Y+BUTTON_SIZE_Y/2,BUTTON_SIZE_Y/2-1,BUTTON_SIZE_X-3,RGB(color[5].r,color[5].g,color[5].b));
	
	LCD_PutPixel(BUTTON_POS_X+2, BUTTON_POS_Y+2, RGB(color[6].r,color[6].g,color[6].b));
	LCD_PutPixel(BUTTON_POS_X+BUTTON_SIZE_X-2, BUTTON_POS_Y+2,RGB(color[6].r,color[6].g,color[6].b));
	LCD_PutPixel(BUTTON_POS_X+BUTTON_SIZE_X-2, BUTTON_POS_Y+BUTTON_SIZE_Y-2,RGB(color[6].r,color[6].g,color[6].b));
	LCD_PutPixel(BUTTON_POS_X+2, BUTTON_POS_Y+BUTTON_SIZE_Y-2,RGB(color[6].r,color[6].g,color[6].b));

    LCD_DrawLine(BUTTON_POS_X+3,
	             BUTTON_POS_Y+1,
	             BUTTON_POS_X+BUTTON_SIZE_X-3,
	             BUTTON_POS_Y+1,
	             RGB(color[6].r,color[6].g,color[6].b));
							 
	LCD_DrawLine(BUTTON_POS_X+1,
	             BUTTON_POS_Y+3,
	             BUTTON_POS_X+1,
	             BUTTON_POS_Y+BUTTON_SIZE_Y-3,
	             RGB(color[6].r,color[6].g,color[6].b));
							 
	LCD_DrawLine(BUTTON_POS_X+BUTTON_SIZE_X-1,
	             BUTTON_POS_Y+3,
	             BUTTON_POS_X+BUTTON_SIZE_X-1,
	             BUTTON_POS_Y+BUTTON_SIZE_Y-3,
	             RGB(color[6].r,color[6].g,color[6].b));
	
	LCD_DrawLine(BUTTON_POS_X+3,
	             BUTTON_POS_Y+BUTTON_SIZE_Y-1,
	             BUTTON_POS_X+BUTTON_SIZE_X-3,
	             BUTTON_POS_Y+BUTTON_SIZE_Y-1,
	             RGB(color[6].r,color[6].g,color[6].b));
	len = strlen(caption);
	
	if(len>BUTTON_SIZE_X/8)
	  return 1;
	
	LCD_DispStr(BUTTON_POS_X+BUTTON_SIZE_X/2-(len*8)/2,BUTTON_POS_Y+BUTTON_SIZE_Y/2-8,caption,&_FONT);	 
	
	return 0;
}

#define MOVE_RECT_SIXE 15
void rect_move(unsigned short next_xpos,unsigned short next_ypos,unsigned color)
{
	static unsigned short gbuf[MOVE_RECT_SIXE*MOVE_RECT_SIXE];
	static short last_xpost = 0,last_ypost = 0;
	static char first_flag = 0;
	int i;
	int pixel_cnt = 0;
	
	if(!first_flag) /* first time ? */
	{
		first_flag = 1;
		for(i=0,pixel_cnt=0;i<MOVE_RECT_SIXE*MOVE_RECT_SIXE;i++)
		{
			gbuf[pixel_cnt] = LCD_GetPixel(next_xpos+pixel_cnt/MOVE_RECT_SIXE,next_ypos+pixel_cnt%MOVE_RECT_SIXE);
			pixel_cnt++;
		}

		for(i=0,pixel_cnt=0;i<MOVE_RECT_SIXE*MOVE_RECT_SIXE;i++)
		{
			LCD_PutPixel(next_xpos+pixel_cnt/MOVE_RECT_SIXE,next_ypos+pixel_cnt%MOVE_RECT_SIXE,color);
			pixel_cnt++;
		}
	}
	else
	{
			for(i=0,pixel_cnt=0;i<MOVE_RECT_SIXE*MOVE_RECT_SIXE;i++)/* put last pixel */
			{
			    LCD_PutPixel(last_xpost+pixel_cnt/MOVE_RECT_SIXE,last_ypost+pixel_cnt%MOVE_RECT_SIXE,gbuf[pixel_cnt]);
				pixel_cnt++;
			}

			for(i=0,pixel_cnt=0;i<MOVE_RECT_SIXE*MOVE_RECT_SIXE;i++)/* get the new field */
			{
				gbuf[pixel_cnt] = LCD_GetPixel(next_xpos+pixel_cnt/MOVE_RECT_SIXE,next_ypos+pixel_cnt%MOVE_RECT_SIXE);
				pixel_cnt++;
			}

			for(i=0,pixel_cnt=0;i<MOVE_RECT_SIXE*MOVE_RECT_SIXE;i++)
			{
				LCD_PutPixel(next_xpos+pixel_cnt/MOVE_RECT_SIXE,next_ypos+pixel_cnt%MOVE_RECT_SIXE,color);
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
struct gui_handler * button_create(struct gui_msg_t*p_msg,int (*callback)(enum event_type,void *data))
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

	handler_insert(&handler[now]);

	return &handler[now];
}

int button_show(struct gui_msg_t*p_msg)
{
	return button_create_aschild(p_msg->x,p_msg->y,p_msg->xsize,p_msg->ysize,p_msg->caption,p_msg->mode);
}

/* widget on focus */
int button_onfocus(struct gui_msg_t*p_msg)
{
	return button_create_aschild(p_msg->x,p_msg->y,p_msg->xsize,p_msg->ysize,p_msg->caption,1);
}
/* widget lose focus */
int button_losefocus(struct gui_msg_t*p_msg)
{
	return button_create_aschild(p_msg->x,p_msg->y,p_msg->xsize,p_msg->ysize,p_msg->caption,0);
}










