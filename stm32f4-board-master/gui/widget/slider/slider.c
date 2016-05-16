/*
 * slider.c
 *
 *  Created on: 2016Äê5ÔÂ14ÈÕ
 *      Author: Administrator
 */
#include "fs.h"
#include "lcd_hw.h"
#include "string.h"


extern void LCD_DrawLine(uint16_t _usX1 , uint16_t _usY1 , uint16_t _usX2 , uint16_t _usY2 , uint16_t _usColor);
extern void LCD_Fill_Rect(uint16_t _usX, uint16_t _usY, uint16_t _usHeight, uint16_t _usWidth, uint16_t _usColor);

struct rgb{
unsigned char r;
unsigned char g;
unsigned char b;
};


#define SLIDER_WIT 10
#define SLIDER_HIG 20

extern void LCD_DrawCircle(uint16_t _usX, uint16_t _usY, uint16_t _usRadius, uint16_t _usColor);

void slider_create(uint16_t x,uint16_t y,uint16_t x_size,uint16_t y_size,uint16_t focus)
{
	struct rgb color[10];
int i,z=0;
	if(1)
	{
		color[0].r = color[0].g = color[0].b = 176;
		color[1].r = color[1].g = color[1].b = 231;
		color[2].r = color[2].g = color[2].b = 252;
	}
	
	LCD_DrawLine(x,y,x+x_size,y,RGB(color[0].r , color[0].g ,color[0].b));
	LCD_DrawLine(x,y+1,x+x_size,y+1,RGB(color[1].r , color[1].g ,color[1].b));
	LCD_DrawLine(x,y+2,x+x_size,y+2,RGB(color[1].r , color[1].g ,color[1].b));
	LCD_DrawLine(x,y+3,x+x_size,y+3,RGB(color[2].r , color[2].g ,color[2].b));
	
	for(i=0;i<8;i++)
	{
	  LCD_DrawCircle(x+20,y+1,8-i,RGB(215-z,215-z,215-z));
	  z+=7;
	}



}














