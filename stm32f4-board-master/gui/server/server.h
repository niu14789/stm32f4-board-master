/*
 * server.h
 *
 *  Created on: 2016��5��15��
 *      Author: Administrator
 */

#ifndef __SERVER_H__
#define __SERVER_H__

int gui_event_done(gui_msg *p_msg,enum event_type event);
int gui_server(void);
int gui_enevt_check(void);

#endif /* __SERVER_H__ */
