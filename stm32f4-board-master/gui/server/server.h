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
int gui_revert_widget(struct gui_handler * p_gui_root,struct gui_handler * p_gui_same);

#endif /* __SERVER_H__ */
