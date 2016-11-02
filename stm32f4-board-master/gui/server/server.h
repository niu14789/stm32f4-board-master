/*
 * server.h
 *
 *  Created on: 2016��5��15��
 *      Author: Administrator
 */

#ifndef __SERVER_H__
#define __SERVER_H__


int gui_server(void);
int gui_enevt_check(void);
int gui_event_check(void);
int gui_event_done(gui_msg *p_msg);
int gui_event_idle(void);
static int gui_revert_widget(struct gui_handler * p_gui_root,struct gui_handler * p_gui_same);
static int gui_with_in(struct gui_handler *gui_hander_root,unsigned short x,unsigned short y);
static window_hwnd * gui_find_window(window_hwnd * current_hwnd,unsigned short x,unsigned short y);

#endif /* __SERVER_H__ */
