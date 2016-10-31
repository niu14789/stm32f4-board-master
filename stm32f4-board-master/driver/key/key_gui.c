/*
 * key_gui.c
 *
 *  Created on: 2016��5��14��
 *      Author: Administrator
 */

/*
 * key_gui.c
 *
 *  Created on: 2016��5��14��
 *      Author: Administrator
 */
#include "fs.h"
#include "gui.h"
#include "stdio.h"

/* about windows */
#include "window.h"
#include "gui.h"
#include "button.h"
static window_hwnd  window_handler_key,window_handler_t;
/* ------------- */

int key_gui_callback(enum event_type event,void *data);

struct gui_msg_t key_gui_msg = {
	70,        /* x position */
	50,        /* y position */
	40,        /* x size     */
	20,        /* y size     */
	"unclock",     /* caption    */
	FOCUS_OFF  /* init mode  */
};

struct nxgui_object key_gui_object = {
	NULL,
	button,
	&key_gui_msg,
	key_gui_callback
};



int key_gui_callback(enum event_type event,void *data)
{
	static unsigned char flag = 0;

	gui_message gui_msg_tmp =
	{
		100,
		80,
		150,
		120,
		"main_window",
		"/sdcard/main.bmp",
		0,
		0,
		__GUI_WIDGET_MODE_0     | /* pic mode , with caption */
		__GUI_WIDGET_TYPE_OCT   | /* right angle mode */
		__GUI_WIDGET_FRAME_NONE | /* without frame */
		__GUI_WIDGET_THEME_0    | /* theme 0 */
		__GUI_WIDGET_HANDLE      /* no ues */
	};

	struct gui_msg_t b1_msg = {
			10,
			80,
			50,
			30,
	};

	if(flag != 0)
	{
		return ERR;
	}
	flag = 1;
	/* create the default create */
	window_create(&window_handler_key,&gui_msg_tmp,NULL);

	button_create(&window_handler_key,&b1_msg,NULL);

	b1_msg.x = 80;

	button_create(&window_handler_key,&b1_msg,NULL);

	refresh();

	gui_msg_tmp.x = 120;
	gui_msg_tmp.y = 20;
	gui_msg_tmp.xsize = 170;
	gui_msg_tmp.ysize = 80;

	b1_msg.x = 10;
	b1_msg.y = 40;

	window_create(&window_handler_t,&gui_msg_tmp,NULL);
	button_create(&window_handler_t,&b1_msg,NULL);
	b1_msg.x = 110;
	button_create(&window_handler_t,&b1_msg,NULL);
	refresh();

	return 0;
}












