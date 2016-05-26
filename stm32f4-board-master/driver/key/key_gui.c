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

int key_gui_callback(enum event_type event,void *data);

struct gui_msg_t key_gui_msg = {
	300,        /* x position */
	185,        /* y position */
	80,        /* x size     */
	60,        /* y size     */
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
// 	extern int lcd_fd;
// 	switch(event)
// 	{
// 		case onfocus:
// 		    write(lcd_fd,"keyonfocus",1);
// 			break;
// 		case losefocus:
// 			write(lcd_fd,"keylosefocus",1);
// 			break;
// 		default:break;
// 	}
	char s_send[5]={0x53,0x00,0x02,0x11,0x66};
	printf(s_send);
	
	return 0;
}












