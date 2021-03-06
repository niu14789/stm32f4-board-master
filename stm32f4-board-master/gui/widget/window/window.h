/*
 * window.h
 *
 *  Created on: 2016骞�5鏈�26鏃�
 *      Author: YJ-User17
 */

#ifndef GUI_WINDOW_WINDOW_H_
#define GUI_WINDOW_WINDOW_H_


window_hwnd * window_create(window_hwnd * hwnd,struct gui_msg_t*p_msg,int (*callback)(enum event_type,void *data));
int window_create_asparent( struct gui_msg_t * p_msg,unsigned char event);
int window_insert(window_hwnd * hwnd);
static int window_refresh(void);
int refresh_now(window_hwnd * now);
#endif /* GUI_WINDOW_WINDOW_H_ */
