/*
 * led_gui.c
 *
 *  Created on: 2016��5��14��
 *      Author: Administrator
 */

/*
 * led_gui.c
 *
 *  Created on: 2016��5��14��
 *      Author: Administrator
 */
#include "fs.h"
#include "gui.h"
#include "button.h"

int led_gui_callback(enum event_type event,void *data);

struct gui_msg_t led_gui_msg = {
	100,     /* x position */
	200,     /* y position */
	50,     /* x size     */
	30,     /* y size     */
	"led",  /* caption    */
	1       /* init mode  */
};

struct nxgui_object led_gui_object = {
	NULL,
	button,
	&led_gui_msg,
	led_gui_callback
};



int led_gui_callback(enum event_type event,void *data)
{
// 	extern int lcd_fd;
// 	switch(event)
// 	{
// 		case onfocus:
// 		    write(lcd_fd,"ledonfocus",1);
// 			break;
// 		case losefocus:
// 			write(lcd_fd,"ledlosefocus",1);
// 			break;
// 		default:break;
// 	}
	return 0;
}












