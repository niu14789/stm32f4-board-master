/*
 * button.h
 *
 *  Created on: 2016��5��11��
 *      Author: Administrator
 */

#ifndef __BUTTON_H__
#define __BUTTON_H__


window_hwnd * button_create(window_hwnd * hwnd,struct gui_msg_t*p_msg,int (*callback)(enum event_type,void *data));

/*                 */

int button_onfocus(struct gui_msg_t*p_msg);
int button_losefocus(struct gui_msg_t*p_msg);
int button_show(struct gui_handler * g_hmd);

#endif /* __BUTTON_H__ */
