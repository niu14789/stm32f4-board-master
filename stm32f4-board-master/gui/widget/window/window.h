/*
 * window.h
 *
 *  Created on: 2016年5月26日
 *      Author: YJ-User17
 */

#ifndef GUI_WINDOW_WINDOW_H_
#define GUI_WINDOW_WINDOW_H_


struct gui_handler * window_create(struct gui_msg_t*p_msg,int (*callback)(enum event_type,void *data));


#endif /* GUI_WINDOW_WINDOW_H_ */
