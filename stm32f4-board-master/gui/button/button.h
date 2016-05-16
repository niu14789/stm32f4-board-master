/*
 * button.h
 *
 *  Created on: 2016��5��11��
 *      Author: Administrator
 */

#ifndef __BUTTON_H__
#define __BUTTON_H__


int button_create(struct gui_msg_t*p_msg,int (*callback)(enum event_type,void *data));


#endif /* __BUTTON_H__ */
