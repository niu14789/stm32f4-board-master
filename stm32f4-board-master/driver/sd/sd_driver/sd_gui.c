/*
 * sd_gui.c
 *
 *  Created on: 2016��5��14��
 *      Author: Administrator
 */




/*
 * sd_gui.c
 *
 *  Created on: 2016��5��14��
 *      Author: Administrator
 */

/*
 * sd_gui.c
 *
 *  Created on: 2016��5��14��
 *      Author: Administrator
 */
#include "fs.h"
#include "gui.h"
#include "button.h"

int sd_gui_callback(enum event_type event,void *data);

struct gui_msg_t sd_gui_msg = {
	100,     /* x position */
	100,     /* y position */
	50,     /* x size     */
	30,     /* y size     */
	"sd",  /* caption    */
	1       /* init mode  */
};

struct nxgui_object sd_gui_object={
	NULL,
	button,
	&sd_gui_msg,
	sd_gui_callback
};

int sd_gui_callback(enum event_type event,void *data)
{
	extern int lcd_fd;
	switch(event)
	{
		case onfocus:
		    write(lcd_fd,"sdonfocus",1);
			break;
		case losefocus:
			write(lcd_fd,"sdlosefocus",1);
			break;
		default:break;
	}
	return 0;
}













