/*
 * msg.h
 *
 *  Created on: 2016年11月2日
 *      Author: YJ-User17
 */

#ifndef GUI_MSG_MSG_H_
#define GUI_MSG_MSG_H_

int gui_send_msg(struct gui_handler* handler,enum event_type  event_type,void *data);
int gui_read_msg(char * data,unsigned int len);
int gui_send_msgl0(enum event_type event_type , unsigned short x_pos , unsigned short y_pos , unsigned short id , void *pri_data);
int gui_read_msgl0(char * data,unsigned int len);

#endif /* GUI_MSG_MSG_H_ */


